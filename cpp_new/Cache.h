#ifndef CACHE_H
#define CACHE_H

#include <unordered_map>
#include <deque>
#include <utility>
#include <ctime>
#include <iostream>

template <typename KeyType, typename ValueType> class Cache {
    public:
        Cache();
        Cache(long max_size);
        bool insert(const KeyType& key, const ValueType& value);
        int count(const KeyType& key);
        ValueType& get(const KeyType& key);
        void removeEldest();
        void setMaxSize(long max_size);

        void clear();


        // to be launched periodically
    private:
        std::unordered_map<KeyType, ValueType> cache_map;
        std::deque<std::pair<typename std::unordered_map<KeyType, ValueType>::iterator, time_t> > track_deque;
        long max_size_;

};

template<typename KeyType, typename ValueType>
Cache<KeyType, ValueType>::Cache() { 
    // at least 1
    max_size_ = 1;
}

template<typename KeyType, typename ValueType>
Cache<KeyType, ValueType>::Cache(long max_size) { 
    max_size_ = max_size;
}

template<typename KeyType, typename ValueType>
void Cache<KeyType, ValueType>::setMaxSize(long max_size) {
    max_size_ = max_size;
}

template<typename KeyType, typename ValueType>
bool Cache<KeyType, ValueType>::insert(const KeyType& key, const ValueType& value) {
    if (track_deque.size() > max_size_) {
        removeEldest();
    }
    std::pair<typename std::unordered_map<KeyType, ValueType>::iterator, bool> result =
        cache_map.insert(std::make_pair(key, value));

    if (!result.second) {
        (result.first)->second = value;
    }
    track_deque.push_back(std::make_pair(result.first, time(NULL)));

    return result.second;
}

template<typename KeyType, typename ValueType>
void Cache<KeyType, ValueType>::removeEldest() {
    cache_map.erase(track_deque.front().first);
    track_deque.pop_front();
}

template<typename KeyType, typename ValueType>
ValueType& Cache<KeyType, ValueType>::get(const KeyType& key) {
    return cache_map[key];
}

template<typename KeyType, typename ValueType>
int Cache<KeyType, ValueType>::count(const KeyType& key) {
    return cache_map.count(key);
}

template<typename KeyType, typename ValueType>
void Cache<KeyType, ValueType>::clear() {
    cache_map.clear();
    track_deque.clear();
}

#endif
