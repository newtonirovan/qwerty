#include <iostream>
#include "contact.h"
#include "contactbst.h"
#include "myvector.h"
#include<cstdlib>
#include<iomanip>
#include<stdexcept>
#include<sstream>
using namespace std;

//constructor
template <typename T>
MyVector<T>::MyVector(int cap){
	data = new T[cap];
	v_size = 0;
	v_capacity = cap;
}


//destructor
template <typename T>
MyVector<T>::~MyVector(){
	for (int i = 0; i < v_size; ++i)
	{
		delete data[i];
	}
	delete[] data;
}


//add an element at the end of vector
template <typename T>
void MyVector<T>::push_back(T *element){
	if (v_size == v_capacity){
		T *temp = new T[max(1, 2 * v_capacity)];
		for (int i = 0; i < v_capacity; i++){
			temp[i] = data[i];
		}
		v_capacity = max(1, 2 * v_capacity);
		data = temp;
		delete[] temp;
	}
	data[v_size] = element;
	v_size += 1;
}


//removes an element from the index
template <typename T>
void MyVector<T>::erase(int index){
	if (index > v_size-1){
		cout<<"Invalid index!"<<endl;
	}
	else if (index < 0){
		cout<<"Invalid index!"<<endl;
	}
	else{
		for (int i = index; i < v_size - 1; i++){
			data[i] = data[i+1];
		}
		v_size -= 1;
	}
}


//return reference of the element at index
template <typename T>
T& MyVector<T>::at(int index){
	if (index > v_size-1){
		cout<<"Invalid index!"<<endl;
		return NULL;
	}
	else if (index < 0){
		cout<<"Invalid index!"<<endl;
		return NULL;
	}
	else{
		return data[index];
	}
}

//return current size of vector
template <typename T>
int MyVector<T>::size() const{
	return v_size;
}


//return capacity of vector
template <typename T>
int MyVector<T>::capacity() const{
	return v_capacity;
}


//return true if the vector is empty, false otherwise
template <typename T>
bool MyVector<T>::empty() const{
	if(v_size == 0){
		return true;
	}
	else{
		return false;
	}
}

