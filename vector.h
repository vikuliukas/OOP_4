#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>
#include <iterator>
#include <limits>

template <typename T>

class vector{
    private:
    size_t _size, _capacity;
    T * _data;

    public:
    typedef T& reference;
    typedef const T& const_reference;
    typedef T* iterator;
    typedef const T* const_iterator;
    typedef std::reverse_iterator<iterator> reverse_iterator;
    typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

    vector() : _size{0}, _capacity{0}, _data{new T[_size]} {}
    vector(size_t size) : _size{ size }, _capacity{ size }, _data{ new T[size] } {}
    vector(size_t size, T& value) : _size{ size }, _capacity{ size }, _data{ new T[size] } {std::fill_n(_data, size, value); }
    vector(std::initializer_list<T> list) : _size{list.size()}, _capacity{_size}, _data{new T[_size]} { std::copy(list.begin(), list.end(), _data); }
    vector(iterator first, iterator last) : _size{last-first}, _capacity{_size}, _data{new T[_size]} {
        for(size_t i = 0; i < last - first; i++){
            _data[i] = *(first + i);
        }
    }
    vector(const vector& x) : _size{x.size()}, _capacity{x.capacity()}, _data{new T[_size]} {std::copy(x.begin(), x.end(), _data); }
    vector(vector&& x) :  _size{x.size()}, _capacity{x.capacity()}, _data{new T[_size]} {
        std::move(x.begin(), x.end(), _data);
        delete[] x._data;
        x.clear();
    }

    ~vector(){ delete[] _data; }

    vector& operator=(const vector& x){
        _size = x.size();
        _capacity = x.capacity();
        std::copy(x.begin(), x.end(), _data);
        return *this;
    }

    iterator begin() noexcept { return _data; }
    const_iterator begin() const noexcept { return _data; }
    iterator end() noexcept { return _data + _size; }
    const_iterator end() const noexcept { return _data + _size; }
    reverse_iterator rbegin() noexcept { return reverse_iterator(_data + _size); }
    const_reverse_iterator rbegin() const noexcept  { return reverse_iterator(_data + _size); }
    reverse_iterator rend() noexcept { return reverse_iterator(_data); }
    const_reverse_iterator rend() const noexcept { return reverse_iterator(_data); }
    
    size_t size() const { return _size; }
    size_t max_size() const {  return std::numeric_limits<size_t>::max(); }
    size_t capacity() const { return _capacity; }
    bool empty() const { return _size == 0; }

    void resize (size_t size){
       if( size < _size ){
            T *temp = new T[size];
            std::copy(&_data[0], &_data[size], temp);
            delete[] _data;
            _data = temp;
            _size = size;
            _capacity = size;

        }
        else{
            resize(size,0);
        }
    }

    void resize (size_t size, const T& val){
        if( size < _size ){
            T *temp = new T[size];
            std::copy(&_data[0], &_data[size], temp);
            delete[] _data;
            _data = temp;
            _size = size;
            _capacity = size;

        }
        if (size > _capacity ) {
            T *temp = new T[size];
            std::copy(&_data[0], &_data[_size], temp);
            delete[] _data;
            std::fill(&temp[_size], &temp[size], 0);
            _data = temp;
            _size = size;
            _capacity = size;
        }
    }

    void reserve (size_t capacity){
        if(capacity > _capacity){
            *temp = new T[capacity];
            std::copy(&_data[0], &_data[_size], temp);
            delete[] _data;
            _data = temp;
        }
    }

    void shrink_to_fit(){
        if(_capacity > _size){
            T *temp = new T[_size];
            std::move(&_data[0], &_data[_size], temp);
            delete[] _data;
            _data = temp;
            _capacity = _size;
        }
    }

    reference operator[] (size_t n){ return _data[n]; }
    const_reference operator[] (size_t n) const { return _data[n]; }
    reference front() { return _data[0]; }
    const_reference front() const { return _data[0]; }
    reference back() { return _data[size]; }
    const_reference back() const { return _data[size]; }
    T* data() noexcept { return _data; }
    const T* data() const noexcept {return _data; }

    void assign (iterator first, iterator last){
        _size = last - first;
        _capacity = last - first;
        _data = new T[_size];
        for(size_t i = 0; i < last - first; i++){
            _data[i] = *(first + i);
        }
    }

    void assign (size_t n, const T& val){
        _size = n;
		_capacity = n;
		delete[] _data;
		T * _data = new T[_size];
		std::fill_n(_data, _size, val);
    }

    void assign (std::initializer_list<T> il){
        _size = il.size();
        _capacity = _size;
        _data = new T[_size];
        std::copy(il.begin(), il.end(), _data);
    }

	void push_back(const T & n) {
		if (_size == _capacity) resize(_size * 1.5, 0);
		_data[_size] = n;
		_size++;
	}

    void pop_back(){ _size--; }

    void swap(vector& x) {
        std::swap(_size, x._size);
        std::swap(_capacity, x._capacity);
        std::swap(_data, x._data);
    }

    void clear() {
		_size = 0;
		delete[] _data;
		_data = new T[_capacity];
	}

};


#endif