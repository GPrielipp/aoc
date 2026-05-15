import sys, os, re

def solve1(filename):
  beams = set()
  numSplits = 0
  numWorlds = list()
  with open(filename, 'r') as file:
    for idx, line in enumerate(file.readlines()):
      line = line.strip()

      if idx == 0:
        startBeam = line.index('S')
        beams.add( startBeam )
        numWorlds = [0 for _ in range(len(line))]
        numWorlds[ startBeam ] = 1
      else:
        splitters = [match.start() for match in re.finditer(r'\^', line)]
        
        for splitter in splitters:
          if splitter in beams:
            beams.remove(splitter)
            # split the beam
            left, right = splitter - 1, splitter + 1

            beams.add(left)
            beams.add(right)

            curPath = numWorlds[splitter]
            numWorlds[splitter] = 0
            numWorlds[left] += curPath
            numWorlds[right] += curPath

            numSplits += 1

  return numSplits, sum(numWorlds)

if __name__ == '__main__':
  if len(sys.argv) != 2:
    print(f'usage: {sys.argv[0]} <filename>')
    exit(1)
  
  filename = sys.argv[1]

  if not os.path.isfile(filename):
    print(f'Error opening "{filename}"')
    exit(1)

  print('part 1 + 2:', solve1(filename))