#include <stdio.h>
#include <stdlib.h>

extern char **environ;

int string_length(const char *str) {
        int length = 0;
        while (str[length] != '\0') {
                length++;
        }
        return length;
}

int string_compare(const char *str1, const char *str2) {
        int i = 0;
        while (str1[i] != '\0' && str2[i] != '\0') {
                if (str1[i] != str2[i]) {
                        return 0;
                }
                i++;
        }
        return (str1[i] == '\0' && str2[i] == '\0');
}

void display_path() {
        char *path = NULL;
        int i = 0;

        while (environ[i] != NULL) {
                if (string_compare(environ[i], "PATH=")) {
                        path = environ[i] + 5;
                        break;
                }
                i++;
        }

        if (path != NULL) {
                printf("%s\n", path);
        }
        if (path != NULL) {
                printf("%s\n", path);
        }
}

/*int main() {
        display_path();
        return 0;
}*/
