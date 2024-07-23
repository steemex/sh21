

#include "sprintf.h"
#define S21_NULL ((void *)0)
int s21_sprintf(char *str, const char *format, ...) {
  flags flags_struct = {0};
  int counter_l = 0;
  va_list ptr;
  va_start(ptr, format);
  while (format && *format) {
    if (*format != '%') {
      *str = *format;
      str++;
      format++;
      counter_l++;
    } else {
      *str = '\0';
      format++;
      format = find_all_flags(format, &flags_struct);
      format = find_spec(format, &flags_struct);
      if (format) {
        if (flags_struct.spec == '%') {
          *str = '%';
          str++;
          counter_l++;
        } else {
          str = callSpecifFun(&ptr, flags_struct, &str, &format, &counter_l);
        }
      }
      clear_struct(&flags_struct);
    }
  }
  *str = '\0';
  if (!format) counter_l = -1;
  va_end(ptr);
  return counter_l;
}

const char *find_all_flags(const char *str, flags *flags_struct) {
  while (*str == '-' || *str == '+' || *str == '0' || *str == '#' ||
         *str == ' ') {  // если есть флаг
    if (*str == '-') {
      flags_struct->minus = 1;
    } else if (*str == '+') {
      flags_struct->plus = 1;
    } else if (*str == '#') {
      flags_struct->del = 1;
    } else if (*str == '0') {
      flags_struct->zero = 1;
    } else if (*str == ' ') {
      flags_struct->space = 1;
    }
    str++;
  }

  if (*str == '*') {
    str++;
    flags_struct->width = -999;
  } else {
    while (*str >= '0' && *str <= '9') {
      flags_struct->width *= 10;

      flags_struct->width += *str - '0';
      str++;
    }
  }

  if (*str == '.') {
    str++;
    flags_struct->prec = 1;
    if (*str == '*') {
      flags_struct->accur = -999;
      str++;
    } else {
      while (*str >= '0' && *str <= '9') {
        flags_struct->accur *= 10;
        flags_struct->accur += *str - '0';
        str++;
      }
    }
  }
  while (*str == 'h' || *str == 'l' || *str == 'L') {
    flags_struct->length = *str;
    str++;
  }
  return str;
}
const char *find_spec(const char *str, flags *flags_struct) {
  int flag_no_spec = -999;
  if (str && *str && !(*str >= 48 || *str <= 57)) {
    if (*str == 'd' || *str == 'i' || *str == 'o' || *str == 'u' ||
        *str == 'c' || *str == 's' || *str == 'p' || *str == 'n' ||
        *str == 'x' || *str == 'X' || *str == 'e' || *str == 'E' ||
        *str == 'f' || *str == 'g' || *str == 'G') {
      flag_no_spec = 1;
    } else {
      flag_no_spec = 0;
    }
  }
  if (str && *str) {
    flags_struct->spec = *str;
    str++;
  }
  if (!flag_no_spec) {
    str = S21_NULL;
  }
  return str;
}
char *callSpecifFun(va_list *ptr, flags flags_struct, char **str,
                    const char **format, int *counter_l) {
  if (flags_struct.width == -999) {
    int width = va_arg(*ptr, size_t);
    flags_struct.width = width;
  }
  if (flags_struct.accur == -999) {
    int ac = va_arg(*ptr, size_t);
    flags_struct.accur = ac;
  }
  char spec = flags_struct.spec;

  if (spec == 'd' || spec == 'i') {
    *str = d_spec(str, flags_struct, ptr, counter_l);
  } else if (spec == 'o' || spec == 'u' || spec == 'x' || spec == 'X') {
    *str = u_d_spec(str, flags_struct, ptr, counter_l);
  } else if (spec == 'e' || spec == 'E' || spec == 'f' || spec == 'g' ||
             spec == 'G') {
    *str = f_spec(str, flags_struct, ptr, counter_l);
  } else if (spec == 'c') {
    *str = c_spec(str, flags_struct, ptr, format, counter_l);
  } else if (spec == 's') {
    *str = s_spec(str, flags_struct, ptr, format, counter_l);
  } else if (spec == 'p') {
    *str = p_spec(str, flags_struct, ptr, counter_l);
  } else if (spec == 'n') {
    *str = n_spec(str, ptr, *counter_l);
  }
  return *str;
}

