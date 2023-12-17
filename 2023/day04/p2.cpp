#include <iostream>
#include <fstream>
#include <vector>
#include <map>
using namespace std;

struct Card
{
  static const int nWins = 10;
  static const int nNums = 25;
  int id;
  vector<int> winNums;
  vector<int> nums;
};

istream& operator>>(istream& is, Card& card);
int countWins(Card card);
int pow(int base, int exp);
Card copy(Card card);

int main()
{
  map<int, vector<Card>> cards;
  int numCards = 0;
  Card card;

  // read the cards in
  ifstream file("input.txt");
  while(file >> card && ++numCards)
    cards[numCards].push_back( card );

  // count and copy
  for(int i = 1; i <= numCards; i++)
  {
    for(int j = 0; j < cards[i].size(); j++)
    {
      int n2Spread = countWins(cards[i][j]);
      // disperse the wins among the remaining cards
      int ncardsRemaining = numCards - i;
      int idx = i + 1;
      // disperse the wins
      while(n2Spread--)
      {
        // card to copy
        Card cp = copy(cards[idx][0]);
        // add it to the card
        cards[idx].push_back( cp );

        // reset to the front
        if(++idx > numCards) idx = i + 1;
      }
    }
  }


  // count up the scratch cards
  int sum = 0;
  for(int i = 1; i <= numCards; i++)
  {
    sum += cards[i].size();
  }
  cout << sum << endl;

  return 0;
}

istream& operator>>(istream& is, Card& card)
{
  string junk;
  int num;

  // read "Card ##:"
  is >> junk >> junk;
  
  card.winNums.clear();
  for(int i = 0; i < card.nWins; i++)
  {
    is >> num;
    card.winNums.push_back( num );
  } 

  // " | "
  is >> junk;

  card.nums.clear();
  for(int i = 0; i < card.nNums; i++)
  {
    is >> num;
    card.nums.push_back( num );
  }

  return is;
}

int countWins(Card card)
{
  int count = 0;
  for(int i = 0; i < card.nWins; i++)
  {
    for(int j = 0; j < card.nNums; j++)
    {
      if(card.nums[j] == card.winNums[i])
        count++;
    }
  }
  return count;
}

int pow(int base, int exp)
{
  if(exp == 0)
    return 1;
  return base * pow(base, exp-1);
}

Card copy(Card card)
{
  Card newCard;
  newCard.winNums = vector<int>( card.winNums );
  newCard.nums = vector<int>( card.nums );
  return newCard; 
}
