#include "../s21_string.h"
char *s21_strstr(const char *haystack, const char *needle) {
  int haystack_len = s21_strlen(haystack);
  int needle_len = s21_strlen(needle);

  if (needle_len == 0) {
    return (char *)haystack;
  }

  for (int i = 0; i < haystack_len; i++) {
    if (haystack[i] == needle[0]) {
      int j;
      for (j = 1; j < needle_len; j++) {
        if (haystack[i + j] != needle[j]) {
          break;
        }
      }
      if (j == needle_len) {
        return (char *)haystack + i;
      }
    }
  }

  return S21_NULL;
}