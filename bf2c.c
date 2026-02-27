#include <stdio.h>

int main(int argc, char** argv)
{
  int c;
  FILE* program;
  
  if (argc > 1)
  {
    program = fopen(argv[1], "r");
    if (program == NULL)
    {
      printf("?\n");
      return 1;
    }
  }
  else
  {
    printf("?\n");
    return 1;
  }
  
  c = getc(program);
  
  printf("#include <stdio.h>\nunsigned char t[30000];int p;\nint main(){");
  
  while (c != EOF)
  {
    switch (c)
    {
      case '+':
        printf("t[p]++;");
        break;
      case '-':
        printf("t[p]--;");
        break;
      case '>':
        printf("p++;");
        break;
      case '<':
        printf("p--;");
        break;
      case '.':
        printf("putchar(t[p]);");
        break;
      case ',':
        printf("t[p]=getchar();");
        break;
      case '[':
        printf("while(t[p]){");
        break;
      case ']':
        printf("}");
        break;
       default:
         break;
    }
    c = getc(program);
  }
  printf("}\n");
  
  return 0;
}
