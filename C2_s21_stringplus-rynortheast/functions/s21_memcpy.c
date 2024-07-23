#include "../s21_string.h"

void *s21_memcpy(void *dest, const void *src, s21_size_t n) {
  const unsigned char *src_cpy = (const unsigned char *)src;
  unsigned char *mid_res = (unsigned char *)dest;

  for (s21_size_t i = 0; i < n; i++) {
    mid_res[i] = src_cpy[i];
  }
  return dest;
}