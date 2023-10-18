#include "main.h"

/**
 * strtow - Splits a string into words based on delimiters.
 * @str: Input string.
 * @delimiters: Delimiter string to split the input string.
 *
 * Return: Array of strings containing the words (or NULL on failure).
 */
char **strtow(char *str, char *delimiters)
{
    int i, j, k, m, num_words = 0;
    char **words_array;

    if (str == NULL || str[0] == '\0')
        return (NULL);

    /* If delimiters are not provided, use space as the default delimiter */
    if (!delimiters)
        delimiters = " ";

    /* Count the number of words in the input string */
    for (i = 0; str[i] != '\0'; i++)
    {
        if (!is_delim(str[i], delimiters) && (is_delim(str[i + 1], delimiters) || !str[i + 1]))
            num_words++;
    }

    /* If no words found, return NULL */
    if (num_words == 0)
        return (NULL);

    /* Allocate memory for the array of words */
    words_array = malloc((1 + num_words) * sizeof(char *));
    if (!words_array)
        return (NULL);

    /* Extract words from the input string and store them in the array */
    for (i = 0, j = 0; j < num_words; j++)
    {
        /* Skip delimiter characters */
        while (is_delim(str[i], delimiters))
            i++;

        k = 0;

        /* Calculate the length of the current word */
        while (!is_delim(str[i + k], delimiters) && str[i + k])
            k++;

        /* Allocate memory for the current word */
        words_array[j] = malloc((k + 1) * sizeof(char));
        if (!words_array[j])
        {
            /* Free previously allocated memory in case of failure */
            for (k = 0; k < j; k++)
                free(words_array[k]);
            free(words_array);
            return (NULL);
        }

        /* Copy the characters of the word into the array */
        for (m = 0; m < k; m++)
            words_array[j][m] = str[i++];

        words_array[j][m] = '\0'; /* Null-terminate the word */
    }

    words_array[j] = NULL; /* Null-terminate the array of words */
    return (words_array);
}

/**
 * strtow2 - Splits a string into words based on a delimiter.
 * @str: Input string.
 * @delimiter: Delimiter character to split the string.
 *
 * Return: Array of strings containing the words (or NULL on failure).
 */
char **strtow2(char *str, char delimiter)
{
    int i, j, k, m, num_words = 0;
    char **words_array;

    if (str == NULL || str[0] == '\0')
        return (NULL);

    /* Count the number of words in the input string */
    for (i = 0; str[i] != '\0'; i++)
    {
        if ((str[i] != delimiter && str[i + 1] == delimiter) ||
            (str[i] != delimiter && !str[i + 1]) || str[i + 1] == delimiter)
        {
            num_words++;
        }
    }

    /* If no words found, return NULL */
    if (num_words == 0)
        return (NULL);

    /* Allocate memory for the array of words */
    words_array = malloc((1 + num_words) * sizeof(char *));
    if (!words_array)
        return (NULL);

    /* Extract words from the input string and store them in the array */
    for (i = 0, j = 0; j < num_words; j++)
    {
        /* Skip delimiter characters */
        while (str[i] == delimiter && str[i] != '\0')
            i++;

        k = 0;

        /* Calculate the length of the current word */
        while (str[i + k] != delimiter && str[i + k] && str[i + k] != delimiter)
            k++;

        /* Allocate memory for the current word */
        words_array[j] = malloc((k + 1) * sizeof(char));
        if (!words_array[j])
        {
            /* Free previously allocated memory in case of failure */
            for (k = 0; k < j; k++)
                free(words_array[k]);
            free(words_array);
            return (NULL);
        }

        /* Copy the characters of the word into the array */
        for (m = 0; m < k; m++)
            words_array[j][m] = str[i++];

        words_array[j][m] = '\0'; /* Null-terminate the word */
    }

    words_array[j] = NULL; /* Null-terminate the array of words */
    return (words_array);
}

