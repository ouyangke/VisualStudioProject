#include<stdio.h>

#define LENGTH(array) (sizeof(array) / sizeof(array[0]))

int main(){

	int array[] = {1,2,3,4,5,6};
	int length = LENGTH(array);
	printf("数组长度为:%d\n",length);
	return 0;
}
