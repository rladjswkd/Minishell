To handle

- init pipe
- process1 fork
- get_next_line
	- HEREDOC입력을 받는다.
	- STDIN으로 넘어오는 값을 개행단위로 입력받아서 저장한다.
		- 자료구조에 저장한뒤 마지막에 임시파일을 쓰거나
		- 처음부터 임시파일에 저장한다.
- tmp file
	- check
	- tmp file open
- HEREDOC str wrte to tmp file
	- 이전 here doc 입력값이 덮여쓰이지는 않는지 확인필요
		- 덮여쓰여지지 않는다.
- write tmp file data to STDIN
- connect pipe
	- process1 pipe[WRITE_END] to STDOUT
	- process2 pipe[READ_END] to STDIN
- execute cmd
	- 만약 없는 cmd라면 exit(127);

- fd를 heredoc 용 fd linked list로 만들었다.
- parsing 이후 execution 이전에 heredoc은 따로 처리해서 linked list로 만들어준다.
	- heredoc을 redirection에서 

- free_node확인 필요
	- done

parse list
- parse한것을 다 읽어서 redirs에서 heredoc을 찾는다.
  찾으면 그때마다 입력을 받아서 linked list에 fd로 넣는다.
- main에서 heredoc_fd_list 포인터를 받아와서 heredoc에 대한 입력을 받는다.
- heredoc_fd_list를 execute_processing에 parameter로 넘겨준다.
	- redir할때 heredoc이면 한개씩 꺼내서 dup2으로 연결한다.
	- heredoc_fd_list에서 꺼낸 fd의 node는 제거한다.
	  시작노드에서 다음 노드를 가리키게 변경한다.
	  더 이상 가리킬것이 없어졌을때 heredoc_fd_list를 free할 필요없다.
	  이유는 heredoc_fd_list를 포인터없이 선언할것이므로.