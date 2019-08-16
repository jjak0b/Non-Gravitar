#ifndef INCLUDE_MATRIX_CPP // #pragma once crea warning ... quindi utilizzo il metodo old school
#define INCLUDE_MATRIX_CPP

#include "Matrix.hpp"
#include <stddef.h>

namespace Matrix{
	template < class T >
	Matrix<T>::Matrix(unsigned int _rows, unsigned int _columns ){
		this->realRows = _rows;
		this->realColumns = _columns;
		this->rows = _rows;
		this->columns = _columns;
		unsigned int size = (_rows * _columns );
		if( size > 0){
			this->data = new T[ size ];
		}
	}

	template < class T >
	Matrix<T>::~Matrix(){
		if( this->data != NULL ){
			delete[] this->data;
			this->data = NULL;
		}
		this->realRows = 0;
		this->realColumns = 0;
		this->rows = 0;
		this->columns = 0;
	}

	template < class T >
	void Matrix<T>::SetSignificantRows( unsigned int _rows ){
		this->rows = _rows < this->realRows ? _rows : this->realRows;
	}

	template < class T >
	void Matrix<T>::SetSignificantColumns( unsigned int _columns ){
		this->columns = _columns < this->realColumns ? _columns : this->realColumns;
	}

	template < class T >
	unsigned int Matrix<T>::GetRows(){
		return this->rows;
	}

	template < class T >
	unsigned int Matrix<T>::GetColumns(){
		return this->columns;
	}

	template < class T >
	bool Matrix<T>::Load( const T **array2d, unsigned int _rows, unsigned int _columns ){
		if( array2d != NULL ){
			unsigned int min_rows = _rows > this->rows ? this->rows : _rows;
			unsigned int min_columns = _columns > this->columns ? this->columns : _columns;
			for( unsigned int i = 0; i < min_rows; i++ ){
				for( unsigned int j = 0; j < min_columns; j++ ){
					this->SetValue( array2d[ i ][ j ], i, j );
				}
			}
		}
		return false;
	}

	template < class T >
	bool Matrix<T>::SetValue( const T value, unsigned int row, unsigned int column ){
		if( ( row >= 0 && row < this->rows ) && ( column >= 0 && column < this->columns ) ){
			this->data[ ( ( this->realColumns * row ) + column ) ] = value;
			return true;
		}
		else{
			return false;
		}
	}

	template < class T >
	bool Matrix<T>::GetValue( T* value, unsigned int row, unsigned int column ){
		if( value != NULL && ( row >= 0 && row < this->rows ) && ( column >= 0 && column < this->columns ) ){
			*value = this->data[ ( ( this->realColumns * row ) + column ) ];
			return true;
		}
		else {
			return false;
		}
	}

	template < class T >
	void Matrix<T>::Copy( Matrix<T> *_data, unsigned int row, unsigned int column ){
		if( _data != NULL){
			T value;
			for (unsigned int i = 0; i < _data->rows && i < this->rows; i += 1){
				for (unsigned int j = 0; j < _data->columns && j < this->columns; j += 1){
					if( _data->Matrix<T>::GetValue( &value, i, j ) ){
						this->SetValue( value , row+i, column+j );
					}
				}
			}
		}
	}

	template < class T >
	void Matrix<T>::Fill( const T value ){
		for (unsigned int i = 0; i < this->rows; i += 1){
			for (unsigned int j = 0; j < this->columns; j += 1){
				this->data[ ( ( this->realColumns * i ) + j ) ] = value;
			}
		}
	}
}
#endif