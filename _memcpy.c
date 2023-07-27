#include "sshell.h"

/**
 * _memcpy - this function copies memory area
 * @src:memory copied from
 * @dest:memory stored in
 * @n:bytes to be copied
 * Return:ptr
 */
 
char *_memcpy(char *dest, char *src, unsigned int n)
{
        char *ptr = dest;

        while (n--)
        {
                *dest++ = *src++;
        }
        return (ptr);
}
