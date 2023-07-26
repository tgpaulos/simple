#include "sshell.h"

/**
 * main - is a unix command line inpterpreter.
 * 
 * Description: Display a prompt and wait for the user to type
 * -a command. A command line always ends with a new line.
 * -The prompt is dsiplay again each time a command executed.
 * -The command line are simple, no semicolons, pipes,redirectio
 * -The command line are made only of one word. No arguments.
 * -If an executable cannot be found, print an error message and
 *  diplay the prompt again.
 * -Handle errors and end of a file condition (Ctrl + D).
 *
 * Return: 1-success
 */
int main(int argc, char **argv)
{
	size_t bsize = 1024, strptrln;
	char *buff, ch;
	char **argv, **cmd, *path, *command;
	char *pmt = "\n#sshell$";
	char *environ[] = {NULL};
	char *dlmtr_c = " \n";
	ssize_t rcnt, wcnt;
	pid_t mpid;
	int status, fd[2];
	int succ = 1, fail = -1, i;

	mpid = getpid();
	if (pipe(fd) < 0)
	{
		perror("pipe error");
		exit(1);
	}
	buff = (char *)malloc(bsize * sizeof(ch));
	if (buff == NULL)
		return (fail);
	while (1)
	{
		wcnt = write(1,pmt, 10);
		if (wcnt == -1)
			return (-1);
		intlzstr(buff, bsize, '\0');
		rcnt = read(0, buff, bsize);
		if (rcnt == -1)
			return (fail);
	        argv = _tostrarr(buff, dlmtr_c, &strptrln);
		path = NULL;
		command = argv[0];
		cmd = iszrpath(command, path);
		if (cmd == NULL)
		{
			perror("Main:Error-memory error\n");
			continue;
		}
		path = cmd[1];
		argv[0] = _getcmdpath(cmd[0], path);
		if (path != NULL)
			free(path);
		if (argv[0] == NULL)
		{
			printf(":No such file or directory\n");
			continue;
		}
		mpid = fork();
		printf("%s = %d\n", "forked", (int)mpid);
		if (mpid == -1)
		{
			perror("Error:");
			exit (1);
		}
		else if(mpid == 0)
		{
			printf("%s\n", "Child process");
			close(fd[0]);
			dup2(fd[1], STDOUT_FILENO);
			execve(argv[0], argv, environ);
			printf("%s\n", ":No such file or directory");
			exit(1);
		}
		close(fd[1]);
		printf("%s\n", "parent process");
		while ((rcnt = read(fd[0], buff, sizeof(buff))) > 0)
		{
			wcnt = write(1, buff, rcnt);
			if (wcnt < 0)
				return (fail);
		}
		if (rcnt < 0)
			return (fail);
		wait(&status);
		_freearrmem(argv, strptrln);
		_freemem(path);
		_freearrmem(cmd,3); 

	}
	return (succ);
}


/**
 * intlzstr - initalizes the string or arr of chars.
 * @strptr: pointer to the string to be initialized.
 * @strln: size of the array
 * @ch: character to be initalized with
 *
 */

void intlzstr(char *strptr, size_t strln, char ch)
{
	size_t i;
	
	for (i = 0; i < strln; i++)
		strptr[i] = ch;
}
/**
 * intlzarrptr - initialize array of pointers to NULL
 * @arrptr: pointer to array of pointers
 * @arrptrln: length of the array of pointers.
 *
 * Return: initialized array of pointers.
 */
void intlzarrptr( char **arrptr, size_t arrptrln)
{
	size_t i;

/*	printf("intlzarrptr: Entered\n"); */
	for (i = 0; i < arrptrln; i++)
		arrptr[i] = NULL;
}
/**
 * _freearrmem - free the array of memory used.
 * @ptr: pointer to memory.
 * @ptrln: length of the memory.
 *
 */
void _freearrmem(char **ptr, size_t ptrln)
{
	size_t  i;

	printf("freearrmem: Entered\n");
	for (i = 0; i < ptrln; i++)
	{
		if (ptr[i] != NULL)
		{
			free(ptr[i]);
			ptr[i] = NULL;
		}
	}
	if (ptr != NULL)
	{
		free(ptr);
		ptr = NULL;
	}
	
	printf("freearrmem: Finished\n");
}
/**
 * _freemem - free a char array of memory used
 * @ptr: pointer to char of array
 */
void _freemem(char *ptr)
{
	if (ptr != NULL)
	{
		free(ptr);
		ptr = NULL;
	}
}
/**
 * _lktostr - finds str in another str
 * @strs: soucre string where we look
 * @strf: the string to be found
 *
 * Return: 1-succ -1-fail.
 */

int _lktostr(char *strs, char *strf)
{
	size_t i, j;
	int fail = -1;
	int succ = 1;

	for (i = 0; strs[i] != '\0'; i++)
	{
		if (strs[i] == strf[0])
		{
			while (strf[j] != '\0' && strs[i + j] != strf[j])
				j++;
			if ((size_t)_strlen(strf) == j)
				return (succ);
		}
	}
	return (fail);
}
