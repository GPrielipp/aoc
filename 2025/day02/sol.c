#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "../sol.h"
#include <string.h>

typedef struct {
  long long start;
  long long end;
} range_t;

range_t* next_range(FILE* file) {
  if(feof(file)) return NULL;

  // start-end,<next range>...,<last range>
  range_t* range = malloc(sizeof(*range));
  range->start = 0;
  range->end = 0;
  char str[2] = {0};
  char c;
  bool seenDash = false;
  while(!feof(file) && (c = fgetc(file)) != ',') {
    if(c == '\n' || c == ' ' || c == '\t' || c == -1) continue;
    str[0] = c;
    if(c == '-') seenDash = true;
    else if(seenDash){
      range->end *= 10;
      range->end += atoi(str);
    } else {
      range->start *= 10;
      range->start += atoi(str);
    }
  }

  return range;
}

void check_range(range_t* range, sol_t* sol) {
  // sequence of digits repeated twice
  // no leading zeros
  char str[64] = {0};

  for(long long num = range->start; num <= range->end; num++) {
    memset(str, 0, sizeof(str));

    snprintf(str, sizeof(str), "%lld", num);

    int slen = strlen(str);
    int half = slen / 2;
    if(slen % 2 == 0) {
      // compare first half to second half
      bool good = true;
      for(int i = 0; i < half; i++) {
        /*printf("%lld:\t%c == %c\n", num, str[i], str[half+i]);*/
        good = good && str[i] == str[half+i];
      }

      if(good) {
        /*printf("Invalid: %lld\n", num);*/
        sol->p1 += num;        
      }

    }

    // p2 (other sub patterns)
    char pat[64] = {0};
    char rep[64] = {0};
    for(int len = 1; len < half+1; len++) {
      if(slen % len == 0) {
        memset(pat, 0, sizeof(pat));
        memset(rep, 0, sizeof(rep));
        strncpy(pat, str, len);
        pat[len] = '\0';

        for(int i = 0; i < slen / len; i++) {
          strcat(rep, pat);
        }
        if(strcmp(rep, str) == 0) {
          /*printf("%s\t%s\t%lld\n", pat, rep, num);*/
          sol->p2 += num;
          break;
        }
      }
    }
  }
}

int main(int argc, char* argv[]) {
  if(argc != 2) {
    printf("usage: %s <input filepath>\n", argv[0]);
    return 1;
  }

  FILE* file = fopen(argv[1], "r");
  sol_t* sol = new_sol();

  range_t* range;
  while((range = next_range(file)) != NULL) {
    check_range(range, sol);

    free(range);
  }

  fclose(file);

  printf("part1: %lld\n", sol->p1);
  printf("part2: %lld\n", sol->p2);


  return 0;
}
