#include "priority_queue.hpp"

struct ReverseInt {
    int data;
    bool operator<(const ReverseInt &x) const {return data < x.data;}
    bool operator>(const ReverseInt &x) const {return data > x.data;}
};

/* Output the k largest number: minheap */
int main(void) {
  int n;
  int k;
  std::cin >> n >> k;
  PriorityQueue<struct ReverseInt> heapq;
  // First k numbers only enqueue
  for (int i = 0; i < k; i++) {
    struct ReverseInt x;
    std::cin >> x.data;
    heapq.enQueue(x);
  }
  for (int i = k; i < n; i++) {
    struct ReverseInt x;
    std::cin >> x.data;
    if (heapq.getTop() < x) {
        
        heapq.deQueue();
        heapq.enQueue(x);
    }
  }
  
  std::cout << heapq.getTop().data << std::endl;
  return 0;
}

// example: 7 1 | 5 9 8