import sys, os, re

import math, functools, itertools, heapq
def dist(A, B):
  return math.sqrt( sum([ pow(a-b, 2) for a,b in zip( A, B )] ) )

class DisjointSet:
  def __init__(self, elements):
    self.map = { el: i for i, el in enumerate(elements) }
    self.elements = list(elements)
    self.parents = [i for i in range(len(elements))]
  
  def find(self, el) -> int:
    p = self.map[el]

    while p != self.parents[p]:
      p = self.parents[p]
    
    return p

  def union(self, setA, setB) -> None:
    self.parents[self.find(setA)] = self.find(setB)

  def sets(self) -> list:
    sets = {}
    
    for el in self.elements:
      root = self.find(el)
      if root not in sets:
        sets[root] = []
      sets[root].append(self.map[el])

    return list(sets.values())

  def __repr__(self) -> str:
    return str(self)
  
  def __str__(self) -> str:
    return ' '.join([str(x) for x in range(len(self.elements))]) + '\n' + ' '.join([str(x) for x in self.parents])

def read_file(filename):
  # read the data
  points = []
  with open(filename, 'r') as file:
    for idx, line in enumerate(file.readlines()):
      line = line.strip()

      point = tuple(int(x) for x in line.split(','))
      points.append(point)

  return points

def mul(l: list):
  tot = 1
  for e in l:
    tot *= e
  return tot

def solve(filename, iterations):
  points = read_file(filename)

  ds = DisjointSet(points)

  combos = sorted(itertools.combinations(points, 2), key=lambda x: dist(x[0], x[1]))

  # print('\n'.join([str(x) for x in combos[:10:]]))

  for i in range(iterations):
    a, b = combos[i]
    ds.union( a, b )

  sets = ds.sets()
  sets.sort(key=lambda x: len(x), reverse=True)

  part1 = mul([len(x) for x in sets[:3]])

  # this portion may take too long ... may need to keep track of the sets with each union
  part2 = 0
  for a, b in combos[iterations:]:
    ds.union(a,b)

    sets = ds.sets()
    if len(sets) == 1:
      part2 = a[0] * b[0]
      break


  return part1, part2

if __name__ == '__main__':
  if len(sys.argv) != 3:
    print(f'usage: {sys.argv[0]} <filename> <iterations>')
    exit(1)
  
  filename = sys.argv[1]
  iterations = int(sys.argv[2])

  if not os.path.isfile(filename):
    print(f'Error opening "{filename}"')
    exit(1)

  print('part 1 + 2:', solve(filename, iterations))