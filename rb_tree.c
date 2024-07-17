#ifndef _MY_DS_RBTREE_C
#define _MY_DS_RBTREE_C
#include<stdlib.h>
#include"rb_tree.h"

//给定一个起始结点,寻找其最小值
rb_tree_node* _rb_tree_node_minimum(rb_tree_node* _node) {
	while (_node->Lchild != NULL) {
		_node = _node->Lchild;
	}
	return _node;
}


//给点一个起始结点,寻找其最大值
rb_tree_node* _rb_tree_node_maximum(rb_tree_node* _node) {
	while (_node->Rchild != NULL) {
		_node = _node->Rchild;
	}
	return _node;
}


//判断两个结点是否相等
bool_t _rb_tree_node_equal(rb_tree_node* _L, rb_tree_node* _R) {
	return *_L->_data_ptr = *_R->_data_ptr;
}


//迭代器自增
void _rb_tree_iterator_inc(rb_tree_iterator* _self) {
	//若右子树存在,则前往右子树的最左结点
	if (_self->_node_ptr->Rchild != NULL) {
		_self->_node_ptr = _self->_node_ptr->Rchild;
		while (_self->_node_ptr->Lchild != NULL) {
			_self->_node_ptr = _self->_node_ptr->Lchild;
		}
	}
	else {
		//右子树不存在，寻找向上回溯其中序后继
		rb_tree_node* _temp = _self->_node_ptr->parent;
		while (_self->_node_ptr != _temp->Rchild) {
			_self->_node_ptr = _temp;
			_temp = _temp->parent;
		}
		//这里用来处理直接从右子树爬到根的情况
		//例如中序遍历的最后一个结点
		if (_self->_node_ptr->Rchild != _temp) {
			_self->_node_ptr = _temp;
		}
	}
}


//迭代器自减
void _rb_tree_iterator_dec(rb_tree_iterator* _self) {
	if (_self->_node_ptr->Lchild != NULL) {
		_self->_node_ptr = _self->_node_ptr->Lchild;
		while (_self->_node_ptr->Rchild != NULL) {
			_self->_node_ptr = _self->_node_ptr->Rchild;
		}
	}
	else {
		rb_tree_node* _temp = _self->_node_ptr->parent;
		while (_self->_node_ptr != _temp->Lchild) {
			_self->_node_ptr = _temp;
			_temp = _temp->parent;
		}
		_self->_node_ptr = _temp;
	}
}


void _rb_tree_L_rotate(rb_tree_node* _x, rb_tree_node* _root) {
	//注意这里是整棵树的root
	//右旋主要操作的是旋转中心结点x与其左孩子
	rb_tree_node* _temp = _x->Rchild;

	//将x左孩子的右子树过继给x
	_x->Rchild = _temp->Lchild;
	if (_temp->Lchild != NULL) {
		//如果x左孩子的右孩子存在,则报告其父节点更新
		_temp->Lchild->parent = _x;
	}
	//将x本身的父结点过继给其左孩子
	_temp->parent = _x->parent;

	if (_x == _root) {
		_root = _temp;
	}
	else if (_x == _x->parent->Lchild) {
		//如果x是其父结点的右孩子,则向其父结点报告其右孩子更新
		_x->parent->Lchild = _temp;
	}
	else {
		//否则,向其父结点报告其左孩子更新
		_x->parent->Rchild = _temp;
	}
	//建立x与其左孩子的双向链接
	_temp->Lchild = _x;
	_x->parent = _temp;
}


void _rb_tree_R_rotate(rb_tree_node* _x, rb_tree_node* _root) {
	rb_tree_node* _temp = _x->Lchild;
	_x->Lchild = _temp->Rchild;
	if (_temp->Rchild != NULL) {
		_temp->Rchild->parent = _x;
	}
	_temp->parent = _x->parent;

	if (_x == _root) {
		_root = _temp;
	}
	else if (_x == _x->parent->Rchild) {
		_x->parent->Rchild = _temp;
	}
	else {
		_x->parent->Lchild = _temp;
	}
	_temp->Rchild = _x;
	_x->parent = _temp;
}


