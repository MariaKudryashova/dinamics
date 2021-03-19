import pandas as pd
import decimal
import random
import numpy as np
import math
import mathportrait as mp
import config as c
import time
import json
import sys


def load_data(name_file):
    data = pd.read_csv(name_file, sep=',', header=None)
    p_es = pd.to_numeric(data[2][(len(data) - c.N):len(data)])
    # приводим массив значений в формат, удобный для работы с векторами
    p_es = np.array(p_es)
    return p_es


def estimate_params(min_m, max_m):
    # размерность вектора
    ms = [i + min_m for i in range(max_m) if (i + min_m) <= max_m]
    eps = mp.get_epsilon(c.max_eps)
    return ms, eps

def save_result(name_file):
    with open(name_file, 'w') as f:
        json.dump(dict_result, f)

#сохраним промежуточные значения
def save_midresult(array, m):
    file_name = c.NAME_MIDRESULT + '/' + f"m_{m}.json"
    #print(file_name)
    with open(file_name, 'w') as f:
        json.dump(array, f)
        
if __name__ == '__main__':

    start_time = time.time()

    p_es = load_data(c.NAME_FILE)
    ms, eps = estimate_params(c.min_m, c.max_m)
    #print(ms)
    #print(eps)
    # расчитываем корреляционный интеграл для m по диапазону eps, p остается фиксированным
    results = []
    dict_result = {}
    for i, m in enumerate(ms):
        v = mp.get_vektors(np.array(p_es), m, c.p)
        #print(f"v = {v}")
        array_r = mp.estimates(eps, v)
        results.append(array_r)
        print(f"m = {m}")
        print("--- {} seconds ---".format((time.time() - start_time)))

        dict_result[m] = array_r
        save_midresult(array_r, m)
    
    # Время работы
    print("--- {} seconds ---".format((time.time() - start_time)))

    save_result(c.NAME_RESULTFILE)

