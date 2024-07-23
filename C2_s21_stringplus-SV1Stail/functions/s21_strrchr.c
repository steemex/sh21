#include "../s21_string.h"
char *s21_strrchr(const char *str, int c) {
  char *ptr = (char *)str;
  char *ret;
  int check = 0;
  while (*ptr != '\0') {
    if (*ptr == c) {
      ret = ptr;
      check = 1;
    }
    ptr++;
  }
  if (!check) {
    ret = S21_NULL;
  }
  return ret;
}