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
    p_es = pd.to_numeric(data[0][(len(data) - c.N):len(data)])
    # приводим массив значений в формат, удобный для работы с векторами
    p_es = np.array(p_es)
    return p_es


def estimate_params(min_m, max_m):
    # размерность вектора
    ms = [i + min_m for i in range(max_m) if (i + min_m) <= max_m]
    eps = mp.get_epsilon(c.min_eps, c.max_eps, c.speed_eps)
    #print(f"eps = {eps[0]}:{eps[len(eps)-1]}")
    return ms, eps

def save_result(array, name):
    name_file = name + f"_p{c.p}(eps{c.min_eps}-{c.max_eps}).txt";
    with open(name_file, 'w') as f:
        #json.dump(array, f)
        for arr in array:
            for row in arr:
                f.write("%s\n"%row)


#сохраним промежуточные значения
def save_midresult(array, m, name):
    file_name = name + '/' + f"m_{m}_p{c.p}(eps{c.min_eps}-{c.max_eps}).txt"
    with open(file_name, 'w') as f:
        #json.dump(array, f)
        for row in array:
            f.write("%s\n"%row)
        
        
if __name__ == '__main__':
    start_time = time.time()
    
    p_es = load_data(c.NAME_FILE)
    ms, eps = estimate_params(c.min_m, c.max_m)
    
    # расчитываем корреляционный интеграл для m по диапазону eps, p остается фиксированным
    results = []
    for i, m in enumerate(ms):
        v = mp.get_vektors(np.array(p_es), m, c.p)
        #print(f"v = {v}")
        array_r = mp.estimates(m, eps, v, c.DELIMETER)
        results.append(array_r)
        print(f"m = {m}")
        print("---from start: {} seconds ---".format((time.time() - start_time)))
        save_midresult(array_r, m, c.NAME_MIDRESULT)
    
    # Время работы
    #print("---from start: {} seconds ---".format((time.time() - start_time)))

    save_result(results, c.NAME_RESULTFILE)

