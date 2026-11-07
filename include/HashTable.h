
// Purpose: Custom hash table keyed by facility ID (string -> record index).
//          Collision strategy: separate chaining (each bucket is a vector).
// Author:  Member A
#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <string>
#include <vector>

class HashTable {
public:
    // Initial number of buckets. Chains grow, so there is no maximum entry count.
    static const int DEFAULT_CAPACITY = 13;

    explicit HashTable(int capacity = DEFAULT_CAPACITY);

    // Custom string hash: h = (h * 31 + c) mod capacity over the uppercase key.
    int hash(const std::string& key) const;

    // Inserts key -> value. Returns false (and changes nothing, including the
    // collision count) if the key already exists, ignoring case.
    bool insert(const std::string& key, int value);

    // Looks up key (case-insensitive). Returns true and sets value if found.
    bool find(const std::string& key, int& value) const;

    int capacity() const;    // number of buckets
    int size() const;        // number of stored entries
    int collisions() const;  // accepted inserts that landed in a nonempty bucket

private:
    struct Entry {
        std::string key;   // normalized (uppercase) key
        int value;         // index of the facility record
    };
    std::vector<std::vector<Entry> > buckets;
    int entryCount;
    int collisionCount;
};

#endif
