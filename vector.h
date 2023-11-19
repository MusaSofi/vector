#ifndef VECTOR_H
#define VECTOR_H

#include<stdexcept>
#include<iostream>
using namespace std;

template<typename T>
class Vector{
public:
	class ConstIterator;
	class Iterator;
	using value_type = T;
	using size_type = std::size_t;
	using difference_type = std::ptrdiff_t;
	using reference = value_type&;
	using const_reference = const value_type&;
	using pointer = value_type*;
	using const_pointer = const value_type*;
	using iterator = Vector::Iterator;
	using const_iterator = Vector::ConstIterator;
private:
	size_t sz;
	size_t max_sz;
	static constexpr size_t min_sz{5};
	pointer values;
public:

	~Vector(){
		delete[] values;	
	}

	
	Vector():Vector(min_sz){}

	Vector(const Vector& src){
		max_sz = src.max_sz;
		values = new value_type[src.max_sz];
		for(size_t i{0}; i < src.sz; ++i){
			values[i] = src.values[i];

		}
		sz = src.sz;
	}



	Vector(size_t n){
		if(n < min_sz)
			n = min_sz;
		max_sz = n;
		values = nullptr;
		sz = 0;
		reserve(n);
	}

	
	Vector(std::initializer_list<value_type> l){
		values = nullptr;
		sz = 0;
		max_sz = l.size();
		reserve(max_sz);
		for(const value_type& item : l)
			this->push_back(item);
	} 

	

	Vector operator= (Vector src){
		swap(sz,src.sz);
		swap(max_sz, src.max_sz);
		swap(values, src.values);
		return *this;

	}

	size_t size() const{
		return sz;
	}

	bool empty() const{
		return sz == 0;
	}

	void clear(){
		sz = 0;
	}

	void reserve(size_t n){
		size_t new_sz{0};
		if (n > max_sz)
			new_sz = n;
		else 
			new_sz = max_sz;
		value_type* new_values = new value_type[new_sz];
		for(size_t i{0}; i < sz; ++i)
			new_values[i] = values[i];

		max_sz = new_sz;
		delete[] values;
		values = new_values;
	}

	void shrink_to_fit(){
		max_sz = sz;
		value_type* new_values = new value_type[max_sz];
		for(size_t i{0}; i < max_sz; ++i)
			new_values[i] = values[i];

		delete[] values;
		values = new_values;
		
	}



	void push_back(value_type val){
		if (sz >= max_sz)
			reserve(max_sz*2 + 1);
		
		values[sz++] = val;
	}

	void pop_back(){
		if (empty())
			throw std::runtime_error("Vector is alredy empty");
		sz--;
	}

	value_type& operator[](size_t index){
		if(index > (sz-1))
			throw std::runtime_error("Out of bouns");
		return values[index];
	}


	const value_type& operator[](size_t index) const{
		if(index > (sz-1))
			throw std::runtime_error("Out of bouns");
		return values[index];
	}

	size_t capacity() const{
		return max_sz;
	}



	friend ostream& operator<<(ostream& o, const Vector& v){
			bool first{true};
		o << "[";
		for(size_t i{0}; i < v.sz; i++){
			if(first == true){
				o << v.values[i];
				first = false;
			}
			else
				o << ", " << v.values[i];
		}
		o << "]";
		return o;
	}

	class Iterator{
	public:
		using value_type = Vector::value_type;
		using reference = Vector::reference;
		using pointer = Vector::pointer;
		using difference_type = Vector::difference_type;
		using iterator_category = std::forward_iterator_tag;
	private:
		pointer ptr;
		size_t sz;
		size_t currentIndex;
	public:
		Iterator():ptr{nullptr}, sz{0}, currentIndex{0}{}
		Iterator(pointer ptr, size_t sz, size_t currentIndex):ptr{ptr}, sz{sz}, currentIndex{currentIndex}{}
		reference operator*() const {
			if(sz == currentIndex)
				throw std::runtime_error("Out of bounds");
			return *ptr;
		}
		pointer operator->() const {
			if(sz == currentIndex)
				throw std::runtime_error("Out of bounds");
			return ptr;
		}

		operator const_iterator() const {
			return const_iterator(ptr, sz, currentIndex);
		}
		bool operator==(const const_iterator& i)const{
			return	static_cast<const_iterator>(*this) == i;
		}
		bool operator!=(const const_iterator& i)const{
			return !(*this == i);
		}
		
		iterator& operator++() {
			if(currentIndex < sz){			
				++ptr;
				++currentIndex;
			}
			return *this;
		}

		iterator operator++(int) {
			iterator old(*this);
			++*this;
			return old;
		}

		friend Vector::difference_type operator-(const Vector::iterator& lop, const Vector::iterator& rop) {
			return lop.ptr - rop.ptr;
		}
	};

	class ConstIterator {
	public:
		using value_type = Vector::value_type;
		using reference = Vector::const_reference;
		using pointer = Vector::const_pointer;
		using difference_type = Vector::difference_type;
		using iterator_category = std::forward_iterator_tag;
	private:
		pointer ptr;
		size_t sz;
		size_t currentIndex;
	public:
		ConstIterator():ptr{nullptr}, sz{0}, currentIndex{0}{}
		ConstIterator(pointer ptr, size_t sz, size_t currentIndex):ptr{ptr}, sz{sz}, currentIndex{currentIndex}{}

		bool operator==(const const_iterator& i) const {
			return this->ptr == i.ptr;		
		}

		bool operator!=(const const_iterator& i) const {
			return !(*this == i);
		}

		reference operator*() const {
			if(sz == currentIndex)
				throw std::runtime_error("Out of bounds");
			return *ptr;
		}

		pointer operator->() const {
			if(sz == currentIndex)
				throw std::runtime_error("Out of bounds");
			return ptr;
		}

		const_iterator& operator++() {	
			if(currentIndex < sz){			
				++ptr;
				++currentIndex;
			}		
			return *this;
		}

		const_iterator operator++(int) {
			const_iterator old(*this);
			++*this;
			return old;
		}

		friend Vector::difference_type operator- (const Vector::const_iterator& lop, const Vector::const_iterator& rop) {
			return lop.ptr - rop.ptr;
		}
	};

	iterator begin(){
		if(sz == 0)
			return end();
		else
			return Iterator(values, sz, 0);
	}

	iterator end(){
		return Iterator(values+sz, sz, sz);
	}
	const_iterator begin() const{
		if(sz == 0)
			return end();
		else
			return ConstIterator(values, sz, 0);


	}
	const_iterator end() const{
		return ConstIterator(values+sz, sz, sz);

	}

	iterator insert (const_iterator pos, const_reference val) { 
		auto diff = pos - begin ();
		if (diff < 0 || static_cast <size_type>(diff) > sz) 
			throw std::runtime_error("Iterator out of bounds "); 
		size_type current{static_cast<size_type>(diff)};
		if (sz >= max_sz) 
			reserve(max_sz+2);
		for (auto i{sz}; i-- > current;)
			values [i+1] = values[i];
		values[current] = val;
		++sz;
		return iterator(values+current, sz, current);
	}

	iterator erase(const_iterator pos) {
		auto diff = pos - begin();
		if (diff < 0 || static_cast<size_type>(diff) >= sz)
			throw runtime_error("Iterator out of bounds");
		size_type current{static_cast<size_type>(diff)};
		for (auto i{current}; i < sz - 1; ++i)
			values[i] = values[i+1];
		--sz;
		return iterator{values + current, sz, current};
	}

};
#endif
