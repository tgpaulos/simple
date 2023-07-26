#include "sshell.h"
/**
 * _cpsasbtoc - copy str a and str b to strc c in respective order.
 * @str_a: the first string  to be copied.
 * @str_b: the second string to be copied.
 * @ch: character to get in between them.
 *
 * Return: str_c- pointer to concatnated string.
 */

char *_cpsasbtoc(char *str_a, char *str_b, char ch)
{
	size_t strln_a, strln_b, strln_c;
	size_t i;
	char *strptr;

	if (str_a == NULL || str_b == NULL)
		return (NULL);
	strln_a = _strlen(str_a);
	strln_b = _strlen(str_b);
	strln_c = strln_a + strln_b + 1;
	strptr = (char *)malloc((strln_c + 1) * sizeof(char));
	if (strptr == NULL)
		return (NULL);
	for (i = 0; i < strln_c; i++)
	{
		if (i < strln_a)
			strptr[i] = str_a[i];
		else
		{
			if (i == strln_a && ch != '\0')
				strptr[i] = ch;
			else
				strptr[i] = str_b[i - strln_a - 1];
		}
	}
	strptr[i] = '\0';
	return (strptr);
}
