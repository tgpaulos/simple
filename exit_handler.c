#include "sshell.h"
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

/**
 * handle_exi -
 *
 */

void handle_exit(void)
{
	exit(EXIT_SUCCESS);
}

