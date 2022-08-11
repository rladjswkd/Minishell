
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

# include "structure_linked_list.h"

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

void		free_token_list(t_list *list);
void		free_token(t_list *list);

#endif
