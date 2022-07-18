- readline()으로 입력받는다.
- lexer, parser를 거쳐서 전처리된다.

- pipe럭의 STDOUT이 오른쪽 블럭의 STDIN으로 처리된다.
        어떻게 일반화할 것인가?
    - dup으로 pipe를 저장해야한다.

블럭이 2개만 있을때는 파이프 1개를 놓아서 연결한다.
블럭이 3개면 파이프 2개가 필요하다.
파이프를 만들고 이후에 fork를 떠서 다음과 연결한다.
구조체에 pipe_read fd를 담을 변수와 write를 담을 변수를 생성한다.
// echo a > outfile | cat
read = dup()
write =

{
    int fd[2];

    if (pipe(fd) < 0)
        return (1);
    pid1 = fork();
    if (pid1 < 0)
        return (1);
    else if (pid1 == 0)
    {
        close(fd[0]);
        dup2(fd[1], STDOUT_FILENO)
    }
    close(fd[1]);
}