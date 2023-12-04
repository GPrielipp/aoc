#include <iostream>
#include <fstream>
using namespace std;

int parse(string line);

int main()
{
  int sum = 0;
  ifstream file("input.txt");
  string line;

  while(file >> line)
    sum += parse(line);

  cout << sum << endl;
}

// parses a number out of a string like 
// first and last digit
// 1abc2 -> 12
// a1b2c3d4e5 -> 15 
int parse(string line)
{
  int first = -1;
  int last = 0;
  for(char c : line)
  {
    if(c <= '9' && c >= '0')
    {
      if(first < 0)
        first = c-'0';
      last = c-'0';
    } 
  }
  return first*10 + last;
}
