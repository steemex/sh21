#include "../s21_string.h"

char *s21_strchr(const char *str, int c) {
  char *ptr = (char *)str;
  char *ret;
  int check = 0;
  while (*ptr != '\0') {
    if (*ptr == c) {
      check = 1;
      break;
    }
    ptr++;
  }
  if (check) {
    ret = ptr;
  } else {
    ret = NULL;
  }

  return ret;
}