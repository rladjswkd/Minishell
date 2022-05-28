#include <unistd.h>
#include <stddef.h>

/*
 * change directory
 * chdir 명령어의 return 값이 int이므로 성공시에는 0이라서
 * 언제나 chdir의 반환값을 전달하기로 결정
 * 해당값에 대한 strerror처리 필요
 */
int change_directory_cmd(const char *path)
{
    int ret;

    ret = chdir(path);
    if (ret != 0)
        return (ret);
    return (ret);
}