#include <iostream>
#include <string>
#include <vector>

using namespace std;

string haystack;
string needle;
vector<size_t> table;

void Pre(const string& needle, vector<size_t>& table)
{
  table.assign(needle.size(), 0);

  size_t begin = 1;
  size_t matched = 0;

  while (begin + matched < needle.size())
  {
    if (needle[begin + matched] == needle[matched])
    {
      ++matched;
      table[begin + matched - 1] = matched;
    }
    else
    {
      if (matched == 0)
      {
        ++begin;
      }
      else
      {
        begin += matched - table[matched - 1];
        matched = table[matched - 1];
      }
    }
  }
}

size_t Kmp(const string& haystack, const string& needle, const vector<size_t>& table)
{
  size_t begin = 0;
  size_t matched = 0;
  while (begin + needle.size() <= haystack.size())
  {
    if (haystack[begin + matched] == needle[matched])
    {
      ++matched;

      if (matched == needle.size())
      {
        return 1;
      }
    }
    else
    {
      if (matched == 0)
      {
        ++begin;
      }
      else
      {
        begin += matched - table[matched - 1];
        matched = table[matched - 1];
      }
    }
  }

  return 0;
}

int main(void)
{
  // For Faster IO
  ios_base::sync_with_stdio(false);
  cout.tie(nullptr);
  cin.tie(nullptr);

  // Read input
  cin >> haystack >> needle;

  // Solve
  Pre(needle, table);
  cout << Kmp(haystack, needle, table) << '\n';

  return 0;
}
