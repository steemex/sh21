#include "../s21_string.h"

char *s21_strncat(char *dest, const char *src, s21_size_t n) {
  char *ptr = dest;

  while (*ptr != '\0') {
    ptr++;
  }

  while (*src != '\0' && n > 0) {
    *ptr = *src;
    ptr++;
    src++;
    n--;
  }

  *ptr = '\0';

  return dest;
}