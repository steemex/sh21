#include "../s21_string.h"
char *s21_strpbrk(const char *str1, const char *str2) {
  char *ptr = (char *)str1;
  char *ret;
  int check = 0;
  while (*ptr != '\0') {
    int j = 0;
    while (str2[j] != '\0') {
      if (*ptr == str2[j]) {
        check = 1;
      }
      j++;
    }
    if (check) {
      break;
    }
    ptr++;
  }
  if (check) {
    ret = ptr;
  } else {
    ret = S21_NULL;
  }

  return ret;
}