#include <stdio.h>
#include <stdlib.h>
#include "../sol.h"

int main(int argc, char* argv[]) {
  if(argc != 2) {
    printf("usage: %s <input filepath>\n", argv[0]);
    return 1;
  }

  FILE* file = fopen(argv[1], "r");

  sol_t* sol = new_sol();

  fclose(file);
  
  printf("part1: %lld\n", sol->p1);
  printf("part2: %lld\n", sol->p2);

  return 0;
}
