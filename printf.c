#include <stdio.h>
#include <unistd.h>
#include "main.h"
#include <stdarg.h>

#define BUFFER_SIZE 1024

void print_buffer(char buffer[], int *buff_ind)
{
	if (*buff_ind > 0)
		write(1, &buffer[0], *buff_ind);

	*buff_ind = 0;
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
	char buffer[BUFFER_SIZE];
	int counter = 0;
	int i, j = 0;
	int c = 0;

	va_start(list, format);
	if (*format == '\0')
		return (-1);

	for (i = 0; format[i] != '\0'; ++i)
	{
		if (format[i] != '%')
		{
			buffer[++j] = format[i];
			if (j == BUFFER_SIZE)
				print_buffer(buffer, &j);
			counter++;
		}

		else
		{
			i++;
			if (c == -1)
				return (-1);
			counter += c;
		}
	}
	va_end(list);
	return (counter);
}
