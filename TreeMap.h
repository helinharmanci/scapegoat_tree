#ifndef TREEMAP_H
#define TREEMAP_H

#include <iostream>
#include <vector>

#include "KeyValuePair.h"
#include "ScapegoatTree.h"

template<class K, class V>
class TreeMap {
public: // DO NOT CHANGE THIS PART.
    TreeMap();

    void clear();

    const V &get(const K &key) const;

    bool pop(const K &key);

    bool update(const K &key, const V &value);

    const KeyValuePair<K, V> &ceilingEntry(const K &key);

    const KeyValuePair<K, V> &floorEntry(const K &key);

    const KeyValuePair<K, V> &firstEntry();

    const KeyValuePair<K, V> &lastEntry();

    void pollFirstEntry();

    void pollLastEntry();

    std::vector<KeyValuePair<K, V> > subMap(K fromKey, K toKey) const;

    void print() const;

private: // YOU MAY ADD YOUR OWN UTILITY MEMBER FUNCTIONS HERE.

private: // DO NOT CHANGE THIS PART.
    ScapegoatTree<KeyValuePair<K, V> > stree;
};


template<class K, class V>
TreeMap<K, V>::TreeMap() {}


/*
 * This function removes all key-value mappings from this map so that it becomes empty.
 */
template<class K, class V>
void TreeMap<K, V>::clear() {

	stree.removeAllNodes();
}

/*
 * This function returns the value of the key-value mapping specified with the given key from this map. If
 * there exists no such key-value mapping in this tree map, this function should throw NoSuchItemException.
 */
template<class K, class V>
const V &TreeMap<K, V>::get(const K &key) const {

	KeyValuePair<K,V> kv(key);
	return stree.get(kv).getValue();
}


/*
 * This function removes the key-value mapping specified with the given key from this map and returns
 * true. If there exists no such key-value mapping in this tree map, this function should return false.
 */
template<class K, class V>
bool TreeMap<K, V>::pop(const K &key) {
	KeyValuePair<K,V> kv(key);
	return stree.remove(kv);
}


/*
 * This function adds a new key-value mapping specified with the given key and value to this map and
 * returns true. It takes the mapping information (key and value) as parameter and inserts a new
 * KeyValuePair object to the stree scapegoat tree. If there already exists a mapping with the given
 * key in this tree map, this function should return false.
 */
template<class K, class V>
bool TreeMap<K, V>::update(const K &key, const V &value) {

	KeyValuePair<K,V> kv(key, value);
	return stree.insert(kv);
}


/*
 * This function returns a key-value mapping from this tree map associated with the least key greater
 * than or equal to the given key. If there exists no such key-value mapping in this tree map, this function
 * should throw NoSuchItemException.
 */
template<class K, class V>
const KeyValuePair<K, V> &TreeMap<K, V>::ceilingEntry(const K &key) {

	KeyValuePair<K,V> kv(key);
	return stree.getCeiling(key);
}


/*
 * This function returns a key-value mapping from this tree map associated with the greatest key
 * less than or equal to the given key. If there exists no such key-value mapping in this tree map,
 * this function should throw NoSuchItemException
 */
template<class K, class V>
const KeyValuePair<K, V> &TreeMap<K, V>::floorEntry(const K &key) {

	KeyValuePair<K,V> kv(key);
	return stree.getFloor(kv);
}



/*
 * This function returns a key-value mapping from this tree map associated with the least key. If there
 * exists no such key-value mapping in this tree map, this function should throw NoSuchItemException.
 */
template<class K, class V>
const KeyValuePair<K, V> &TreeMap<K, V>::firstEntry() {

	return stree.getMin();
}

/*
 * This function returns a key-value mapping from this tree map associated with the greatest key. If there
 * exists no such key-value mapping in this tree map, this function should throw NoSuchItemException.
 */
template<class K, class V>
const KeyValuePair<K, V> &TreeMap<K, V>::lastEntry() {

	return stree.getMax();
}


/*
 * This function removes the key-value mapping associated with the least key from this map. If there
 * exists no such key-value mapping in this tree map, this function should throw NoSuchItemException.
 */
template<class K, class V>
void TreeMap<K, V>::pollFirstEntry() {

	KeyValuePair<K,V> kv(stree.getMin());
	stree.remove(kv);
}

/*
 * This function removes the key-value mapping associated with the greatest key from this map. If there
 * exists no such key-value mapping in this tree map, this function should throw NoSuchItemException.
 */
template<class K, class V>
void TreeMap<K, V>::pollLastEntry() {

	KeyValuePair<K,V> kv(stree.getMax());
	stree.remove(kv);
}


/*
 * This function returns a portion of this map whose keys range from fromKey, inclusive, to toKey,
 * inclusive as std::vector of key-value mappings. For this function, you may assume that there are
 * key-value mappings in this map with keys fromKey and toKey, and you may also assume that fromKey
 * is less than or equal to toKey.
 */
template<class K, class V>
std::vector<KeyValuePair<K, V> > TreeMap<K, V>::subMap(K fromKey, K toKey) const {

	KeyValuePair<K,V> from(fromKey);
	KeyValuePair<K,V> to(toKey);
	std::vector< KeyValuePair<K,V> > vec;
	KeyValuePair<K,V> temp=stree.get(from);

	if(to==from)
		vec.push_back(from);

	else
    {
		while(temp >= from && temp<to)
		{
			vec.push_back(temp);
			temp=stree.getNext(temp);
		}
		vec.push_back(stree.get(to));
	}

	return vec;
}


/*
 * This function prints the tree map.
 */
template<class K, class V>
void TreeMap<K, V>::print() const {

    std::cout << "# Printing the tree map ..." << std::endl;

    std::cout << "# ScapegoatTree<KeyValuePair<K, V> > stree:" << std::endl;
    stree.printPretty();

    std::cout << "# Printing is done." << std::endl;
}

#endif //TREEMAP_H
