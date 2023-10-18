#include "main.h"

/**
 * print_error - prints an error messages 
 * @info_: the parameter and return shell_info struct
 * @err_str: The string containing specified error type
 * 
 * Return: 0 if no numbers in string, converted number otherwise
 *        -1 on error
*/

void print_error(shell_info *info_, char *err_str)
{
	cm_eputs(info_->fname);
	cm_eputs(": ");
	print_d(info_->count_line, STDERR_FILENO);
	cm_eputs(": ");
	cm_eputs(info_->argv[0]);
	cm_eputs(": ");
	cm_eputs(err_str);
}

/**
 * convert_number - Converts a number to a string in the specified base.
 * @number: The number to be converted.
 * @base: The base for conversion (e.g., 10 for decimal, 16 for hexadecimal).
 * @flags: Conversion flags.
 *
 * Return: A string representing the number in the specified base.
 */

char *convert_number(long int number, int base, int flags)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = number;

	if (!(flags & CONVERT_UNSIGNED) && number < 0)
	{
		n = -number;
		sign = '-';

	}
	array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do	{
		*--ptr = array[n % base];
		n /= base;
	} while (n != 0);

	if (sign)
		*--ptr = sign;
	return (ptr);
}


/**
 * print_d - Prints a decimal (integer) number (base 10).
 * @input: The input number.
 * @fd: The file descriptor to write to.
 *
 * Return: Number of characters printed.
 */
int print_d(int input, int fd)
{
	int (*__putchar)(char) = cm_putchar;
	int i, count = 0;
	unsigned int _abs_, current;

	if (fd == STDERR_FILENO)
		__putchar = cm_eputchar;

	if (input == 0) {
		__putchar('0');
		count++;
		return count;
	}

	if (input < 0)
	{
		_abs_ = -input;
		__putchar('-');
		count++;
	}
	else
		_abs_ = input;
	current = _abs_;

	for (i = 1000000000; i > 1; i /= 10)
	{
		if (_abs_ / i)
		{
			__putchar('0' + current / i);
			count++;
		}
		current %= i;
	}
	__putchar('0' + current);
	count++;

	return (count);
}



/**
 * str_to_int - Converts a string to an integer.
 * @s: The string to be converted.
 * Return: Converted number if valid, -1 on error.
 */

int str_to_int(char *s)
{
	int i = 0;
	unsigned long int result = 0;

	if (*s == '+')
		s++;  /* TODO: why does this make main return 255? */
	for (i = 0;  s[i] != '\0'; i++)
	{
		if (s[i] >= '0' && s[i] <= '9')
		{
			result *= 10;
			result += (s[i] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (result);
}


/**
 * custom_puts - Outputs a string to the standard output
 * @str: The string to be printed
 *
 
 *
 * Return: N/A (void)
 */

void cm_puts(char *string)
{
	int index = 0;

	if (!string)
		return;

	while (string[index] != '\0')
	{
		cm_putchar(string[index]);
		index++;
	}
}