char *d_spec(char **str, flags flags_struct, va_list *ptr, int *counter_l) {
  long int va_holder = va_arg(*ptr, long int);
  int index = 0, size_out_str;
  char *mas = calloc(21, sizeof(char)), *tmp = mas;
  if (flags_struct.length == 'h') {
    va_holder = (short)va_holder;
  } else if (flags_struct.length == 0) {
    va_holder = (int)va_holder;
  }
  int_to_str(va_holder, mas, 10);
  if (va_holder == 0 && flags_struct.prec && !flags_struct.accur) {
    mas[0] = 0;
  }
  if (mas[0] == '-') mas++;

  if (21 > (flags_struct.accur > flags_struct.width ? flags_struct.accur
                                                    : flags_struct.width)) {
    size_out_str = 21 + 2;
  } else if (flags_struct.accur > flags_struct.width) {
    size_out_str = flags_struct.accur + 2;
  } else {
    size_out_str = flags_struct.width + 2;
  }
  char *res = calloc(size_out_str, sizeof(char));
  insert_padding(res, flags_struct, &index, s_len(mas));
  if (va_holder < 0) {
    add_minus_Index(res, index);
  } else {
    add_plus_Index(flags_struct, res, index);
  }
  for (; (flags_struct.accur - (int)s_len(mas)) > 0;
       index++, flags_struct.accur--) {
    s_cat(res, "0");
  }

  s_cat(res, mas);
  if (flags_struct.minus) {
    while ((int)s_len(res) < flags_struct.width) s_cat(res, " ");
  }
  s_cat(*str, res);
  int out_str = s_len(res);
  *counter_l += out_str;
  free(res);
  free(tmp);
  return *str + out_str;
}
char *u_d_spec(char **str, flags flags_struct, va_list *ptr, int *counter_l) {
  unsigned long int va_holder = va_arg(*ptr, unsigned long int);
  int size_out_str;
  char mas[24] = {0};
  if (flags_struct.length == 'h') {
    va_holder = (unsigned short)va_holder;
  } else if (flags_struct.length == 0) {
    va_holder = (unsigned int)va_holder;
  }
  if (flags_struct.spec == 'o') {
    uns_to_str(va_holder, mas, 8);
  } else if (flags_struct.spec == 'u') {
    uns_to_str(va_holder, mas, 10);
  } else {
    uns_to_str(va_holder, mas, 16);
  }
  if (flags_struct.spec == 'X') {
    UPPER(mas);
  }
  if (va_holder == 0 && flags_struct.prec && !flags_struct.accur) {
    mas[0] = 0;
  }
  int index = 0;
  if (24 > (flags_struct.accur > flags_struct.width ? flags_struct.accur
                                                    : flags_struct.width)) {
    size_out_str = 24 + 2;
  } else if (flags_struct.accur > flags_struct.width) {
    size_out_str = flags_struct.accur + 2;
  } else {
    size_out_str = flags_struct.width + 2;
  }
  char *res = calloc(size_out_str, sizeof(char));
  insert_padding(res, flags_struct, &index, s_len(mas));
  print_base(flags_struct, va_holder, res, &index, &(flags_struct.accur));

  for (; flags_struct.accur - (int)s_len(mas) > 0;
       index++, flags_struct.accur--)
    res[index] = '0';

  res[index] = '\0';
  s_cat(res, mas);
  if (flags_struct.minus) {
    while ((int)s_len(res) < flags_struct.width) {
      s_cat(res, " ");
    }
  }
  s_cat(*str, res);
  int out_str = s_len(res);
  *counter_l += out_str;
  free(res);
  return *str + out_str;
}

