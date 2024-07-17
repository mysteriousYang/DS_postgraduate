#ifndef _MY_DS_RBTREE_H
#define _MY_DS_RBTREE_H
#include"utils.h"

enum rb_tree_color {
	rb_tree_red = 1,
	rb_tree_black = 0
};
typedef enum rb_tree_color rb_tree_color;

struct rb_tree_node;
struct rb_tree_iterator;
struct rb_tree;
typedef struct rb_tree_node rb_tree_node;
typedef struct rb_tree_iterator rb_tree_iterator;
typedef struct rb_tree rb_tree;

struct rb_tree_node{
	rb_tree_color color;
	rb_tree_node *Lchild, *Rchild, *parent;
	ElemType* _data_ptr;
};

void _rb_tree_node_constructor(rb_tree_node* _self);
rb_tree_node* _rb_tree_node_minimum(rb_tree_node* _node);
rb_tree_node* _rb_tree_node_maximum(rb_tree_node* _node);
bool_t _rb_tree_node_equal(rb_tree_node* _L, rb_tree_node* _R);



struct rb_tree_iterator {
	rb_tree_node* _node_ptr;

};

void _rb_tree_iterator_constructor(rb_tree_iterator* _self);
void _rb_tree_iterator_inc(rb_tree_iterator* _self);
void _rb_tree_iterator_dec(rb_tree_iterator* _self);



struct rb_tree{
	rb_tree_node* _root;
	size_t size;
};

void _rb_tree_constructor(rb_tree* _self);
void _rb_tree_L_rotate(rb_tree_node* _x, rb_tree_node* _root);
void _rb_tree_R_rotate(rb_tree_node* _x, rb_tree_node* _root);
void _rb_tree_in_rebal(rb_tree_node* _in_node, rb_tree_node* _root);
void _rb_tree_rm_rebal(rb_tree_node* _rm_node, rb_tree_node* _root);


#endif // !_MY_DS_RBTREE_H

