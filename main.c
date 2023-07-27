#include <stdlib.h>
#include "sshell.h"

/*int main() {
    char *command = "ls";
    int result = search_path_for_command(&command);
    if (result == 0) {

    } else {

    }
    free(command);
    return 0;
}*/

int main(void)
{
	runShell();
	{
		char *command = "ls";
		int result = search_path_for_command(&command);
		if (result == 0) {

		} else {

		}
		free(command);
		return 0;
	}
	return (0);
}

