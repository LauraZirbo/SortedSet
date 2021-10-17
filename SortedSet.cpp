#include "SortedSet.h"
#include "SortedSetIterator.h"
#include <iostream>
using namespace std;

SortedSet::SortedSet(Relation r) {
	this->arr.cap = 10;
	this->arr.rel = r;
	this->arr.size = 0;
	this->arr.elems = new TElem[arr.cap];
	this->arr.next = new int[this->arr.cap];
	this->arr.prev = new int[this->arr.cap];
	this->arr.head = -1;
	this->arr.tail = -1;
	for (int i = 2; i < this->arr.cap; i++)
	{
		this->arr.next[i] = i + 1;
		this->arr.prev[i] = i - 1;
	}
	this->arr.next[this->arr.cap] = -1;
	this->arr.prev[this->arr.cap] = this->arr.cap - 1;
	this->arr.next[1] = 2;
	this->arr.prev[1] = -1;
	this->arr.firstEmply = 1; 
}//Complexity: Theta(n) - n is the initial capacity;


bool SortedSet::add(TComp elem) {
	if (this->arr.cap==this->arr.size)
	{
		TElem* newElems = new TElem[this->arr.cap * 2];
		int* newNext = new int[this->arr.cap * 2];
		int* newPrev = new int[this->arr.cap * 2];
		for (int i = 1; i <= this->arr.cap; i++)
		{
			newElems[i] = this->arr.elems[i];
			newNext[i] = this->arr.next[i];
			newPrev[i] = this->arr.prev[i];
		}
		for (int i = this->arr.cap + 1; i < this->arr.cap * 2; i++)
		{
			newNext[i] = i + 1;
			newPrev[i] = i - 1;
		}
		newNext[this->arr.cap * 2] = -1;
		newPrev[this->arr.cap * 2] = this->arr.cap * 2 - 1;
		this->arr.elems = newElems;
		this->arr.next = newNext;
		this->arr.prev = newPrev;
		this->arr.firstEmply = this->arr.cap + 1;
		this->arr.cap = this->arr.cap * 2;
		//resize

	}

	if (this->arr.head == -1)
	{
		this->arr.elems[this->arr.firstEmply] = elem;
		int j = this->arr.next[this->arr.firstEmply];
		this->arr.head = this->arr.firstEmply;
		this->arr.tail = this->arr.firstEmply;
		this->arr.next[this->arr.firstEmply] = -1;
		this->arr.prev[this->arr.firstEmply] = -1;
		this->arr.firstEmply = j;
		this->arr.prev[this->arr.firstEmply] = -1;
		this->arr.size++;
		return true;
		//We do this if the list is empty
	}
	else
	{
		if (this->arr.rel(elem, this->arr.elems[this->arr.head]))
		{
			if (elem == this->arr.elems[this->arr.head])
				return false;
			this->arr.elems[this->arr.firstEmply] = elem;
			int j = this->arr.next[this->arr.firstEmply];
			this->arr.next[this->arr.firstEmply] = this->arr.head;
			this->arr.prev[this->arr.firstEmply] = -1;
			this->arr.prev[this->arr.head] = this->arr.firstEmply;
			this->arr.head = this->arr.firstEmply;
			this->arr.firstEmply = j;
			this->arr.prev[this->arr.firstEmply];

			this->arr.size++;
			return true;
			//We do this if the element must be inserted ahead of the list
		}
		else
		{
			int i = this->arr.next[this->arr.head];
			while(i != -1)
			{
				if (this->arr.rel(elem, this->arr.elems[i]))
				{
					if (elem == this->arr.elems[i])
						return false;
					this->arr.elems[this->arr.firstEmply] = elem;
					int j = this->arr.next[this->arr.firstEmply];
					this->arr.next[this->arr.firstEmply] = i;
					this->arr.prev[this->arr.firstEmply] = this->arr.prev[i];
					this->arr.next[this->arr.prev[i]] = this->arr.firstEmply;
					this->arr.prev[i] = this->arr.firstEmply;
					this->arr.firstEmply = j;
					this->arr.prev[this->arr.firstEmply] = -1;
					this->arr.size++;
					return true;
				}//We do this if we must isert it anywhere before the last element (Which is why we use
				// do - while instead of while, which would stop without checking if the the element 
				// should be inserted before the last element
				i = this->arr.next[i];
			} 

			this->arr.elems[this->arr.firstEmply] = elem;
			int j = this->arr.next[this->arr.firstEmply];
			this->arr.next[this->arr.firstEmply] = -1;
			this->arr.next[this->arr.tail] = this->arr.firstEmply;
			this->arr.prev[this->arr.firstEmply] = this->arr.tail;
			this->arr.tail = this->arr.firstEmply;
			this->arr.firstEmply = j;
			this->arr.prev[this->arr.firstEmply] = -1;
			this->arr.size++;
			
			return true;
			// We do this if the given element should be inserted after the last element
		}
	}
	return false;
}//Best Case: Theta(1), Worst case Theta (n) - Because the set is sorted , Average case O(n)


