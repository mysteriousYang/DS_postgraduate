#ifndef _MY_DS_LINK_QUEUE_H_
#define _MY_DS_LINK_QUEUE_H_
#include"utils.h"
#include"single_list.h"


struct link_queue;
typedef struct link_queue link_queue;

struct link_queue{
	single_list* _data_field;
	size_t size;
};


link_queue*	link_queue_constructor();
bool_t		link_queue_empty(link_queue* _self);
ElemType	link_queue_back(link_queue* _self);
ElemType	link_queue_front(link_queue* _self);
void		link_queue_push(link_queue* _self, ElemType _data);
void		link_queue_pop(link_queue* _self);

#endif // !_MY_DS_LINK_QUEUE_H_

