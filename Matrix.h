#pragma once

#include <iostream>

template<typename T>
class Matrix{
	protected:
		int m_row;
		int m_column;
		T** m_arr_2d;
	public:
		Matrix() = delete;
		Matrix(int,int);
		virtual ~Matrix();
		Matrix(const Matrix<T>&);
		Matrix<T>& operator =(const Matrix<T>&);
		Matrix(Matrix<T>&&);
		Matrix<T>& operator =(Matrix<T>&&);
};

template<typename T>
Matrix<T>::Matrix(int n, int m){
	if (n < 1 || m < 1){
		std::cerr << "Sizes of matrix can't be negative or 0\n";
		exit(0);
	}
	m_row = n;
	m_column = m;
	m_arr_2d = new T*[m_row];
	for(int i = 0; i < m_row; i++){
		m_arr_2d[i] = new T[m_column];
	}
}

template<typename T>
Matrix<T>::~Matrix(){
	for(int i = 0; i < m_row; i++){
		delete[] m_arr_2d[i];
		m_arr_2d[i] = nullptr;
	}
	delete[] m_arr_2d;
	m_arr_2d = nullptr;
}

template<typename T>
Matrix<T>::Matrix(const Matrix<T>& obj){
	this->m_row = obj.m_row;
	this->m_column = obj.m_column;
	this->m_arr_2d = new T*[this->m_row];
	for (int i = 0; i < this->m_row; i++){
		this->m_arr_2d[i] = new T[this->m_column];
		for (int j = 0; j < m_column; j++){
			this->m_arr_2d[i][j] = obj.m_arr_2d[i][j];
		}
	}
}

template<typename T>
Matrix<T>& Matrix<T>::operator = (const Matrix<T>& obj){
	if (this != &obj){
		for (int i = 0; i < this->m_row; i++){
			delete[] this->m_arr_2d[i];
			this->m_arr_2d[i] = nullptr;
		}
		delete[] this->m_arr_2d;
		this->m_arr_2d = nullptr;
		this->m_row = obj.m_row;
		this->m_column = obj.m_column;
		this->m_arr_2d = new T*[this->m_row];
		for (int i = 0; i < this->m_row; i++){
			this->m_arr_2d[i] = new T[this->m_column];
			for (int j = 0; j < m_column; j++){
				this->m_arr_2d[i][j] = obj.m_arr_2d[i][j];
			}
		}
	}
	return *this;
}

template<typename T>
Matrix<T>::Matrix(Matrix<T>&& obj)
	: m_row(obj.m_row), m_column(obj.m_column), m_arr_2d(obj.m_arr_2d)
{
	obj.m_row = 0;
	obj.m_column = 0;
	obj.m_arr_2d = nullptr;
}

template<typename T>
Matrix<T>& Matrix<T>::operator=(Matrix<T>&& obj)
{
	if (this != &obj){
		for (int i = 0; i < this->m_row; i++){
			delete[] this->m_arr_2d[i];
		}
		delete[] this->m_arr_2d;
		this->m_row = obj.m_row;
		this->m_column = obj.m_column;
		this->m_arr_2d = obj.m_arr_2d;
		obj.m_row = 0;
		obj.m_column = 0;
		obj.m_arr_2d = nullptr;
	}
	return *this;
}