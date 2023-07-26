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

#define BUFFER_SIZE 256
#define PROMPT "$SSH"
#define MAX_ARGUMENTS 100

extern char **environ;
void readCommand(char **argv, ssize_t *read);
void executeCommand(char **argv);
void runShell(void);
char *build_command_path(const char *command, const char *directory);

void exit(int status);
char *lkdirfcmd(char *path, char *cmd);
char *lkpath(char *envp[]);
char **readcmd(int argc, char **argv, size_t *ptrarrln, char *envp[]);
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
