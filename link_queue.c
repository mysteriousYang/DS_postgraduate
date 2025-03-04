#ifndef _MY_DS_LINK_QUEUE_C_
#define _MY_DS_LINK_QUEUE_C_
#include"link_queue.h"
#include<stdio.h>
#include<stdlib.h>
#include<memory.h>

//链式队列构造函数
link_queue* link_queue_constructor() {
	link_queue* _self = new(link_queue);
	if (_self == NULL) {
		raise(MemoryOut);
	}

	_self->_data_field = single_list_constructor();

	_self->size = 0;
	return _self;
}


//获得队列尾元素
ElemType link_queue_back(link_queue* _self) {
	return single_list_back(_self->_data_field);
}


//获得队列头元素
ElemType link_queue_front(link_queue* _self) {
	return single_list_front(_self->_data_field);
}


//链式队列判空
bool_t link_queue_empty(link_queue* _self) {
	return (_self->size == 0);
}


//链式队列入队
void link_queue_push(link_queue* _self, ElemType _data) {
	single_list_push_back(_self->_data_field, _data);
	_self->size++;
}


//链式队列出队
void link_queue_pop(link_queue* _self) {
	single_list_pop_front(_self->_data_field);
	_self->size--;
}


//链式队列析构
void link_queue_destory(link_queue* _self) {
	single_list_destory(_self->_data_field);
	free(_self);
}


//链式队列接口测试
void link_queue_test() {
	srand((unsigned)new(char));
	link_queue* q = link_queue_constructor();

	for (int i = 0; i < 50; i++) {
		link_queue_push(q, rand());
	}

	for (int i = 1; !link_queue_empty(q);i++) {
		printf("%d\t", link_queue_front(q));
		link_queue_pop(q);
		if (i % 10 == 0) {
			putchar(10);
		}
	}

	link_queue_destory(q);
}

#endif // !_MY_DS_LINK_QUEUE_C_
