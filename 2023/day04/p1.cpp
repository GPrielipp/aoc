#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

int num_matches(vector<int> win, vector<int> nums);
int pow(int base, int exp);
istream& operator>>(istream& is, vector<int>& card);

int main()
{
  vector<int> card;
  vector<int> wins;

  // calc the sum
  int sum = 0;
  ifstream file;
  file.open("input.txt", ios::in);
  string j;
  char pipe;
  for(int k = 0; k < 198; k++)
  {
    file >> j >> j;

    int num;
    wins.clear(); 
    // read in win
    for(int i = 0; i < 10 && file >> num; i++) 
      wins.push_back(num);

    file >> pipe;

    // read in card
    card.clear();
    for(int i = 0; i < 25 && file >> num; i++) 
      card.push_back(num);
     
    int num_match = num_matches(wins, card);
    cout << "MATCH: " << num_match << " " << "SCORE: " << pow(2, num_match-1) << " "; 
    sum += pow(2, num_match-1);
    cout << "SUM: " << sum << endl;
  }
  file.close();

  cout << sum << endl;

  return 0;
}

int num_matches(vector<int> win, vector<int> nums)
{
  int match = 0;
  for(int w = 0; w < win.size(); w++)
  {
    for(int n = 0; n < nums.size(); n++)
    {
      if(win[w] == nums[n]) match++;
    }
  }
  return match;
}

int pow(int base, int exp)
{
  if(exp < 0)
    return 0;
  if(exp == 0)
    return 1;
  return base * pow(base, exp-1);
}

istream& operator>>(istream& is, vector<int>& card)
{
  card = vector<int>();
  int num;
  while(is >> num)
    card.push_back(num);

  return is;
}
