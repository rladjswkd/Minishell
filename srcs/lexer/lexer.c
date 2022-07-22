#include "lexer.h"
#include <stdlib.h>
#include <stdio.h> // remove
#include <string.h> // strerror
#include <errno.h> // errno codes
#include <readline/readline.h>
#include <readline/history.h>
void	free_compound(t_list *);
void	free_command(t_list *);
void	print_token_content(t_list *, char *); //remove
void	print_simple_content(t_list *, char *); //remove
void	print_compound_content(t_list *); // remove
void	print_command_content(t_list *); // remove

int	malloc_wrapper(size_t size, void **ptr)
{
	size_t	 i;
	char	*cptr;

	*ptr = malloc(size);
	if (!(*ptr))
		return (0);
	i = 0;
	cptr = (char *)(*ptr);
	while (i < size)
		cptr[i++] = 0;
	return (1);
}

int	is_delimiter(char *s)
{
	char	c;

	c = *s;
	return (c == CHAR_LREDIR || c == CHAR_RREDIR || c == CHAR_VERBAR
		|| c == CHAR_LBRACKET || c == CHAR_RBRACKET
		|| c == CHAR_SPACE || c == CHAR_TAB
		|| (c == CHAR_AMPERSAND && *(s + 1) == CHAR_AMPERSAND));
}

int	is_quote(char c)
{
	return (c == CHAR_SQUOTE || c == CHAR_DQUOTE);
}

int	extract_normal(char *str, int *types)
{
	int	len;

	*types = TOKEN_NORMAL;
	len = 0;
	while (str[len] && !(is_delimiter(&(str[len])) || is_quote(str[len])))
		len++;
	if (is_quote(str[len]))
		*types |= TOKEN_CONCAT;
	return (len);
}

int	extract_redir(char *str, int *types)
{
	*types = TOKEN_REDIR;
	if (*str != *(str + 1))
		return (1);
	if (*str == CHAR_LREDIR)
		*types |= TOKEN_HEREDOC;
	return (2);
}

int	extract_quote(char *str, int *types)
{
	char	quote;
	int		len;

	quote = *str;
	len = 1;
	*types = TOKEN_NORMAL | TOKEN_DQUOTE;
	if (quote == CHAR_SQUOTE)
		*types = TOKEN_NORMAL | TOKEN_SQUOTE;
	while (*(++str) && *str != quote)
		len++;
	if (!(*str))
		return (-1);
	if (str[len] && !is_delimiter(&(str[len])))
		*types |= TOKEN_CONCAT;
	return (len + 1);
}

int	extract_bracket(char *str, int *types)
{
	*types = TOKEN_LBRACKET;
	if (*str == CHAR_RBRACKET)
		*types = TOKEN_RBRACKET;
	return (1);
}

int	extract_logical_pipe(char *str, int *types)
{
	if (*str == CHAR_VERBAR && *(str + 1) != CHAR_VERBAR)
	{
		*types = TOKEN_PIPE;
		return (1);
	}
	*types = TOKEN_LOGICAL;
	return (2);
}

int	ignore_blank(char *str, int *types)
{
	int	len;

	*types = TOKEN_IGNORE;
	len = 0;
	while (str[len] == CHAR_SPACE || str[len] == CHAR_TAB)
		len++;
	return (len);
}

t_token	*get_token(t_list *token_list)
{
	return ((t_token *)(token_list->node));
}

int	get_token_type(t_list *token_list)
{
	return (((t_token *)(token_list->node))->types);
}

int	get_index(char c1, char c2)
{
	return ((c1 == CHAR_LREDIR || c1 == CHAR_RREDIR) * 1
		| (c1 == CHAR_SQUOTE || c1 == CHAR_DQUOTE) * 2
		| (c1 == CHAR_LBRACKET || c1 == CHAR_RBRACKET) * 3
		| ((c1 == CHAR_AMPERSAND && c2 == CHAR_AMPERSAND)
			|| c1 == CHAR_VERBAR) * 4
		| (c1 == CHAR_SPACE || c1 == CHAR_TAB) * 5);
}

