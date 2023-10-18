#include"main.h"
/**
 * main - entry point
 * @ac: arg count
 * @av: arg vector
 *
 * Return: 0 on success, 1 on error
 */
int main(int argc, char **argv)
{
    shell_info info[] = {INFO_INIT};

    setupFileDescriptor(info, argc, argv);
    initializeShell(info, argv);

    return EXIT_SUCCESS;
}

