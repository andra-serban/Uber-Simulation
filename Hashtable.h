// Copyright Andra Serban
#ifndef HASHTABLE_H_
#define HASHTABLE_H_

#include <list>
#include <iterator>
#include <iostream>

template <typename Tkey, typename Tvalue> struct info {
  Tkey key;
  Tvalue value;
};

template <typename Tkey, typename Tvalue> class Hashtable {
 private:
  std::list<struct info<Tkey, Tvalue>> *H;
  int size;
  int capacity;
  int (*hash)(Tkey);

 public:
    Hashtable(int capacity, int (*h)(Tkey)) {
        this->capacity = capacity;
        hash  = h;
        H = new std::list<struct info<Tkey, Tvalue>> [capacity];
    }

    ~Hashtable() {
        delete[] H;
    }

    void put(Tkey key, Tvalue value) {
        int index = hash(key) % capacity;
        info<Tkey, Tvalue> elem;
        elem.key = key;
        elem.value = value;
        H[index].push_back(elem);
    }

    void remove(Tkey key) {
        int index = hash(key) % capacity;
        info<Tkey, Tvalue> aux;
        int ok = 0;
        for (auto it = H[index].begin(); it != H[index].end(); ++it) {
            if (it->key == key) {
              it = H[index].erase(it);
              return;
            }
        }
    }

    Tvalue get(Tkey key) {
        int index = hash(key) % capacity;
        for (auto elem : H[index]) {
            if (elem.key == key) {
                return elem.value;
            }
        }
        return -1;
    }

    bool has_key(Tkey key) {
        int index = hash(key) % capacity;
        for (auto elem : H[index]) {
            if (elem.key == key) {
                return 1;
            }
        }
    return 0;
    }

    std::list<struct info<Tkey, Tvalue>>* getHashtable() {
        return H;
    }

    int get_size() {
        return size;
    }

    int get_capacity() {
        return capacity;
    }

    void print_hashtable() {
        for (int i = 0; i < capacity; i++) {
            std::cout << "HASH = " << i << ": ";
            typename std::list<struct info<Tkey, Tvalue>>::iterator it;
            for (it = H[i].begin(); it != H[i].end(); it++) {
                std::cout << it->key<< " | ";
            }
            std::cout << "\n";
        }
    }
};

#endif  // HASHTABLE_H_
