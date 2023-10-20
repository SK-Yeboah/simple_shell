#include "main.h"


/**
 * shell_loop - Main loop for the shell, reads and processes user input.
 *
 * @param info Pointer to a shell_info structure containing shell-related information.
 * @param av Command-line arguments passed to the shell program.
 *
 *
 * Parameters:
 *   - info: Pointer to a shell_info structure where shell-related information
 *           will be stored and updated during the shell's execution.
 *   - av: Command-line arguments passed to the shell program, typically used
 *         for initialization purposes.
 *
 * Return: Returns the exit status or error code to the caller.
 */
int shell_loop(shell_info *info, char **av) {
    ssize_t r = 0;
    int builtin_ret = 0;

    for (; r != -1 && builtin_ret != -2;) {
        clear_info(info);
        if (is_interactive(info)) {
            cm_puts("$ ");
        }
        cm_eputchar(BUFFER_FLUSH);
        r = get_input(info);

        if (r != -1) {
            set_info(info, av);
            switch (find_builtin(info)) {
                case -1:
                    find_cmd(info);
                    break;
                case -2:
                    /* Exit the shell based on error number or status.*/
                    if (info->error_num == -1) {
                        exit(info->status);
                    }
                    exit(info->error_num);
                default:
                    break;
            }
        } else if (is_interactive(info)) {
            cm_putchar('\n');
        }

        free_info(info, 0);
    }

    /* Write command history to file and free allocated memory.*/
    write_history_to_file(info);
    free_info(info, 1);

    /* Exit the shell with the appropriate status or error code.*/
    if (!is_interactive(info) && info->status) {
        exit(info->status);
    }

    if (builtin_ret == -2) {
        /* Handle exit based on error number or status for non-interactive mode.*/
        if (info->error_num == -1) {
            exit(info->status);
        }
        exit(info->error_num);
    }

    return builtin_ret;
}


/**
 * find_builtin - finds a builtin command
 * @info: the parameter & return info struct
 *
 * Return: -1 if builtin not found,
 * 	0 if builtin executed successfully,
 * 	1 if builtin found but not successful,
 * 	2 if builtin signals exit()
 */
int find_builtin(shell_info *info)
{
	int i, built_in_ret = -1;
	builtin_table builtintbl[] = {
		{"exit", _myexit},
		{"env", _myenv},
		{"help", _myhelp},
		{"history", _myhistory},
		{"setenv", _mysetenv},
		{"unsetenv", _myunsetenv},
		{"cd", _mycd},
		{"alias", _myalias},
		{NULL, NULL}
	};

	for (i = 0; builtintbl[i].type; i++)
		if (cm_strcmp(info->argv[0], builtintbl[i].type) == 0)
		{
			info->count_line++;
			built_in_ret = builtintbl[i].func(info);
			break;
		}
	return (built_in_ret);
}

/**
 * find_cmd - finds a command in PATH
 * @info: the parameter & return info struct
 *
 * Return: void
 */
void find_cmd(shell_info *info)
{
	char *path = NULL;
	int i, k;

	info->path = info->argv[0];
	if (info->linecount_flag == 1)
	{
		info->count_line++;
		info->linecount_flag = 0;
	}
	for (i = 0, k = 0; info->arg[i]; i++)
		if (!is_delim(info->arg[i], " \t\n"))
			k++;
	if (!k)
		return;

	path = find_path(info, _getenv(info, "PATH="), info->argv[0]);
	if (path)
	{
		info->path = path;
		fork_cmd(info);
	}
	else
	{
		if ((is_interactive(info) || _getenv(info, "PATH=")
					|| info->argv[0][0] == '/') && is_cmd(info, info->argv[0]))
			fork_cmd(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			print_error(info, "not found\n");
		}
	}
}

/**
 * fork_cmd - forks a an exec thread to run cmd
 * @info: the parameter & return info struct
 *
 * Return: void
 */
void fork_cmd(shell_info *info)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		/* TODO: PUT ERROR FUNCTION */
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(info->path, info->argv, get_environ(info)) == -1)
		{
			free_info(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
		/* TODO: PUT ERROR FUNCTION */
	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				print_error(info, "Permission denied\n");
		}
	}
}

