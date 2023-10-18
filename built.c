#include "main.h"


/**
 * _myexit - Handles the 'exit' command, allowing the shell to exit.
 * @info: Pointer to the information struct, contains arguments and status.
 *
 * Returns:
 *   -2 to signal the shell to exit with the specified exit status.
 *   Sets info->err_num to the exit status if provided.
 *   Sets info->status to 2 if an illegal number is provided.
 *   Returns 1 if an error occurs during exit handling.
 */
int _myexit(shell_info *info)
{
	int exit_status;
	
	/* Check if there is an argument for the exit command */
    if (info->argv[1])
    {
        /* Convert the argument to an integer (exit status) */
        exit_status = str_to_int(info->argv[1]);

        /* Handle illegal number case */
        if (exit_status == -1)
        {
            info->status = 2; /** < Set status to indicate illegal number */
            print_error(info, "Illegal number: ");
            cm_eputs(info->argv[1]); /** < Print the illegal number */
            cm_eputchar('\n'); /** < Print newline character */
            return 1; /** < Return 1 to indicate error */
        }

        info->error_num = exit_status; /** < Set exit status to the provided number */
        return -2; /** < Signal the shell to exit with the specified status */
    }

    info->error_num = -1; /** < No exit status provided, set default error number */
    return -2; /** < Signal the shell to exit with the default status */
}


/**
 * _myhelp - Displays help information about the shell's built-in commands.
 * @info: Pointer to the information struct, may contain additional arguments.
 *
 *
 * Returns:
 *   Always returns 0 to indicate successful execution.
 */
int _myhelp(shell_info *info)
{
    char **arguments; /** < Pointer to the array of arguments */

    arguments = info->argv; /** < Store the argument array */

    cm_puts("help call works. Function not yet implemented \n"); /** < Print help message */

    if (0) /** < Temporary workaround to avoid unused variable warning */
        cm_puts(*arguments); /** < Print a specific argument (temporarily unused) */

    return 0; /** < Return 0 to indicate successful execution */
}


/**
 * _mycd - Changes the current working directory of the shell process.
 * @info: Pointer to the information struct containing arguments and environment.
 *
 * This function changes the current working directory of the shell process based on
 * the provided arguments. Handles different cases such as no argument (change to HOME),
 * "-" (change to previous directory), or a specific path.
 *
 * Returns:
 *   0 on successful directory change, 1 on failure.
 */
int _mycd(shell_info *info)
{
    char *current_dir, *target_dir, buffer[1024];
    int chdir_result;

    current_dir = getcwd(buffer, 1024); /* Get the current working directory */

    if (!current_dir)
        cm_puts("TODO: >>getcwd failure message here<<\n"); /* Handle getcwd failure */

    /* Handle different cases based on the number of arguments provided */
    if (!info->argv[1]) /* No argument, change to HOME directory */
    {
        target_dir = _getenv(info, "HOME=");
        if (!target_dir)
            target_dir = _getenv(info, "PWD=");
    }
    else if (cm_strcmp(info->argv[1], "-") == 0) /* Argument is "-", change to previous directory */
    {
        target_dir = _getenv(info, "OLDPWD=");
        if (!target_dir)
        {
            cm_puts(current_dir); /* Print current directory */
            cm_putchar('\n');
            return (1); /* Return 1 to indicate failure */
        }
    }
    else /* Argument is a specific path, change to that directory */
    {
        target_dir = info->argv[1];
    }

    chdir_result = chdir(target_dir); /* Attempt to change directory */

    if (chdir_result == -1) /* Handle chdir failure */
    {
        print_error(info, "can't cd to ");
        cm_eputs(target_dir);
        cm_eputchar('\n');
        return (1); /* Return 1 to indicate failure */
    }

    /* Update the environment variables PWD and OLDPWD */
    _setenv(info, "OLDPWD", current_dir);
    _setenv(info, "PWD", getcwd(buffer, 1024));

    return (0); /* Return 0 to indicate successful directory change */
}


/**
 * _myhistory - Displays the command history of the shell.
 * @info: Pointer to the information struct containing command history.
 *
 * This function prints the command history stored in the `info->history` linked list.
 *
 * Returns:
 *   0 on successful display of history.
 */
int _myhistory(shell_info *info)
{
    print_lnkdlist(info->history); /* Print the command history */
    return (0); /* Return 0 to indicate successful execution */
}


/**
 * unset_alias - Unsets an alias from the alias list.
 * @info: Pointer to the information struct containing alias list.
 * @alias_name: Name of the alias to be unset.
 *
 * This function removes the specified alias from the alias list in the `info` struct.
 *
 * Returns:
 *   0 on successful unset of the alias.
 *   1 if the specified alias was not found.
 */
int unset_alias(shell_info *info, char *alias_name)
{
    char *equals_sign_ptr, temp_char;
    int unset_result;

    equals_sign_ptr = cm_strchr(alias_name, '=');

    /* If there is no '=' sign, the input is not a valid alias format */
    if (!equals_sign_ptr) {
        return 1; /* Return 1 to indicate failure (invalid alias format) */
    }

    /* Temporarily replace '=' with null terminator to extract alias name */
    temp_char = *equals_sign_ptr;
    *equals_sign_ptr = '\0';

    /* Delete the alias node from the alias list */
    unset_result = delete_nodeint_at_index(&(info->aliases),
                                        get_node_index(info->aliases, ln_startsWith(info->aliases, alias_name, -1)));

    /* Restore the original character at the '=' sign */
    *equals_sign_ptr = temp_char;

    return (unset_result); /* Return unset result: 0 for success, 1 for failure (alias not found) */
}

