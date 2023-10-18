#include "main.h"

/**
 * is_cmd - Checks if a given path corresponds to a regular file.
 * @info: Information structure (unused in this context).
 * @path: Path to the file to check.
 *
 * Return: 1 if the path corresponds to a regular file, 0 otherwise.
 */
int is_cmd(shell_info *info, char *path)
{
    struct stat file_stat;

    /* Unused parameter (info) */
    (void)info;

    /* Check if path is NULL or if the stat function fails */
    if (!path || stat(path, &file_stat))
        return (0);

    /* Check if the file is a regular file */
    if (S_ISREG(file_stat.st_mode))
    {
        return 1;
    }

    return (0);
}


/**
 * dup_chars - Extracts a substring from the given string.
 * @pathstr: Input string from which to extract the substring.
 * @start: Starting index of the substring.
 * @stop: Ending index of the substring (exclusive).
 *
 * Return: Pointer to the extracted substring (or NULL on failure).
 */
char *dup_chars(char *pathstr, int start, int stop)
{
    /* Static buffer for the extracted substring*/
    static char extracted_string[1024];
    int i, k = 0;

    /* Copy characters from start index to stop index (exclusive) into the buffer*/
    for (i = start; i < stop; i++)
    {
        if (pathstr[i] != ':')
        {
            extracted_string[k++] = pathstr[i];
        }
    }

    /* Null-terminate the extracted substring */
    extracted_string[k] = '\0';

    /*Return a pointer to the extracted substring*/ 
    return (extracted_string);
}

/**
 * find_executable_in_path - Searches for an executable file in the specified path.
 * @info: Information structure (unused in this context).
 * @path_list: String containing directories separated by colons.
 * @command: Command to search for in the directories.
 *
 * Returns: A pointer to the full path of the executable if found, NULL otherwise.
 */
char *find_path(shell_info *info, char *path_list, char *command)
{
    int index = 0, start_pos = 0;
    char *full_path;

    /* Check if path_list is NULL */
    if (!path_list)
        return NULL;

    /* If command starts with "./", check if it's a valid command path */
    if ((cm_strlen(command) > 2) && starts_with(command, "./"))
    {
        if (is_cmd(info, command))
            return command;
    }

    /* Loop through path_list and search for command in each directory */
    while (1)
    {
        /* If end of path_list or a colon is encountered */
        if (!path_list[index] || path_list[index] == ':')
        {
            /* Extract the current directory from path_list */
            full_path = dup_chars(path_list, start_pos, index);

            /* Check if full_path is empty */
            if (!*full_path)
                cm_strcpy(full_path, command);
            else
            {
                /* Append "/" and command to the full_path */
                cm_strcat(full_path, "/");
                cm_strcat(full_path, command);
            }

            /* Check if the full_path is a valid executable */
            if (is_cmd(info, full_path))
                return full_path;

            /* If end of path_list is reached, break the loop */
            if (!path_list[index])
                break;

            /* Update the starting position for the next directory */
            start_pos = index;
        }

        /* Move to the next character in path_list */
        index++;
    }

    /* Command not found in any directory, return NULL */
    return (NULL);
}

