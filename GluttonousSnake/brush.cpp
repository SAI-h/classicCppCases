#include "brush.h"
#include <cstdio>

void Brush::printf_normal(const char c) {
    printf("%c", c);
}

void Brush::printf_normal(const char* s) {
    printf("%s", s);
}

void Brush::printf_red(const char c) {
    printf("\033[0m\033[1;31m%c\033[0m", c);
}

void Brush::printf_red(const char* s) {
    printf("\033[0m\033[1;31m%s\033[0m", s);
}

void Brush::printf_green(const char c) {
    printf("\033[0m\033[1;32m%c\033[0m", c);
}

void Brush::printf_green(const char* s) {
    printf("\033[0m\033[1;32m%s\033[0m", s);
}

void Brush::printf_yellow(const char c) {
    printf("\033[0m\033[1;33m%c\033[0m", c);
}

void Brush::printf_yellow(const char* s) {
    printf("\033[0m\033[1;33m%s\033[0m", s);
}

void Brush::printf_blue(const char c) {
    printf("\033[0m\033[1;34m%c\033[0m", c);
}

void Brush::printf_blue(const char* s) {
    printf("\033[0m\033[1;34m%s\033[0m", s);
}

void Brush::printf_pink(const char c) {
    printf("\033[0m\033[1;35m%c\033[0m", c);
}

void Brush::printf_pink(const char* s) {
    printf("\033[0m\033[1;35m%s\033[0m", s);
}

void Brush::printf_cyan(const char c) {
    printf("\033[0m\033[1;36m%c\033[0m", c);
}

void Brush::printf_cyan(const char* s) {
    printf("\033[0m\033[1;36m%s\033[0m", s);
}

void Brush::printf_pink(const bool INT_FORMAT, const int n) {
    printf("\033[0m\033[1;35m%d\033[0m", n);
}