#include <signal.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include <stdlib.h>
#include <termios.h>

void handler(int signum)
{
    if (signum != SIGINT)
        return;
	printf("^C\n");
    rl_on_new_line();
    rl_replace_line("", 1);
    rl_redisplay();
}

void	set_signal()
{
	signal(SIGINT, handler);    // CTRL + C
	// signal(SIGQUIT, SOG);
}

/*

		{
			// printf("\033[1A");
			// printf("\033[10C");
			printf("exit\n");
			exit(-1);
		}
*/
int	main(int argc, char **argv, char **envp)
{
	char			*str;
	struct	termios	term;

	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~(ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
	set_signal();
	while (1)
	{
		str = readline("pepsi zero> ");
		if (str == NULL)
		{
			printf("exit\n");
			break ;
		}
		else if (*str == '\0')
			free(str);
		else
		{
			add_history(str);
			printf("%s\n", str);
			free(str);
			str = NULL;
		}
	}
	return (0);
}