int	create_token(t_list **token_list, char *str, int len, int types)
{
	t_token	*token;

	if (types & TOKEN_IGNORE)
		return (1);
	if (len < 0)
		return (0);
	if (!malloc_wrapper(sizeof(t_list), (void **)token_list))
		return (0);
	if (!malloc_wrapper(sizeof(t_token), (void **)&(*token_list)->node))
		return (0);
	len -= (!!(types & (TOKEN_SQUOTE | TOKEN_DQUOTE))) << 1;
	str += !!(types & (TOKEN_SQUOTE | TOKEN_DQUOTE));
	token = get_token(*token_list);
	if (!malloc_wrapper(len + 1, (void **)&(token->data)))
		return (0);
	while (len--)
		(token->data)[len] = str[len];
	token->types = types;
	return (1);
}
/*
int	create_token(t_list **token_list, char *str, int len, int types)
{
	if (types & TOKEN_IGNORE)
		return (1);
	if (len < 0)
		return (0);
	*token_list = (t_list *)malloc(sizeof(t_list));
	if (!(*token_list))
		return (0);
	(*token_list)->node = (t_token *)malloc(sizeof(t_token));
	if (!get_token(*token_list))
		return (0);
	len -= (!!(types & (TOKEN_SQUOTE | TOKEN_DQUOTE))) << 1;
	str += !!(types & (TOKEN_SQUOTE | TOKEN_DQUOTE));
	get_token(*token_list)->data = (char *)malloc(sizeof(len + 1));
	if (!(get_token(*token_list)->data))
		return (0);
	(get_token(*token_list)->data)[len] = 0;
	while (len--)
		(get_token(*token_list)->data)[len] = str[len];
	get_token(*token_list)->types = types;
	return (1);
}
*/
int	tokenize_input(char *str, t_list *token_header)
{
	int			len;
	int			types;
	t_list		*cur;
	static int	(*len_fp[6])(char *, int *) = {
		&extract_normal, &extract_redir,
		&extract_quote,	&extract_bracket,
		&extract_logical_pipe, &ignore_blank
	};

	while (*str)
	{	
		len = (len_fp[get_index(*str, *(str + 1))])(str, &types);
		if (!create_token(&cur, str, len, types))
			return (0);
		if (!(types & TOKEN_IGNORE))
		{
			token_header->next = cur;
			token_header = token_header->next;
		}
		types = 0;
		str += len;
	}
	token_header->next = 0;
	return (1);
}

int	is_redir_error(int curr, int next)
{
	return (curr & TOKEN_REDIR && !(next & TOKEN_NORMAL));
}

int	is_pipe_logical_error(int curr, int next)
{
	return (curr & (TOKEN_PIPE | TOKEN_LOGICAL)
		&& !(next & (TOKEN_NORMAL | TOKEN_REDIR | TOKEN_LBRACKET)));
}

int	is_bracket_error(int curr, int next)
{
	int	lmask;
	int	rmask;

	lmask = TOKEN_NORMAL | TOKEN_REDIR | TOKEN_LBRACKET;
	rmask = TOKEN_PIPE | TOKEN_LOGICAL | TOKEN_RBRACKET;
	return ((curr & TOKEN_LBRACKET && !(next & lmask))
		|| (curr & TOKEN_RBRACKET && next && !(next & rmask)));
}

int	is_normal_error(int curr, int next)
{
	return (curr & TOKEN_NORMAL && next && next & TOKEN_LBRACKET);
}

int	is_error(int curr, int next, int *pair)
{
	*pair += curr == TOKEN_LBRACKET;
	*pair -= curr == TOKEN_RBRACKET;
	return (*pair < 0 || is_redir_error(curr, next)
			|| is_normal_error(curr, next)
			|| is_pipe_logical_error(curr, next)
			|| is_bracket_error(curr, next));
}

