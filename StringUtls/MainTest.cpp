//Test code here

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdlib.h>

#ifdef __cplusplus
}
#endif

#include <iostream>
#include "StringUtils.h"

extern char* Ken_i2a(unsigned i, char* a, unsigned r);

int main(void)
{
  char a[100] = {0};
  char *end = Ken_i2a(10, a, 3); //将10转换为3进制
  *end = 0;
  printf("Ken_i2a(10, a, 3) result: %s\n", a);

  system("pause");
  return 0;
}
