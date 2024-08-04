#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include"single_list.h"

int main() {
	single_list* L = single_list_constructor();

	int arr[] = { 1,2,3,4,5,6 };
	for (int i = 0; i < 6; ++i) {
		single_list_push_front(L, arr[i]);
	}
	single_list_pop_back(L);

	single_list_print(L);

	return 0;
}