//插入结点后的红黑树自平衡函数
void _rb_tree_in_rebal(rb_tree_node* _in_node, rb_tree_node* _root) {
	//插入共有12种可能,其中有4种是不需要进行调整的
	// <<< Group 1 >>>
	// 序号 插入结点相对父结点位置 父结点颜色 父结点相对祖父结点位置 叔叔结点颜色
	// 1	L					B			L				*
	// 2	L					B			R				*
	// 3	R					B			L				*
	// 4	R					B			R				*
	// 调整策略: 不调整
	// 
	// <<< Group 2 >>>
	// 序号 插入结点相对父结点位置 父结点颜色 父结点相对祖父结点位置 叔叔结点颜色
	// 5	L					R			L				NULL
	// 6	L					R			R				NULL
	// 7	R					R			L				NULL
	// 8	R					R			R				NULL
	// 调整策略:	5/8
	//			将父结点染黑
	//			将组父结点染红
	//			旋转父结点(5:右旋, 8:左旋)
	// 
	//			6/7
	//			将插入结点染黑
	//			将组父结点染红
	//			旋转父结点(6:左旋, 7:右旋)
	//			旋转组父结点(6:右旋, 7:左旋)
	// 
	// <<< Group 3 >>>
	// 序号 插入结点相对父结点位置 父结点颜色 父结点相对祖父结点位置 叔叔结点颜色
	// 9	L					R			L				R
	// 10	L					R			R				R
	// 11	R					R			L				R
	// 12	R					R			R				R
	// 调整策略:	将父结点和叔叔结点染黑
	//			将祖父结点染红
	//			递归,将祖父结点插入上一层

	//首先将插入结点设为红色
	_in_node->color = rb_tree_red;

	//两个连续的红色结点才需调整
	while (_in_node != _root
		&& _in_node->parent->color == rb_tree_red) {
		
		//如果插入结点的父节点是祖父结点的左孩子
		if (_in_node->parent == _in_node->parent->parent->Lchild) {
			rb_tree_node* _uncle = _in_node->parent->parent->Rchild;
			
			//如果叔叔结点存在并且是红色的
			if (_uncle != NULL && _uncle->color == rb_tree_red) {
				//情况9 11
				_in_node->parent->color = rb_tree_black;
				_uncle->color = rb_tree_black;
				_in_node->parent->parent->color = rb_tree_red;
				_in_node = _in_node->parent->parent;
			}

			else {
				if (_in_node == _in_node->parent->Rchild) {
					//情况6
					_in_node = _in_node->parent;
					_rb_tree_L_rotate(_in_node, _root);
				}
				//情况5
				_in_node->color = rb_tree_black;
				_in_node->parent->parent = rb_tree_red;
				_rb_tree_R_rotate(_in_node->parent->parent, _root);
			}
		}
	
		//考虑插入结点的父节点是祖父结点的右孩子
		else {
			rb_tree_node* _uncle = _in_node->parent->parent->Lchild;

			if (_uncle != NULL && _uncle->color == rb_tree_red) {
				//情况10 12
				_in_node->parent->color = rb_tree_black;
				_uncle->color = rb_tree_black;
				_in_node->parent->parent->color = rb_tree_red;
				_in_node = _in_node->parent->parent;
			}

			else {
				if (_in_node == _in_node->parent->Lchild) {
					//情况7
					_in_node = _in_node->parent;
					_rb_tree_R_rotate(_in_node, _root);
				}
				_in_node->color = rb_tree_black;
				_in_node->parent->parent->color = rb_tree_red;
				_rb_tree_L_rotate(_in_node->parent->parent, _root);
			}
		}
		//情况0 插入根结点
		_root->color = rb_tree_black;
	}
}

#endif // !_MY_DS_RBTREE_C