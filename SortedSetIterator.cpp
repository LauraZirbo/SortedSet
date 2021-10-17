#include "SortedSetIterator.h"
#include <exception>
#include <iostream>
using namespace std;

SortedSetIterator::SortedSetIterator(const SortedSet& m) : multime(m)
{
	this->current = m.arr.head;
}//Theta(1)


void SortedSetIterator::first() {
	this->current = this->multime.arr.head;
}//Theta(1)


void SortedSetIterator::next() {
	if (this->current == -1)
		throw exception();
	else
		this->current = this->multime.arr.next[this->current];
}//Theta(1)


TElem SortedSetIterator::getCurrent()
{
	if (this->current == -1)
		throw exception();
	//cout << "Current:" << this->current << endl;

	return this->multime.arr.elems[this->current];
}//Theta(1)

bool SortedSetIterator::valid() const {
	if (this->current != -1)
		return true;
	return false;
}//Theta(1)

