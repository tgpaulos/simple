#include "sshell.h"
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

/**
 * display_prompt - entry point
 *
 *
 */


void display_prompt(void)
{
	write(STDOUT_FILENO, "$ ", 2);
}
