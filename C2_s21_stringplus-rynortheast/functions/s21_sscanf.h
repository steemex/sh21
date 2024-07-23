#include <stdarg.h>
#include <stdlib.h>

typedef struct Token {
  int w;
  int len;
  int l;
  int s;
} Token;

int HandleToken(Token t, va_list va, char **buf, int *count);

int perchandler(char **buf, int *count);
int phandler(va_list va, Token t, char **buf, int *count);
int chandler(va_list va, Token t, char **buf, int *count);
int dihandler(va_list va, Token t, char **buf, int *count);
int eEfgGhandler(va_list va, Token t, char **buf, int *count);
int ouxXhandler(va_list va, Token t, char **buf, int *count);
int shandler(va_list va, Token t, char **buf, int *count);
int nhandler(va_list va, Token t, int count);

char *getToken(char *pfor, Token *t);