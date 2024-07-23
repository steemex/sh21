#include "../s21_string.h"
char *s21_strtok(char *str, char const *delim) {
  static char *save_ptr;

  if (str != S21_NULL) {
    save_ptr = str;
  }

  if (save_ptr == S21_NULL || *save_ptr == '\0') {
    return S21_NULL;
  }

  char *token_start = save_ptr;
  char *token_end;

  while (*save_ptr != '\0' && s21_strchr(delim, *save_ptr) != S21_NULL) {
    save_ptr++;
  }

  token_end = save_ptr;
  while (*save_ptr != '\0' && s21_strchr(delim, *save_ptr) == S21_NULL) {
    save_ptr++;
  }

  if (*save_ptr != '\0') {
    *save_ptr = '\0';

    if (*token_start == ' ') {
      int space_count = 0;
      int token_len = s21_strlen(token_start);
      for (int i = 0; i < token_len; i++) {
        if (token_start[i] == ' ') {
          space_count++;
        }
      }
      for (int i = 0; i < token_len; i++) {
        token_start[i] = token_start[space_count];
        space_count++;
      }
    }
    save_ptr++;
  }

  return token_end;
}