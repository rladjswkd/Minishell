
#include <stdlib.h>

/*
 * exit status는 무엇인가?
 * shell에서 exit 42에서 넘어오는 값을 의미하는가?
 * exit == exit 0 wsl(ubuntu)에서는 바로 종료된다.
 * exit 1이나 다른 값은 정상처리된다.
 * exit character, string의 경우 error 문구발생
 * builtin별로 인자에 대한 처리가 나뉘므로 그에 따른 예외처리 추가적으로 필요
 */
void    exit_cmd(int status)
{
    exit(status);
}