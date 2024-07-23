#include "../s21_string.h"
void *s21_memset(void *str, int c, s21_size_t n) {
  unsigned char *str_cpy = (unsigned char *)str;

  for (s21_size_t i = 0; i < n; i++) {
    str_cpy[i] = c;
  }
  return str;
}
