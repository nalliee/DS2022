#include <iostream>
#include <vector>
#include <ctime>
#include "BinarySearchTree.h"

using namespace std;

template <typename Comparable>

void BSTSorting(vector<Comparable> &_arr, int _mode = 0)
{
  BinarySearchTree<Comparable> tree;
  clock_t start, end;
  double time = 0;
  if(_mode == 0)
  {
    //test the list rundown time of mode 0
    start = clock();
    for(int i = 0; i <_arr.size(); ++i)
    {
      tree.insert(_arr[i]);
    }
    end = clock();
    time = (double)(end-start)/CLOCKS_PER_SEC;
  }
  else if(_mode == 1) 
  {
    //test the list rundown time of mode 1
    for(int j = 0; j < 100; ++j)
    {
      tree.makeEmpty();
      start = clock();
      for(int i = _arr.size()-1; i >= 1; --i)
      {
        int k = random()%i;
        Comparable temp = _arr[k];
        _arr[k] = _arr[i];
        _arr[i] = temp;
      }
      // input list of integer
      for(int i = 0; i < _arr.size(); ++i)
      {
        tree.insert(_arr[i]);
      }
      end = clock();
      time += (double)(end-start)/CLOCKS_PER_SEC;
    }
  }
  // if list size is <= 10000, print the arranged list of tree
  if(_arr.size() <= 10000)
  {
    cout << "After sorting: " << endl;
    tree.printTree();
  }
  cout << "TIme for executing: " << time << "s" << endl;
}


int main()
{

  int mode;
  vector<int> _arr;

  cout << "Enter sorting mode: ";
  cin >> mode;
  
  //while mode is not 1 or 0, clear the mode and remind the user to enter 1 or 0
  while(cin.fail() || mode != 1 && mode != 0)
  {
    cin.clear();
    cin.ignore();
    cout << "Please enter 0 or 1." << "Enter sorting mode: ";
    cin >> mode;
  } 
  
  cout << "Enter your array: " << endl;
  for(int temp = 0; cin >> temp;)
  {
    _arr.push_back(temp);
    if(cin.get() == '\n') break;
  }
  if(_arr.size() == 1)
  {
    int length = _arr.back();
    _arr.pop_back();
    for(int temp = length; temp >= 1; temp--)
    {
      _arr.push_back(temp);
    }
  }
  BSTSorting(_arr,mode);
  return 0;
}

  
