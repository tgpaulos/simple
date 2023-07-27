#include "sshell.h"
/**
 * incrarrptrmem - increase the memeory allocated by malloc
 * @arrptr: hold array of pointer to strings
 * @arrptrln: length  of the old  array pointers
 *
 * Return: new array of pointers  to strings.
 */
char **incrarrptrmem(char **arrptr, size_t *arrptrln)
{
	char **arrptr_n;
	size_t arrptrln_o, i;

	printf("incrarrptrmmry: Entered\n");
	arrptrln_o = *arrptrln;
	*arrptrln = (size_t)2 * (*arrptrln);
	arrptr_n = (char **)malloc((*arrptrln + 1) * sizeof(char));
	if (arrptr_n == NULL)
		return (NULL);
	for (i = 0; i < arrptrln_o; i++)
		arrptr_n[i] = arrptr[i];
	for (i = arrptrln_o; i < *arrptrln; i++)
		arrptr_n[i] = NULL;
	arrptr_n[i] = NULL;
	free(arrptr);
	return (arrptr_n);
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
void intlzarrptr(char **arrptr, size_t arrptrln)
{
	size_t i;

	for (i = 0; i < arrptrln; i++)
		arrptr[i] = NULL;
}

/**
 * setcmd_t - sets value to memeber of struct cmd_t
 * @p: cmd_t struct pointer
 * @pthn: holds value for the pathname pointer
 * @argv: holds value for argv pointer
 * @envp: holds value for envp pointer
 *
 * Return:  pointer to the setted cmd_t structure
 */
void setcmd_t(struct cmd_t *p, char *pthn, char **argv, char **envp)
{
	p->pthn = pthn;
	p->argv = argv;
	p->envp = envp;
}
