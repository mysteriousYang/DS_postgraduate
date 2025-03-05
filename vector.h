#ifndef _MY_DS_VECTOR_H_
#define _MY_DS_VECTOR_H_
#include"utils.h"

#if !(defined DEFAULT_VECTOR_CAPACITY) || (DEFAULT_VECTOR_CAPACITY <= 0)
#define DEFAULT_VECTOR_CAPACITY 20
#endif // !(defined DEFAULT_VECTOR_CAPACITY) || (DEFAULT_VECTOR_CAPACITY <= 0)



struct vector;
typedef ElemType* vector_iterator;
typedef struct vector vector;


struct vector {
	size_t _capacity;
	size_t size;
	vector_iterator begin, end;
	ElemType* data;

};


vector*		vector_constructor();
vector*		vector_reserve_constructor(size_t _capacity);
vector*		vector_clone(vector* _src);
bool_t		vector_empty(vector* _self);
void		vector_push_back(vector* _self, ElemType _data);
ElemType	vector_back(vector* _self);
void		vector_pop_back(vector* _self);
ElemType	vector_front(vector* _self);
void		vector_remove(vector* _self, vector_iterator _it);
void		vector_print(vector* _self);
void		vector_destory(vector* _self);

vector_iterator vector_find(vector* _self, ElemType _data);
vector_iterator vector_iterator_inc(vector_iterator _self);
vector_iterator vector_iterator_dec(vector_iterator _self);

#endif // !_MY_DS_VECTOR_H_
