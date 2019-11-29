// Tokenizer

#include "Tokenizer.h"
#include <iostream>
#include <algorithm>

using namespace std;

// callback function
int isForwardSlash(int c)
{
   return (c == '/');
}

// Default delimiter can be found in Tokenizer.h
vector<string> split(const string& str, int delimiter(int))
{
   vector<string> result;
   // iterators to str
   auto e = end(str);
   auto i = begin(str);
   while (i != e)
   {
      // Find first char != delimiter
      i = find_if_not(i, e, delimiter);
      if (i != e)
      {
         // Find first char == delimiter
         auto j = find_if(i, e, delimiter);
         // Substring between i (begin) and j (end) added to result
         result.push_back(string(i, j));
         i = j;
      }
   }
   return result;
}
