#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>
#include <iterator>
#include <memory>
#include <limits>

template <class T>

class vector{
    public:
    typedef T& reference;
    typedef const T& const_reference;
    typedef T* iterator;
    typedef const T* const_iterator;
    typedef std::reverse_iterator<iterator> reverse_iterator;
    typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

    vector() {
        _data = _capacity = _size = nullptr;
        }
    vector(size_t size) {
        _data = _alloc.allocate(size);
        _size = _capacity = _data + size;
        }
    vector(size_t size, const T& value) {
        _data = _alloc.allocate(size);
        _size = _capacity = _data + size;
        std::uninitialized_fill(_data, _size, value);
        }
    vector(const vector & x) {
			_data = _alloc.allocate(x.end() - x.begin());
			_size = _capacity = std::uninitialized_copy(x.begin(), x.end(), _data);
		}
    vector(std::initializer_list<T> list){
            _data = _alloc.allocate(list.end() - list.begin());
			_size = _capacity = std::uninitialized_copy(list.begin(), list.end(), _data);
        }
    vector(iterator first, iterator last) {
            _data = _alloc.allocate(last - first);
		    _size = _capacity = std::uninitialized_copy(first, last, _data);
        }
    ~vector(){ clear(); }

    iterator begin() noexcept { return _data; }
    const_iterator begin() const noexcept { return _data; }
    iterator end() noexcept { return _size; }
    const_iterator end() const noexcept { return _size; }
    reverse_iterator rbegin() noexcept { return reverse_iterator(_size); }
    const_reverse_iterator rbegin() const noexcept  { return reverse_iterator(_size); }
    reverse_iterator rend() noexcept { return reverse_iterator(_data); }
    const_reverse_iterator rend() const noexcept { return reverse_iterator(_data); }
    
    size_t size() const { return _size - _data; }
    size_t max_size() const {  return std::numeric_limits<size_t>::max(); }
    size_t capacity() const { return _capacity - _data; }
    bool empty() const { return _size - _data == 0; }

	void resize(size_t size) {
		if (size == 0) {
            clear();
            return;
        }
		if (size == _capacity - _data){
            return;
        }
		iterator temp_data = _alloc.allocate(size);
		iterator temp_size, temp_capacity, end;
		if (size < _size - _data){
            end = _data + size;
        }
		else{
            end = _size;
        }
		std::move(_data, end, temp_data);
		temp_size = temp_data + (end - _data);
		temp_capacity = temp_data + size;
		while (temp_size != temp_capacity) {
			*(temp_size) = T();
			temp_size ++;
		}
		clear();
		_data = temp_data;
		_size = temp_size;
		_capacity = temp_capacity;
	}

    void reserve(size_t size) {
        if (size > _capacity) {
            iterator temp_data = _alloc.allocate(size);
            iterator temp_size = std::uninitialized_copy(_data, _size, temp_data);
            clear();
            _data = temp_data;
            _size = temp_size;
            _capacity = _data + size;
        }
    }
    void shrink_to_fit(){
        iterator temp_data = _alloc.allocate(_size - _data), temp_size, temp_capacity;
		std::move(_data, _size, temp_data);
		temp_size = temp_capacity = temp_data + (_size - _data);
		clear();
		_data = temp_data;
		_size = temp_size;
		_capacity = temp_capacity;
    }

    vector& operator=(const vector& x){
        if (&x == this){
           return *this;
        }
		clear();
		_data = _alloc.allocate(x.end() - x.begin());
		_size = _capacity = std::uninitialized_copy(x.begin(), x.end(), _data);
    }
    reference operator[] (size_t n){ return _data[n]; }
    const_reference operator[] (size_t n) const { return _data[n]; }
    reference front() { return _data[0]; }
    const_reference front() const { return _data[0]; }
    reference back() { return _data[size]; }
    const_reference back() const { return _data[size]; }
    T* data() noexcept { return _data; }
    const T* data() const noexcept {return _data; }

    void assign (size_t size, const T& value){
       clear();
		_data = _alloc.allocate(size);
		_size = _capacity = _data + size;
		std::uninitialized_fill(_data, _size, value);
    }

    void assign (iterator first, iterator last) {
        _data = _alloc.allocate(last - first);
	    _size = _capacity = std::uninitialized_copy(first, last, _data);
    }

	void clear() {
		if (_data) {
			iterator it = _capacity;
			while (it != _data) _alloc.destroy(--it);
			_alloc.deallocate(_data, _size - _data);
			_data = _size = _capacity = nullptr;
		}
	}
    
	void push_back(const T & value) {
		if (_size == _capacity){
            grow();
        }
        _alloc.construct(_size++, value);
	}

    void pop_back(){
        _size--;
        _alloc.destroy(_size + 1);
    }

    void swap(vector& x) {
        std::swap(_size, x._size);
        std::swap(_capacity, x._capacity);
        std::swap(_data, x._data);
    }

    private:
    iterator _size, _capacity, _data;
    std::allocator<T> _alloc;
	void grow()
	{
		size_t size = std::max(2 * (_capacity - _data), ptrdiff_t(1));
		iterator temp_data = _alloc.allocate(size);
		iterator temp_size = std::uninitialized_copy(_data, _size, temp_data);
		clear();
		_data = temp_data;
		_size = temp_size;
		_capacity = _data + size;
	}
};

#endif