// Copyright 2021 NNTU-CS
#ifndef INCLUDE_TPQUEUE_H_
#define INCLUDE_TPQUEUE_H_
#include <cassert>
template<typename T>
class TPQueue {
 private:
  T *arr;
  int size;
  int begin, end;
  int count;
  int stepBack(int index) {
    int res = --index;
    if (res < 0)
        res += size + 1;
    return res;
  }
  int stepForward(int index) {
    int res = ++index;
    if (res > size)
        res -= size + 1;
    return res;
  }
 public:
  TPQueue() :
    size(100),
    begin(0), end(0), count(0) {
    arr = new T[size + 1];
  }
  ~TPQueue() {
    delete[] arr;
  }
  void push(const T &item) {
    assert(count < size);
    if (count != 0 && item.prior > arr[count - 1].prior) {
    arr[end++] = item;
    count++;
    for (int i = 1; i< count; i++)
      if (arr[count - i].prior > arr[count - (i + 1)].prior) {
        T dub = arr[count - i];
        arr[count - i] = arr[count - (i + 1)];
        arr[count - (i + 1)] = dub;
      }
  } else {
    arr[end++] = item;
    count++;
  }
    if (end > size)
        end -= size + 1;
  }
  T pop() {
    assert(count > 0);
    T item = arr[begin];
    count--;
    begin = stepForward(begin);
    return item;
  }
  T get() const {
    assert(count > 0);
    return arr[begin];
  }
  bool isEmpty() const {
    return count == 0;
  }
  bool isFull() const {
    return count == size;
  }
};
struct SYM {
  char ch;
  int  prior;
};
#endif // INCLUDE_TPQUEUE_H_
