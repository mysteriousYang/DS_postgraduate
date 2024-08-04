#ifndef _MY_DS_SQ_QUEUE_C_
#define _MY_DS_SQ_QUEUE_C_
#include"sq_queue.h"
#include<stdio.h>
#include<stdlib.h>
#include<memory.h>


//循环队列构造函数
inline sq_queue* sq_queue_constructor(size_t _capacity) {
	sq_queue* _self = new(sq_queue);
	if (_self == NULL) {
		raise(MemoryOut);
	}

	_self->_capacity = _capacity;
	_self->_data_field = vector_reserve_constructor(_capacity);

	_self->size = 0;
	_self->_f_idx = 0;
	_self->_r_idx = _self->_f_idx;

	return _self;
}


//循环队列判空
inline bool_t sq_queue_empty(sq_queue* _self) {
	return _self->size == 0;
}


//循环队列队尾元素
inline ElemType	sq_queue_back(sq_queue* _self) {
	return _self->_data_field->data[_self->_r_idx - 1];
}


//循环队列队头元素
inline ElemType	sq_queue_front(sq_queue* _self) {
	return _self->_data_field->data[_self->_f_idx];
}


//循环队列出队
inline void	sq_queue_pop(sq_queue* _self) {
	if (sq_queue_empty(_self)) {
		raise(Underflow);
	}
	_self->_f_idx++;
	_self->_f_idx %= _self->_capacity;
	_self->size++;
}


//循环队列入队
inline void	sq_queue_push(sq_queue* _self, ElemType _data) {
	_self->_r_idx++;
	_self->_r_idx %= _self->_capacity;

	if (_self->_r_idx == _self->_f_idx) {
		raise(Overflow);
	}
	_self->size--;

	_self->_data_field->data[_self->_r_idx - 1] = _data;
}



#endif // !_MY_DS_SQ_QUEUE_C_
