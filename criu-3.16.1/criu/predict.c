#include <python3.12/Python.h>
#include <stdio.h>
#include "log.h"
extern PyObject *pFuncShift, *pFuncSSDP;

int dataShiftPredict(int *dirtylist, int N, double P, int inputSize, int outSize);
void SSDP_predict(float *predict, float *dirty_list, float *access_list, float *system_list[], int length);

int dataShiftPredict(int *dirtylist, int N, double P, int inputSize, int outSize)
{
	int times = 0, actual_label = dirtylist[N - 1], predict_label;
	double percentage = 0;
	for (int i = N - 1; i >= 0; i--) {
		if (dirtylist[i] == actual_label)
			times++;
		else
			break;
	}
	percentage = (double)times / N;
	if (percentage > P)
		predict_label = actual_label;
	else
		predict_label = actual_label ^ 1;
	return predict_label;

	/*
	if (pFuncShift && PyCallable_Check(pFuncShift)) {
		// 创建一个空的 Python 列表
		PyObject *pList = PyList_New(0), *pValue; // 创建一个空列表

		// 使用传入的浮点数组填充 Python 列表
		for (int i = 0; i < inputSize; i++) {
			PyObject *pValue;
			pValue = PyLong_FromLong(dirtylist[i]); // 创建浮点数元素
			PyList_Append(pList, pValue);		// 添加到列表
			Py_DECREF(pValue);			// 释放元素对象
		}

		// 调用 Python 函数，传入列表
		pValue = PyObject_CallFunctionObjArgs(pFuncShift, pList, PyLong_FromLong(N), PyFloat_FromDouble(P), NULL); // 调用函数
		Py_DECREF(pList);											   // 释放列表对象
		if (pValue != NULL) {
			// 确保返回的是列表
			if (PyList_Check(pValue)) {
				PyObject *item = PyList_GetItem(pValue, 0);	      // 获取每个元素
				int result = (int)PyLong_AsLong(item);
				Py_DECREF(pValue);
				return result; // 返回 C 整数数组
			} else {
				fprintf(stderr, "Expected a list from Python function.\n");
			}
			Py_DECREF(pValue);
		} else {
			PyErr_Print();
		}
	} else {
		PyErr_Print();
	}
	return 0;
	*/
}

void SSDP_predict(float *predict, float *dirty_list, float *access_list, float *system_list[], int length)
{
	if (pFuncSSDP && PyCallable_Check(pFuncSSDP)) {
		PyObject *pValue;
		// 转换C数组为Python列表
		PyObject *dirtyList = PyList_New(length);
		PyObject *accessList = PyList_New(length);
		PyObject *systemList = PyList_New(length); // 创建外层列表

		for (int i = 0; i < length; i++) {
			PyObject *innerList = PyList_New(7); // 假设每行有7个元素
			PyList_SetItem(dirtyList, i, PyFloat_FromDouble(dirty_list[i]));
			PyList_SetItem(accessList, i, PyFloat_FromDouble(access_list[i]));

			// 创建内层列表，并填充数据
			for (int j = 0; j < 7; j++) {
				PyList_SetItem(innerList, j, PyFloat_FromDouble(system_list[i][j]));
			}
			PyList_SetItem(systemList, i, innerList); // 将内层列表加入到外层列表
		}

		// 调用Python函数
		//pArgs = PyTuple_Pack(3, dirtyList, accessList, systemList);
		pValue = PyObject_CallFunctionObjArgs(pFuncSSDP, dirtyList, accessList, systemList);

		// 处理返回结果
		if (pValue != NULL) {
			// 假设返回的结果是一个Python列表，将其转换为C数组
			Py_ssize_t size = PyList_Size(pValue);
			for (Py_ssize_t i = 0; i < size; i++) {
				predict[i] = PyFloat_AsDouble(PyList_GetItem(pValue, i));
			}
			Py_DECREF(pValue);
			return;
		} else {
			PyErr_Print();
		}
		// 释放Python对象
		Py_DECREF(dirtyList);
		Py_DECREF(accessList);
		Py_DECREF(systemList);
		//Py_DECREF(pArgs);
	} else {
        PyErr_Print();
		//fprintf(stderr, "找不到函数 'unstable_page_inference'\n");
	}
	return;
}

// int main() {
//     // FILE *file = fopen("data.txt", "r");
//     int N = 4;
//     double P = 0.8;
//     int size = 0;

//     int dirtylist[]={0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
//     int inputSize = sizeof(dirtylist) / sizeof(dirtylist[0]);
//     int* result = dataShiftPredict(dirtylist,N,P,inputSize,&size);
//     if (result != NULL && size > 0) {
//         for (int i = 0; i < size; i++) {
//             printf("%d\n", result[i]); // 输出结果
//         }
//         free(result); // 释放内存
//     }else{
//         printf("input list is unstable, can not predict with dataShift method");
//     }
//     return 0;
// }
