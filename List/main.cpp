#include <iostream>
#include "DoubleLinkedList.h"

using namespace std;

DoubleLinkedList<int>::iterator find(DoubleLinkedList<int>& list, const int val)
{
  bool flag = false;
  typename DoubleLinkedList<int>::iterator b = list.begin();
  typename DoubleLinkedList<int>::iterator e = list.end();
  
  for (; b != e; ++b)
    {
      if (*b == val)
	{flag = true;
      break;
	}
    }
  if (!flag)
    b = e;
  return b;
  
}

void PrintList(const DoubleLinkedList<int> &l)
{
  DoubleLinkedList<int>::const_iterator itr;
  for(itr = l.begin(); itr != l.end(); ++itr)
    {
      cout << *itr << " ";
    }
  cout << endl;
}

int main()
{
  DoubleLinkedList<int> list;
  DoubleLinkedList<int>::iterator iter;
  for(int i = 1; i <= 5; ++i)
    {
      list.push_back(i);
    }
  
  PrintList(list);
  iter = find(list,3);
  list.erase(iter);
  PrintList(list);
  iter = find(list,3);

  return 0;
  
}
