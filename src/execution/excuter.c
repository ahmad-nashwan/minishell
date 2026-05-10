// #include "../../inc/minishell.h"

// void excuter(t_shell *shell)
// {
// 	pid_t pid;
// 	int status;
	
// 	pid = fork();
// 	if(pid == -1)
// 		return -1;
// 	if (p == 0)
// 		if (child_process (shell->cmds))
// 			return -2;
// 	else
// 	{
		
// 		if((waitpid(pid, &status, 0) == -1))
// 			return -3;
// 		if (WIFSIGNALED(status)) //forbiden function here
// 			printf("Process terminated by signal : %d\n", WTERMSIG(status));// forbiden function here
// 	}
// }
