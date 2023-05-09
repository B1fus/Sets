#pragma once
#include <iostream>
#include "RBtree.h"

template <typename T>
class Set : public RBTree<T>
{
public:
	Set();
	Set(Set<T> const& set);
	void merge(Set<T> const &source);
	void intersect(Set<T> const &source);
	void substract(Set<T> const &source);
	void symmetricDifference(Set<T> const &source);
	bool* get_characteristic_vector(Set<T> const& universum);
	Set<T>& operator=(Set<T> const& r);
	Set<T> operator|(Set<T> const& r) const;
	Set<T> operator&(Set<T> const &r) const;
	Set<T> operator-(Set<T> const &r) const;
	Set<T> operator^(Set<T> const &r) const;
};

template<typename T>
Set<T>::Set(){}

template<typename T>
Set<T>::Set(Set<T> const& set)
{
	this->copy(set);
}

template<typename T>
void Set<T>::merge(Set<T> const &source)
{
	typename Set<T>::iterator iter = source.begin();
	for (; iter != source.end(); iter++) {
		this->insert(iter->key);
	}
}

template<typename T>
void Set<T>::intersect(Set<T> const &source)
{
	typename Set<T>::iterator iter = source.begin();
	Set<T> *res = new Set<T>;
	for (; iter != source.end(); iter++) {
		if (this->contains(iter->key)) res->insert(iter->key);
	}
	this->clear();
	this->topNode = res->topNode;
}

template<typename T>
void Set<T>::substract(Set<T> const& source)
{
	typename Set<T>::iterator iter = this->begin();
	Set<T>* res = new Set<T>;
	for (; iter != this->end(); iter++) {
		if (!source.contains(iter->key)) res->insert(iter->key);
	}
	this->clear();
	this->topNode = res->topNode;
}

template<typename T>
void Set<T>::symmetricDifference(Set<T> const& source)
{
	typename Set<T>::iterator iter = source.begin();
	Set<T>* res = new Set<T>;
	for (; iter != source.end(); iter++) {
		if (!this->contains(iter->key)) res->insert(iter->key);
	}
	iter = this->begin();
	for (; iter != this->end(); iter++) {
		if (!source.contains(iter->key)) res->insert(iter->key);
	}
	this->clear();
	this->topNode = res->topNode;
}

template<typename T>
bool* Set<T>::get_characteristic_vector(Set<T> const& universum)
{
	bool* mas = new bool[universum.size()];
	typename Set<T>::iterator iterU = universum.begin();
	typename Set<T>::iterator iterT = this->begin();
	int i = 0;
	while (iterU != nullptr && iterT != nullptr) {
		mas[i] = 0;
		if (iterU->key == iterT->key) {
			mas[i] = 1;
			iterU++;
			iterT++;
		}
		else if (iterU->key < iterT->key) iterU++;
		else iterT++;
		i++;
	}
	if (i != universum.size()) {
		for (; i < universum.size(); i++) mas[i] = 0;
	}
	return mas;
}

template<typename T>
Set<T>& Set<T>::operator=(Set<T> const& r)
{
	if (&r == this) return *this;
	this->copy(r);
	return *this;
}

template<typename T>
Set<T> Set<T>::operator|(Set<T> const& r) const
{
	Set<T> res;
	res.copy(*this);
	res.merge(r);
	return res;
}

template<typename T>
Set<T> Set<T>::operator&(Set<T> const& r) const
{
	Set<T> res;
	res.copy(*this);
	res.intersect(r);
	return res;
}

template<typename T>
Set<T> Set<T>::operator-(Set<T> const& r) const
{
	Set<T> res;
	res.copy(*this);
	res.substract(r);
	return res;
}

template<typename T>
Set<T> Set<T>::operator^(Set<T> const& r) const
{
	Set<T> res;
	res.copy(*this);
	res.symmetricDifference(r);
	return res;
}
