// Hw-week13-1
#ifndef IOSTREAM_H_
#define IOSTREAM_H_
#include <iostream>
#endif

#include "sort.hpp"

int main(void) {
  int n;
  int rep=0;
  std::cin >> n;
  if (n==0) {
      std::cout << n << std::endl;
      return 0;
  }
  SET<int,int> *array = new SET<int, int>[n];
  if (!array) return 0;
  for (int i = 0; i < n; i++) {
    int x;
    std::cin >> x;
    array[i].key = x;
  }
  quickSort(array,0,n-1);

  for (int i = 1; i < n; i++) {
    if (array[i].key == array[i-1].key)
        rep++;
  }
  std::cout << n-rep << std::endl;
  return 0;

}

// test example: 1 1 2 2 2 2 3 3 3 3 4 4 5
// total: n
// repeated element(trivial): k
// result: n - k