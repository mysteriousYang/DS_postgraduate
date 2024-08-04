#ifndef _MY_DS_RBTREE_C
#define _MY_DS_RBTREE_C
#include<stdlib.h>
#include"rb_tree.h"


//��㹹�캯��
inline rb_tree_node* _rb_tree_node_constructor() {
	rb_tree_node* _self = new(rb_tree_node);
	if (_self == NULL) {
		raise(MemoryOut);
	}

	_self->Lchild = NULL;
	_self->Rchild = NULL;
	_self->_data_ptr = NULL;

	_self->color = rb_tree_red;
	return _self;
}


//����һ����ʼ���,Ѱ������Сֵ
rb_tree_node* _rb_tree_node_minimum(rb_tree_node* _node) {
	while (_node->Lchild != NULL) {
		_node = _node->Lchild;
	}
	return _node;
}


//����һ����ʼ���,Ѱ�������ֵ
rb_tree_node* _rb_tree_node_maximum(rb_tree_node* _node) {
	while (_node->Rchild != NULL) {
		_node = _node->Rchild;
	}
	return _node;
}


//�ж���������Ƿ����
bool_t _rb_tree_node_equal(rb_tree_node* _L, rb_tree_node* _R) {
	return *_L->_data_ptr = *_R->_data_ptr;
}


//����������
rb_tree_iterator _rb_tree_iterator_inc(rb_tree_iterator _self) {
	//������������,��ǰ����������������
	if (_self->Rchild != NULL) {
		_self = _self->Rchild;
		while (_self->Lchild != NULL) {
			_self = _self->Lchild;
		}
	}
	else {
		//�����������ڣ�Ѱ�����ϻ�����������
		rb_tree_node* _temp = _self->parent;
		while (_self != _temp->Rchild) {
			_self = _temp;
			_temp = _temp->parent;
		}
		//������������ֱ�Ӵ������������������
		//����������������һ�����
		if (_self->Rchild != _temp) {
			_self = _temp;
		}
	}
	return _self;
}


//�������Լ�
rb_tree_iterator _rb_tree_iterator_dec(rb_tree_iterator _self) {
	if (_self->Lchild != NULL) {
		_self = _self->Lchild;
		while (_self->Rchild != NULL) {
			_self = _self->Rchild;
		}
	}
	else {
		rb_tree_node* _temp = _self->parent;
		while (_self != _temp->Lchild) {
			_self = _temp;
			_temp = _temp->parent;
		}
		_self = _temp;
	}
	return _self;
}


