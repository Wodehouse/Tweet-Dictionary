/*
  Wodehouse
  linear dictionary header file
*/

#include <stdexcept>
using std::pair;
using std::runtime_error;
using std::vector;

template <typename K, typename V> LinearDictionary<K, V>::LinearDictionary() {
    this->size = 0;
    //throw runtime_error("Not yet implemented: LinearDictionary<K,V>::LinearDictionary");
}

template <typename K, typename V> LinearDictionary<K, V>::~LinearDictionary() {
    // TODO: implement destructor
    this->list.erase(list.begin() + 0, this->list.begin() + this->size);
}

template <typename K, typename V> int LinearDictionary<K, V>::getSize() {
    return this->size;
    //throw runtime_error("Not yet implemented: LinearDictionary<K,V>::getSize");
}

template <typename K, typename V> bool LinearDictionary<K, V>::isEmpty() {
    if(this->size == 0) {
        return true; 
    }
    else {
        return false; 
    }
    //throw runtime_error("Not yet implemented: LinearDictionary<K,V>::isEmpty");
}

template <typename K, typename V>
void LinearDictionary<K, V>::insert(K key, V value) {
    //we can check through the list and make sure the key doesn't exist
    for(int i=0; i < this->size; i++){
        K key_i = this->list[i].first;     
        if(key_i == key){   //key exists
            throw runtime_error("Can't insert key that exists!");
        }
    }
    //if the key doesn't exist
    pair<K,V> KV_pair(key, value);
    this->list.push_back(KV_pair);
    this->size++;  
}

template <typename K, typename V>
void LinearDictionary<K, V>::update(K key, V value) {
    //search for key in list and change the value
    //myVector[index] = value
    bool exists = false;
    for(int i=0; i < this->size; i++){
        K key_i = this->list[i].first;     
        //V value_i = this->list[i].second;
        if(key_i == key){   //set value to new value(and exists to true) if key is found
            //p1.first = 5; 
            this->list[i].second = value;
            exists = true;
        }
    }
    if(exists == false){
        throw runtime_error("Can't update key that doesn't exist!");
    }
    //throw runtime_error("Key doesn't exist!");
}

template <typename K, typename V> V LinearDictionary<K, V>::get(K key) {
    
    for(int i=0; i < this->size; i++){
        K key_i = this->list[i].first;     
        V value_i = this->list[i].second;
        if(key_i == key){   //if key is found, return its value
            return value_i; 
        }
    }
    throw runtime_error("Key doesn't exist!");
}

template <typename K, typename V> bool LinearDictionary<K, V>::contains(K key) {
    for(int i=0; i < this->size; i++){
        K key_i = this->list[i].first;     
        if(key_i == key){   //if key is found, return true
            return true; 
        }
    }
    //gone through entire list and have not found key
    return false; 
}

template <typename K, typename V> void LinearDictionary<K, V>::remove(K key) {
    //vector = this->list
    bool exists = false;
    for(int i=0; i < this->size; i++){      //go through list
        K key_i = this->list[i].first;     
        if(key_i == key){   //if key is found, 'i' is index of K,Vpair
            this->list.erase(this->list.begin() + i, this->list.begin() + i + 1);   //removes one item
            this->size--;
            exists = true;
        }
            
    }
    if(exists == false){
        throw runtime_error("Can't remove a key that doesn't exist!");
    }
    
}

template <typename K, typename V> vector<K> LinearDictionary<K, V>::getKeys() {
   vector<pair<K, V>> items = this->getItems();   //returns a vector of items
   //create a vector of keys
   vector<K> keys; 
   //go through 'items' and add to our key vector
   for (int i=0; i < items.size(); i++){ 
       K key_i = items[i].first;
       keys.push_back(key_i);
   }
   return keys;
    //throw runtime_error("Not yet implemented: LinearDictionary<K,V>::getKeys");
}

template <typename K, typename V>
vector<pair<K, V>> LinearDictionary<K, V>::getItems() {
    return this->list;
    //throw runtime_error("Not yet implemented: LinearDictionary<K,V>::getItems");
}

template <typename T> void removeFromVector(vector<T> &list, int index){
  if(index < 0 || index >= list.size()){
    throw runtime_error("index out of range in removeFromVector");
  }
  list.erase(list.begin()+index, list.begin()+index+1);
}


