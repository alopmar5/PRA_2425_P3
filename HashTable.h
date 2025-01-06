#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <ostream>
#include <stdexcept>
#include <string>
#include "../PRA_2425_P1/ListLinked.h"
#include "Dict.h"
#include "TableEntry.h"

template <typename V>
class HashTable : public Dict<V> {
private:
    int n;
    int max;
    ListLinked<TableEntry<V>>* table;

    int h(std::string key) {
        int sum = 0;
        for (char c : key) {
            sum += static_cast<int>(c);
        }
        return sum % max;
    }

public:
    HashTable(int size) : n(0), max(size) {
        table = new ListLinked<TableEntry<V>>[max];
    }

    ~HashTable() {
        delete[] table;
    }

    void insert(std::string key, V value) override {
        int bucket = h(key);
        TableEntry<V> entry(key, value);
        for (int i = 0; i < table[bucket].size(); ++i) {
            if (table[bucket].get(i) == entry) {
                throw std::runtime_error("Clave ya existente: " + key);
            }
        }
        table[bucket].append(entry);
        ++n;
    }

    V search(std::string key) override {
        int bucket = h(key);
        TableEntry<V> entry(key);
        for (int i = 0; i < table[bucket].size(); ++i) {
            if (table[bucket].get(i) == entry) {
                return table[bucket].get(i).value;
            }
        }
        throw std::runtime_error("Clave no encontrada: " + key);
    }

    V remove(std::string key) override {
        int bucket = h(key);
        TableEntry<V> entry(key);
        for (int i = 0; i < table[bucket].size(); ++i) {
            if (table[bucket].get(i) == entry) {
                TableEntry<V> removed = table[bucket].remove(i);
                --n;
                return removed.value;
            }
        }
        throw std::runtime_error("Clave no encontrada: " + key);
    }

    int entries() const override {
        return n;
    }

    int capacity() const {
        return max;
    }

    V operator[](std::string key) {
        return search(key);
    }

    friend std::ostream& operator<<(std::ostream& out, const HashTable<V>& ht) {
        for (int i = 0; i < ht.max; ++i) {
            out << "Cubeta " << i << ": ";
            for (int j = 0; j < ht.table[i].size(); ++j) {
                out << ht.table[i].get(j) << " ";
            }
            out << std::endl;
        }
        return out;
    }
};

#endif 

