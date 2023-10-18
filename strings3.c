#include "main.h"

/**
 * is_interactive - Checks if the shell is running in interactive mode.
 * @info: Pointer to the info_t struct.
 *
 * This function checks if the shell is running interactively by verifying
 * if it's connected to a terminal and the read file descriptor is less
 * than or equal to 2 (standard input, output, or error).
 *
 * Return:
 * - 1 if the shell is running interactively, 0 otherwise.
 */
int is_interactive(shell_info *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}


/**
 * is_delim - Checks if a character is a delimiter.
 * @c: The character to check.
 * @delim: Pointer to a null-terminated string containing delimiter characters.
 *
 * This function checks if the character 'c' is one of the delimiter characters
 * specified in the 'delim' string.
 *
 * Return:
 * - 1 if the character is a delimiter, 0 otherwise.
 */
int is_delim(char c, char *delim)
{
	while (*delim) {
		if (*delim == c) {
			return 1;
		}
		delim++;
	}
	return 0;
}


/**
 * _isalpha - Checks if a character is an alphabetic character (uppercase or lowercase).
 * @c: The character to check.
 *
 * Return:
 * - 1 if the character is an alphabetic character (uppercase or lowercase).
 * - 0 otherwise.
 */
int _isalpha(int c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}



/**
 * _atoi - Converts a string to an integer.
 * @str: The input string.
 *
 * Return: The integer converted from the input string.
 */
int _atoi(char *str)
{
	int index, sign = 1, digitFlag = 0, output;
	unsigned int result = 0;

	for (index = 0; str[index] != '\0' && digitFlag != 2; index++)
	{
		if (str[index] == '-')
			sign *= -1;

		if (str[index] >= '0' && str[index] <= '9')
		{
			digitFlag = 1;
			result *= 10;
			result += (str[index] - '0');
		}
		else if (digitFlag == 1)
			digitFlag = 2;
	}

	if (sign == -1)
		output = -result;
	else
		output = result;

	return output;
}

