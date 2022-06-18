# 입력 라인 모듈화
- 어떻게 모듈화 할것인가?
- 가장 작은 동작단위로 나눈다.
- 나누기 위해 큰 동작부터 파악한다.
- 공통되는 부분을 나누고(구조가 공통되는 것)
	- 일부 값만 바뀌는 것은 parameter나 함수형 포인터를 이용한다.


- 큰 동작은 무엇인가?
process | cat > file1 | process 형태로 나뉘어진다.

- process는 어떻게 구성되는가
	token으로 구성된다.
	- cmd, file, redirection, input value, option 로 구성된다.
	- 특수 기호도 고려해야한다.
		'-, ',", ~, etc
		- white list사용
		- 처리할것만하고 아닌것은 error처리
	- 우선순위(파싱단, 파스트리 순서대로 실행)
	- cmd file
- 입력값의 동작은 무엇인가?
	- cmd
	- file
	- input value
	- redirection
	- etc argument

- 명령어 블럭의 동작은 어떻게 이루어지는가
	- 명령어, 입력값, file, redirection등으로 이루어지며 그것들에 순서에 따라 달라진다.
	- 그렇다면 명령어에 따라 인자가 필요하다면 어떤 위치에 필요한가
- 동작과정에서 구조적으로 공통되는 부분
	- redirection
		- input
		- output
		- append
		- heredoc
		redirection 옵션을 받고 그에 따라 처리하게한다.
		공통점은 open함수로 fd를 받아서
		값을 read하거나
		값을 write한다.
	- cmd 처리
	- file 처리
	- input value 처리
- cmd 특징은 무엇인가
	- 인자값을 받아서 처리하거나
		echo "", exit long, sleep
	- STDIN을 받아서 처리
		cat, tail, more, head
	- file name으로 처리
		vi
	- 인자없이 처리
		ls, pwd
- redirection
	- input
	- output
	- append
	- heredoc
- input value
- file

< file1 cmd1 cmd2 file2 >
<< || < | > || >>
