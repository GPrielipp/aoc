/* p2.cpp
 * GEORGE PRIELIPP */
#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
using namespace std;

struct Game
{
  int id;
  bool isgood;
  int r, g, b;
};

istream& operator>>(istream& is, Game& g);
bool ispossible(Game game, int ttl, int r, int g, int b);

constexpr int R = 12;
constexpr int G = 13;
constexpr int B = 14;
constexpr int TTL = R + G + B;

int main()
{
  Game g;

  ifstream file("input.txt");
  int sum = 0;
  while(file >> g)
  {
    sum += g.r*g.g*g.b;
  }

  cout << sum << endl;

  return 0;
}

istream& operator>>(istream& is, Game& g)
{
  char c;
  string junk;
  g.isgood = true;
  g.r = 0;
  g.g = 0;
  g.b = 0;

  // read the id 
  is >> junk >> g.id >> c;

  // the line
  stringstream ss;
  char word[4096]; //  should be big enough to read entire line
  is.getline(word, 4096, '\n');
  
  ss << word;

  // read the rest of the line into the game
  int num;
  string color;
  cout << ss.str() << endl;
  while(ss >> num >> color)
  {
    cout << ss.str() << endl; 
    if(color[0] == 'r')
    {
      g.r = max(g.r, num);
    }
    else if (color[0] == 'g')
    {
      g.g = max(g.g, num);
    }
    else if(color[0] == 'b')
    {
      g.b = max(g.b, num);
    }
  }

  return is;  
}

bool ispossible(Game game, int ttl, int r, int g, int b)
{
  return game.isgood;
}
