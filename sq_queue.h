#ifndef _MY_DS_SQ_QUEUE_H_
#define _MY_DS_SQ_QUEUE_H_
#include"utils.h"
#include"vector.h"


struct sq_queue;
typedef struct sq_queue sq_queue;


struct sq_queue {
	size_t _capacity;
	size_t _f_idx, _r_idx;
	vector* _data_field;
	size_t size;
};


sq_queue*	sq_queue_constructor(size_t _capacity);
bool_t		sq_queue_empty(sq_queue* _self);
ElemType	sq_queue_back(sq_queue* _self);
ElemType	sq_queue_front(sq_queue* _self);
void		sq_queue_pop(sq_queue* _self);
void		sq_queue_push(sq_queue* _self, ElemType _data);


#endif // !_MY_DS_SQ_QUEUE_H_
