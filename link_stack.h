#ifndef _MY_DS_LINK_STACK_H_
#define _MY_DS_LINK_STACK_H_
#include"utils.h"
#include"single_list.h"


struct link_stack;
typedef struct link_stack link_stack;


struct link_stack {
	single_list* _data_field;
	size_t size;
};


link_stack* link_stack_constructor();
bool_t		link_stack_empty(link_stack* _self);
void		link_stack_push(link_stack* _self, ElemType _data);
void		link_stack_pop(link_stack* _self);
ElemType	link_stack_back(link_stack* _self);


#endif //_MY_DS_LINK_STACK_H_
