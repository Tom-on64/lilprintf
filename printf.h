/**************************************************************
 * \author Tom-on
 * \breif  Lilprintf is the smallest full-ish printf() 
 *         implementation i was able to write. It is intended
 *         as the printf implementation for my OS kern.
 **************************************************************/
#ifndef _PRINTF_H
#define _PRINTF_H

#include <stdarg.h>
#include <stddef.h>

/*
 * This function outputs a character to the standard output
 * YOU MUST DEFINE THIS FUNCTION ON YOUR OWN
 * \param c The character to print
 */
void _putchar(char c);

/*
 * This function outputs a NULL terminated string to the standard output
 * YOU MUST DEFINE THIS FUNCTION ON YOUR OWN
 * \param s The string to print
 */
void _putstr(char* s);

/* 
 *  Prints a formatted string to the output buffer
 */
int printf(const char* fmt, ...);
int vprintf(const char* fmt, va_list va);

/* 
 *  Writes a formatted string to a buffer
 *  \param buf A pointer to the buffer to be written to
 *  \param len The maximum size of the buffer (to prevent buffer overflow)
 *  \param fmt The string specifying the output format
 *  \param va Variable argument list
 *  \return The number of characters written to the buffer
 */
int snprintf(char* buf, size_t len, const char* fmt, ...);
int vsnprintf(char* buf, size_t len, const char* fmt, va_list va);

/*
 *  Uses a custom output function to output a formatted string
 *  \param outfn The function to output a character
 *  \param arg An argument pointer for data passed to the output function
 *  \param fmt The string specifying the output format
 *  \param va Variable argument list
 *  \return The number of characters sent to the output function
 */
int pprintf(void (*outfn)(char c, void* arg), void* arg, const char* fmt, ...);
int vpprintf(void (*outfn)(char c, void* arg), void* arg, const char* fnt, va_list va);

#endif