char *f_spec(char **str, flags flags_struct, va_list *ptr, int *counter_l) {
  long double va_holder, val;
  int exponenta = 0, index = 0, valueLength = 0, exceptional_сase = 0;
  if (flags_struct.length == 'L') {
    val = va_holder = va_arg(*ptr, long double);
  } else {
    val = va_holder = va_arg(*ptr, double);
  }
  char mas[MAX] = {0};
  char *str_number = &(mas[1]);
  int accur = flags_struct.prec ? flags_struct.accur : 6;
  exceptional_сase = value_to_str(va_holder, str_number, val, &valueLength);
  if (!exceptional_сase) {
    process_g(&(flags_struct.spec), &accur, str_number, &exponenta, va_holder);
    if (flags_struct.spec == 'e' || flags_struct.spec == 'E') {
      e_spec(va_holder, flags_struct, accur, &str_number, exponenta);
    } else {
      round_exp(valueLength, accur, str_number, flags_struct);
      cut_off_zeros(str_number, flags_struct, exponenta);
    }
    if ((str_number[s_len(str_number) - 1] == '.') &&
        !(flags_struct.spec == 'f' && flags_struct.del))
      str_number[s_len(str_number) - 1] = 0;
  }
  if (str_number[-1]) str_number = mas;
  int size_out_str =
      ((unsigned int)(flags_struct.width + 2) > (s_len(str_number) + 2)
           ? (unsigned int)(flags_struct.width + 2)
           : (s_len(str_number) + 2));
  char *res = calloc(size_out_str + 1, sizeof(char));
  for (;
       !flags_struct.minus && (flags_struct.width - (int)s_len(str_number) > 0);
       index++, flags_struct.width--) {
    if (flags_struct.zero)
      res[index] = '0';
    else
      res[index] = ' ';
  }
  if (!exceptional_сase)
    if (va_holder < 0.) {
      add_minus_Index(res, index);
    } else {
      add_plus_Index(flags_struct, res, index);
    }
  else if (isinf(va_holder) > 0 || isnan(va_holder)) {
    add_plus_Index(flags_struct, res, index);
  }
  if (flags_struct.spec == 'E' || flags_struct.spec == 'G') {
    UPPER(str_number);
  }
  if (mas[0] != 0) {
    s_cat(res, mas);
  } else {
    s_cat(res, str_number);
  }
  if (flags_struct.minus)
    for (; (int)s_len(res) < flags_struct.width;) s_cat(res, " ");
  s_cat(*str, res);
  int out_str = s_len(res);
  *counter_l += out_str;
  free(res);
  return *str + out_str;
}

char *c_spec(char **str, flags flags_struct, va_list *ptr, const char **format,
             int *counter_l) {
  wchar_t smb = va_arg(*ptr, wchar_t);

  if (flags_struct.length != 'l') {
    smb = (char)smb;
  }
  if (flags_struct.length == 'l' && smb > 127) {
    (**str) = '\0';
    *format = 0;
  } else {
    for (; !flags_struct.minus && (flags_struct.width - 1 > 0);
         (*str)++, flags_struct.width--, (*counter_l)++)
      (**str) = ' ';
    (**str) = smb;
    (*str)++, (*counter_l)++;
    if (flags_struct.minus) {
      for (; (flags_struct.width - 1 > 0);
           (*str)++, flags_struct.width--, (*counter_l)++)
        (**str) = ' ';
    }
    **str = '\0';
  }
  return *str;
}

char *s_spec(char **str, flags flags_struct, va_list *ptr, const char **format,
             int *counter_l) {
  if (flags_struct.length == 'l') {
    l_s_spec(str, flags_struct, ptr, format, counter_l);
  } else {
    char *va_holder = va_arg(*ptr, char *);
    int length = va_holder == S21_NULL ? 6 : s_len(va_holder);
    if (flags_struct.prec && flags_struct.accur < length)
      length = flags_struct.accur;
    if (flags_struct.prec && va_holder == S21_NULL && flags_struct.accur < 6)
      length = 0;
    int size_out_str =
        (length > flags_struct.width ? length : flags_struct.width) + 2;
    char *res = calloc(size_out_str, sizeof(char));
    int index = 0;
    for (; !flags_struct.minus && (flags_struct.width - length > 0);
         index++, flags_struct.width--) {
      if (flags_struct.zero)
        res[index] = '0';
      else
        res[index] = ' ';
    }

    if (va_holder != S21_NULL) {
      for (int q = 0; q < length; q++, index++) {
        res[index] = va_holder[q];
      }
    } else if (length != 0) {
      char *string = "(null)";
      for (int rt = 0; rt < 7; rt++, index++) res[index] = string[rt];
    }
    res[index] = '\0';
    if (flags_struct.minus) {
      for (; s_len(res) < (size_t)flags_struct.width; index++) {
        res[index] = ' ';
      }
    }
    s_cat(*str, res);
    *str += s_len(res);
    *counter_l += s_len(res);
    free(res);
  }
  return *str;
}

