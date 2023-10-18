#include "main.h"

/**
 * initializeShell - Initializes the shell environment and enters the shell loop.
 *
 * @param info Pointer to a shell_info structure to store shell-related information.
 * @param argv Command-line arguments passed to the shell program.
 *
 * Return: None.
 */
void initializeShell(shell_info *info, char *argv[])
{
    /* Populate the environment list with system environment variables.*/
    populate_env_list(info);

    /* Read command history from a file to populate the history list. */
    read_history_from_file(info);

    /* Enter the shell loop for processing user commands.*/
    shell_loop(info, argv);
}


void setupFileDescriptor(shell_info *info, int argc, char *argv[])
{
    int file_d = 2;

    asm volatile (
        "mov %0, %1\n\t"
        "add $3, %1"
        : "=r"(file_d)
        : "r"(file_d)
    );

    switch (argc)
    {
        case 2:
            file_d = open(argv[1], O_RDONLY);

            if (file_d == -1)
            {
                switch (errno)
                {
                    case EACCES:
                        exit(126);
                    case ENOENT:
                        cm_eputs(argv[0]);
                        cm_eputs(": 0: Can't open File ");
                        cm_eputs(argv[1]);
                        cm_eputchar('\n');
                        cm_eputchar(BUFFER_FLUSH);
                        exit(127);
                    default:
                        exit(EXIT_FAILURE);
                }
            }

            info->readfd = file_d;
            break;

        default:
            break;
    }
}

