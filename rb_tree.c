#ifndef _MY_DS_RBTREE_C
#define _MY_DS_RBTREE_C
#include<stdlib.h>
#include"rb_tree.h"

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
void _rb_tree_iterator_inc(rb_tree_iterator* _self) {
	//������������,��ǰ����������������
	if (_self->_node_ptr->Rchild != NULL) {
		_self->_node_ptr = _self->_node_ptr->Rchild;
		while (_self->_node_ptr->Lchild != NULL) {
			_self->_node_ptr = _self->_node_ptr->Lchild;
		}
	}
	else {
		//�����������ڣ�Ѱ�����ϻ�����������
		rb_tree_node* _temp = _self->_node_ptr->parent;
		while (_self->_node_ptr != _temp->Rchild) {
			_self->_node_ptr = _temp;
			_temp = _temp->parent;
		}
		//������������ֱ�Ӵ������������������
		//����������������һ�����
		if (_self->_node_ptr->Rchild != _temp) {
			_self->_node_ptr = _temp;
		}
	}
}


//�������Լ�
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
				_in_node->parent->parent = rb_tree_red;
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

#endif // !_MY_DS_RBTREE_C