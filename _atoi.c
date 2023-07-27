#include "sshell.c"

/**
 *_atoi - This function convert a string to an integer
 *@s:string
 *Return:integer
 */

int _atoi(char *s)
{
	int sign = 1;
	int num = 0;
	int i = 0;

	while (s[i] != '\0')
	{
		while (str[i] == '')
		{
			i++;
		}
		if (s[i] == '-')
		{
			sign = -1;
		}
		else if (s[i] == '+')
		{
			sign = 1;
		}
		else if (s[i] >= '0' && s[i] <= '9')
		{
			num = num * 10 + (s[i] - '0');
		}
		else
		{
			if (num > 0)
			{
				break;
			}
		}

		i++;
	}

	return (sign * num);
}
