#ifndef CACHE_H
#define CACHE_H

#include <unordered_map>
#include <list>
#include <utility>
#include <ctime>
#include <iostream>

template <typename KeyType, typename ValueType> class Cache {
    public:
        Cache();
        Cache(size_t max_size);
        void setMaxSize(size_t max_size);

        void insert(const KeyType& key, const ValueType& value);
        bool exist(const KeyType& key);
        ValueType& get(const KeyType& key);
        void clear();


    private:
        void removeLeastUse();

        std::list<std::pair<KeyType, ValueType> > item_list;
        std::unordered_map<KeyType, decltype(item_list.begin())> item_map;
        size_t cache_size_;

};

template<typename KeyType, typename ValueType>
Cache<KeyType, ValueType>::Cache(): cache_size_(100) { 
    ;
}

template<typename KeyType, typename ValueType>
Cache<KeyType, ValueType>::Cache(size_t cache_size): cache_size_(cache_size) { 
    ;
}

template<typename KeyType, typename ValueType>
void Cache<KeyType, ValueType>::setMaxSize(size_t cache_size) {
    cache_size_ = cache_size;
}

template<typename KeyType, typename ValueType>
void Cache<KeyType, ValueType>::insert(const KeyType& key, const ValueType& value) {
    auto it = item_map.find(key);
    // replace original value if key exists
    if (it != item_map.end()) {
        item_list.erase(it->second);
        item_map.erase(it);
    }

    item_list.push_front(make_pair(key, value));
    item_map.insert(make_pair(key, item_list.begin()));
    removeLeastUse();

}

template<typename KeyType, typename ValueType>
void Cache<KeyType, ValueType>::removeLeastUse() {
    while (item_map.size() > cache_size_) {
        auto last_it = item_list.end();
        last_it--;
        item_map.erase(last_it->first);
        item_list.pop_back();
    }
}

template<typename KeyType, typename ValueType>
ValueType& Cache<KeyType, ValueType>::get(const KeyType& key) {
    // assert(exist(key));
    auto it = item_map.find(key);
    item_list.splice(item_list.begin(), item_list, it->second);
    return it->second->second;
}

template<typename KeyType, typename ValueType>
bool Cache<KeyType, ValueType>::exist(const KeyType& key) {
    return (item_map.count(key) > 0);
}

template<typename KeyType, typename ValueType>
void Cache<KeyType, ValueType>::clear() {
    item_map.clear();
    item_list.clear();
}

#endif
