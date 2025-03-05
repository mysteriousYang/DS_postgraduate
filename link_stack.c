#ifndef _MY_DS_LINK_STACK_C_
#define _MY_DS_LINK_STACK_C_
#include"link_stack.h"
#include<stdio.h>
#include<stdlib.h>
#include<memory.h>


//链栈构造函数
link_stack* link_stack_constructor() {
	link_stack* _self = new(link_stack);
	if (_self == NULL) {
		raise(MemoryOut);
	}

	_self->_data_field = single_list_constructor();
	_self->size = 0;

	return _self;
}


//链栈判空函数
bool_t link_stack_empty(link_stack* _self) {
	return (_self->size == 0);
}


//链栈入栈
void link_stack_push(link_stack* _self, ElemType _data) {
	single_list_push_back(_self->_data_field, _data);
	_self->size++;
}


//链栈出栈
void link_stack_pop(link_stack* _self) {
	single_list_pop_back(_self->_data_field);
	_self->size--;
}


//获得栈顶元素
ElemType link_stack_back(link_stack* _self) {
	return single_list_back(_self->_data_field);
}


//链栈析构函数
void link_stack_destory(link_stack* _self) {
	single_list_destory(_self->_data_field);
	free(_self);
}


//链栈接口测试
void link_stack_test() {
	link_stack* s = link_stack_constructor();

	srand((unsigned)new(char));

	printf("测试数据：\n");
	ElemType test_data[50];
	for (int i = 0; i < 50; i++) {
		test_data[i] = rand();
		printf("%d\t", test_data[i]);
		link_stack_push(s, test_data[i]);

		if ((i + 1) % 10 == 0) {
			putchar(10);
		}
	}

	putchar(10);
	putchar(10);
	for (int i = 1; !link_stack_empty(s); i++) {
		printf("%d\t", link_stack_back(s));
		link_stack_pop(s);

		if (i % 10 == 0) {
			putchar(10);
		}
	}
}


#endif // !_MY_DS_LINK_STACK_C_
