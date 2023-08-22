#ifndef _MAIN_H_
#define _MAIN_H_
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdarg.h>

#define BUFFER_SIZE 1024

int _printf(const char *format, ...);
int _putchar(char c);

/* buffer_handler function */
void flush_buffer(int *count);
void append_to_buffer(const char *str, int *count);
void print_character(char c, int *count);
void print_string_to_buffer(const char *s, int *count);
/* buffer_handler function */

#endif
