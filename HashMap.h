#ifndef dshashtable_h
#define dshashtable_h

#include "document.h"
#include <vector>
#include <iostream>
#include <algorithm>
#include <fstream>

#define DEBUG false

/*!
 * \class templated hashmap to store keys iassociated with a value
 * hash key to determine location and store entry with key and value in an array
 * @tparam K template param 1
 * @tparam V template param 2
 */
template <typename K, typename V>
class HashMap {

private:
    ///\struct \private structure entry to store entry into HashTable
    struct Entry {
        K key;  ///\var store key to store data by
        V value; ///\var store data to be retrived by key
        Entry(K k, V v):key(k), value(v) {}
    };

    std::vector<Entry>* table = nullptr; ///\var \private vector to hold all entries
    int num_elements = 0;  ///\var \private number of elements held in hashtable
    int table_size = 0;  ///\var \private size of vector holding entries

public:
    /*!
     * \fn constructor
     */
    HashMap() {
        table_size = 100;
        table = new std::vector<Entry>[table_size];
    }
    /*!
     * \fn copy constructor
     * loop through each item in array and copy
     * \param hashtable to copy
     */
    HashMap(const HashMap<K, V>& copy){
        table_size = copy.table_size;
        for(int i=0;i<copy.table_size;i++){
            table[i] = copy[i];
        }
    }
    /*!
     * \fn delete all data
     * override all old data and create new array
     */
    void clearData(){
        table = new std::vector<Entry>[table_size];
    }
    /*!
     * \fn insert new entry into the hashtable
     * create hash for key then modulo by size to determine location to store entry
     * create entry based on key and value and push_back into vector at given array location
     * \param theKey key to be hashed and stored
     * \param theValue value to be referenced by key
     */
    void insert(const K& theKey, const V& theValue){
        Entry e(theKey, theValue);
        auto hash_value = std::hash<K>{}(theKey);
        int location = hash_value % table_size;
        if(DEBUG) std::cout << theKey << ": "
                            << hash_value << std::endl;
        bool alreadyThere = false;
        for(int i=0;i<table[location].size();i++){
            if(table[location].at(i).key == theKey)
                alreadyThere = true;
        }
        if(!alreadyThere)
            num_elements++;
        table[location].push_back(e);
    }
    /*!
     * \fn return all values associated by given key
     * hash key to determine location and loop through all items to save ones with matching keys into vector
     * \param theKey key to be hashed and searched for
     * \return all values found associated with key in a vector
     */
    std::vector<V> get_value(const K& theKey){
        std::vector<V> vec;
        auto location = std::hash<K>{}(theKey) % table_size;
        for(auto &c : table[location]) {
            if(c.key == theKey)
                vec.push_back(c.value);
        }
        return vec;
    }
    /*!
     * \fn returns if any values of a key exist in a table
     * hash key and search all items in location for given key
     * \param theKey key to be searched for
     * \return boolean holding if key was found or not
     */
    bool contains(const K& theKey){
        auto location = std::hash<K>{}(theKey) % table_size;
        for(auto &c : table[location]) {
            if(c.key == theKey)
                return true;
        }
        return false;
    }
    /*!
     * \fn returns the number of elements in the hashmap
     * \return number of elements in hashmap
     */
    int getNumElemnets(){
        return num_elements;
    }
};

#endif