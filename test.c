#include "printf.h"
#include <unistd.h>
#include <string.h>

void _putchar(char c) { write(1, &c, 1); }
void _putstr(char* s) { write(1, s, strlen(s)); }

int main() {
    char buf[1024];

    char* word = "World";
    int l = snprintf(buf, 1024, "Hello, %s!", word);
    buf[++l] = '\0';

    _putstr(buf);
}

