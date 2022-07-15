#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>

// struct termios org_term;
struct termios new_term;

// org_term에 초기 터미널 세팅 저장
// void save_input_mode(void)
// {
// 		tcgetattr(STDIN_FILENO, &org_term); // STDIN으로부터 터미널 속성을 받아온다
// }

// new_term에 원하는 터미널 속성 설정
void set_input_mode(void)
{
		tcgetattr(STDIN_FILENO, &new_term); // STDIN으로부터 터미널 속성을 받아온다
		new_term.c_lflag &= ~(ECHOCTL);  // ICANON, ECHO 속성을 off
		// new_term.c_cc[VMIN] = 1;               // 1 바이트씩 처리
		// new_term.c_cc[VTIME] = 0;              // 시간은 설정하지 않음
		tcsetattr(STDIN_FILENO, TCSANOW, &new_term); // 변경된 속성의 터미널을 STDIN에 바로 적용
}

// 기존의 터미널 세팅으로 다시 변경
// void reset_input_mode(void)
// {
// 		tcsetattr(STDIN_FILENO, TCSANOW, &org_term);  // STDIN에 기존의 터미널 속성을 바로 적용
// }

int main(void)
{
		int 	ch = 0;
		char	*str;
		
		// save_input_mode();       // 터미널 세팅 저장
		set_input_mode();        // 터미널 세팅 변경
		while (1)
		{
			str = readline("$>");
			if (str == NULL)
			{
				printf("exit\n");
				break ;
			}
			else
				printf("%s\n", str);
				// write(0, &ch, sizeof(int));
			free(str);
			ch = 0;
		}
		// reset_input_mode();      // 터미널 세팅 초기화
		return (0);
}