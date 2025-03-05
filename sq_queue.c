#ifndef _MY_DS_SQ_QUEUE_C_
#define _MY_DS_SQ_QUEUE_C_
#include"sq_queue.h"
#include<stdio.h>
#include<stdlib.h>
#include<memory.h>


//循环队列构造函数
sq_queue* sq_queue_constructor(size_t _capacity) {
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
bool_t sq_queue_empty(sq_queue* _self) {
	return _self->size == 0;
}


//循环队列队尾元素
ElemType sq_queue_back(sq_queue* _self) {
	return _self->_data_field->data[_self->_r_idx - 1];
}


//循环队列队头元素
ElemType sq_queue_front(sq_queue* _self) {
	return _self->_data_field->data[_self->_f_idx];
}


//循环队列出队
void sq_queue_pop(sq_queue* _self) {
	if (sq_queue_empty(_self)) {
		raise(Underflow);
	}
	_self->_f_idx++;
	_self->_f_idx %= _self->_capacity;
	_self->size++;
}


//循环队列入队
void sq_queue_push(sq_queue* _self, ElemType _data) {
	_self->_r_idx++;
	_self->_r_idx %= _self->_capacity;

	if (_self->_r_idx == _self->_f_idx) {
		raise(Overflow);
	}
	_self->size--;

	_self->_data_field->data[_self->_r_idx - 1] = _data;
}


//循环队列析构函数
void sq_queue_destory(sq_queue* _self) {
	while (!sq_queue_empty(_self)) {
		sq_queue_pop(_self);
	}
}


//堆迭代器自检，修改parent等字段
void heap_iterator_update(heap_iterator* _it) {
	_it->parent = _it->location / 2;
	_it->Lchild = 2 * _it->location + 1;
	_it->Rchild = 2 * _it->location + 2;

	if (_it->Lchild >= _it->_q_ptr->size) {
		_it->Lchild = _it->_q_ptr->size;
	}
	if (_it->Rchild >= _it->_q_ptr->size) {
		_it->Rchild = _it->_q_ptr->size;
	}
}


//堆迭代器下沉
void heap_iterator_sink(heap_iterator* _it) {
	size_t xchg = _it->Lchild;
	while (_it->Lchild != _it->_q_ptr->size) {
		if (_it->_q_ptr->_pr == greater) {
			if (_it->_q_ptr->_data_field->data[_it->Rchild]
			> _it->_q_ptr->_data_field->data[_it->Lchild]) {
				xchg = _it->Rchild;
			}

			if (_it->_q_ptr->_data_field->data[_it->location]
				< _it->_q_ptr->_data_field->data[xchg]) {
				ElemType temp = _it->_q_ptr->_data_field->data[_it->location];
				_it->_q_ptr->_data_field->data[_it->location] = _it->_q_ptr->_data_field->data[xchg];
				_it->_q_ptr->_data_field->data[xchg] = temp;

				_it->location = xchg;
				heap_iterator_update(_it);
			}
			break;
		}

		//less
		else {
			if (_it->_q_ptr->_data_field->data[_it->Rchild]
				< _it->_q_ptr->_data_field->data[_it->Lchild]) {
				xchg = _it->Rchild;
			}

			if (_it->_q_ptr->_data_field->data[_it->location]
				> _it->_q_ptr->_data_field->data[xchg]) {
				ElemType temp = _it->_q_ptr->_data_field->data[_it->location];
				_it->_q_ptr->_data_field->data[_it->location] = _it->_q_ptr->_data_field->data[xchg];
				_it->_q_ptr->_data_field->data[xchg] = temp;

				_it->location = xchg;
				heap_iterator_update(_it);
			}
			break;
		}
	}
}


//优先队列构造函数
priority_queue* priority_queue_constructor(priority _pr) {
	priority_queue* _self = new(priority_queue);
	if (_self == NULL) {
		raise(MemoryOut);
	}

	_self->_data_field = vector_constructor();
	_self->_capacity = _self->_data_field->_capacity;
	_self->size = 0;

	_self->_pr = _pr;

	return _self;
}


//优先队列基于向量的构造函数
priority_queue* priority_queue_from_vector(priority _pr, vector* _initializer_list) {
	priority_queue* _self = new(priority_queue);
	if (_self == NULL) {
		raise(MemoryOut);
	}

	_self->_data_field = vector_clone(_initializer_list);
	_self->_capacity = _self->_data_field->_capacity;
	_self->size = _self->_data_field->size;

	_self->_pr = _pr;

	return _self;
}


#endif // !_MY_DS_SQ_QUEUE_C_
