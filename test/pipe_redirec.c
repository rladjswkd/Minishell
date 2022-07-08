#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

/*
- 각 케이스별로 핵심적으로 필요한것은 무엇인가?
    - 왼쪽에서 오른쪽으로 가는 경우
        - STDOUT -> fd[WRITE_END]
        - STDIN -> fd[READ_END]
    - fork 뜨기 전에 pipe를 생성해야한다.
        - 파이프를 생성해야하는지 확인한다.
            - 파싱결과에 파이프가 있는가?
        - 파이프 생성과  fork만 병렬적으로 되도록 해준다.
            - 실행의 경우 왼쪽에서 오른쪽으로 흐른다. 
- pipe 1개만 생성
    - pipe(fd)
    - first child fork()
        - STDOUT -> fd[WRITE_END]
    - second child fork()
        - fd[READ_END] -> STDIN
- pipe 2개 생성
    - pipe(fd)
    - first child fork()
        - STDOUT -> fd[WRITE_END]
    - second child fork()
        - fd[READ_END] -> STDIN
*/
int main(int argc, char **argv)
{
    printf();
    return (0);
}