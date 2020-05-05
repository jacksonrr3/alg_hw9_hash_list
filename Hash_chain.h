#pragma once
#include "VectorArray.h"
#include "List.h"

template <typename V>
struct Pair 
{
	int _key;
	V _value;

	Pair() = default;
	Pair& operator=(const Pair& p) = default;

	Pair(int key) :_key(key), _value() {}
	Pair(int key, V value) :_key(key), _value(value) {}

	friend bool operator==(const Pair<V>& p1, const Pair<V>& p2);

};

template <typename V>
bool operator==(const Pair<V>& p1, const Pair<V>& p2) {
	return p1._key == p2._key;
}


template <typename T>
struct Hash_Chain {

	List<Pair<T> >*  _hash_table; //������������ ������
	std::size_t _table_size;

	std::size_t hash(int i) {
		return (i % _table_size);
	}

public:
	//Hash_Chain():_hash_table() {}

	Hash_Chain(std::size_t size) :_table_size(size), _hash_table(new List<Pair<T> >[size]) {}

	~Hash_Chain() = default;

	void ins(int key, const T& value) {
		_hash_table[hash(key)].enqueue({ key, value });
	}

	bool del(int key) {
		bool b = false;

		for (Node<Pair<T>>* n = _hash_table[hash(key)].getHead(); n; n = n->getNext()) {
			if (n->getItem()._key == key) {
				_hash_table[hash(key)].remove_node(n);
				break;
			}
		}
		return b;
	}

	T search(int key) {
		Pair<T> temp;

		for (Node<Pair<T>>* n = _hash_table[hash(key)].getHead(); n; n = n->getNext()) {
			if (n->getItem()._key == key) {
				temp = n->getItem();
				break;
			}
		}

		return temp._value;
	}

};