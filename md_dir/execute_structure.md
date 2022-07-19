# execute structure

- execute structure
	- heredoc
	- expansion
	- wild card
	- cmd type별 처리
		- 구조별로 달라질 수 있는 부분은 무엇인가?
		- group
		- pipeline
			- pipeline에서 scmd를 처리해야할때는?
				왜 다시 scmd도 돌리지 않고 pipeline 안에서 처리해야하는가?
		- scmd
- after processing
	- free the list

# execute action
- after heredoc proceess

- simple cmd
	- ㄷㅌ
	- redirection
	- builtin
- pipe

- and_or(group)

---------------------

# executer structer
- 어떤 동작이 필요한가?
- 무엇이 목적인가?
- 왜 해야하는가?

## 동작 명세
- 파싱된 결과를 각 조건에 맞게 실행해야한다.
    - 파싱된 결과는 어떠한가?
        - l_cmd라는 리스트로 구성된다.
            - l_cmd는 l_args, l_redir 리스트로 구성된다.
            - l_cmd의 구분 기준은 연산자이다.
                연산자는 meta character를 포함한다.
                blank, pipe, and or operation
                < << >> > 도 포함되지만 그 부분들은 redir으로 뺀다.

    - 각 조건이란 무엇을 의미하는가?
        - group이 먼저 실행된다.
        - pipe도 실행된다.
        - subshell도 실행되지만
            subshell과 pipe가 겹치면 fork는 한번만 된다.
            기준은 무엇인가
        - group이 먼저 실행되는게 맞는가? pipe는 어떠한가?
        - 명령어와 그 인자들은 
        

- exit status