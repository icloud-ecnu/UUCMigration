import numpy as np
import statistics as st


'''
是否稳定在函数外部判定即可
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
    return predictions