char *l_s_spec(char **str, flags flags_struct, va_list *ptr,
               const char **format, int *counter_l) {
  int ascs = 0;
  wchar_t *symbols = va_arg(*ptr, wchar_t *);
  if (symbols != 0) {
    for (; ascs >= 0 && symbols[ascs]; ascs++)
      if (symbols[ascs] > 127) ascs = -999;
  }

  if (ascs < 0) {
    **str = 0;
    *format = 0;
  } else {
    int index = 0, length;
    if (symbols == 0) {
      length = 0;
    } else {
      length = ascs;
    }
    if (flags_struct.prec && flags_struct.accur < length) {
      length = flags_struct.accur;
    }
    if (flags_struct.prec && symbols == 0 && flags_struct.accur < 6) {
      length = 0;
    }
    int size_out_str = 2;
    if (length > flags_struct.width) {
      size_out_str += length;
    } else {
      size_out_str += flags_struct.width;
    }
    char *res = calloc(size_out_str, sizeof(char));

    for (; !flags_struct.minus && (flags_struct.width - length > 0);
         index++, flags_struct.width--) {
      res[index] = ' ';
    }
    if (symbols != 0) {
      for (int q = 0; q < length; q++, index++) {
        res[index] = symbols[q];
      }
    } else if (length != 0) {
      char *string = "(null)";
      for (int rt = 0; rt < 7; rt++, index++) res[index] = string[rt];
    }
    res[index] = '\0';
    if (flags_struct.minus) {
      for (; (int)s_len(res) < flags_struct.width;) s_cat(res, " ");
    }
    s_cat(*str, res);
    *str += s_len(res);
    *counter_l += s_len(res);
    free(res);
  }
  return *str;
}

char *p_spec(char **str, flags flags_struct, va_list *ptr, int *counter_l) {
  long long int va_holder = va_arg(*ptr, long long int);
  char mas_p[MAX] = {0};
  if (va_holder == 0) {
    s_cat(mas_p, "(null)");
  } else {
    uns_to_str(va_holder, mas_p, 16);
  }

  int size_out_str = 0;

  if ((20 + 4) > (flags_struct.accur + 4 > flags_struct.width + 2
                      ? flags_struct.accur + 4
                      : flags_struct.width + 2)) {
    size_out_str = 20 + 4;
  } else if ((flags_struct.accur + 4) > (flags_struct.width + 2)) {
    size_out_str = flags_struct.accur + 4;
  } else {
    size_out_str = flags_struct.width + 2;
  }
  char *res = calloc(size_out_str, sizeof(char));
  int index = 0;
  for (; !flags_struct.minus &&
         (flags_struct.width -
              ((flags_struct.accur * (va_holder != 0)) > (int)s_len(mas_p)
                   ? (flags_struct.accur * (va_holder != 0))
                   : (int)s_len(mas_p)) -
              2 * (va_holder != 0) >
          0);
       index++, flags_struct.width--) {
    res[index] = ' ';
  }

  if (va_holder != 0) {
    if (flags_struct.plus == 1 || flags_struct.space == 1) {
      if (index != 0)
        res[index - 1] = flags_struct.plus ? '+' : ' ';
      else {
        res[index] = flags_struct.plus ? '+' : ' ';
        index++;
      }
    }
    res[index] = '0';
    res[index + 1] = 'x';
    index += 2;
  }

  for (; va_holder != 0 && flags_struct.accur - (int)s_len(mas_p) > 0;
       index++, flags_struct.accur--) {
    res[index] = '0';
  }

  res[index] = '\0';
  s_cat(res, mas_p);

  if (flags_struct.minus) {
    for (; (int)s_len(res) < flags_struct.width;) s_cat(res, " ");
  }

  int outs_str = s_len(res);
  s_cat(*str, res);
  *counter_l += outs_str;
  free(res);
  return *str + outs_str;
}

