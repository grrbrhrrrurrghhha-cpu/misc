#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define CV 0
#define CVC 1
#define CCV 2

#define SVO 0
#define SOV 1
#define VSO 2
#define VOS 3
#define OSV 4
#define OVS 5

#define BEFORE_NOUN 0
#define AFTER_NOUN 1

#define PARTICLE_PLURAL 0
#define PARTICLE_AFFIX 1

#define TOTAL_VOWELS 7
#define TOTAL_CONSONANTS 28

#define LIST_SIZE (sizeof(swadeshList) / sizeof(swadeshList[0]))
#define VOCABULARY_SIZE 100

static char* swadeshList[LIST_SIZE] = {"I", "you", "we", "this", "that", "who", "what", "not", "all", "many", "one", "two", "big", "long", "small", "woman", "man", "person", "fish", "bird", "dog", "louse", "tree", "seed", "leaf", "root", "bark", "skin", "flesh", "blood", "bone", "grease", "egg", "horn", "tail", "feather", "hair", "head", "ear", "eye", "nose", "mouth", "tooth", "tongue", "claw", "foot", "knee", "hand", "belly", "neck", "breast", "heart", "liver", "drink", "eat", "bite", "see", "hear", "know", "sleep", "die", "kill", "swim", "fly", "walk", "come", "lie", "sit", "stand", "give", "say", "sun", "moon", "star", "water", "rain", "stone", "sand", "earth", "cloud", "smoke", "fire", "ash", "burn", "path", "mountain", "red", "green", "yellow", "white", "black", "night", "hot", "cold", "full", "new", "good", "round", "dry", "name", "plural particle", "past particle", "present particle", "future particle", "question particle", "yes", "no"};

char* generateSyllable(int type, int vowelCount, \
  int consonantCount, char* vowels[], char* consonants[])
{
  char *a, *randomVowel, *randomConsonant, *randomConsonant1, \
    *randomConsonant2;
  switch (type)
  {
    case CV:
        randomVowel = vowels[rand() % vowelCount];
        randomConsonant = consonants[rand() % consonantCount];
        a = 
          malloc(strlen(randomConsonant) + strlen(randomVowel) + 1);
        strcpy(a, randomConsonant);
        strcpy(a + strlen(randomConsonant), randomVowel);
        a[strlen(randomConsonant) + strlen(randomVowel)] = 0;
      break;
    case CVC:
        randomVowel = vowels[rand() % vowelCount];
        randomConsonant1 = consonants[rand() % consonantCount];
        randomConsonant2 = consonants[rand() % consonantCount];
        a = 
          malloc(strlen(randomConsonant1) + strlen(randomVowel) + \
          strlen(randomConsonant2) + 1);
        strcpy(a, randomConsonant1);
        strcpy(a + strlen(randomConsonant1), randomVowel);
        strcpy(a + strlen(randomConsonant1) + strlen(randomVowel), \
          randomConsonant2);
        a[strlen(randomConsonant1) + strlen(randomVowel) + \
        strlen(randomConsonant2)] = 0;
      break;
    case CCV:
        randomVowel = vowels[rand() % vowelCount];
        randomConsonant1 = consonants[rand() % consonantCount];
        randomConsonant2 = consonants[rand() % consonantCount];
        a = 
          malloc(strlen(randomConsonant1) + strlen(randomVowel) + strlen(randomConsonant2) + 1);
        strcpy(a, randomConsonant1);
        strcpy(a + strlen(randomConsonant1), randomConsonant2);
        strcpy(a + strlen(randomConsonant1) + strlen(randomConsonant2), randomVowel);
        a[strlen(randomConsonant1) + strlen(randomVowel) + strlen(randomConsonant2)] = 0;
      break;
    default:
      return "Unknown syllable type!";
      break;
  }
  return a;
}

