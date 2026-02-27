#include <stdio.h>

#define GRID_SIZE 256
#define MAX_CODE_LENGTH 65536

int main()
{
  char code[MAX_CODE_LENGTH + 1];
  char grid[GRID_SIZE][GRID_SIZE];
  int x, y, ip, i, balance;
  
  for (y = 0; y < GRID_SIZE; y++)
  {
    for (x = 0; x < GRID_SIZE; x++)
    {
      grid[y][x] = 0;
    }
  }
  
  x = 0;
  y = 0;
  
  fgets(code, MAX_CODE_LENGTH, stdin);
  code[MAX_CODE_LENGTH] = 0;
  
  for (ip = 0; code[ip] != 0; ip++)
  {
    switch (code[ip])
    {
      case '^':
        y--;
        if (y < 0)
          y = GRID_SIZE - 1;
        break;
      case 'v':
        y++;
        if (y >= GRID_SIZE)
          y = 0;
        break;
      case '>':
        x++;
        if (x >= GRID_SIZE)
          x = 0;
        break;
      case '<':
        x--;
        if (x < 0)
          x = GRID_SIZE - 1;
        break;
      case '@':
        grid[y][x] ^= 1;
        break;
      case '{':
        if (grid[y][x] == 0)
        {
          balance = 1;
          for (i = ip + 1; code[i] != 0; i++)
          {
            switch (code[i])
            {
              case '{':
                balance++;
                break;
              case '}':
                balance--;
                break;
            }
            if (balance == 0)
            {
              ip = i;
              break;
            }
          }
        }
        break;
      case '}':
        if (grid[y][x] != 0)
        {
          balance = 1;
          for (i = ip - 1; i >= 0; i--)
          {
            switch (code[i])
            {
              case '{':
                balance--;
                break;
              case '}':
                balance++;
                break;
            }
            if (balance == 0)
            {
              ip = i;
              break;
            }
          }
        }
        break;
      default:
        break;
    }
  }
  
  return 0;
}
