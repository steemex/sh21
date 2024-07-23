#include "../s21_string.h"
char *s21_strerror(int errnum) {
  if (errnum > -1 && errnum < ERR_LIST_SIZE) {
    char *err_list[] = ERROR_LIST;
    return err_list[errnum];
  }
  static char error[512];
  if (ERR_LIST_SIZE == 134) {
    sprintf(error, "Unknown error %d", errnum);
  } else {
    sprintf(error, "Unknown error: %d", errnum);
  }
  return error;
}