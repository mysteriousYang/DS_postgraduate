#ifndef _MY_DS_SQ_QUEUE_H_
#define _MY_DS_SQ_QUEUE_H_
#include"utils.h"
#include"vector.h"


enum priority {
	less,
	greater
};

struct sq_queue;
typedef struct sq_queue sq_queue;
struct priority_queue;
struct heap_iterator;
typedef struct heap_iterator heap_iterator;
typedef struct priority_queue priority_queue;
typedef enum priority priority;


struct sq_queue {
	size_t _capacity;
	size_t _f_idx, _r_idx;
	vector* _data_field;
	size_t size;
};

struct heap_iterator {
	priority_queue* _q_ptr;
	size_t Lchild, Rchild, parent, location;
};

struct priority_queue {
	size_t _capacity;
	vector* _data_field;
	priority _pr;
	size_t size;
};


sq_queue*	sq_queue_constructor(size_t _capacity);
bool_t		sq_queue_empty(sq_queue* _self);
ElemType	sq_queue_back(sq_queue* _self);
ElemType	sq_queue_front(sq_queue* _self);
void		sq_queue_pop(sq_queue* _self);
void		sq_queue_push(sq_queue* _self, ElemType _data);
void		sq_queue_destory(sq_queue* _self);

void				heap_iterator_update(heap_iterator* _it);
void				heap_iterator_sink(heap_iterator* _it);
priority_queue*		priority_queue_constructor(priority _pr);
priority_queue*		priority_queue_from_vector(priority _pr, vector* _initializer_list);
void				priority_queue_build_heap(priority_queue* _self);


#endif // !_MY_DS_SQ_QUEUE_H_
