#include "main.h"

static char buffer[BUFFER_SIZE];
static int buffer_index;
/**
 * flush_buffer - clear buffer
 * @count: counter
 *
 * Return: void
 */
void flush_buffer(int *count)
{

	write(1, buffer, buffer_index);
	*count += buffer_index;
	buffer_index = 0;
}

/**
 * append_to_buffer - append to bueffer
 * @str: string
 * @count: counter
 * Return: void
 */
void append_to_buffer(const char *str, int *count)
{
	int i;

	for (i = 0; str[i] != '\0'; ++i)
	{
		buffer[buffer_index++] = str[i];
		if (buffer_index >= BUFFER_SIZE - 1)
		{
			flush_buffer(count);
		}
	}
}

/**
 * print_character - print character
 * @c: character string
 * @count: counter
 * Return: void
 */
void print_character(char c, int *count)
{

	buffer[buffer_index++] = c;
	if (buffer_index >= BUFFER_SIZE - 1)
	{
		flush_buffer(count);
	}
}

/**
 * print_string_to_buffer - print string to buffer
 * @s: character string
 * @count: counter
 * Return: void
 */
void print_string_to_buffer(const char *s, int *count)
{
	while (*s)
	{
		print_character(*s, count);
		s++;
	}
}
