# pipe, rediction module

- parameter만 넘겨줘서 redirection하게 한다.
- multipipe 역시 처리하게한다.
	- cat | cat ||||| cat
	- 현재 명령어 프로세스에서 다음 파이프가 있는지 확인한다.
		- 있다면 STDOUT을 파이프에 fd[WRITE_END]로 연결
		- 없다면 STDOUT으로 반환
			- outfile이 있다면 redirection
			  이 또한 redirection이므로 해당 함수를 가져와서 처리한다.
			  fd를 반환한다.

- 명령어에 맞는 위치가 있는가?

