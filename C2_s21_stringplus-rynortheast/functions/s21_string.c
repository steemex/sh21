#include "../s21_string.h"

// void *s21_memchr(const void *str, int c, s21_size_t n) {
//   const unsigned char *s = (const unsigned char *)str;

//   for (s21_size_t i = 0; i < n; i++) {
//     if (*(s + i) == c) {
//       return (void *)(s + i);
//     }
//   }
//   return S21_NULL;
// }

// int s21_memcmp(const void *str1, const void *str2, s21_size_t n) {
//   const unsigned char *s1 = (const unsigned char *)str1;
//   const unsigned char *s2 = (const unsigned char *)str2;

//   for (s21_size_t i = 0; i < n; i++) {
//     if (*(s1 + i) != *(s2 + i)) {
//       return *(s1 + i) - *(s2 + i);
//     }
//   }
//   return 0;
// }

// void *s21_memcpy(void *dest, const void *src, s21_size_t n) {
//   const unsigned char *src_cpy = (const unsigned char *)src;
//   unsigned char *mid_res = (unsigned char *)dest;

//   for (s21_size_t i = 0; i < n; i++) {
//     mid_res[i] = src_cpy[i];
//   }
//   return dest;
// }

// void *s21_memset(void *str, int c, s21_size_t n) {
//   unsigned char *str_cpy = (unsigned char *)str;

//   for (s21_size_t i = 0; i < n; i++) {
//     str_cpy[i] = c;
//   }
//   return str;
// }

// char *s21_strncat(char *dest, const char *src, s21_size_t n) {
//   char *ptr = dest;

//   while (*ptr != '\0') {
//     ptr++;
//   }

//   while (*src != '\0' && n > 0) {
//     *ptr = *src;
//     ptr++;
//     src++;
//     n--;
//   }

//   *ptr = '\0';

//   return dest;
// }

// char *s21_strchr(const char *str, int c) {
//   char *ptr = (char *)str;
//   char *ret;
//   int check = 0;
//   while (*ptr != '\0') {
//     if (*ptr == c) {
//       check = 1;
//       break;
//     }
//     ptr++;
//   }
//   if (check) {
//     ret = ptr;
//   } else {
//     ret = S21_NULL;
//   }

//   return ret;
// }

// int s21_strncmp(const char *str1, const char *str2, s21_size_t n) {
//   int ret = 0;
//   for (s21_size_t i = 0; i < n; i++) {
//     if (str1[i] != str2[i]) {
//       ret = str1[i] - str2[i];
//       break;
//     }
//   }
//   return ret;
// }

// char *s21_strncpy(char *dest, const char *src, s21_size_t n) {
//   s21_size_t i;

//   for (i = 0; i < n && src[i] != '\0'; i++) {
//     dest[i] = src[i];
//   }

//   for (; i < n; i++) {
//     dest[i] = '\0';
//   }

//   return dest;
// }

// s21_size_t s21_strcspn(const char *str1, const char *str2) {
//   int i = 0;
//   int check = 0;
//   while (str1[i] != '\0') {
//     int j = 0;
//     while (str2[j] != '\0') {
//       if (str1[i] == str2[j]) {
//         check = 1;
//       }
//       j++;
//     }
//     if (check) {
//       break;
//     }
//     i++;
//   }

//   return i;
// }

// s21_size_t s21_strlen(const char *str) {
//   int i = 0;
//   while (str[i] != '\0') {
//     i++;
//   }
//   return i;
// }

// char *s21_strpbrk(const char *str1, const char *str2) {
//   char *ptr = (char *)str1;
//   char *ret;
//   int check = 0;
//   while (*ptr != '\0') {
//     int j = 0;
//     while (str2[j] != '\0') {
//       if (*ptr == str2[j]) {
//         check = 1;
//       }
//       j++;
//     }
//     if (check) {
//       break;
//     }
//     ptr++;
//   }
//   if (check) {
//     ret = ptr;
//   } else {
//     ret = S21_NULL;
//   }

//   return ret;
// }

// char *s21_strrchr(const char *str, int c) {
//   char *ptr = (char *)str;
//   char *ret;
//   int check = 0;
//   while (*ptr != '\0') {
//     if (*ptr == c) {
//       ret = ptr;
//       check = 1;
//     }
//     ptr++;
//   }
//   if (!check) {
//     ret = S21_NULL;
//   }
//   return ret;
// }

// char *s21_strstr(const char *haystack, const char *needle) {
//   int haystack_len = s21_strlen(haystack);
//   int needle_len = s21_strlen(needle);

//   if (needle_len == 0) {
//     return (char *)haystack;
//   }

//   for (int i = 0; i < haystack_len; i++) {
//     if (haystack[i] == needle[0]) {
//       int j;
//       for (j = 1; j < needle_len; j++) {
//         if (haystack[i + j] != needle[j]) {
//           break;
//         }
//       }
//       if (j == needle_len) {
//         return (char *)haystack + i;
//       }
//     }
//   }

//   return S21_NULL;
// }

// char *s21_strtok(char *str, char const *delim) {
//   static char *save_ptr;

//   if (str != S21_NULL) {
//     save_ptr = str;
//   }

//   if (save_ptr == S21_NULL || *save_ptr == '\0') {
//     return S21_NULL;
//   }

//   char *token_start = save_ptr;
//   char *token_end;

//   while (*save_ptr != '\0' && s21_strchr(delim, *save_ptr) != S21_NULL) {
//     save_ptr++;
//   }

//   token_end = save_ptr;
//   while (*save_ptr != '\0' && s21_strchr(delim, *save_ptr) == S21_NULL) {
//     save_ptr++;
//   }

//   if (*save_ptr != '\0') {
//     *save_ptr = '\0';

//     if (*token_start == ' ') {
//       int space_count = 0;
//       int token_len = s21_strlen(token_start);
//       for (int i = 0; i < token_len; i++) {
//         if (token_start[i] == ' ') {
//           space_count++;
//         }
//       }
//       for (int i = 0; i < token_len; i++) {
//         token_start[i] = token_start[space_count];
//         space_count++;
//       }
//     }
//     save_ptr++;
//   }

//   return token_end;
// }

// char *s21_strerror(int errnum) {
//   if (errnum > -1 && errnum < ERR_LIST_SIZE) {
//     char *err_list[] = ERROR_LIST;
//     return err_list[errnum];
//   }
//   static char error[512];
//   if (ERR_LIST_SIZE == 134) {
//     sprintf(error, "Unknown error %d", errnum);
//   } else {
//     sprintf(error, "Unknown error: %d", errnum);
//   }
//   return error;
// }
