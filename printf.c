#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "main.h"
#include <stdarg.h>

static char buffer[BUFFER_SIZE];
static int buffer_index;

/**
 * print_integer_to_buffer - print integer
 * @num: number to be printed
 * @count: count of num
 * @base: base number
 * Return: void
 */
void print_integer_to_buffer(int num, int *count, int base)
{
	int tempNum = num;
	char *numStr = NULL;
	int i, digit, digitCount = 0;

	if (num == 0)
	{
		print_character('0', count);
		return;
	}
	if (num < 0)
	{
		print_character('-', count);
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
	append_to_buffer(numStr, count);
	free(numStr);
}

/**
 * print_binary_to_buffer - print in into binary
 * @num: integer
 * @count: int count
 * Return: void
 */
void print_binary_to_buffer(unsigned int num, int *count)
{
	int i, j = 0;
	char binaryStr[32];

	if (num == 0)
	{
		buffer[buffer_index++] = '0';
		if (buffer_index >= BUFFER_SIZE - 1)
		{
			flush_buffer(count);
		}
		return;
	}
	while (num > 0)
	{
		binaryStr[j++] = '0' + (num & 1);
		num >>= 1;
	}

	for (i = j - 1; i >= 0; --i)
	{
		buffer[buffer_index++] = binaryStr[i];
		if (buffer_index >= BUFFER_SIZE - 1)
			flush_buffer(count);
	}
}

/**
 * handle_custom_specifiers - Function that handle specifiers
 * @c: format
 * @list: num args
 * @count: counter
 *
 * Return: void
 *
 */

void handle_custom_specifiers(char c, va_list list, int *count)
{
	int base;
	unsigned int num1, num2;
	char ch, *str, *str1, *ptr;

	if ((c == 'c' && c == 's' && c == '%'))
	{
		ch = va_arg(list, int);
		str = va_arg(list, char *);
		print_character(ch, count);
		print_string_to_buffer(str, count);
		print_character('%', count);
	}
	else if (c == 'S')
	{
		str1 = va_arg(list, char *);
		while (*str1)
		{
			if (*str1 < 32 || *str1 >= 127)
				print_special_character(*str1, count);
			else
			{
				print_character(*str1, count);
			}
			str1++;
		}
	}
	else if ((c == 'b'))
	{
		num1 = va_arg(list, unsigned int);
		print_binary_to_buffer(num1, count);
	}
	else if (c == 'd' || c == 'i' || c == 'u' || c == 'o' 
			|| c == 'x' || c == 'X')
	{
		num2 = va_arg(list, unsigned int);
		base = (c == 'o') ? 8 : ((c == 'x' || c == 'X') ? 16 : 10);
		print_integer_to_buffer(num2, count, base);
	}
	else if (c == 'p')
	{
		ptr = va_arg(list, void *);
		print_string_to_buffer("0x", count);
		print_integer_to_buffer((unsigned long)ptr, count, 16);
	}
}

/**
 * process_format - process the format
 * @format: format
 * @list: num arg
 * @count: counter
 * Return: void
 */
void process_format(const char *format, va_list list, int *count)
{
	int i;
	char c;

	for (i = 0; (c = format[i]); ++i)
	{
		if (c == '%')
		{
			c = format[++i];
			handle_custom_specifiers(c, list, count);
		}
		else
		{
			print_character(c, count);
		}
	}
}

/**
 * _printf - Printf function
 * @format: format
 * Return: printed characters
 *
 */
int _printf(const char *format, ...)
{
	va_list list;
	int counter = 0;

	va_start(list, format);
	process_format(format, list, &counter);
	va_end(list);

	flush_buffer(&counter);
	return (counter);
}
