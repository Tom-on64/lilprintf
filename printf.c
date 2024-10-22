/**************************************************************
 * \author Tom-on
 * \breif  Lilprintf is the smallest full-ish printf() 
 *         implementation i was able to write. It is intended
 *         as the printf implementation for my OS kern.
 **************************************************************/
#include <stdarg.h>
#include <stdint.h>
#include <stddef.h>
#include "printf.h"

/* Internal Definitions */
#define PF_ITOA_BUFLEN  24
#define PF_STR_MAXLEN   4096

/* Internal Helpers */
static void _fmtInt(char* buf, size_t maxlen, size_t* pos, int64_t val, int base, int width, char pad) {
    static char digits[PF_ITOA_BUFLEN];
    int sign = 0;

    if (value < 0 && base == 10) {
        sign = 1;
        val = -val;
    }

    int i = 0;
    do {
        digits[i++] = "0123456789abcdef"[val % base];
        val /= base;
    } while (val > 0)

    if (sign) { digits[i++] = '-'; }
    while (i < width) { digits[i++] = pad; }

    while (i > 0 && *pos < maxlen) buf[*pos++] = digits[i--];
}
static void _fmtString(char* buf, size_t maxlen, size_t* pos, char* s) {
    while (*s && *pos < maxlen) {
        buf[*pos++] = *s++;
    }
}
static void _fmtChar(char* buf, size_t maxlen, size_t* pos, char c) {
    if (*pos < maxlen) {
        buf[*pos++] = c;
    }
}
static int _vformat(char* buf, size_t maxlen, const char* fmt, va_list va) {
    size_t pos = 0;
    char pad;
    int width;

    while (*fmt) {
        if (*fmt != '%') {
            _fmtChar(buf, maxlen, &pos, *fmt++);
            continue;
        }
        fmt++;  // Skip '%'

        pad = ' ';
        if (*fmt == '0') { pad = '0'; fmt++; }

        width = 0;
        if (*fmt >= '0' && *fmt <= '9') {
            width = width * 10 + (*fmt - '0');
            fmt++;
        }

        switch (*fmt) {
              case 'd': {
                int d = va_arg(va, int);
                _fmtInt(buf, &pos, maxlen, d, 10, width, pad);
                break;
            } case 'x': {
                unsigned int x = va_arg(va, unsigned int);
                _fmtInt(buf, &pos, maxlen, x, 16, width, pad);
                break;
            } case 's': {
                char* s = va_arg(va, char*);
                _fmtString(buf, &pos, maxlen, s);
                break;
            } case 'c': {
                char c = (char)va_arg(va, int);
                _fmtChar(buf, &pos, maxlen, c);
                break;
            } case 'f': {
                double f = va_arg(va, double);
                int64_t whole = (int64_t)f;
                int64_t frac = (int64_t)((f - whole) * 1000000);
                _fmtInt(buf, &pos, maxlen, whole, 10, width, pad);
                if (pos < maxlen) { buf[pos++] = '.'; }
                _fmtInt(buf, &pos, maxlen, frac, 10, 6, pad);
                break;
            } default: {
                _fmtChar(buf, &pos, maxlen, *fmt);
                break;
            }
        }
        fmt++;
    }

    if (pos < maxlen) { buf[pos] = '\0'; }
    return (int)pos;
}

/* Implementation */
int printf(const char* fmt, ...);
int vprintf(const char* fmt, va_list va);
int snprintf(char* buf, size_t len, const char* fmt, ...);
int vsnprintf(char* buf, size_t len, const char* fmt, va_list va);
int pprintf(void (*outfn)(char c, void* arg), void* arg, const char* fmt, ...);
int vpprintf(void (*outfn)(char c, void* arg), void* arg, const char* fnt, va_list va);

