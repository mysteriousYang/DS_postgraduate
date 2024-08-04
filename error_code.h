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
	"�ظ�����\n",
	"�����������\n",
	"���������ɷ���\n",
	"�޷������ڴ�\n"
};

#endif // !_MY_DS_ERROR_CODE_