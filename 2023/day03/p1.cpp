#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

struct point
{
  char adj;
  int val;

  bool operator==(point other)
  {
    return other.adj == adj && other.val == val;
  }
};

vector<point> neighbors(vector<string> engine, int row, int col);
point getpoint(vector<string> engine, char adj, int row, int col);
bool isdigit(char c);

int main()
{
  // read the input file
  ifstream file("input.txt");
  
  vector<string> engine;
  string line;
  while(file >> line)
    engine.push_back(line);

  for(int i = 0; i < engine.size(); i++)
  {
    for(int j = 0; j < engine[i].length(); j++)
      cout << engine[i][j];
    cout << endl;
  }

  // loop through the characters
  // find the non-dots and create a vector with those points
  vector<point> points;
  for(int line = 0; line < engine.size(); line++)
  {
    for(int col = 0; col < engine[line].length(); col++)
    {
      char c = engine[line][col];
      //if(c == '*') cout << line << " " << col << "LOOK HERE <== " << endl;
      if(c != '.' && !isdigit(c))
      {
        //cout << "found: " << c << " (" << line << ", " << col << ")" << endl;
        vector<point> ns = neighbors(engine, line, col);       
        
        // add the neighbors to the points
        points.insert(points.end(), ns.begin(), ns.end());
        //cout << "points.size() = " << points.size() << endl;
      }
    }
  }

  // sum up the points
  int sum = 0;
  for(point p : points)
  {
    sum += p.val;
  }

  cout << sum << endl;

  return 0;
}

vector<point> neighbors(vector<string> engine, int row, int col)
{
  vector<point> ns;
  
  // check the 3x3
  cout << endl;
  cout << "STARTING FROM: (" << row << ", " << col << ")" << endl;
  for(int i = -1; i <= 1; i++)
  {
    for(int j = -1; j <= 1; j++)
    {
      // check bounds
      if(row + i < engine.size() && row + i >= 0 &&
         col + j < engine[row].length() && col + j >= 0 &&
         !(i == 0 && j == 0))
      {
        cout << "CHECKING: (" << row+i << ", " << col+j << ") = " << engine[row+i][col+j] << " isdigit? " << (isdigit(engine[row+i][col+j]) ? "yes":"no") << endl;
        if(isdigit(engine[row+i][col+j]))
        {
          //cout << "found digit: (" << row + i << ", " << col + j << ") => " << engine[row+i][col+j] << endl;
          ns.push_back( getpoint(engine, engine[row][col], row + i, col + j) );
        }
      }
    }
  }
  cout << endl;

  // filter out the uniques
  sort(ns.begin(), ns.end(), [=](point a, point b){ return a.val > b.val; });
  auto it = unique(ns.begin(), ns.end());
  ns.resize(distance(ns.begin(), it));

  return ns;
};

point getpoint(vector<string> engine, char adj, int row, int col)
{
  //cout << "searching: (" << row << ", " << col << ")" << endl;
  // need to check along the col
  point p;
  p.adj = adj;

  // get left bound
  int left = col;
  for(int i = col; i >= 0 && isdigit(engine[row][i]); i--)
  {
    //cout << engine[row][i];
    left = i;
  }
  //cout << " left " << left << endl;

  // get right bound
  int right = col;
  for(int i = col; i < engine[row].length() && isdigit(engine[row][i]); i++)
  {
    //cout << engine[row][i];
    right = i;
  }
  //cout << " right " << right << endl;

  // convert bounds to int
  p.val = 0;
  for(int i = left; i <= right; i++)
  {
    p.val += engine[row][i] - '0';
    if(right - i > 0)
      p.val *= 10;
  }
   
  cout << "point found: (" << p.val << ", \'" << p.adj << "\')" << endl;

  return p;
}

bool isdigit(char c)
{
  //cout << "isdigit(" << c << ")" << endl;
  return c >= '0' && c <= '9';
}