int	check_syntax(t_list *token_list)
{
	int		type;
	int		next;
	int		pair;
	t_list	*cur;

	if (get_token_type(token_list)
		& (TOKEN_PIPE | TOKEN_LOGICAL | TOKEN_RBRACKET))
		return (0);
	pair = 0;
	cur = token_list;
	while (cur)
	{
		type = get_token_type(cur);
		next = 0;
		if (cur->next)
			next = get_token_type(cur->next);
		if (is_error(type, next, &pair))
			return (0);
		cur = cur->next;
	}
	return (pair == 0);
}


void	mask_redirarg_type(t_list *token_list)
{
	while (token_list)
	{
		if (get_token_type(token_list) & TOKEN_REDIR)
		{
			token_list = token_list->next;
			get_token(token_list)->types |= TOKEN_REDIRARG;
			while (get_token_type(token_list) & TOKEN_CONCAT)
			{
				token_list = token_list->next;
				get_token(token_list)->types |= TOKEN_REDIRARG;
			}
		}
		token_list = token_list->next;
	}
}

int	get_simple_type(t_list *parsed)
{
	return (((t_simple *)(parsed->node))->type);
}

t_simple	*get_simple(t_list *parsed)
{
	return ((t_simple *)(parsed->node));
}

int	get_compound_type(t_list *parsed)
{
	return (((t_compound *)(parsed->node))->type);
}

t_compound	*get_compound(t_list *parsed)
{
	return ((t_compound *)(parsed->node));
}

int	get_command_type(t_list *parsed)
{
	return (((t_command *)(parsed->node))->type);
}

t_command	*get_command(t_list *parsed)
{
	return ((t_command *)(parsed->node));
}
/*
int	create_command(t_list **neu, int type)
{
	*neu = (t_list *)malloc(sizeof(t_list));
	if (!(*neu))
		return (0);
	(*neu)->node = (t_command *)malloc(sizeof(t_command));
	if (!((*neu)->node))
		return (0);
	get_command(*neu)->type = type;
	return (1);
}
*/
int	create_command(t_list **neu, int type)
{
	if (!malloc_wrapper(sizeof(t_list), (void **)neu))
		return (0);
	if (!malloc_wrapper(sizeof(t_command), (void **)(&(*neu)->node)))
		return (0);
	get_command(*neu)->type = type;
	return (1);
}

int	find_simple_type(t_list *token_list)
{
	int	type;
	
	if (!token_list)
		return (0);
	type = get_token_type(token_list);
	if (type & (TOKEN_NORMAL | TOKEN_REDIR))
		return (SIMPLE_NORMAL);
	else if (type & TOKEN_PIPE)
		return (SIMPLE_PIPE);
	else if (type & TOKEN_LBRACKET)
		return (SIMPLE_LBRACKET);
	else if (type & TOKEN_RBRACKET)
		return (SIMPLE_RBRACKET);
	else if (type & TOKEN_LOGICAL)
	{
		if ((get_token(token_list)->data)[0] == CHAR_AMPERSAND)
			return (SIMPLE_AND);
		return (SIMPLE_OR);
	}
	return (0);
}

void	append_token(t_list **simple, t_list *token)
{
	t_list	*current;

	if (!(*simple))
	{
		*simple = token;
		return ;
	}
	current = *simple;
	while (current->next)
		current = current->next;
	current->next = token;
}

void	parse_args_redirs(t_list *parsed, t_list **list)
{
	t_simple	*simple;
	t_list		*next;

	while (find_simple_type(*list) & SIMPLE_NORMAL)
	{
		simple = get_simple(parsed);
		next = (*list)->next;
		if (get_token_type(*list) & (TOKEN_REDIR | TOKEN_REDIRARG))
			append_token(&(simple->redirs), *list);
		else
			append_token(&(simple->args), *list);
		(*list)->next = 0;
		*list = next;
	}
}

