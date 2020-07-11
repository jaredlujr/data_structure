/*
    Sorting algorithms
*/

#ifndef IOSTREAM_H_
#define IOSTREAM_H_
#include <iostream>
#endif

template <class KEY, class OTHER>
class SET {
 public:
  KEY key;
  OTHER other;
};

template <class KEY, class OTHER>
int partition(SET<KEY, OTHER> array[], int low, int high) {
  SET<KEY, OTHER> x = array[low];
  while(low < high) {
    // [<----] Find first element less than x.key, adpat "high"
    while (low < high && array[high].key >= x.key) high--;
    if (low < high) {
      array[low] = array[high]; 
      low++;
    }
    // [---->] FInd first element larger than x.key, adapt "low"
    while (low < high && array[low].key <= x.key) low++;
    if (low < high) {
      array[high] = array[low];
      high--;
    }
  } //while
  array[low] = x;
  return low;
}

/* Ascending order */
template <class KEY, class OTHER>
void quickSort(SET<KEY, OTHER> array[],int low, int high) {
  if(low>=high) return;
  int part = partition(array, low, high);
  quickSort(array, low, part);
  quickSort(array, part+1, high);
}