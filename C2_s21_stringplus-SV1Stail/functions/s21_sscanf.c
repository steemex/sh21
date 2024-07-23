#include "s21_sscanf.h"

#include "../s21_string.h"
#include "string.h"

int s21_sscanf(const char *buf, const char *format, ...) {
  if (*buf == '\0') return -1;

  int totalcount = 0;

  char *str = malloc((s21_strlen(buf) + 1) * sizeof(char));
  s21_strncpy(str, buf, s21_strlen(buf) + 1);
  char *form = malloc((s21_strlen(format) + 1) * sizeof(char));
  s21_strncpy(form, format, s21_strlen(format) + 1);
  char *pbuf = str;
  char *pfor = form;

  va_list va;
  va_start(va, format);
  int count = 0;

  while (*pfor && (*pbuf == *pfor || *pfor == '%')) {
    if (*pfor == '%') {
      Token t;
      pfor = getToken(pfor, &t);
      int r = HandleToken(t, va, &pbuf, &count);
      if (r == -1) break;
      totalcount += r;
    } else {
      pbuf++;
      pfor++;
      count++;
    }
  }

  free(str);
  free(form);
  va_end(va);

  return totalcount;
}

int HandleToken(Token t, va_list va, char **buf, int *count) {
  int r = 0;
  switch (t.s) {
    case 'c':
      r = chandler(va, t, buf, count);
      break;
    case 'd':
    case 'i':
      r = dihandler(va, t, buf, count);
      break;
    case 'e':
    case 'E':
    case 'f':
    case 'g':
    case 'G':
      r = eEfgGhandler(va, t, buf, count);
      break;
    case 'o':
    case 'u':
    case 'x':
    case 'X':
      r = ouxXhandler(va, t, buf, count);
      break;
    case 's':
      r = shandler(va, t, buf, count);
      break;
    case 'p':
      r = phandler(va, t, buf, count);
      break;
    case 'n':
      r = nhandler(va, t, *count);
      break;
    case '%':
      r = perchandler(buf, count);
      break;
  }
  return r;
}

int perchandler(char **buf, int *count) {
  int r = 0;
  while (**buf && **buf == ' ') {
    (*buf)++;
    (*count)++;
  }
  if (**buf == '%') {
    (*count)++;
  } else
    r = -1;
  return r;
}

char *getToken(char *pfor, Token *t) {
  t->w = 0;
  if (*(++pfor) == '*') {
    t->w = 1;
    pfor++;
  }
  t->len = (*pfor > 47 && *pfor < 58) ? (*pfor++) - 48 : -1;
  while (*pfor > 47 && *pfor < 58) {
    t->len = t->len * 10 + (*(pfor++) - 48);
  }
  if (*pfor == 'h' || *pfor == 'l' || *pfor == 'L')
    t->l = *pfor++;
  else
    t->l = 0;
  t->s = *pfor++;
  return pfor;
}

int nhandler(va_list va, Token t, int count) {
  if (!t.w) {
    *(int *)va_arg(va, void *) = (int)count;
  }
  return 0;
}

int ouxXhandler(va_list va, Token t, char **buf, int *count) {
  int r = 0;
  char *ep = S21_NULL;
  unsigned long long d = 0;
  char *tmp = S21_NULL;
  if (t.len != -1) {
    tmp = malloc((t.len + 1) * sizeof(char));
    s21_strncpy(tmp, *buf, t.len);
    tmp[t.len] = '\0';
  } else
    tmp = *buf;
  if (t.s == 'u')
    d = strtoull(tmp, &ep, 10);
  else if (t.s == 'o')
    d = strtoull(tmp, &ep, 8);
  else if (t.s == 'x')
    d = strtoull(tmp, &ep, 16);
  else
    d = strtoull(tmp, &ep, 0);
  if (ep != tmp) {
    if (!t.w) {
      r++;
      if (t.l == 'h')
        *(unsigned short *)va_arg(va, void *) = (unsigned short)d;
      else if (t.l == 'l')
        *(unsigned long *)va_arg(va, void *) = (unsigned long)d;
      else if (t.l == 'L')
        *(unsigned long long *)va_arg(va, void *) = (unsigned long long)d;
      else
        *(unsigned *)va_arg(va, void *) = (unsigned)d;
    }
    if (t.len != -1) {
      *buf += t.len;
      free(tmp);
    } else {
      *count += ep - *buf;
      *buf = ep;
    }
  }
  return r;
}

