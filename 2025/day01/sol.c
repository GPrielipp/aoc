#include <stdio.h>
#include <stdlib.h>
#include "../sol.h"

#define N 100

typedef struct {
  char dir;
  unsigned int dist;
} inst_t;

typedef struct {
  int numTimesClickZero;
  int remainder;
} mod_t;

inst_t* new_inst(char dir, unsigned int dist) {
  inst_t* inst = malloc(sizeof(*inst));
  inst->dir = dir;
  inst->dist = dist;
  return inst;
}

inst_t* read_inst(FILE* file) {
  char line[64] = {0};
  
  if (fgets(line, sizeof(line), file) != NULL) 
    return new_inst(line[0], atoi( line+1 ));
  else
    return NULL;
}

mod_t calc(inst_t* inst, int pos) {
  int dir = 1;
  if(inst->dir == 'L') dir = -1;
  else if(inst->dir == 'R') dir = 1;

  int clickedZero = 0;

  // spin the dial
  for(int i = 0; i < inst->dist; i++) {
    pos += dir;
  
    if(pos < 0)  pos = N-1;
    if(pos == N) pos = 0;
    if(pos == 0) clickedZero++;
}

  return (mod_t){.numTimesClickZero=clickedZero, .remainder=pos};
}

void solve(inst_t* inst, int* pos, sol_t* sol) {
  mod_t res = calc(inst, *pos);

  int old = *pos;
  
  *pos = res.remainder;

  printf("The dial is rotated %c%d from %d to point at %d; during this rotation, it points at zero %dx.\n", inst->dir, inst->dist, old, *pos, res.numTimesClickZero);

  sol->p2 += res.numTimesClickZero;

  if(*pos == 0) {
    sol->p1 ++;
  }
}

int main(int argc, char* argv[]) {
  if(argc != 2) {
    printf("usage: %s <input filepath>\n", argv[0]);
    return 1;
  }

  FILE* file = fopen(argv[1], "r");

  sol_t* sol = new_sol();

  int pos = 50;

  printf("The dial starts by pointing at %d\n", pos);

  inst_t* inst;
  while((inst = read_inst(file)) != NULL) {
    solve(inst, &pos, sol);
    free(inst);
  } 

  fclose(file);

  printf("part1: %lld\n", sol->p1);
  printf("part2: %lld\n", sol->p2);

  return 0;
}
