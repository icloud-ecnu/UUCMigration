import numpy as np
import statistics as st

<<<<<<< HEAD

'''
是否稳定在函数外部判定即可
=======
>>>>>>> a31c4057336b61d89215308f0d424bffdff1564c
def getCV(dirtyarray:list):
    mean_value=np.mean(dirtyarray)
    if mean_value==0:
        return -1
    if len(dirtyarray)==1:
        standard_deviation=0
    else:
        standard_deviation=st.stdev(dirtyarray)
    return standard_deviation / mean_value

def isStable(dirtyarray:list):
    cv=getCV(dirtyarray)
    if cv == -1: # 全0
        return True
    return True if cv < 0.2 else False
<<<<<<< HEAD
'''
def dataShift(dirtyList, N, P):
    real = []
    predictions = []
    percentage_dirty = 1
    for j in range(N-1,-1,-1):
        if window[j]==actual_label:
            percentage_dirty+=1
        else:
            break
    percentage_dirty = percentage_dirty / N
    if percentage_dirty > P:
        predicted_label = actual_label
    else:
        predicted_label = actual_label ^ 1
    real.append(actual_label)
    predictions.append(predicted_label)
=======

def dataShift(dirtyList, N=4, P=0.8):
    print(f"dirtylist is {dirtyList}")
    real = []
    predictions = []
    if isStable(dirtyList):
        # print(dirtyList)
        # 确保有足够的数据点进行预测
        if len(dirtyList) > N:
            # print(dirtyList)
            i=len(dirtyList)-N-1
            window = dirtyList[i:i+N]
            percentage_dirty = (sum(window) / N) * 100
            actual_label = dirtyList[i+N] 
            predicted_label = 1 if percentage_dirty > P else 0   
            real.append(actual_label)
            predictions.append(predicted_label)

            assert len(real) == len(predictions)
            print(f"real is {real}, predictions is {predictions}")
            # 检查 real_array 和 predict_array 是否包含至少一个 '1'
    else:
        print("unstable dirtylist")
>>>>>>> a31c4057336b61d89215308f0d424bffdff1564c
    return predictions




