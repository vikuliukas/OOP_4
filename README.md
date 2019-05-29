# OOP_4

# Vector kurimas

# Užduoties tikslas:
- sukurti veikiantį vektorių.

# 5 funkcijos:

## reserve

```c++
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
```
- Funkcija `reserve` padidina vectoriaus `_capacity` iki skaičiaus `size`.

## push_back

```c++
	void push_back(const T & value) {
		if (_size == _capacity){
            grow();
        }
        _alloc.construct(_size++, value);
	}
```
- Funkcija `push_back` prideda narį į vectoriaus pabaigą su reišme `value`, jeigu nariui nėra vietos (size == capacity), tada einama į funkciją `grow`, kur padidinama vectoriaus `_capacity`.

## pop_back

```c++
    void pop_back(){
        _size--;
        _alloc.destroy(_size + 1);
    }
```
- Funkcija `pop_back` sunaikiną paskutinį vektoriaus narį ir sumažina vektoriaus `_size`.

## clear

```c++
	void clear() {
		if (_data) {
			iterator it = _capacity;
			while (it != _data) _alloc.destroy(--it);
			_alloc.deallocate(_data, _size - _data);
			_data = _size = _capacity = nullptr;
		}
	}
```
- Funkcija `clear` ištrina vektoriaus elementus.

## swap

```c++
    void swap(vector& x) {
        std::swap(_size, x._size);
        std::swap(_capacity, x._capacity);
        std::swap(_data, x._data);
    }
```
- Funkcija `swap` sukeičia du vektorius vietomis.

# Efektyvumo/spartos analizė:

```shell
##Kai sz = 10000:
- std::vector užtruko: 0.0002537 sek.
- mano vector užtruko: 0.000224 sek.
##Kai sz = 100000:
- std::vector užtruko: 0.0022329 sek.
- mano vector užtruko: 0.002539 sek.
##Kai sz = 1000000:
- std::vector užtruko: 0.0208856 sek.
- mano vector užtruko: 0.0188308 sek.
##Kai sz = 10000000:
- std::vector užtruko: 0.229281 sek.
- mano vector užtruko: 0.229431 sek.
##Kai sz = 100000000:
- std::vector užtruko: 2.16319 sek.
- mano vector užtruko: 2.073 sek.
```
## Atminties perskirstymai
# tikrinimas:
```c++
	int t1=0,t2=0;
	unsigned int sz = 100000000;
	std::vector<int> v1;
	for (int i = 1; i <= sz; ++i){
		v1.push_back(i);
		if(v1.size()==v1.capacity()){
			t1 ++;
		}
	}
	std::cout<<"std::vector: "<<t1<<" kartus\n";
	
	vector<int> v2;
	for (int i = 1; i <= sz; ++i){
		v2.push_back(i);
		if(v2.size()==v2.capacity()){
			t2 ++;
		}
	}
	std::cout<<"mano vector: "<<t2<<" kartus\n";
```
# rezultatas:
```shell
std::vector: 27 kartus
mano vector: 27 kartus
```
# Trečiojo darbo programoje:
## Kai studentų yra 100000 ir kiekvienas iš jų turi 100 pažymių.
```shell
std::vector užtruko: 2.70265 sek.
mano vector užtruko: 2.56225 sek.
```