int dihandler(va_list va, Token t, char **buf, int *count) {
  int r = 0;
  char *ep = S21_NULL;

  char *tmp = S21_NULL;
  if (t.len != -1) {
    tmp = malloc((t.len + 1) * sizeof(char));
    s21_strncpy(tmp, *buf, t.len);
    tmp[t.len] = '\0';
  } else
    tmp = *buf;

  long long int d =
      (t.s == 'd') ? strtoull(tmp, &ep, 10) : strtoull(tmp, &ep, 0);
  if (ep != *buf) {
    if (!t.w) {
      r++;
      if (t.l == 'h')
        *(short int *)va_arg(va, void *) = (short int)d;
      else if (t.l == 'l')
        *(long int *)va_arg(va, void *) = (long int)d;
      else if (t.l == 'L')
        *(long long int *)va_arg(va, void *) = (long long int)d;
      else
        *(int *)va_arg(va, void *) = (int)d;
    }
    if (t.len != -1) {
      *buf += t.len;
      free(tmp);
    } else {
      *count += ep - *buf;
      *buf = ep;
    }
  }
  return r;
}

int eEfgGhandler(va_list va, Token t, char **buf, int *count) {
  int r = 0;
  char *ep = S21_NULL;
  double d = 0;
  if (t.len != -1) {
    char *tmp = malloc((t.len + 1) * sizeof(char));
    s21_strncpy(tmp, *buf, t.len);
    tmp[t.len] = '\0';
    d = strtod(tmp, &ep);
    free(tmp);
    ep = *buf + t.len;
  } else
    d = strtold(*buf, &ep);
  if (ep != *buf) {
    if (!t.w) {
      r++;
      if (t.l == 'L')
        *(long double *)va_arg(va, void *) = d;
      else
        *(float *)va_arg(va, void *) = (float)d;
    }
    *count += ep - *buf;
    *buf = ep;
  }
  return r;
}

int shandler(va_list va, Token t, char **buf, int *count) {
  while (**buf == ' ') {
    (*buf)++;
    (*count)++;
  }
  int r = 0;
  int i = 0;
  char *temp = S21_NULL;
  if (t.len != -1) {
    temp = malloc(t.len + 1);
    for (i = 0; **buf && i < t.len && **buf != ' '; i++) {
      temp[i] = **buf;
      (*buf)++;
    }
    temp[t.len] = '\0';
  } else {
    temp = malloc(5000 * sizeof(char));
    while (**buf && **buf != ' ') {
      temp[i++] = **buf;
      (*buf)++;
    }
  }
  if (!t.w) {
    r++;
    s21_strncpy((char *)va_arg(va, void *), temp, s21_strlen(temp) + 1);
  }
  *count += i;
  free(temp);
  return r;
}

int phandler(va_list va, Token t, char **buf, int *count) {
  int r = 0;
  char *ep;
  char *tmp = S21_NULL;
  if ((**buf > 47 && **buf < 58) ||
      ((*buf)[0] == '0' && ((*buf)[1] == 'x' || (*buf)[1] == 'X'))) {
    if (t.len != -1) {
      tmp = malloc((t.len + 1) * sizeof(char));
      s21_strncpy(tmp, *buf, t.len);
      tmp[t.len] = '\0';
    } else
      tmp = *buf;

    unsigned long v = strtoul(tmp, &ep, 16);
    if (ep != tmp) {
      if (!t.w) {
        r++;
        *(void **)va_arg(va, void **) = (void *)v;
      }
      if (t.len != -1) {
        *buf += t.len;
        free(tmp);
      } else {
        *count = ep - *buf;
        *buf = ep;
      }
    }
  }
  return r;
}

int chandler(va_list va, Token t, char **buf, int *count) {
  int r = 0;
  if (!t.w) {
    r++;
    *(char *)va_arg(va, void *) = **buf;
    (*buf)++;
  } else
    (*buf)++;
  (*count)++;
  return r;
}