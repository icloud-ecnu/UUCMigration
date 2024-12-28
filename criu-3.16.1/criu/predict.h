#ifndef PREDICT_H
#define PREDICT_H

#include <stdio.h> // 需要用于 FILE 类型
#include <Python.h> // 引入 Python API

// 函数原型声明
int* dataShiftPredict(int* dirtylist, int N, int P, int inputSize, int *outSize);
float* SSDP_predict(float *dirty_list, float *access_list, float *system_list, int length);

#endif // PREDICT_H
