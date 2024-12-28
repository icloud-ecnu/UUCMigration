#ifndef PREDICT_H
#define PREDICT_H

#include <stdio.h> // 需要用于 FILE 类型
<<<<<<< HEAD
#include <python3.12/Python.h> // 引入 Python API

// 函数原型声明
int dataShiftPredict(int* dirtylist, int N, double P, int inputSize, int outSize);
void SSDP_predict(float* predict,float *dirty_list, float *access_list, float *system_list[], int length);
=======
#include <Python.h> // 引入 Python API

// 函数原型声明
int* dataShiftPredict(int* dirtylist, int N, int P, int inputSize, int *outSize);
float* SSDP_predict(float *dirty_list, float *access_list, float *system_list, int length);
>>>>>>> a31c4057336b61d89215308f0d424bffdff1564c

#endif // PREDICT_H
