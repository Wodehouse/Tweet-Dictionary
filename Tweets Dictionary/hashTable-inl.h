/*
  Wodehouse
  hash table header file
*/

#include <stdexcept>


#include "hashFunctions.h"

using std::pair;
using std::runtime_error;
using std::vector;

template <typename K, typename V> HashTable<K, V>::HashTable() {
    this->capacity = 10;      //
    this->size = 0;     //number of elements currently in hash table
    //this->hashArray = new Dictionary<K,V>*[capacity];
    this->hashArray = new LinearDictionary<K,V>[capacity];
    this->greatestLoadFactor = 0.75;
    //int* array = new int[size];
    //throw runtime_error("Not yet implemented: HashTable<K,V>::HashTable");
}

template <typename K, typename V>
HashTable<K, V>::HashTable(float maxLoadFactor) {
    this->capacity = 10;      //
    this->size = 0;     //number of elements currently in hash table
    //this->hashArray = new Dictionary<K,V>*[capacity];
    this->hashArray = new LinearDictionary<K,V>[capacity];
    this->greatestLoadFactor = maxLoadFactor;
    //throw runtime_error("Not yet implemented: HashTable<K,V>::HashTable(float)");
}

template <typename K, typename V> HashTable<K, V>::~HashTable() {
    /*
    for(int i=0; i< this->capacity;i++){
        delete this->hashArray[i]; 
    }
    */
    //delete this->hashArray[i]; 
    delete[] this->hashArray;
}

template <typename K, typename V> int HashTable<K, V>::getSize() {
    return this->size;
    //throw runtime_error("Not yet implemented: HashTable<K,V>::getSize");
}

template <typename K, typename V> bool HashTable<K, V>::isEmpty() {
    if(this->size == 0){
        return true; 
    }
    else{
        return false; 
    }
    //throw runtime_error("Not yet implemented: HashTable<K,V>::isEmpty");
}

template <typename K, typename V> void HashTable<K, V>::insert(K key, V value) {
    int index = hash(key, capacity);
    //insert KV_pair if key does not exist in dictionary
    //dictionary is this->hashArray[index]
    //throw runtime_error("Not yet implemented: HashTable<K,V>::insert");
    this->hashArray[index].insert(key, value);
    this->size++;
    //check if we have exceeded maxLoadFactor
    if((this->size/this->capacity) >= this->greatestLoadFactor){
        this->expandCapacity(); 
    }

}

template <typename K, typename V> void HashTable<K, V>::update(K key, V value) {
    int index = hash(key, capacity);
    //update KV_pair if key does exist in dictionary
    //dictionary is this->hashArray[index]
    this->hashArray[index].update(key, value);
    //throw runtime_error("Not yet implemented: HashTable<K,V>::update");
}

template <typename K, typename V> V HashTable<K, V>::get(K key) {
    int index = hash(key, capacity);
    return this->hashArray[index].get(key);
    //throw runtime_error("Not yet implemented: HashTable<K,V>::get");
}

template <typename K, typename V> bool HashTable<K, V>::contains(K key) {
    int index = hash(key, capacity);
    return this->hashArray[index].contains(key);
    //throw runtime_error("Not yet implemented: HashTable<K,V>::contains");
}

template <typename K, typename V> void HashTable<K, V>::remove(K key) {
    int index = hash(key, capacity);
    this->hashArray[index].remove(key);
    this->size--;
    //throw runtime_error("Not yet implemented: HashTable<K,V>::remove");
}

template <typename K, typename V> vector<K> HashTable<K, V>::getKeys() {
    vector<pair<K,V>> items = this->getItems(); 
    vector<K> keys;
    for(int i=0; i < items.size(); i++){
        keys.push_back(items[i].first); 
    }
    return keys; 
    //throw runtime_error("Not yet implemented: HashTable<K,V>::getKeys");
}

template <typename K, typename V>
vector<pair<K, V>> HashTable<K, V>::getItems() {
    vector<pair<K, V>> items;
    for(int i=0; i < this->capacity; i++){
        vector<pair<K, V>> vect_i = this->hashArray[i].getItems();  //this is a vector with KV pairs of an index
        //add each of them to items
        for(int j=0; j< vect_i.size(); j++){    //each dictionaries' KV pairs added to items
            pair<K, V> KV_pair = vect_i[j];
            items.push_back(KV_pair);
        }
    }
    return items; 
    //call getItems on each index
    //throw runtime_error("Not yet implemented: HashTable<K,V>::getItems");
}

template <typename K, typename V> void HashTable<K, V>::expandCapacity() {
    vector<pair<K,V>> items = this->getItems(); 
    this->capacity *= 2;
    LinearDictionary<K,V>* newArray = new LinearDictionary<K,V>[capacity];
    

    for(int i = 0; i < items.size(); i++){
        K key = items[i].first; 
        V value = items[i].second; 
        int index = hash(key, capacity);
        newArray[index].insert(key, value);

    }
    delete[] this->hashArray; 
    this->hashArray = newArray; 
    //throw runtime_error("Not yet implemented: HashTable<K,V>::expandCapacity");
}

