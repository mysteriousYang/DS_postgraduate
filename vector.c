#ifndef _MY_DS_VECTOR_C_
#define _MY_DS_VECTOR_C_
#define _CRT_SECURE_NO_WARNINGS
#include"vector.h"
#include<stdlib.h>
#include<stdio.h>
#include<memory.h>


//动态数组的构造函数
inline vector* vector_constructor() {
	vector* _self = new(vector);
	if (_self == NULL) {
		raise(MemoryOut);
	}

	_self->_capacity = DEFAULT_VECTOR_CAPACITY;
	_self->data = (ElemType*)calloc(_self->_capacity, sizeof(ElemType));
	if (_self->data == NULL) {
		raise(MemoryOut);
	}

	_self->size = 0;
	_self->begin = _self->data;
	_self->end = _self->begin + _self->size;

	return _self;
}


//带预分配的接口
inline vector* vector_reserve_constructor(size_t _capacity) {
	vector* _self = new(vector);
	if (_self == NULL) {
		raise(MemoryOut);
	}

	_self->_capacity = _capacity;
	_self->data = (ElemType*)calloc(_self->_capacity, sizeof(ElemType));

	if (_self->data == NULL) {
		raise(MemoryOut);
	}

	_self->size = 0;
	_self->begin = _self->data;
	_self->end = _self->begin + _self->size;

	return _self;
}


//动态数组判空
bool_t vector_empty(vector* _self) {
	return _self->begin == _self->end;
}


//动态数组尾插
void vector_push_back(vector* _self, ElemType _data) {
	//如果不够长就延长一下
	if (_self->_capacity <= _self->size + 1) {
		_self->data = (ElemType*)realloc(
			_self->data,
			2 * _self->_capacity * sizeof(ElemType)
		);
		if (_self->data == NULL) {
			raise(MemoryOut);
		}
		_self->_capacity *= 2;
	}
	*_self->end = _data;
	_self->end = vector_iterator_inc(_self->end);
	_self->size++;
}


//返回尾部元素
ElemType vector_back(vector* _self) {
	if (vector_empty(_self)) {
		raise(Underflow);
	}
	return *(vector_iterator_dec(_self->end));
}


//弹出尾部元素
void vector_pop_back(vector* _self) {
	if (vector_empty(_self)) {
		raise(Underflow);
	}
	_self->end = vector_iterator_dec(_self->end);
	_self->size--;
}


//返回首部元素
ElemType vector_front(vector* _self) {
	if (vector_empty(_self)) {
		raise(Underflow);
	}
	return *_self->begin;

}


//移除元素
void vector_remove(vector* _self, vector_iterator _it) {
	memcpy(_it, _it + 1, (_self->end - _it - 1) / sizeof(ElemType));
	_self->end--;
	_self->size--;
}


//打印数组元素
void vector_print(vector* _self) {
	for (vector_iterator _it = _self->begin;
		_it != _self->end;
		_it = vector_iterator_inc(_it)) {
		if (sizeof(ElemType) == 4)
			printf("%d ", *_it);
		else if (sizeof(ElemType) == 8)
			printf("%lf ", *_it);
	}
	putchar('\n');
}


//动态数组析构函数
void vector_destory(vector* _self) {
	free(_self->data);
	free(_self);
}


//查找元素
vector_iterator vector_find(vector* _self, ElemType _data) {
	for (vector_iterator _it = _self->begin;
		_it != _self->end;
		_it = vector_iterator_inc(_it)
		) {
		if (*_it == _data)
			return _it;
	}
	return _self->end;
}


//迭代器自增
vector_iterator vector_iterator_inc(vector_iterator _self) {
	return _self + 1;
}


//迭代器自减
vector_iterator vector_iterator_dec(vector_iterator _self) {
	return _self - 1;
}


#endif // !_MY_DS_VECTOR_C_
