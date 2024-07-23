#ifndef SPRINTF_H
#define SPRINTF_H

#include <ctype.h>
#include <inttypes.h>
#include <limits.h>
#include <locale.h>
#include <math.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#define MAX 4086

typedef struct flags {
  int spec;
  int length;
  int minus;
  int plus;
  int zero;
  int space;
  int width;
  int del;
  int accur;
  int prec;
} flags;

size_t s_len(const char *str);
char *s_cat(char *stringa, const char *ptr);
void *s_memmove(void *stringa, const void *ptr, size_t number);
int s21_sprintf(char *str, const char *format, ...);
const char *find_all_flags(const char *str, flags *flags_struct);
const char *find_spec(const char *str, flags *flags_struct);
char *callSpecifFun(va_list *ptr, flags flags_struct, char **str,
                    const char **format, int *counter_l);
char *d_spec(char **str, flags a, va_list *ptr, int *counter_l);
char *u_d_spec(char **str, flags a, va_list *ptr, int *counter_l);
char *f_spec(char **str, flags a, va_list *ptr, int *counter_l);
char *c_spec(char **str, flags a, va_list *ptr, const char **format,
             int *counter_l);
char *s_spec(char **str, flags a, va_list *ptr, const char **format,
             int *counter_l);
char *l_s_spec(char **str, flags flags_struct, va_list *ptr,
               const char **format, int *counter_l);
char *p_spec(char **str, flags a, va_list *ptr, int *counter_l);
char *n_spec(char **str, va_list *ptr, int counter_l);
char *int_to_str(long long int value, char *result, int op);
void clear_struct(flags *flags_struct);
void insert_padding(char *result, flags flags_struct, int *i, int strlength);
void add_plus_Index(flags flags_struct, char *str, int i);
void add_minus_Index(char *str, int i);
char *uns_to_str(long long unsigned value, char *result, int op);
int value_to_str(long double x, char *numberStr, long double extendedValue,
                 int *length);
void process_g(int *spec, int *accur, char *numberStr, int *exponenta,
               long double x);
void print_base(flags flags_struct, unsigned long x, char *result, int *i,
                int *accur);
void UPPER(char *x);
void cut_off_zeros(char *numberStr, flags flags_struct, int exponenta);
void round_exp(int length, int accur, char *numberStr, flags flags_struct);
void e_to_str(long double x, char *numberStr, char *nunu, flags a, int *i,
              int accur);
void e_spec(long double x, flags flags_struct, int accur, char **z,
            int exponenta);
void double_to_str(long double x, long double extendedValue, char *numberStr,
                   int *length);
void lf_to_char(long double number, int symbols, char **str);
char *swap(char s[]);

#endif
