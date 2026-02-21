#include <iostream>
#include <bitset>
#include <vector>
#include <random>
#include <string>

static std::string target = ""; // paste target here

static char commands[10][10] = {
  {'S', -1, 'Y', '-', -1, -1, -1, -1, '+', -1},
  {-1, -1, -1, -1, -1, -1, -1, '-', -1, '>'},
  {'>', -1, -1, -1, -1, -1, '+', -1, -1, -1},
  {-1, -1, -1, -1, -1, -1, ',', -1, -1, -1},
  {-1, ']', -1, '#', -1, '[', -1, 'S', -1, -1},
  {-1, '&', -1, -1, -1, -1, -1, -1, -1, -1},
  {-1, 'E', -1, -1, -1, -1, -1, -1, -1, '['},
  {']', '.', -1, -1, -1, -1, -1, -1, -1, -1},
  {-1, -1, -1, -1, '<', -1, '@', -1, -1, '<'},
  {-1, -1, -1, 'L', -1, ':', -1, -1, -1, -1}
};

inline int mod256(int a) {
  return (a % 256 + 256) % 256;
}

inline int mod16(int a) {
  return (a % 16 + 16) % 16;
}

inline int f(uint8_t x) {
  return ((int)x * 91 + 114514) * 77;
}

int g(int x) {
  int result = 0;
  std::bitset<32> bits(x);
  for (int i = 0; i < 32; i++) {
    if (bits[i]) {
      result += i + 1;
    }
  }
  return result % 10;
}

char getCommand(uint8_t a, uint8_t b) {
  int c = (uint8_t)mod256(a * b + 191980);
  int d = (uint8_t)mod256(b * b * b - 35);
  int e = (uint8_t)((mod16(c) ^ mod16(a)) * (mod16(c) ^ mod16(a)));
  int c_ = (uint8_t)(mod256(c - e) ^ a);
  int d_ = (uint8_t)(mod256(d * e) ^ a);
  
  return commands[g(c_ + d)][g(d_ + e + c)];
}

int main() {
  size_t len = 0;
  int tick = 0;
  std::vector<uint8_t> code(target.length() + 1);
  std::random_device rd;
  std::mt19937 rng(rd());
  
  while (len < code.size() - 1) {
    if (len > 0)
      len--;
    tick = 0;
    while (len < code.size() - 1 && tick < 256) {
      if (len == 0)
        code[len] = rng() % 256;
      code[len + 1] = rng() % 256;
      if (getCommand(mod256(f(code[len])), \
      mod256(f(code[len + 1]) + len + 1)) == target[len]) {
        len++;
      }
      tick++;
    }
  }
  
  for (size_t i = 0; i < code.size(); i++) {
    std::cout << (int)code[i];
    if (i != code.size() - 1)
      std::cout << ", ";
  }
  std::cout << std::endl;
  
  return 0;
}