void generateVocabulary(char* b[], int type, int vowelCount, \
  int consonantCount, char* vowels[], char* consonants[])
{
  for (int i = 0; i < LIST_SIZE; i++)
  {
    bool repeats = true;
    while (repeats)
    {
      b[i] = generateSyllable(type, vowelCount, consonantCount, \
        vowels, consonants);
      repeats = false;
      for (int j = 0; j < i; j++)
        repeats = repeats || (strcmp(b[j], b[i]) == 0);
    }
  }
}

void choose(int n1, int n2, char* a[], char* b[])
{
  for (int i = 0; i < n1; i++)
  {
    bool repeats = true;
    while (repeats)
    {
      b[i] = a[rand() % n2];
      repeats = false;
      for (int j = 0; j < i; j++)
        repeats = repeats || (strcmp(b[j], b[i]) == 0);
    }
  }
}

int main()
{
  srand(time(NULL));
  char* vowels[] = {"a", "ae", "e", "i", "o", "oe", "u"};
  char* consonants[] = {"q", "w", "r", "t", "th", "y", "p", "ph", \
    "s", "sh", "d", "dh", "f", "g", "gh", "h", "j", "k", "kh", "l", \
    "z", "zh", "x", "c", "v", "b", "n", "m"};
  int vowelCount = (rand() % 3) + 5;
  int consonantCount = (rand() % 13) + 12;
  char* conlangVowels[vowelCount];
  char* conlangConsonants[consonantCount];
  int syllableType = rand() % 3;
  char* words[LIST_SIZE];
  int wordOrder = rand() % 6;
  int adjectivePosition = rand() % 2;
  int pluralType = rand() % 2;
  char *part1, *part2;

  choose(vowelCount, TOTAL_VOWELS, vowels, conlangVowels);
  printf("Vowels chosen: ");
  for (int i = 0; i < vowelCount; i++)
  {
    printf("%s ", conlangVowels[i]);
  }
  printf("\n");

  choose(consonantCount, TOTAL_CONSONANTS, consonants, \
    conlangConsonants);
  printf("Consonants chosen: ");
  for (int i = 0; i < consonantCount; i++)
  {
    printf("%s ", conlangConsonants[i]);
  }
  printf("\n");
  
  printf("Syllable structure chosen: ");
  switch (syllableType)
  {
    case CV:
      printf("CV\n");
      break;
    case CVC:
      printf("CVC\n");
      break;
    case CCV:
      printf("CCV\n");
      break;
    default:
      printf("Error: Unknown type\n");
      return 1;
      break;
  }
  
  printf("Word order chosen: ");
  switch (wordOrder)
  {
    case SVO:
      printf("SVO\n");
      break;
    case SOV:
      printf("SOV\n");
      break;
    case VSO:
      printf("VSO\n");
      break;
    case VOS:
      printf("VOS\n");
      break;
    case OSV:
      printf("OSV\n");
      break;
    case OVS:
      printf("OVS\n");
      break;
    default:
      printf("Error: Unknown type\n");
      return 1;
      break;
  }
  
  printf("Adjective position chosen: ");
  switch (adjectivePosition)
  {
    case BEFORE_NOUN:
      printf("before noun\n");
      break;
    case AFTER_NOUN:
      printf("after noun\n");
      break;
    default:
      printf("Error: Unknown type\n");
      return 1;
      break;
  }
  
  printf("Plural type chosen: ");
  switch (pluralType)
  {
    case PARTICLE_PLURAL:
      printf("plural\n");
      break;
    case PARTICLE_AFFIX:
      printf("affix\n");
      break;
    default:
      printf("Error: Unknown type\n");
      return 1;
      break;
  }
  
  generateVocabulary(words, syllableType, vowelCount, consonantCount, \
    conlangVowels, conlangConsonants);
  for (int i = 0; i < LIST_SIZE; i++)
  {
    printf("%s: %s\n", swadeshList[i], words[i]);
  }
  
  part1 = words[rand() % VOCABULARY_SIZE];
  part2 = words[rand() % VOCABULARY_SIZE];
  printf("Name Chosen: %s%s\n", part1, part2);
  
  return 0;
}
