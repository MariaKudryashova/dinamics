import numpy as np
import json
import time



def get_epsilon(min_eps, max_eps, speed_eps):
    eps = []
    j = min_eps
    for i in range(500):
        j = round(j * speed_eps, 2)
        eps.append(j)
        if j > max_eps:
            break
    return eps

def get_vektors(x, m, p):
    # функция формирует массив векторов в m-мерном пространстве с заданным значением p
    # размерность реконструированного пространства
    # m
    # фиксированное число
    # рекомендуется подбирать так, чтобы улучшить результат
    # p

    j = [i for i in reversed(range(len(x)))]
    #print(j)
    v = []
    for k in j:
        num = [k - i * p for i in range(m)]
        value = [x[i] for i in num if i > 0]
        if np.shape(value)[0] < m:
            break
        v.append(value)
    v = np.array(v)
    return v

#функция Хевисайда
def func_theta(x):
    if x < 0:
        return 0
    else:
        return 1

def corr_integral(epsilon, v):
    summ = 0
    #количество векторов заданной размерности
    M = len(v)
    for i in range(M):
        for j in range(M):
            if i != j:
                s = epsilon - (np.linalg.norm(v[i] - v[j]))
                t = func_theta(s)
                summ += t
    C = 1 / (M * (M - 1)) * summ
    return C

def estimates(m, eps, v, delimeter):
    array_r = []
    for j, ep in enumerate(eps):
        ci = corr_integral(ep, v)
        msg = f"{m}{delimeter}{ep}{delimeter}{ci}"
        array_r.append(msg)
        
    return array_r