char *n_spec(char **str, va_list *ptr, int counter_l) {
  int *va_holder = va_arg(*ptr, int *);
  *va_holder = counter_l;
  return *str;
}
char *int_to_str(long long int value, char *res, int op) {
  int number, index = 0;
  if (value < 0) {
    number = value * -1;
  } else {
    number = value;
  }
  while (number) {
    int tmp = number % op;

    if (tmp >= 10) {
      res[index++] = 97 + (tmp - 10);
    } else {
      res[index++] = 48 + tmp;
    }

    number /= op;
  }

  if (index == 0) {
    res[index++] = '0';
  }

  if (value < 0) {
    res[index++] = '-';
  }

  res[index] = '\0';

  return swap(res);
}

char *uns_to_str(long long unsigned value, char *res, int op) {
  long long unsigned number = value;

  int index = 0;

  while (number) {
    int tmp = number % op;

    if (tmp >= 10) {
      res[index++] = 97 + (tmp - 10);
    } else {
      res[index++] = 48 + tmp;
    }

    number /= op;
  }

  if (index == 0) {
    res[index++] = '0';
  }

  res[index] = '\0';

  return swap(res);
}

size_t s_len(const char *str) {
  int index = 0;
  while (str[index] != '\0') {
    index++;
  }
  return index;
}
char *s_cat(char *stringa, const char *ptr) {
  size_t k = s_len(stringa);
  for (int i = 0; (ptr[i] != '\0'); i++, k++) {
    stringa[k] = ptr[i];
  }
  return stringa;
};
char *swap(char s[]) {
  char tmp;
  int i, j;
  for (i = 0, j = s_len(s) - 1; i < j; i++, j--) {
    tmp = s[i];
    s[i] = s[j];
    s[j] = tmp;
  }
  return s;
}
void lf_to_char(long double number, int symbols, char **str) {
  long double delitel = powl(10, symbols);
  int tmp = (int)(fmodl(number, delitel) / (delitel / 10.0));
  if (number / delitel >= 1) {
    symbols++;
    lf_to_char(number, symbols, str);
  } else if ((int)number == 0) {
    tmp = 0;
  }
  **str = tmp + '0';
  (*str)++;
  **str = '\0';
}

void double_to_str(long double va_holder, long double val, char *str_number,
                   int *length) {
  if (va_holder < 0) {
    va_holder = -1 * va_holder;
  }
  val = (va_holder - fmodl(va_holder, 1));
  char *kind_of_int = str_number;

  if (val == 0)
    str_number[0] = '0';
  else {
    lf_to_char(va_holder, 1, &kind_of_int);
  }
  s_cat(str_number, ".");

  *length = s_len(str_number);
  val = va_holder = fabsl(fmodl(va_holder, 1));
  char digit[2] = {'0', 0};
  for (int i = 0; i < 50; i++) {
    val = va_holder = va_holder * 10;
    val -= fmodl(val, 1);
    digit[0] = val + '0';
    s_cat(str_number, digit);
    val = va_holder = fmodl(va_holder, 1);
  }
}
void *s_memmove(void *stringa, const void *ptr, size_t number) {
  unsigned char *stringa_sub = (unsigned char *)stringa;
  unsigned char *ptr_sub = (unsigned char *)ptr;
  unsigned char tmp[number];

  for (size_t i = 0; i < number; i++) {
    tmp[i] = ptr_sub[i];
  }
  for (size_t i = 0; i < number; i++) {
    stringa_sub[i] = tmp[i];
  }
  return stringa_sub;
}

void e_spec(long double va_holder, flags flags_struct, int accur,
            char **out_str, int exponenta) {
  char *str = *out_str;
  int index = 0;
  char *mas = calloc(s_len(str), sizeof(char));
  e_to_str(va_holder, str, mas, flags_struct, &index, accur);

  if (exponenta && !flags_struct.del) {
    for (int s = s_len(str) - 1; s > 0 && str[s] == '0'; s--) {
      str[s] = 0;
    }
  }
  if (va_holder != 0) {
    if (index - 1 < 10) {
      s_cat(mas, "0");
      int_to_str(index - 1, &(mas[3]), 10);
    } else {
      int_to_str(index - 1, &(mas[2]), 10);
    }
  }
  if (str[s_len(str) - 1] == '.' && !flags_struct.del) str[s_len(str) - 1] = 0;
  s_cat(str, mas);
  free(mas);
}

