#include <termios.h>
#include <unistd.h>
#include <stdio.h>

int main(void)
{
	char    c;
	char    s[42];
	struct termios term;
	ssize_t	len;
	
	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~ICANON;    // non-canonical input 설정
	term.c_lflag &= ~ECHO;      // 입력 시 터미널에 보이지 않게
	term.c_cc[VMIN] = 42;        // 최소 입력 버퍼 크기
	term.c_cc[VTIME] = 0;       //버퍼 비우는 시간 (timeout)
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
	len = read(STDIN_FILENO, s, sizeof(s));
	s[len] = '\0';
	while (len > 0)
	{
		printf("input: %s\n", s);
	}
}
