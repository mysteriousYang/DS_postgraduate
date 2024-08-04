#ifndef _MY_DS_UTILS_H
#define _MY_DS_UTILS_H

#ifndef ElemType
#define ElemType int
#endif // !ElemType

enum ErrorCode {
	DuplicateConstruct = 1,
	Overflow = 2,
	Underflow = 3,
	MemoryOut = 4,
};
typedef enum ErrorCode ErrorCode;

extern const char* ErrorMessages[];

typedef unsigned long long size_t;
typedef int bool_t;

//void raise(ErrorCode _error_code);

//���ʹ����ͨ�����Ļ����ǻᱨWarning������raiseʹ�ú꺯����
#define raise(_error_code)	perror(ErrorMessages[_error_code]); \
							exit(_error_code);


//Ĭ��alloctor����,����д��ô���������Զ�����new�꺯��
#define new(_Ty) (_Ty*)malloc(sizeof(_Ty))


#endif // !_MY_DS_UTILS_H

