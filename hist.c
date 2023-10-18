#include "main.h"


/**
 * renumber_history - Renumber the history list in the info struct.
 * @info: The information struct containing the history data.
 *
 * Return: Number of history items in the renumbered history list.
 */
int renumber_history(shell_info *info)
{
    linkedList_node *currentNode = info->history;
    int i = 0;

    while (currentNode)
    {
        currentNode->number = i++;
        currentNode = currentNode->next;
    }
    return (info->histcount = i);
}


/**
 * get_history_file - Get the full path of the history file.
 * @info: The information struct containing environment data.
 *
 * Return: A dynamically allocated string containing the history file path,
 *         or NULL if memory allocation fails or HOME environment variable is
 *         not set.
 */
char *get_history_file(shell_info *info)
{
    char *historyFilePath, *homeDir;

    homeDir = _getenv(info, "HOME=");
    if (!homeDir)
        return (NULL);
    
    historyFilePath = malloc(sizeof(char) * (cm_strlen(homeDir) + cm_strlen(HIST_FILE) + 2));
    if (!historyFilePath)
        return (NULL);
    
    historyFilePath[0] = 0;
    cm_strcpy(historyFilePath, homeDir);
    cm_strcat(historyFilePath, "/");
    cm_strcat(historyFilePath, HIST_FILE);
    
    return (historyFilePath);
}


/**
 * write_history_to_file - Writes history to a file.
 * @info: Pointer to the information struct containing history data.
 *
 * Return: 1 on success, -1 on failure.
 */
int write_history_to_file(shell_info *info)
{
    ssize_t fileDescriptor;
    char *historyFilePath = get_history_file(info);
    linkedList_node *currentNode = NULL;

    if (!historyFilePath)
        return (-1);

    fileDescriptor = open(historyFilePath, O_CREAT | O_TRUNC | O_RDWR, 0644);
    free(historyFilePath);
    if (fileDescriptor == -1)
        return (-1);

    for (currentNode = info->history; currentNode; currentNode = currentNode->next)
    {
        cm_putsfd(currentNode->string, fileDescriptor);
        cm_putfd('\n', fileDescriptor);
    }
    cm_putfd(BUFFER_FLUSH, fileDescriptor);
    close(fileDescriptor);
    return (1);
}


/**
 * read_history_from_file - Reads history from a file into the history list.
 * @info: Pointer to the information struct where history data will be stored.
 *
 * Return: Number of history entries read from the file.
 */
int read_history_from_file(shell_info *info)
{
    int i, lastIndex = 0, lineCount = 0;
    ssize_t fileDescriptor, bytesRead, fileSize = 0;
    struct stat fileStat;
    char *buffer = NULL, *historyFilePath = get_history_file(info);

    if (!historyFilePath)
        return (0);

    fileDescriptor = open(historyFilePath, O_RDONLY);
    free(historyFilePath);
    if (fileDescriptor == -1)
        return (0);

    if (!fstat(fileDescriptor, &fileStat))
        fileSize = fileStat.st_size;
    if (fileSize < 2)
        return (0);

    buffer = malloc(sizeof(char) * (fileSize + 1));
    if (!buffer)
        return (0);

    bytesRead = read(fileDescriptor, buffer, fileSize);
    buffer[fileSize] = 0;

    if (bytesRead <= 0)
        return (free(buffer), 0);

    close(fileDescriptor);

    for (i = 0; i < fileSize; i++)
    {
        if (buffer[i] == '\n')
        {
            buffer[i] = 0;
            build_history_list(info, buffer + lastIndex, lineCount++);
            lastIndex = i + 1;
        }
    }

    if (lastIndex != i)
        build_history_list(info, buffer + lastIndex, lineCount++);
    
    free(buffer);

    info->histcount = lineCount;

    while (info->histcount-- >= HIST_MAX)
        delete_nodeint_at_index(&(info->history), 0);

    renumber_history(info);
    return (info->histcount);
}



/**
 * add_history_entry - Adds a history entry to the history list.
 * @info: Pointer to the information struct where history data is stored.
 * @entry: The history entry to add to the history list.
 * @linecount: Line number associated with the history entry.
 *
 * Return: 0 on success, -1 on failure.
 */

int build_history_list(shell_info *info, char *buf, int linecount)
{
	linkedList_node *node = NULL;

	if (info->history)
		node = info->history;
	add_node_end(&node, buf, linecount);

	if (!info->history)
		info->history = node;
	return (0);
}

