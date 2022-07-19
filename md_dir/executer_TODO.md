# executer TODO

- execute structure
	- 과정 서술
		- heredoc 입력처리
			- heredoc 입력받은 것 제거는 마지막에 일괄적으로 close한다.
			- 사용하고 안쓸때 바로 제거한다.
		- 값이 들어왔을때
			- 어떻게 값이 들어오고
			- 어떻게 값이 처리되는가
			- 해당 과정을 시뮬레이션 해본다.
	- 필요사항 명세
		- 구조체 멤버변수
			- 명령어 블럭 아래
			- args redirs
				- args
					- cmd, argv(s) 
	
	- pipe, redirec 필요 멤버변수 확정
		- pipe 있는지는 어떻게 판단할 것인가?
			- pipe 개수를 count한다.
			- 현재 확인 중인 pipe index를 확인한다.
	- 재귀로 돌면서 확인하는 것은 어떻게할 것인가?
		- 해당 과정을 시뮬레이션 해본다.
			- 짧은 케이스부터 긴 것으로 넘어가본다.
	- 핵심 과정은 무엇인가?
		- group, pipe먼저 실행되며
		단말로 내려가면 scmd가 실행된다.
		해당 실행결과가 True이면 이후 과정도 마져 진행되며
		그렇지않으면 진행을 멈춘다.
	- 모든 할당된 것들은 execute이후에 전부 제거하는 과정을 거친다.
	- exit status 처리
		execute를 진행하는 핵심함수로 값을 return하여 exit status를 업데이트한다.
	- env singleton

- builtin 자료구조변경
	- double array list -> libft style linked list


- 핵심은 무엇인가?
	- execute 구조를 확정해야한다.
	- 그 과정속에서 시뮬레이션이 필요하다.
		- input값에 대한 명확한 확정
		- output값에 대한 예상

- 쉽게 해볼수 있는것
	- execve() readline에서 처리
	- redirection 처리
	- pipe 처리
	- builtin처리
	- heredoc 처리
	- exit status
	- refer code들 참고 및 이해
		- 직접 따라치면서 이해해본다.
		- 어떤식으로 재귀를 돌렸는가?
		- 공통되는 사항은 무엇인가?
		- group 과 pipe
			- 왼쪽에서 오른쪽으로 진행되어야하지만
			- group일떄 진행 순서가 달라질 수 있다.
				그러한 케이스는 어떻게 되는가?



