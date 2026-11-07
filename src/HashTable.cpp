
#include "HashTable.h"
#include "Utils.h"

const int HashTable::DEFAULT_CAPACITY;

HashTable::HashTable(int capacity) {
    if (capacity <= 0) capacity = DEFAULT_CAPACITY;
    buckets.resize(capacity);
    entryCount = 0;
    collisionCount = 0;
}

int HashTable::hash(const std::string& key) const {
    int h = 0;
    for (size_t i = 0; i < key.length(); i++) {
        h = (h * 31 + key[i]) % buckets.size();
    }
    return h;
}

bool HashTable::insert(const std::string& key, int value) {
    std::string upperKey = utils::toUpper(key);
    int h = hash(upperKey);
    
    // Check for duplicate
    for (size_t i = 0; i < buckets[h].size(); i++) {
        if (buckets[h][i].key == upperKey) {
            return false; 
        }
    }
    
    // Record collision if bucket is not empty prior to insertion
    if (!buckets[h].empty()) {
        collisionCount++;
    }
    
    Entry e;
    e.key = upperKey;
    e.value = value;
    buckets[h].push_back(e);
    entryCount++;
    return true;
}

bool HashTable::find(const std::string& key, int& value) const {
    std::string upperKey = utils::toUpper(key);
    int h = hash(upperKey);
    
    for (size_t i = 0; i < buckets[h].size(); i++) {
        if (buckets[h][i].key == upperKey) {
            value = buckets[h][i].value;
            return true;
        }
    }
    return false;
}

int HashTable::capacity() const {
    return (int)buckets.size();
}

int HashTable::size() const {
    return entryCount;
}

int HashTable::collisions() const {
    return collisionCount;
}