void e_to_str(long double va_holder, char *str, char *mas, flags a, int *index,
              int accur) {
  if (str[0] > '0') {
    for (; str[(*index)] != '.'; (*index)++)
      ;
    for (int i = *index; i > 1; i--) {
      str[i] = str[i - 1];
    }
    str[1] = '.';
    s_cat(mas, "e+");
    round_exp(2, accur, str, a);
    if (str[-1] != 0) {
      str[0] = '.';
      s_memmove(&str[1], &str[2], accur + 1);
      for (int y = accur + 1; y < 80; y++) {
        str[y] = 0;
      }
      (*index)++;
    }
  } else if (va_holder == 0) {
    s_cat(mas, "e+00");
    round_exp(2, accur, str, a);
  } else {
    for (; str[(*index)] == '0' || str[(*index)] == '.'; (*index)++)
      ;
    str[0] = str[(*index)];
    s_memmove(&str[2], &str[(*index) + 1], accur + 1);
    round_exp(2, accur, str, a);
    if (str[-1] == '1') {
      str[0] = '.';
      s_memmove(&str[1], &str[2], accur + 1);
      (*index)--;
    }

    if ((*index) - 1 == 0)
      s_cat(mas, "e+");
    else
      s_cat(mas, "e-");
  }
}

void round_exp(int length, int accur, char *str, flags flags_struct) {
  int lens = (int)s_len(str);
  if ((int)(length + accur) < (int)s_len(str)) {
    int i = 1, point = 0;
    if (str[length + accur] >= '5') {
      while (str[length + accur - i] == '9' || str[length + accur - i] == '.') {
        if (str[length + accur - i] == '.')
          point = 1;
        else
          str[length + accur - i] = '0';
        i++;
      }

      if (str[length + accur - i] == 0)
        str[length + accur - i] = '1';
      else
        str[length + accur - i] += 1;
    }
    if (accur == 0) {
      point = 1;
    }
    if (!point)
      str[length + accur] = 0;
    else {
      point = 0;
      for (; str[point] != '.'; point++)
        ;
      if (!flags_struct.del && accur == 0)
        str[point] = 0;
      else
        str[point + accur + 1] = 0;
    }
    for (int i = (int)s_len(str); i < lens; i++) str[i] = 0;
  }
}

void cut_off_zeros(char *str, flags flags_struct, int exponenta) {
  if (exponenta && !flags_struct.del) {
    int point = 0;
    for (int i = 0; i < (int)s_len(str); i++)
      if (str[i] == '.') {
        point = 1;
      }
    for (int i = s_len(str) - 1; point && i > 0 && str[i] == '0'; i--) {
      str[i] = 0;
    }
  }
}

void UPPER(char *va_holder) {
  for (int i = 0; va_holder[i]; i++) {
    if (va_holder[i] >= 'a' && va_holder[i] <= 'z') {
      va_holder[i] -= 32;
    }
  }
}
void print_base(flags flags_struct, unsigned long va_holder, char *res,
                int *index, int *accur) {
  if (flags_struct.del && va_holder != 0) {
    int op = 0;
    if (flags_struct.spec == 'o') {
      if ((*index) > 0 && res[(*index) - 1] == 32) op = (*index) - 1;
      if (op == 0) {
        (*index)++;
      }
      res[op] = '0';
      (*accur)--;
    } else if (flags_struct.spec == 'x' || flags_struct.spec == 'X') {
      if ((*index) > 1 && res[(*index) - 1] == 32) {
        op = (*index) - 2;
      } else if ((*index) == 1 && res[(*index) - 1] == 32) {
        (*index)++;
      } else {
        (*index) += 2;
      }
      res[op] = '0';
      res[op + 1] = flags_struct.spec;
    }
  }
}

