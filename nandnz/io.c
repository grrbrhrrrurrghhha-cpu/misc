#include <stdio.h>
long int code[] = {-1, 2, 0, 2, -1, 1, 5, 8, 0};
unsigned long int ip;

int main(void)
{
  while (code[ip + 2] >= 0)
  {
    if (code[ip] >= 0 && code[ip + 1] >= 0 && code[ip + 2] >= 0)
    {
      code[code[ip]] = ~(code[code[ip]] & code[code[ip + 1]]);
      if (code[code[ip]] != 0)
        ip = code[ip + 2];
      else
        ip += 3;
    }
    else if (code[ip] == -1 && code[ip + 1] >= 0)
    {
      code[code[ip + 1]] = getchar();
      ip += 3;
    }
    else if (code[ip + 1] == -1 && code[ip] >= 0)
    {
      putchar(code[code[ip]] & 0xFF);
      ip += 3;
    }
    else
    {
      return 1;
    }
  }
  
  return 0;
}
