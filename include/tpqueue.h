// Copyright 2021 NNTU-CS
#ifndef INCLUDE_TPQUEUE_H_
#define INCLUDE_TPQUEUE_H_
#include <cassert>

template<typename T>
class TPQueue {
  // Сюда помещается описание структуры "Очередь с приоритетами"
 private:
    T* arr;
    int size;
    int begin, end;
    int count;
    int step_back(int index) {
        int res = --index;
        if (res < 0)
            res += size + 1;
        return res;
    }
    int step_forward(int index) {
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

    void push(const T& item) {
        assert(count < size);
        if (isEmpty()) {
            arr[end] = item;
        } else {
            int cur = step_back(end);
            if (arr[cur].prior >= item.prior) {
                arr[end] = item;
            } else {
                do {
                    arr[step_forward(cur)] = arr[cur];
                    cur = step_back(cur);
                } while (arr[cur].prior < item.prior &&
                    step_forward(cur) != begin);
                arr[step_forward(cur)] = item;
            }
        }
        end = step_forward(end);
        count++;
    }

    T pop() {
        assert(count > 0);
        T item = arr[begin];
        count--;
        begin = step_forward(begin);
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