void process_g(int *spec, int *accur, char *str, int *exponenta,
               long double va_holder) {
  if (*spec == 'e' || *spec == 'E' || *spec == 'g' || *spec == 'G') {
    if (*spec == 'g' || *spec == 'G') {
      *exponenta = 1;
    }
    int decimalPointPosition = 0, positiveExponentRequired = 1;
    if ((va_holder < 10 && va_holder > -10) && fmodl(va_holder, 1) == 0)
      positiveExponentRequired = 0;
    if (positiveExponentRequired) {
      if (str[0] > '0') {
        for (; str[decimalPointPosition] != '.'; decimalPointPosition++)
          ;
      } else {
        for (; str[decimalPointPosition] == '0' ||
               str[decimalPointPosition] == '.';
             decimalPointPosition++)
          ;
      }
      decimalPointPosition--;
      if (str[0] == '0') decimalPointPosition = -1 * decimalPointPosition;
    }

    if (*spec == 'g' || *spec == 'G') {
      if (*accur == 0) *accur = 1;
      if ((-4 <= decimalPointPosition && decimalPointPosition < *accur) ||
          !decimalPointPosition) {
        *accur = *accur - decimalPointPosition - 1;
      } else {
        *accur -= 1;
        *spec -= 2;
        *exponenta = 1;
      }
    }

    if (*accur < 0) *accur = 0;
  }
}
int value_to_str(long double va_holder, char *str, long double val,
                 int *length) {
  int exceptional_сase = 0;
  if (isnan(va_holder)) {
    s_cat(str, "nan");
    exceptional_сase = 1;
  } else if (isinf(va_holder)) {
    if (isinf(va_holder) > 0) {
      s_cat(str, "inf");
    } else if (isinf(va_holder) < 0) {
      s_cat(str, "-inf");
    }
    exceptional_сase = 1;
  } else {
    double_to_str(va_holder, val, str, length);
  }
  return exceptional_сase;
}

void add_minus_Index(char *str, int index) {
  int number = 0;
  if (!(str[0] == '0' || index == 0)) number = index - 1;
  str[number] = '-';
}

void add_plus_Index(flags flags_struct, char *str, int index) {
  int number = 0;
  if (!(str[0] == '0' || index == 0)) {
    number = index - 1;
  }
  if (flags_struct.plus) {
    str[number] = '+';
  } else if (flags_struct.space) {
    str[number] = ' ';
  }
}
void clear_struct(flags *flags_struct) {
  flags_struct->length = 0;
  flags_struct->minus = 0;
  flags_struct->plus = 0;
  flags_struct->accur = 0;
  flags_struct->del = 0;
  flags_struct->space = 0;
  flags_struct->spec = 0;
  flags_struct->prec = 0;
  flags_struct->width = 0;
  flags_struct->zero = 0;
}
void insert_padding(char *res, flags flags_struct, int *index, int lens) {
  while (!flags_struct.minus &&
         (flags_struct.width -
              (flags_struct.accur > lens ? flags_struct.accur : lens) >
          0)) {
    if (!flags_struct.prec && flags_struct.zero)
      res[(*index)] = '0';
    else
      res[(*index)] = ' ';
    (*index)++;
    flags_struct.width--;
  }
}
/*
int main() {
  char buffer[MAX] = {'\0'}, buf[MAX] = {'\0'};

  short h = 34;


 // s21_sprintf(buffer, "Hello world%c%-+10d %% %s%05u %03llld %Lf\n", ch, n,
str,
        //      uns, n_l, fl);
sprintf(
      buf, "%-25.10d%-30.2d%10.12d%11d%*d%*.*d%+-25.*d%+10.2ld%-11.*hd", 253,
      335, 1234, 34, 10, 25, 5, 15, 345, 5, 666, 456789l, 5, h);
      s21_sprintf(
      buffer, "%-25.10d%-30.2d%10.12d%11d%*d%*.*d%+-25.*d%+10.2ld%-11.*hd", 253,
      335, 1234, 34, 10, 25, 5, 15, 345, 5, 666, 456789l, 5, h);


      if (s_len(buffer) == s_len(buf)){
for (int i = 0; i < (int)s_len(buffer); i++){
        if (buf[i] == buffer[i]){
                printf("%c", buffer[i]);
        }else{
                printf("error");
                break;
        }
}
}else{
        printf("go naxyi");
}

  printf("%s", buffer);
}*/
