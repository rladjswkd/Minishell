
#ifndef LEXER_H
# define LEXER_H
# define CHAR_SPACE	' '
# define CHAR_TAB	'\t'
# define CHAR_LREDIR	'<'
# define CHAR_RREDIR	'>'
# define CHAR_SQUOTE	'\''
# define CHAR_DQUOTE	'\"'
# define CHAR_VERBAR	'|'
# define CHAR_LBRACKET	'('
# define CHAR_RBRACKET	')'
# define CHAR_AMPERSAND	'&'

# include "linked_list.h"

typedef struct s_token
{
	int		types;
	char	*data;
	int		heredoc_fd;
}			t_token;

typedef struct s_simple
{
	t_list	*args;
	t_list	*redirs;
	int		type;
}			t_simple;

typedef struct s_compound
{
	t_list	*list;
	t_list	*padding;
	int		type;
}			t_compound;

typedef struct s_command
{
	t_list	*l1;
	t_list	*l2;
	int		type;
}			t_command;

typedef enum e_token_flag
{
	TOKEN_NORMAL = 1,
	TOKEN_REDIR = 2,
	TOKEN_HEREDOC = 4,
	TOKEN_REDIRARG = 8,
	TOKEN_SQUOTE = 16,
	TOKEN_DQUOTE = 32,
	TOKEN_CONCAT = 64,
	TOKEN_PIPE = 128,
	TOKEN_LBRACKET = 256,
	TOKEN_RBRACKET = 512,
	TOKEN_LOGICAL = 1024,
	TOKEN_WILDCARD = 2048,
	TOKEN_IGNORE = 4096
}	t_token_flag;

typedef enum e_command_type
{
	SIMPLE_NORMAL = 1,
	SIMPLE_PIPE = 2,
	SIMPLE_LBRACKET = 4,
	SIMPLE_RBRACKET = 8,
	SIMPLE_AND = 16,
	SIMPLE_OR = 32,
	COMPOUND_PIPELINE = 64,
	COMPOUND_SUBSHELL = 128
}	t_command_type;

int			lexer(char *input, t_list *token_header);
void		print_token_content(t_list *token_list, char *tab);
int			parser(t_list *token_list, t_list *parsed_header);

int			create_token(t_list **token_list, char *str, int len, int types);

int			get_simple_type(t_list *parsed);
t_simple	*get_simple(t_list *parsed);
int			get_compound_type(t_list *parsed);
t_compound	*get_compound(t_list *parsed);
int			get_command_type(t_list *parsed);
t_command	*get_command(t_list *parsed);

t_token		*get_token(t_list *token_list);

#endif

/*
(lldb) p get_compound(compound_pipe_list)->list
(t_list *) $6 = 0x00005555555781c0
(lldb) p get_command(get_compound(compound_pipe_list)->list)
(t_command *) $7 = 0x00005555555781e0
(lldb) p get_command(get_compound(compound_pipe_list)->list)->type
(int) $8 = 1

(lldb) p get_compound(compound_pipe_list)->list
(t_list *) $34 = 0x0000555555596310
(lldb) p get_compound(get_compound(compound_pipe_list)->list)
(t_compound *) $35 = 0x0000555555596410
(lldb) p get_compound(get_compound(compound_pipe_list)->list)->type
(int) $36 = 128
(lldb) p get_compound(get_compound(get_compound(compound_pipe_list)->list)->list)->type
(int) $37 = 64
(lldb) p get_compound(get_compound(get_compound(get_compound(compound_pipe_list)->list)->list)->list)->type
(int) $38 = 1
(lldb) p get_compound(get_compound(get_compound(get_compound(get_compound(compound_pipe_list)->list)->list)->list)->list)->type
(int) $39 = 0
(lldb) p get_compound(get_compound(get_compound(get_compound(compound_pipe_list)->list)->list)->list)
(t_compound *) $40 = 0x0000555555595ef0
(lldb) p get_compound(get_compound(get_compound(get_compound(compound_pipe_list)->list)->list)->list)->types
error: <user expression 59>:1:95: no member named 'types' in 's_compound'
get_compound(get_compound(get_compound(get_compound(compound_pipe_list)->list)->list)->list)->types
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~  ^
(lldb) p get_compound(get_compound(get_compound(get_compound(compound_pipe_list)->list)->list)->list)->type




(echo a | cat) | cat | ls -al || cat a

(echo a | cat) | cat | ls -al


(lldb) p get_token(get_compound(get_compound(compound_pipe_list)->list->next)->list)
(t_token *) $46 = 0x0000555555578320
(lldb) p get_token(get_compound(get_compound(compound_pipe_list)->list->next)->list)->data
(char *) $47 = 0x0000555555578340 "cat"
(lldb) p get_token(get_compound(get_compound(compound_pipe_list)->list->next->next)->list)->data
(char *) $48 = 0x0000555555594cb0 "ls"
(lldb) p get_token(get_compound(get_compound(compound_pipe_list)->list->next->next->next)->list)->data
error: Execution was interrupted, reason: signal SIGSEGV: invalid address (fault address: 0x0).
The process has been returned to the state before expression evaluation.
(lldb) p get_token(get_compound(get_compound(compound_pipe_list)->list->next->next)->list)->data
(char *) $49 = 0x0000555555594cb0 "ls"
(lldb) p get_token(get_compound(get_compound(compound_pipe_list)->list->next->next)->list->next)->data
(char *) $50 = 0x0000555555594d10 "-al"
(lldb) 



 p get_command(get_compound(parse_list)->list)->type
*/