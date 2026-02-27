#include <stdio.h>

#define GRID_SIZE 256
#define MAX_CODE_LENGTH 65536
/* #define DEBUG */


char code[MAX_CODE_LENGTH + 1];
char grid[GRID_SIZE][GRID_SIZE];
int x, y, ip, balance;

int main(void)
{
  x = 0;
  y = 0;
  
  if (fgets(code, MAX_CODE_LENGTH, stdin) == NULL)
    return 1;
  code[MAX_CODE_LENGTH] = 0;
  
  for (ip = 0; code[ip] != 0; ip++)
  {
    switch (code[ip])
    {
      case '^':
        y = (y - 1 + GRID_SIZE) % GRID_SIZE;
        break;
      case 'v':
        y = (y + 1) % GRID_SIZE;
        break;
      case '<':
        x = (x - 1 + GRID_SIZE) % GRID_SIZE;
        break;
      case '>':
        x = (x + 1) % GRID_SIZE;
        break;
      case '@':
        grid[y][x] ^= 1;
        break;
      case '{':
        if (grid[y][x] == 0)
        {
          balance = 1;
          for (ip++; code[ip] != 0; ip++)
          {
            switch (code[ip])
            {
              case '{':
                balance++;
                break;
              case '}':
                balance--;
                break;
            }
            if (balance == 0)
              break;
          }
        }
        break;
      case '}':
        if (grid[y][x] != 0)
        {
          balance = 1;
          for (ip--; ip >= 0; ip--)
          {
            switch (code[ip])
            {
              case '{':
                balance--;
                break;
              case '}':
                balance++;
                break;
            }
            if (balance == 0)
              break;
          }
        }
        break;
      default:
        break;
    }
  }
  
#ifdef DEBUG
  for (y = 0; y < GRID_SIZE; y++)
  {
    for (x = 0; x < GRID_SIZE; x++)
    {
      putchar(grid[y][x] ? '1' : '0');
    }
  }
#endif
  
  return 0;
}
