#ifndef _MY_DS_LINK_QUEUE_C_
#define _MY_DS_LINK_QUEUE_C_
#include"link_queue.h"
#include<stdio.h>
#include<stdlib.h>
#include<memory.h>

//��ʽ���й��캯��
link_queue* link_queue_constructor() {
	link_queue* _self = new(link_queue);
	if (_self == NULL) {
		raise(MemoryOut);
	}

	_self->_data_field = single_list_constructor();

	_self->size = 0;
	return _self;
}


//��ö���βԪ��
ElemType link_queue_back(link_queue* _self) {
	return single_list_back(_self->_data_field);
}


//��ö���ͷԪ��
ElemType link_queue_front(link_queue* _self) {
	return single_list_front(_self->_data_field);
}


//��ʽ�����п�
bool_t link_queue_empty(link_queue* _self) {
	return (_self->size == 0);
}


//��ʽ�������
void link_queue_push(link_queue* _self, ElemType _data) {
	single_list_push_back(_self->_data_field, _data);
	_self->size++;
}


//��ʽ���г���
void link_queue_pop(link_queue* _self) {
	single_list_pop_front(_self->_data_field);
	_self->size--;
}


//��ʽ��������
void link_queue_destory(link_queue* _self) {
	single_list_destory(_self->_data_field);
	free(_self);
}


//��ʽ���нӿڲ���
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
