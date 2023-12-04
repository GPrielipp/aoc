/* p2.cpp 
 * GEORGE PRIELIPP */

#include <iostream>
#include <fstream>
using namespace std;

int parse(string line);
int checkword(int couldbe, int ind, string word, string line);

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
  for(int i = 0; i < line.length(); i++)
  {
    char c = line[i];
    int num = -1;
    switch(c)
    {
      case 'o': // one
        num = checkword(1, i, "one", line);
        break;
      case 't': // two or three
        num = checkword(2, i, "two", line);
        if(num == -1)
          num = checkword(3, i, "three", line);
        break;
      case 'f': // four or five
        num = checkword(4, i, "four", line);
        if(num == -1)
          num = checkword(5, i, "five", line);
        break;
      case 's': // six or seven
        num = checkword(6, i, "six", line);
        if(num == -1)
          num = checkword(7, i, "seven", line);
        break;
      case 'e': // eight
        num = checkword(8, i, "eight", line);
        break;
      case 'n': // nine
        num = checkword(9, i, "nine", line);
        break;
    }

    if(num > -1 && first < 0)
    {
      first = num;
      last = num;
    }
    else if(num > -1)
    {
      last = num;
    }
    else if(c <= '9' && c >= '0')
    {
      if(first < 0)
        first = c-'0';
      last = c-'0';
    } 
  }
  return first*10 + last;
}

int checkword(int couldbe, int ind, string word, string line)
{
  for(int i = 0; i < word.length(); i++)
  {
    if(word[i] != line[ind + i])
      return -1;
  } 
  return couldbe;
}
