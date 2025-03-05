#ifndef _MY_DS_SINGLE_LIST_H_
#define _MY_DS_SINGLE_LIST_H_
#include"utils.h"


struct single_list;
struct single_list_node;
typedef struct single_list_node single_list_node;
typedef struct single_list_node* single_list_iterator;
typedef struct single_list single_list;


struct single_list_node {
	ElemType* _data_ptr;
	single_list_node* next;

};


single_list_node*	 single_list_make_node();
void				 single_list_destory_node(single_list_node* _self);
single_list_iterator single_list_iterator_inc(single_list_iterator _self);


struct single_list {
	single_list_node* header;
	single_list_iterator begin, end;
	size_t size;

};


single_list* single_list_constructor();
bool_t		single_list_empty(single_list* _self);
void		single_list_push_back(single_list* _self, ElemType _data);
void		single_list_pop_back(single_list* _self);
ElemType	single_list_back(single_list* _self);
void		single_list_push_front(single_list* _self, ElemType _data);
void		single_list_pop_front(single_list* _self);
ElemType	single_list_front(single_list* _self);
void		single_list_remove(single_list* _self, single_list_iterator _it);
void		single_list_print(single_list* _self);
void		single_list_destory(single_list* _self);
void		single_list_test();

single_list_iterator
single_list_find(single_list* _self, ElemType _data);

single_list_iterator
single_list_find_pioneer(single_list* _self, single_list_iterator _node);

single_list_iterator
single_list_find_successor(single_list* _self, single_list_iterator _node);

#endif // !_MY_DS_SINGLE_LIST_H_