void	free_token(t_list *token)
{
	free(get_token(token)->data);
	free(token);
}

void	free_token_list(t_list *list)
{
	t_list	*next;

	while (list)
	{
		next = list->next;
		free_token(list);
		list = next;
	}
}

void	free_simple_members(t_list *list)
{
	t_simple	*simple;

	simple = get_simple(list);
	free_token_list(simple->args);
	free_token_list(simple->redirs);
	free(list->node);
}

void	free_compound_members(t_list *list)
{
	t_compound	*compound;
	t_list		*next;

	compound = get_compound(list);
	while (compound->list)
	{
		next = compound->list->next;
		free_command(compound->list);
		free(compound->list);
		compound->list = next;
	}
}

void	free_command(t_list *list)
{
	if (get_command_type(list) & SIMPLE_NORMAL)
		free_simple_members(list);
	else
		free_compound_members(list);
	free(list);
}

int	parse_simple(t_list *token_list, t_list *header)
{
	int	type;
	t_list	*token_ptr;

	while (token_list)
	{
		type = find_simple_type(token_list);
		if (!create_command(&(header->next), type))
			return (0);
		if (type & SIMPLE_NORMAL) // SIMPLE_NORMAL을 제외한 SIMPLE 들은 TOKEN이 free된다.
			parse_args_redirs(header->next, &token_list);
		else
		{
			token_ptr = token_list;
			token_list = token_list->next;
			free_token(token_ptr);
		}
		header = header->next;
	}
	return (1);
}

int	find_lbracket(t_list *parsed, t_list *rbracket, t_list **lbracket)
{
	int		type;

	*lbracket = 0;
	while (parsed && parsed != rbracket)
	{
		type = get_simple_type(parsed);
		if (type & SIMPLE_LBRACKET)
			*lbracket = parsed;
		if (*lbracket && type & SIMPLE_PIPE)
			*lbracket = 0;
		parsed = parsed->next;
	}
	return (*lbracket != 0);
}

int	find_rbracket(t_list *parsed, t_list **rbracket)
{
	t_list	*cur;

	cur = parsed;
	*rbracket = 0;
	while (cur)
	{
		if (get_simple_type(cur) & SIMPLE_RBRACKET)
		{
			*rbracket = cur;
			return (1);
		}
		cur = cur->next;
	}
	return (0);
}

void	get_prev_command(t_list *parsed, t_list *node, t_list **prev)
{
	*prev = 0;
	if (parsed != node)
		while (parsed->next && parsed->next != node)
			parsed = parsed->next;
	*prev = parsed;
}

void	rearrange_subshell(t_list **parsed, t_list *l, t_list *r, t_list *neu)
{
	t_list	*prev_l;
	t_list	*prev_r;

	get_prev_command(*parsed, l, &prev_l);
	if (*parsed == l)
		*parsed = neu;
	else
		prev_l->next = neu;
	get_compound(neu)->list = l->next;
	prev_r = l;
	while (prev_r->next != r)
		prev_r = prev_r->next;
	prev_r->next = 0;
	l->next = 0;
	neu->next = r->next;
	r->next = 0;
	free_command(l);
	free_command(r);
}

int	process_subshell(t_list **parsed, t_list *r)
{
	t_list	*l;
	t_list	*neu;

	if (!r || !find_lbracket(*parsed, r, &l))
		return (1);
	if (get_simple_type(l->next) & COMPOUND_SUBSHELL && l->next->next == r)
		return (0); // syntax error. ((...))
	if (!create_command(&neu, COMPOUND_SUBSHELL))
		return (0);
	rearrange_subshell(parsed, l, r, neu);
	return (1);
}

