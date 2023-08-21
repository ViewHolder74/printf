#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "main.h"
#include <stdarg.h>

/**
 * print_char - function that print character
 * @c: character
 * @count: number of character
 * Return: void
 */
void print_char(char c, int *count)
{
	write(1, &c, 1);
	(*count)++;
}

/**
 * print_string - function that print string
 * @s: string character
 * @count: number of string
 * Return: void
 */
void print_string(const char *s, int *count)
{
	int i;

	for (i = 0; s[i]; ++i)
		print_char(s[i], count);
}

/**
 * print_integer - print integer
 * @num: number to be printed
 * @count: count of num
 * Return: void
 */
void print_integer(int num, int *count)
{
	int tempNum = num;
	char *numStr = NULL;
	int i, digitCount = 0;

	if (num == 0)
	{
		print_char('0', count);
		return;
	}
	if (num < 0)
	{
		print_char('-', count);
		num = -num;
	}
	while (tempNum > 0)
	{
		tempNum /= 10;
		digitCount++;
	}
	numStr = (char *)malloc((digitCount + 1) * sizeof(char));
	for (i = digitCount - 1; i >= 0; i--)
	{
		numStr[i] = '0' + (num % 10);
		num /= 10;
	}
	numStr[digitCount] = '\0';
	print_string(numStr, count);
	free(numStr);
}


/**
 * _printf - Function that produces output according to a format.
 * @format: character string
 *
 * Return: number of characters
 *
 */

int _printf(const char *format, ...)
{
	va_list list;
	char *str;
	char c, ch;
	int i, num, counter = 0;

	va_start(list, format);
	for (i = 0; (c = format[i]); ++i)
	{
		if (c == '%')
		{
			c = format[++i];
			if ((c == 'c') && (c == 's') && (c == '%'))
			{
				ch = va_arg(list, int);
				str = va_arg(list, char *);
				print_char(ch, &counter);
				print_string(str, &counter);
				print_char('%', &counter);
			}
			else if (c == 'd' || c == 'i')
			{
				num = va_arg(list, int);
				print_integer(num, &counter);
			}
		}
		else
		{
			print_char(c, &counter);
		}
	}
	va_end(list);
	return (counter);
}
