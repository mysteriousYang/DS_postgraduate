#ifndef _MY_DS_ERROR_CODE_
#define _MY_DS_ERROR_CODE_

enum ErrorCode {
	DuplicateConstruct = 1,
	Overflow = 2,
	Underflow = 3,
	MemoryOut = 4,
};
typedef enum ErrorCode ErrorCode;

const char* ErrorMessages[] = {
	"",
	"重复构造\n",
	"超出最大容量\n",
	"空容器不可访问\n",
	"无法分配内存\n"
};

#endif // !_MY_DS_ERROR_CODE_