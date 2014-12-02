//Note: 不要过度包含头文件， 系统文件在前，自定义头文件在后
//尽量以Google的code style

#include "StringUtils.h"

char* Ken_i2a(unsigned i, char* a, unsigned r)
{
  if (i/r > 0) a = Ken_i2a(i/r, a, r);
  *a = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ"[i%r];
  return a + 1;
}