void _rb_tree_L_rotate(rb_tree_node* _x, rb_tree_node* _root) {
	//ע����������������root
	//������Ҫ����������ת���Ľ��x��������
	rb_tree_node* _temp = _x->Rchild;

	//��x���ӵ����������̸�x
	_x->Rchild = _temp->Lchild;
	if (_temp->Lchild != NULL) {
		//���x���ӵ��Һ��Ӵ���,�򱨸��丸�ڵ����
		_temp->Lchild->parent = _x;
	}
	//��x����ĸ������̸�������
	_temp->parent = _x->parent;

	if (_x == _root) {
		_root = _temp;
	}
	else if (_x == _x->parent->Lchild) {
		//���x���丸�����Һ���,�����丸��㱨�����Һ��Ӹ���
		_x->parent->Lchild = _temp;
	}
	else {
		//����,���丸��㱨�������Ӹ���
		_x->parent->Rchild = _temp;
	}
	//����x�������ӵ�˫������
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


//�������ĺ������ƽ�⺯��
void _rb_tree_in_rebal(rb_tree_node* _in_node, rb_tree_node* _root) {
	//���빲��12�ֿ���,������4���ǲ���Ҫ���е�����
	// <<< Group 1 >>>
	// ��� ��������Ը����λ�� �������ɫ ���������游���λ�� ��������ɫ
	// 1	L					B			L				*
	// 2	L					B			R				*
	// 3	R					B			L				*
	// 4	R					B			R				*
	// ��������: ������
	// 
	// <<< Group 2 >>>
	// ��� ��������Ը����λ�� �������ɫ ���������游���λ�� ��������ɫ
	// 5	L					R			L				NULL
	// 6	L					R			R				NULL
	// 7	R					R			L				NULL
	// 8	R					R			R				NULL
	// ��������:	5/8
	//			�������Ⱦ��
	//			���鸸���Ⱦ��
	//			��ת�����(5:����, 8:����)
	// 
	//			6/7
	//			��������Ⱦ��
	//			���鸸���Ⱦ��
	//			��ת�����(6:����, 7:����)
	//			��ת�鸸���(6:����, 7:����)
	// 
	// <<< Group 3 >>>
	// ��� ��������Ը����λ�� �������ɫ ���������游���λ�� ��������ɫ
	// 9	L					R			L				R
	// 10	L					R			R				R
	// 11	R					R			L				R
	// 12	R					R			R				R
	// ��������:	��������������Ⱦ��
	//			���游���Ⱦ��
	//			�ݹ�,���游��������һ��

	//���Ƚ���������Ϊ��ɫ
	_in_node->color = rb_tree_red;

	//���������ĺ�ɫ���������
	while (_in_node != _root
		&& _in_node->parent->color == rb_tree_red) {
		
		//���������ĸ��ڵ����游��������
		if (_in_node->parent == _in_node->parent->parent->Lchild) {
			rb_tree_node* _uncle = _in_node->parent->parent->Rchild;
			
			//�����������ڲ����Ǻ�ɫ��
			if (_uncle != NULL && _uncle->color == rb_tree_red) {
				//���9 11
				_in_node->parent->color = rb_tree_black;
				_uncle->color = rb_tree_black;
				_in_node->parent->parent->color = rb_tree_red;
				_in_node = _in_node->parent->parent;
			}

			else {
				if (_in_node == _in_node->parent->Rchild) {
					//���6
					_in_node = _in_node->parent;
					_rb_tree_L_rotate(_in_node, _root);
				}
				//���5
				_in_node->color = rb_tree_black;
				_in_node->parent->parent->color = rb_tree_red;
				_rb_tree_R_rotate(_in_node->parent->parent, _root);
			}
		}
	
		//���ǲ�����ĸ��ڵ����游�����Һ���
		else {
			rb_tree_node* _uncle = _in_node->parent->parent->Lchild;

			if (_uncle != NULL && _uncle->color == rb_tree_red) {
				//���10 12
				_in_node->parent->color = rb_tree_black;
				_uncle->color = rb_tree_black;
				_in_node->parent->parent->color = rb_tree_red;
				_in_node = _in_node->parent->parent;
			}

			else {
				if (_in_node == _in_node->parent->Lchild) {
					//���7
					_in_node = _in_node->parent;
					_rb_tree_R_rotate(_in_node, _root);
				}
				_in_node->color = rb_tree_black;
				_in_node->parent->parent->color = rb_tree_red;
				_rb_tree_L_rotate(_in_node->parent->parent, _root);
			}
		}
		//���0 ��������
		_root->color = rb_tree_black;
	}
}


//ɾ����������ƽ��
inline rb_tree_node* _rb_tree_rm_rebal(
	rb_tree_node* _z,
	rb_tree_node** _ptr_root,
	rb_tree_node** _ptr_leftmost,
	rb_tree_node** _ptr_rightmost) 
{
	rb_tree_node* _y = _z;
	rb_tree_node* _x = NULL;
	rb_tree_node* _x_parent = NULL;

	if (_y->Lchild == NULL) {
		_x = _y->Rchild;
	}
	else {
		if (_y->Rchild == NULL) {
			_x = _y->Lchild;
		}
		else {
			_y = _y->Rchild;
			while (_y->Lchild!=NULL){
				_y = _y->Lchild;
			}
			_x = _y->Rchild;
		}
	}
	if (_y != _z) {
		_z->Lchild->parent = _y;
		_y->Lchild = _z->Lchild;
		if (_y != _z->Rchild) {
			_x_parent = _y->parent;
			if (_x != NULL) {
				_x->parent = _y->parent;
			}
			_y->parent->Lchild = _x;
			_y->Rchild = _z->Rchild;
			_z->Rchild->parent = _y;
		}
		else {
			_x_parent = _y;
		}
		if (*_ptr_root == _z) {
			*_ptr_root = _y;
		}
		else if(_z->parent->Lchild == _z){
			_z->parent->Lchild = _y;
		}
		else {
			_z->parent->Rchild = _y;
			_y->parent = _z->parent;

			rb_tree_color _temp = _y->color;
			_y->color = _z->color;
			_z->color = _temp;

			_y = _z;
		}
	}
	else {
		_x_parent = _y->parent;
		if (_x != NULL) {
			_x->parent = _y->parent;
		}
		if (*_ptr_root == _z) {
			*_ptr_root = _x;
		}
		else {
			if (_z->parent->Lchild == _x) {
				_z->parent->Lchild = _x;
			}
			else {
				_z->parent->Rchild = _x;
			}
		}
		if (*_ptr_leftmost == _z) {
			if (_z->Rchild == 0) {
				*_ptr_leftmost = _z->parent;
			}
			else {
				*_ptr_leftmost = _rb_tree_node_minimum(_x);
			}
		}
		if (*_ptr_rightmost == _z) {
			if (_z->Lchild == NULL) {
				*_ptr_rightmost = _z->parent;
			}
			else{
				*_ptr_rightmost = _rb_tree_node_maximum(_x);
			}
		}
	}

	if (_y->color != rb_tree_red) {
		while(_x != *_ptr_root
			&&(_x==NULL || _x->color==rb_tree_black))
		{ 
			if (_x == _x_parent->Lchild) {
				rb_tree_node* _w = _x_parent->Rchild;
				if (_w->color == rb_tree_red) {
					_w->color = rb_tree_black;
					_x_parent->color = rb_tree_red;
					_rb_tree_L_rotate(_x_parent, *_ptr_root);
					_w = _x_parent->Rchild;
				}
				if ((_w->Lchild == NULL ||
					_w->Lchild->color == rb_tree_black) &&
					(_w->Rchild == NULL ||
					_w->Rchild->color == rb_tree_black))
				{
					_w->color = rb_tree_red;
					_x = _x_parent;
					_x_parent = _x_parent->parent;
				}
				else {
					if (_w->Rchild == NULL ||
						_w->Rchild->color == rb_tree_black)
					{
						if (_w->Lchild != NULL) {
							_w->Lchild->color = rb_tree_black;
						}
						_w->color = rb_tree_red;
						_rb_tree_R_rotate(_w, *_ptr_root);
						_w = _x_parent->Rchild;
					}
				}
				_w->color = _x_parent->color;
				_x_parent->color = rb_tree_black;
				if (_w->Rchild != NULL) {
					_w->Rchild->color = rb_tree_black;
				}
				_rb_tree_L_rotate(_x_parent, *_ptr_root);
				break;
			}
			else {
				rb_tree_node* _w = _x_parent->Lchild;
				if (_w->color == rb_tree_red) {
					_w->color = rb_tree_black;
					_x_parent->color = rb_tree_red;
					_rb_tree_R_rotate(_x_parent, *_ptr_root);
					_w = _x_parent->Lchild;
				}
				if ((_w->Rchild == NULL ||
					_w->Rchild->color == rb_tree_black) &&
					(_w->Lchild == NULL ||
					_w->Lchild->color == rb_tree_black))
				{
					_w->color = rb_tree_red;
					_x = _x_parent;
					_x_parent = _x_parent->parent;
				}
				else {
					if (_w->Lchild == NULL ||
						_w->Lchild->color == rb_tree_black)
					{
						if (_w->Rchild != NULL) {
							_w->Rchild->color = rb_tree_black;
						}
						_w->color = rb_tree_red;
						_rb_tree_L_rotate(_w, *_ptr_root);
						_w = _x_parent->Lchild;
					}
					_w->color = _x_parent->color;
					_x_parent->color = rb_tree_black;
					if (_w->Lchild != NULL) {
						_w->Lchild->color = rb_tree_black;
					}
					_rb_tree_R_rotate(_x_parent, *_ptr_root);
					break;
				}
			}
		}
		if (_x != NULL) {
			_x->color = rb_tree_black;
		}
	}
	return _y;
}

#endif // !_MY_DS_RBTREE_C