long int code[] = {0, 0, -1};
unsigned long int ip;

int main(void)
{
  while (code[ip + 2] >= 0)
  {
    code[code[ip]] = ~(code[code[ip]] & code[code[ip + 1]]);
    if (code[code[ip]] != 0)
      ip = code[ip + 2];
    else
      ip += 3;
  }
  
  return 0;
}
