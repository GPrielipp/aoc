#include <stdio.h>
#include <stdlib.h>
#include "../sol.h"
#include <string.h>

typedef struct {
  char batteries[104];
} bank_t;

bank_t* next_bank(FILE* file) {
  if(feof(file)) return NULL;

  bank_t* bank = malloc(sizeof(*bank));

  fgets(bank->batteries, sizeof(bank->batteries), file);
  size_t len = strlen(bank->batteries);
  bank->batteries[len-1] = '\0'; // get rid of newline

  for(int i = 0; i < len; i++) {
    char c = bank->batteries[i];
    int check = c - '0';
    if( !(check >= 0 && check <= 9) && c != 0) {
      free(bank);
      return NULL;
    }
  }

  return bank; 
}

typedef struct {
  int max, ind;
} pair_t;

pair_t nextMax(bank_t* bank, int len, int from, int bat, int using) {
  int max = 0;
  int ind;
  /*printf("nextMax(..., %d, %d, %d, %d)\n", len, from, bat, using);*/
  for(int i = from; i < len - (using - bat) + 1; i++) {
    int num = bank->batteries[i]-'0';
    if(num > max) { max = num; ind = i;}
  }
  return (pair_t){.max=max, .ind=ind};
}

void solve(bank_t* bank, sol_t* sol) {
  size_t len = strlen(bank->batteries);
  // p1
  pair_t pair = {.max=0, .ind=-1};
  long long val = 0;
  for(int i = 0; i < 2; i++) {
    val *= 10;
    pair = nextMax(bank, len, pair.ind+1, i, 2);
    val += pair.max; 
  }
  sol->p1 += val;
  // p2
  pair.max=0; 
  pair.ind=-1;
  val = 0;
  /*printf("looking at: '%s'\n", bank->batteries);*/
  for(int i = 0; i < 12; i++) {
    val *= 10;
    pair = nextMax(bank, len, pair.ind+1, i, 12);
    /*printf("chose: %d at %d\n", pair.max, pair.ind);*/
    val += pair.max; 
  }
  /*printf("val = '%lld'\n", val);*/
  sol->p2 += val;
}

int main(int argc, char* argv[]) {
  if(argc != 2) {
    printf("usage: %s <input filepath>\n", argv[0]);
    return 1;
  }

  FILE* file = fopen(argv[1], "r");

  sol_t* sol = new_sol();
  
  bank_t* bank;
  while((bank = next_bank(file)) != NULL) {
    solve(bank, sol);

    free(bank);
  }

  fclose(file);
  
  printf("part1: %lld\n", sol->p1);
  printf("part2: %lld\n", sol->p2);

  return 0;
}