int	is_included_pipeline(t_list *parsed)
{
	static int	mask = 
		SIMPLE_NORMAL | COMPOUND_SUBSHELL | COMPOUND_PIPELINE;

	return (parsed && get_command_type(parsed) & mask
		&& parsed->next	&& get_command_type(parsed->next) & SIMPLE_PIPE
		&& parsed->next->next
		&& get_command_type(parsed->next->next) & mask);
}

void	find_pipeline(t_list *parsed, t_list **start, t_list **end)
{
	*start = 0;
	*end = 0;
	while (parsed && !is_included_pipeline(parsed))
		parsed = parsed->next;
	if (!parsed)
		return ;
	*start = parsed;
	while (parsed && is_included_pipeline(parsed))
		parsed = parsed->next->next;
	if (parsed)
		*end = parsed;
}

void	add_list_back(t_list **list, t_list *neu)
{
	t_list	*temp;

	if (!(*list))
	{
		*list = neu;
		return ;
	}
	temp = *list;
	while (temp->next)
		temp = temp->next;
	temp->next = neu;
}

void	rearrange_pipeline(t_list *s, t_list *e, t_list *neu)
{
	t_list	*next;
	int		type;

	while (s != e->next)
	{
		type = get_command_type(s);
		next = s->next;
		if (type & SIMPLE_PIPE)
			free_command(s);
		else if (type & COMPOUND_PIPELINE)
		{
			add_list_back(&(get_compound(neu)->list), get_compound(s)->list);
			get_compound(s)->list = 0;
			free_command(s);
		}
		else
		{
			add_list_back(&(get_compound(neu)->list), s);
			if (s != e)
				s->next = 0;
		}
		s = next;
	}
	e->next = 0;
}

int	process_pipeline(t_list **parsed)
{
	t_list	*start;
	t_list	*end;
	t_list	*neu;
	t_list	*prev_s;
	
	find_pipeline(*parsed, &start, &end);
	if (start && end)
	{
		if (!create_command(&neu, COMPOUND_PIPELINE))
			return (0);
		get_prev_command(*parsed, start, &prev_s);
		if (*parsed == start)
			*parsed = neu;
		else
			prev_s->next = neu;
		neu->next = end->next;
		rearrange_pipeline(start, end, neu);
	}
	return (1);
}

int	find_pipe(t_list *parsed)
{
	while (parsed)
	{
		if (get_command_type(parsed) & SIMPLE_PIPE)
			return (1);
		parsed = parsed->next;
	}
	return (0);
}

int	process_compound(t_list **parsed)
{
	int		flag;
	t_list	*rbracket;

	flag = find_rbracket(*parsed, &rbracket) || find_pipe(*parsed);
	while (flag)
	{
		if (!process_subshell(parsed, rbracket)
			|| !process_pipeline(parsed))
			return (0);
		flag = find_rbracket(*parsed, &rbracket)
			|| find_pipe(*parsed);
	}
	return (1);
}

int	parser(t_list *token_list, t_list *parsed_header)
{
	if (!parse_simple(token_list, parsed_header))
		return (0);
	// print_command_content(parsed_header->next);
	if (!process_compound(&(parsed_header->next)))
		return (0);
	// print_command_content(parsed_header->next);
	return (1);
}

int	lexer(char *input, t_list *token_header)
{
	t_list	*list;

	if (!tokenize_input(input, token_header))
		return (0); // set error message using singleton
	list = token_header->next;
	if (!check_syntax(list))
		return (0); // set error message using singleton for each syntax error type
	mask_redirarg_type(token_header->next);
	return (1);
}

