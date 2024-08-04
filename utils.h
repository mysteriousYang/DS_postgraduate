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

//如果使用普通函数的话老是会报Warning，所以raise使用宏函数了
#define raise(_error_code)	perror(ErrorMessages[_error_code]); \
							exit(_error_code);


//默认alloctor函数,不想写那么长了所以自定义了new宏函数
#define new(_Ty) (_Ty*)malloc(sizeof(_Ty))


#endif // !_MY_DS_UTILS_H

