#ifndef _MY_DS_SINGLE_LIST_C_
#define _MY_DS_SINGLE_LIST_C_
#include"single_list.h"
#include<stdio.h>
#include<stdlib.h>
#include<memory.h>


//����һ�����ĺ���
single_list_node* single_list_make_node() {
	single_list_node* node = new(single_list_node);
	if (node == NULL) {
		raise(MemoryOut);
	}
	node->next = NULL;
	node->_data_ptr = NULL;
	return node;
}


//����������
single_list_iterator single_list_iterator_inc(single_list_iterator _self) {
	return _self->next;
}


//������Ĺ��캯��
single_list* single_list_constructor() {
	single_list* _self = new(single_list);
	if (_self == NULL) {
		raise(MemoryOut);
	}

	_self->size = 0;
	_self->header = single_list_make_node();
	_self->header->next = single_list_make_node();

	_self->begin = _self->header->next;
	_self->end = _self->begin;
	return _self;
}


void single_list_destory_node(single_list_node* _self) {
	free(_self->_data_ptr);
	free(_self);
}


//�������п�
bool_t single_list_empty(single_list* _self) {
	return _self->begin == _self->end;
}


//������β��
void single_list_push_back(single_list* _self, ElemType _data) {
	if(_self->end->_data_ptr == NULL)
		_self->end->_data_ptr = new(ElemType);
	if (_self->end->_data_ptr == NULL) {
		raise(MemoryOut);
	}

	*_self->end->_data_ptr = _data;
	_self->end->next = single_list_make_node();
	_self->end = _self->end->next;
	_self->size++;
}


//�����������
void single_list_pop_back(single_list* _self) {
	if (single_list_empty(_self)) {
		raise(Underflow);
	}
	single_list_iterator _last_elem = single_list_find_pioneer(_self, _self->end);
	_last_elem->next = NULL;
	single_list_destory_node(_self->end);
	_self->end = _last_elem;
	_self->size++;
}


//��ȡβ��Ԫ��
ElemType single_list_back(single_list* _self) {
	if (single_list_empty(_self)) {
		raise(Underflow);
	}
	return *single_list_find_successor(_self, _self->end)->_data_ptr;
}


//������ͷ��
void single_list_push_front(single_list* _self, ElemType _data) {
	single_list_iterator _first_node = _self->begin;
	_self->begin = single_list_make_node();
	_self->header->next = _self->begin;

	_self->begin->_data_ptr = new(ElemType);
	if (_self->begin->_data_ptr == NULL) {
		raise(MemoryOut);
	}
	*_self->begin->_data_ptr = _data;

	_self->begin->next = _first_node;
	_self->size++;
}


//��������ͷ��Ԫ��
void single_list_pop_front(single_list* _self) {
	if (single_list_empty(_self)) {
		raise(Underflow);
	}

	single_list_iterator _temp = _self->begin;
	_self->begin = single_list_iterator_inc(_self->begin);
	_self->header->next = _self->begin;
	free(_temp);
	_self->size--;
}


//�������ͷ��Ԫ��
ElemType single_list_front(single_list* _self) {
	if (single_list_empty(_self)) {
		raise(Underflow);
	}
	return *(_self->begin->_data_ptr);
}


//ɾ������Ԫ��
void single_list_remove(single_list* _self, single_list_iterator _it) {
	if (single_list_empty(_self)) {
		raise(Underflow);
	}

	single_list_iterator _pion = single_list_find_pioneer(_self, _it);
	_pion->next = _it->next;
	single_list_destory_node(_it);
	_self->size--;
}


//��ӡ����Ԫ��
void single_list_print(single_list* _self) {
	for (single_list_iterator _it = _self->begin;
		_it != _self->end;
		_it = single_list_iterator_inc(_it)) {
		if (sizeof(ElemType) == 4)
			printf("%d ", *_it->_data_ptr);
		else if (sizeof(ElemType) == 8)
			printf("%lf ", *_it->_data_ptr);
	}
	putchar('\n');
}


//��������������
void single_list_destory(single_list* _self) {
	single_list_iterator _p = _self->begin;
	single_list_iterator _q;
	while (_p != _self->end) {
		_q = _p;
		_p = single_list_iterator_inc(_p);
		free(_q);
	}
	free(_self->header);
	free(_self->end);
	free(_self);
}


//����Ԫ��
single_list_iterator
single_list_find(single_list* _self, ElemType _data) {
	for (single_list_iterator _it = _self->begin;
		_it != _self->end;
		_it = single_list_iterator_inc(_it)
		) {
		if (*_it->_data_ptr == _data)
			return _it;
	}
	return _self->end;
}


//Ѱ��ĳ������ǰ��
single_list_iterator
single_list_find_pioneer(single_list* _self, single_list_iterator _node) {
	single_list_iterator _it = _self->begin;
	while (_it->next != _node)
		_it = single_list_iterator_inc(_it);
	return _it;
}


//Ѱ��ĳ�����ĺ��(��Ȼ��ʵ����Ҫ����������)
single_list_iterator
single_list_find_successor(single_list* _self, single_list_iterator _node) {
	return single_list_iterator_inc(_node);
}


#endif // !_MY_DS_SINGLE_LIST_C_
