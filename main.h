#ifndef MAIN_H_
#define MAIN_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

extern char **environ;


#define MAX_INPUT_LENGTH 1024
#define WRITE_BUFFER_FLUSH 1024
#define READ_BUFFER_SIZE 1024
#define BUFFER_FLUSH -1


#define CONVERT_UNSIGNED 1
#define CONVERT_LOWERCASE 2

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

/*commmand chaining*/
#define COMMAND_NORM 0
#define COMMAND_OR 1
#define COMMAND_AND 2
#define COMMAND_CHAIN 3



/**
 * ln_list_str - Single linked list
 * @number: The number field
 * @str: The str
 * @next: pointes to the next node
*/

typedef struct Node {
    int number;
    char *string;
    struct Node *next;
}Node;

/*Defining th linked list*/
typedef Node linkedList_node;

typedef struct shell_info
{
    char *path;
    char **argv;
    char *arg;
    char **environ;
    char *fname;
    char **command_Buffer;
    unsigned int count_line;
    int argc;
    int readfd;
    int command_BufferType;
    int linecount_flag;
    int history_count;
    int status;
    int env_changed;
    int error_num;
    int histcount;
    linkedList_node *env;
    linkedList_node *history;
    linkedList_node *aliases;
    
} shell_info;

#define INFO_INIT \
{NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, NULL, NULL, NULL}




typedef struct builtin
{
	char *type;
	int (*func)(shell_info *);
} builtin_table;


/*ln_list.c*/
size_t get_list_len(linkedList_node *current);
size_t print_lnlist_string(const linkedList_node *head);
void free_lnkedlist(linkedList_node **head_ptr);
size_t print_lnkdlist(const linkedList_node *head);
linkedList_node *ln_startsWith(linkedList_node *node, char *prefix, char c);

/*ln_list1.c*/
linkedList_node *add_node_beg(linkedList_node **head, const char *string, int number);
linkedList_node *add_node_end(linkedList_node **head, const char *string, int num);
int delete_nodeint_at_index(linkedList_node **head, unsigned int index);
char **list_to_strings(linkedList_node *head);
ssize_t get_node_index(linkedList_node *head, linkedList_node *node);


/*string.c*/
char *cm_strncat(char *dest, char *src, int n);
char *cm_strncpy(char *dest, char *src, int n);
int cm_strcmp(char *s1, char *s2);
char *cm_strchr(char *s, char c);


/*string1.c*/
char *starts_with(const char *haystack, const char *needle);
int cm_strlen(char *s);
char *cm_strcpy(char *dest, const char *src);
char *cm_strcat(char *dest, char *src);
char *cm_strdup(const char *str);

/*errors.c*/
void cm_eputs(char *str);
int cm_eputchar(char c);
int cm_putfd(char c , int fd);
int cm_putsfd(char *str, int fd);

/*errors1.c*/
void print_error(shell_info *info_, char *err_str);
char *convert_number(long int num, int base, int flags);
int print_d(int input, int fd);
int str_to_int(char *s);
void cm_puts(char *string);

/*comments.c*/
void remove_comments(char *buffer);
int cm_putchar(char c);

/*getline.c*/
ssize_t read_buffer(shell_info *info, char *buf, size_t *i);
ssize_t get_input(shell_info *info);
ssize_t input_buf(shell_info *info, char **buffer, size_t *length);
void sigintHandler(__attribute__((unused))int sig_num);
int _getline(shell_info *info, char **ptr, size_t *length);

/*memory.c*/
int bfree(void **ptr);
char *cm_memset(char *dest, char value, unsigned int size);
void ffree(char **str_array);
void *_realloc(void *prev_ptr, unsigned int old_size, unsigned int new_size);

/*getinfo.c*/
void free_info(shell_info *info, int free_all);
void clear_info(shell_info *info);
void set_info(shell_info *info, char **arg_vector);

/*vars.c*/
int replace_vars(shell_info *info);
int replace_string(char **old_str_ptr, char *new_str);
int replace_alias(shell_info *info);
int is_chain(shell_info *info, char *buffer, size_t *position);
void check_chain(shell_info *info, char *buffer, size_t *position, size_t command_start, size_t buffer_length);

/*parsers.c*/
char *find_path(shell_info *info, char *path_list, char *command);
char *dup_chars(char *pathstr, int start, int stop);
int is_cmd(shell_info *info, char *path);

/*built.c*/
int _myhistory(shell_info *info);
int unset_alias(shell_info *info, char *alias_name);
int _mycd(shell_info *info);
int _myhelp(shell_info *info);
int _myexit(shell_info *info);


/*built1.c*/
int set_alias(shell_info *info, char *alias_definition);
int print_alias(linkedList_node *node);
int _myalias(shell_info *info);

/*env.c*/
int _myenv(shell_info *info);
char *_getenv(shell_info *info, const char *name);
int _mysetenv(shell_info *info);
int _myunsetenv(shell_info *info);
int populate_env_list(shell_info *info);

/*env1.c*/
char **get_environ(shell_info *info);
int _unsetenv(shell_info *info, char *env_var);
int _setenv(shell_info *info, char *var, char *value);



/*strings3.c*/
int _atoi(char *str);
int _isalpha(int c);
int is_delim(char c, char *delim);
int is_interactive(shell_info *info);

/*hist.c*/
int renumber_history(shell_info *info);
char *get_history_file(shell_info *info);
int write_history_to_file(shell_info *info);
int read_history_from_file(shell_info *info);
int build_history_list(shell_info *info, char *buf, int linecount);

/*shell.c*/
int shell_loop(shell_info *info, char **av);
int find_builtin(shell_info *info);
void find_cmd(shell_info *info);
void fork_cmd(shell_info *info);

/*strtok.c*/
char **strtow(char *str, char *d);
char **strtow2(char *str, char d);

/*init.c*/
void initializeShell(shell_info *info, char *argv[]);
void setupFileDescriptor(shell_info *info, int argc, char *argv[]);


void execute_command(shell_info *info);

#endif
