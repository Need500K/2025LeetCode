/**
 * Note: The returned array must be malloced, assume caller calls free().
 */

#include <malloc.h>
#include <stdlib.h>
#include <memory.h>

#pragma warning(disable:4996)

int compare(const void* a, const void* b) {
	return (*(int*)a - *(int*)b);
}

inline void swap(int* arr, int idx0, int idx1) {
	const int tmp = arr[idx0];
	arr[idx0] = arr[idx1];
	arr[idx1] = tmp;
}

int* rearrangeArray(int* nums, int numsSize, int* returnSize) {

	*returnSize = numsSize;
	int* new_arr = (int*)malloc(sizeof(int) * (*returnSize));
	memcpy(new_arr, nums, sizeof(int) * (numsSize));
	qsort(new_arr, numsSize, sizeof(int), compare);

	for (int i = 2; i < numsSize; i += 2) {
		swap(new_arr, i - 1, i);
	}
	return new_arr;


}