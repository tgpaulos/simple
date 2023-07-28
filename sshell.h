#ifndef SSHELL_H
#define SSHELL_H

#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <stdio.h>
#include <fcntl.h>
#include <dirent.h>
#include <string.h>

#define BUFFER_SIZE 1024
#define PROMPT "$SSH"

#define MAX_CMD_LENGTH 128
#define MAX_ARGS 10


#define MAX_ARGUMENTS 100
#define FAIL -1
#define SUCC 0
#define ERRSTR_0 "No such file or directory\n"

extern char **environ;
void display_prompt(void);
void execute_command(char **args);
void handle_exit(void);
void handle_env(void);

char *build_command_path(const char *command, const char *directory);
char *_memcpy(char *dest, char *src, unsigned int n);
int _strcmp(char *s1, char *s2);
char *_strncpy(char *dest, char *src, int n);
char *_strncat(char *dest, char *src, int n);

/**
 * struct cmd_t -structure for command to be executed by execve
 * @pthn: holds the path for the command
 * @argv: pointer to string of argumnts for the command
 * @envp: pointer to the string environmental variable.
 */
struct cmd_t
{
	char *pthn;
	char **argv;
	char **envp;
};
void setcmd_t(struct cmd_t *p, char *pthn, char **argv, char **envp);
void exit(int status);
int _readfd(char **argv, char **envp, int *status);
int ashell(int argc, char **argv, char **envp, int *status);
int ishell(int argc, char **argv, char **envp, int *status);
int execcmd(struct cmd_t *exeptr, int *status);
char *lkdirfcmd(char *path, char *cmd);
char *lkpath(char *envp[]);
char **readcmd(size_t *arrpln);
char *getcmd(char *aptr, char **envp);
size_t _strcp(char *str_a, char *str_b);
size_t _strlen(char *str);

char *_getfullpath(char *cmd);
char **_tostrarr(char *buff, char *dlmtr, size_t *ptrarrln);
char **incrarrptrmem(char **arrptr, size_t *arrptrln);
int _chkfordlmtr(char chr, char *dlmtr);
int _streq(char *strs, char *strf);
int _lktostr(char *strs, char *strf);
char *_getcmdpath(char *cmd, char *path, char *envp[]);
void intlzstr(char *strptr, size_t strln, char ch);
void intlzarrptr(char **arrptr, size_t arrptrln);
char *_cpsasbtoc(char *str_a, char *str_b, char ch);
void _freearrmem(char **ptr, size_t ptrln);
char **iszrpath(char *cmd, int *iszln);
char *readdir_fcmd(char *dirpth, char *cmd);
char *readpathfcmd(char *cmd);
char **sortpath(char **path);
void _freemem(char *ptr);

#endif
