// Copyright [2020] Lu JiaRui

#include <iostream>


class HashTable {
 public:
  HashTable(int m, int n, int p);
  ~HashTable() {
    delete [] data_;
  }
  void Insert(int key);
  int Find(int key) const;
  void PrintTable(void) const;
  void PrintProbeTime(void) const;
 private:
  int *data_;
  int *probe_times_;
  int table_size_;
  int length_;
  int prime_;
  int Hash(int key) const;
};

HashTable::HashTable(int m, int n, int p) :
table_size_(m), length_(n), prime_(p) {
  data_ = new int[m];
  probe_times_ = new int[m];
  for (int i = 0; i < table_size_; i++) {
    data_[i] = -1;  // Intact flag
    probe_times_[i] = 0;  // Probing times to insert each element
  }
}

int HashTable::Hash(int key) const {
  return key % prime_;
}

int HashTable::Find(int key) const {
  int location;  // Location of <key> in Hash Table [0,...,n-1]
  int primal_location;

  location = Hash(key);
  if (data_[location] == -1) return -1;

  primal_location = location;
  while (location < table_size_) {
    if (data_[location] == key) return location;
    location++;
  }
  // From the beginning of the table
  location = 0;
  while (location < primal_location) {
    if (data_[location] == key) return location;
    location++;
  }
  return -1;  // Nothing found
}

void HashTable::Insert(int key) {
  int location;
  int primal_location;
  int probe_count;
  
  location = Hash(key);
  primal_location = location;
  probe_count = 1;
  while (location < table_size_) {
    if (data_[location] == -1) {
      data_[location] = key;
      probe_times_[location] = probe_count;
      return;
    }
    location++;
    probe_count++;
  }
  // From the beginning of the table
  location = 0;
  while (location < primal_location) {
    if (data_[location] == -1) {
      data_[location] = key;
      probe_times_[location] = probe_count;
      return;
    }
    location++;
    probe_count++;
  }
}

void HashTable::PrintTable(void) const {
  for (int i = 0; i < table_size_; i++) {
    std::cout << data_[i] << ' ';
  }
  std::cout << std::endl;
}

void HashTable::PrintProbeTime(void) const {
  for (int i = 0; i < table_size_; i++) {
    std::cout << probe_times_[i] << ' ';
  }
  std::cout << std::endl;
}

int main(void) {
  int p,m,n,x;
  std::cin >> p >> m >> n;
  HashTable ht(m,n,p);
  for (int i = 0; i < n; i++) {
    std::cin >> x;
    ht.Insert(x);
  }
  
  for (int i = 0; i < m; i++)
    std::cout << i << ' ';
  std::cout << std::endl;

  ht.PrintTable();
  ht.PrintProbeTime();
  std::cout << "Find for <25>: " << ht.Find(25) << std::endl;
  return 0;
}