bool SortedSet::remove(TComp elem) {
	int n = this->arr.head;
	int p = -1;
	while (n != -1 && this->arr.elems[n] != elem)
	{
		p = n;
		n = this->arr.next[n];
	}
	if (this->arr.elems[n] == elem)
	{
		if (this->arr.head == n)
			this->arr.head = this->arr.next[this->arr.head];
		else
		{
			if (this->arr.tail == n)
			{
				this->arr.tail = this->arr.prev[this->arr.tail];
			}
			this->arr.next[p] = this->arr.next[n];
		}
		this->arr.next[n] = this->arr.firstEmply;
		this->arr.prev[n] = -1;
		this->arr.prev[this->arr.firstEmply] = n;
		this->arr.firstEmply = n;
		this->arr.size--;

		
		if (this->arr.size!=0 && this->arr.size <= this->arr.cap / 4)
		{
			TElem* newElems = new TElem[this->arr.cap /2];
			int* newNext = new int[this->arr.cap /2];
			int* newPrev = new int[this->arr.cap /2];
			int i = this->arr.head;
			int j = 1;
			while(i!= -1)
			{
				newElems[j] = this->arr.elems[i];
				newNext[j] = j + 1;
				newPrev[j] = j - 1;
				j++;
				i = this->arr.next[i];
			}
			newNext[j-1] = -1;
			newPrev[1] = -1;
			for (int i = j + 1; i < this->arr.cap /2; i++)
			{
				newNext[i] = i + 1;
				newPrev[i] = i - 1;
			}
			newNext[this->arr.cap /2] = -1;
			newPrev[this->arr.cap /2] = this->arr.cap /2 - 1;
			newNext[j] = j + 1;
			newPrev[j] = -1;
			this->arr.elems = newElems;
			this->arr.next = newNext;
			this->arr.prev = newPrev;
			this->arr.head = 1;
			this->arr.tail = j - 1;
			this->arr.firstEmply = j;
			this->arr.cap = this->arr.cap /2;

		}
	
		return true;
	}
	return false;
}//Best Case: Theta(1), Worst case Theta (n) - Because the set is sorted , Average case O(n)


bool SortedSet::search(TComp elem) const {
	int c = this->arr.head;
	while (c != -1 && this->arr.elems[c] != elem)
		c = this->arr.next[c];
	if (c != -1)
		return true;
	return false;
}//Best Case: Theta(1), Worst case Theta (n) - Because the set is sorted , Average case O(n)


int SortedSet::size() const {
	return this->arr.size;
}//Theta(1)



bool SortedSet::isEmpty() const {
	if (this->arr.size == 0)
		return true;
	return false;
}//Theta(1)


SortedSetIterator SortedSet::iterator() const {
	return SortedSetIterator(*this);
}//Theta(1)


SortedSet::~SortedSet() {
	//TODO - Implementation
	/*
	delete[] this->arr.elems;
	delete[] this->arr.next;
	delete[] this->arr.prev;*/
}//Theta(1)