void	print_token_content(t_list *token_list, char *tab) //remove
{
	int	types;

	while (token_list)
	{
		types = get_token_type(token_list);
		printf("\n");
		printf("\033[0;35m%stoken content:\t%s\033[m\n", tab, ((t_token *)(token_list->node))->data);
		printf("\033[0;35m%stoken types:\033[m\t", tab);
		if (types & TOKEN_NORMAL)
			printf("\033[0;35m%s \033[m", "TOKEN_NORMAL");
		if (types & TOKEN_REDIR)
			printf("\033[0;35m%s \033[m", "TOKEN_REDIR");
		if (types & TOKEN_HEREDOC)
			printf("\033[0;35m%s \033[m", "TOKEN_HEREDOC");
		if (types & TOKEN_REDIRARG)
			printf("\033[0;35m%s \033[m", "TOKEN_REDIRARG");
		if (types & TOKEN_SQUOTE)
			printf("\033[0;35m%s \033[m", "TOKEN_SQUOTE");
		if (types & TOKEN_DQUOTE)
			printf("\033[0;35m%s \033[m", "TOKEN_DQUOTE");
		if (types & TOKEN_CONCAT)
			printf("\033[0;35m%s \033[m", "TOKEN_CONCAT");
		if (types & TOKEN_PIPE)
			printf("\033[0;35m%s \033[m", "TOKEN_PIPE");
		if (types & TOKEN_LBRACKET)
			printf("\033[0;35m%s \033[m", "TOKEN_LBRACKET");
		if (types & TOKEN_RBRACKET)
			printf("\033[0;35m%s \033[m", "TOKEN_RBRACKET");
		if (types & TOKEN_LOGICAL)
			printf("\033[0;35m%s \033[m", "TOKEN_LOGICAL");
		if (types & TOKEN_WILDCARD)
			printf("\033[0;35m%s \033[m", "TOKEN_WILDCARD");
		if (types & TOKEN_IGNORE)
			printf("\033[0;35m%s \033[m", "TOKEN_IGNORE");
		printf("\n");
		token_list = token_list->next;
	}
}

void	print_simple_content(t_list *command, char *tab)
{
	int	types;

	types = get_command_type(command);
	printf("\n");
	if (types & SIMPLE_NORMAL)
	{
		printf("%s\033[0;36m%s \033[m", tab, "SIMPLE_NORMAL");
		if (get_simple(command)->args)
		{
			printf("%s\033[0;36m\n\n\t%s\033[m\n", tab, "ARGUMENTS");
			print_token_content(get_simple(command)->args, "\t");
		}
		if (get_simple(command)->redirs)
		{
			printf("\033[0;36m\n\t%s\033[m\n", "RERIECTIONS");
			print_token_content(get_simple(command)->redirs, "\t");
		}
	}
	if (types & SIMPLE_PIPE)
		printf("%s\033[0;36m%s \033[m", tab, "SIMPLE_PIPE");
	if (types & SIMPLE_LBRACKET)
		printf("%s\033[0;36m%s \033[m", tab, "SIMPLE_LBRACKET");
	if (types & SIMPLE_RBRACKET)
		printf("%s\033[0;36m%s \033[m", tab, "SIMPLE_RBRACKET");
	if (types & SIMPLE_AND)
		printf("%s\033[0;36m%s \033[m", tab, "SIMPLE_AND");
	if (types & SIMPLE_OR)
		printf("%s\033[0;36m%s \033[m", tab, "SIMPLE_OR");
	printf("\n");
}

void	print_compound_content(t_list *command)
{
	int	types;
	t_list	*list;

	types = get_command_type(command);
	printf("\n");
	if (get_command_type(command) == COMPOUND_PIPELINE)
		printf("\033[0;31m%s \033[m\n", "COMPOUND_PIPELINE::START");
	else
		printf("\033[0;31m%s \033[m\n", "COMPOUND_SUBSHELL::START");
	list = get_compound(command)->list;
	while (list)
	{
		print_command_content(list);
		list = list->next;
	}
	printf("\033[0;31m::END \033[m\n");
}

void	print_command_content(t_list *command)
{
	while (command)
	{
		if (get_command_type(command) < COMPOUND_PIPELINE)
			print_simple_content(command, "");
		else
			print_compound_content(command);
		command = command->next;
	}
}
