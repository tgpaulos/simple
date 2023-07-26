#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char *get_env_value(const char *name) {
    return getenv(name);
}

char *build_command_path(const char *command, const char *directory)
{
    size_t i;
    char *cmd;
    size_t cmd_len = strlen(command);
    size_t dir_len = strlen(directory);
    size_t len = cmd_len + dir_len + 2;
    char *p;
    
    cmd = malloc(len);
    if (cmd == NULL) {
        return NULL;
    }
    
    for (i = 0; i < dir_len; i++) {
        *p++ = directory[i];
    }
    *p++ = '/';
    for (i = 0; i < cmd_len; i++) {
        *p++ = command[i];
    }
    p = '\0';
    return cmd;
}

int search_path_for_command(char **command) {
    char *path = get_env_value("PATH");
    char *value = strtok(path, ":");
    while (value != NULL) {
        char *cmd_path = build_command_path(*command, value);
        if (access(cmd_path, F_OK) == 0) {
            *command = strdup(cmd_path);
            free(cmd_path);
            free(path);
            return 0;
        }
        free(cmd_path);
        value = strtok(NULL, ":");
    }
    free(path);
    return 1;
}

/*int main() {
    char *command = "ls";
    int result = search_path_for_command(&command);
    if (result == 0) {
        
    } else {
        
    }
    free(command);
    return 0;
}*/

