#ifndef BUILTIN
# define BUILTIN

int		change_directory_cmd(const char *path);
char*	print_current_working_directory_cmd(void);
void    exit_cmd(int status);

#endif