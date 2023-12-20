#pragma once
#include<iostream>

using namespace std;

template<typename T> class Array
{
private:
	T* arr;
	int size;
	int absolute_size;
public:
	Array();
	Array(int num);
	Array(const Array& arr);
	Array(Array&& arr);

	~Array();

	void append(T element);
	void insert(T element, int index);
	void pop(int index);
	void show();

	T& operator[](int index);
};

template<typename T>
Array<T>::Array(int num) {
	this->arr = new T[ num + num / 2 ];
	this->size = num;
	this->absolute_size = num + num / 2;
}

template<typename T>
Array<T>::Array() :Array(5) {
	this->size = 0;
};

template<typename T>
Array<T>::Array(const Array& arr) {
	this->arr = new T[arr.absolute_size];
	this->size = arr.size;
	for (int i = 0; i < arr.size; i++) {
		this->arr[i] = arr.arr[i];
	}
	this->absolute_size = arr.absolute_size;
}

template<typename T>
Array<T>::Array(Array&& arr) {
	this->arr = arr.arr;
	this->size = size;
	this->absolute_size = arr.absolute_size;

	arr.arr = nullptr;
}

template<typename T>
Array<T>::~Array() {
	delete[] this->arr;
}

template<typename T>
void Array<T>::append(T element) {
	if (this->size < this->absolute_size) {
		this->arr[size] = element;
		this->size++;
	}
	else {
		T* newArr = new T[this->absolute_size + this->absolute_size / 2];
		for (int i = 0; i < this->size; i++) {
			newArr[i] = this->arr[i];
		}
		this->arr = newArr;
		this->size = this->absolute_size;
		this->absolute_size += this->absolute_size / 2;
	}
}

template<typename T>
void Array<T>::insert(T element, int index) {
	if (this->size < this->absolute_size) {
		for (int i = size; i > index; i--) {
			this->arr[i] = this->arr[i - 1];
		}
		this->arr[index] = element;
		this->size++;
	}
	else {
		T* newArr = new T[this->absolute_size + this->absolute_size / 2];
		int skip = 0;
		for (int i = 0; i < this->size; i++) {
			if (i == index) skip = 1;
			newArr[i + skip] = this->arr[i];
		}
		newArr[index] = element;
		this->arr = newArr;
		this->size = this->absolute_size;
		this->absolute_size += this->absolute_size / 2;
	}
}

template<typename T>
void Array<T>::pop(int index) {
	if (this->absolute_size / 2 > this->size) {
		T* newArr = new T[this->size + this->size / 2];
		int skip = 0;
		for (int i = 0; i < this->size; i++) {
			if (i == index) {
				skip = 1;
				continue;
			}
			newArr[i - skip] = this->arr[i = skip];
		}
		this->arr = newArr;
		this->absolute_size = this->size + this->size / 2;
		this->size--;
	}
	else {
		for (int i = index; i < this->size - 1; i++) {
			this->arr[i] = this->arr[i + 1];
		}
		this->size--;
	}
}

template<typename T>
T& Array<T>::operator[](int index) {
	return this->arr[index];
}

template<typename T>
void Array<T>::show() {
	for (int i = 0; i < this->size; i++) {
		cout << this->arr[i] << " ";
	}
}

template Array<int>;
template Array<float>;
template Array<bool>;
template Array<double>;
template Array<char>;