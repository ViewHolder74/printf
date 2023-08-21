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
 * @base: base number
 * Return: void
 */
void print_integer(int num, int *count, int base)
{
	int tempNum = num;
	char *numStr = NULL;
	int i, digit, digitCount = 0;

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
		tempNum /= base;
		digitCount++;
	}
	numStr = (char *)malloc((digitCount + 1) * sizeof(char));
	for (i = digitCount - 1; i >= 0; i--)
	{
		digit = num % base;
		if (digit < 10)
			numStr[i] = '0' + digit;
		else
			numStr[i] = 'a' + (digit - 10);
		num /= base;
	}
	numStr[digitCount] = '\0';
	print_string(numStr, count);
	free(numStr);
}

/**
 * print_binary - print in into binary
 * @num: integer
 * @count: int count
 * Return: void
 */
void print_binary(unsigned int num, int *count)
{
	int i, j = 0;
	char binaryStr[32];

	while (num > 0)
	{
		binaryStr[j++] = '0' + (num & 1);
		num >>= 1;
	}

	for (i = j - 1; i >= 0; --i)
		print_char(binaryStr[i], count);
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
	va_list list; char *str, c, ch; int i, num, counter = 0;
	unsigned int b_num, a_num, c_num, d_num;

	va_start(list, format);
	for (i = 0; (c = format[i]); ++i)
	{
		if (c == '%')
		{
			c = format[++i];
			if ((c == 'c') && (c == 's') && (c == '%') && (c == 'u') 
				&&  (c == 'o') && (c == 'x') && (c == 'X'))
			{
				ch = va_arg(list, int);
				str = va_arg(list, char *);
				b_num = va_arg(list, unsigned int);
				a_num = va_arg(list, unsigned int);
				c_num = va_arg(list, unsigned int);
				d_num = va_arg(list, unsigned int);
				print_char(ch, &counter);
				print_string(str, &counter);
				print_char('%', &counter);
				print_integer(b_num, &counter, 10);
				print_integer(a_num, &counter, 8);
				print_integer(c_num, &counter, 16);
				print_integer(d_num, &counter, 16);
			}
			else if (c == 'd' || c == 'i')
			{
				num = va_arg(list, int);
				print_integer(num, &counter, 10);
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
