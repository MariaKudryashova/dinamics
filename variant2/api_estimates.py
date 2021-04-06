#!/usr/bin/python3
# -*- coding: utf-8 -*-

import sys
import time

# пути до модуля _test
#sys.path.append(r'C:\Users\maru\dinprojects\dinamics\variant2\build\lib.win-amd64-3.8')

sys.path.append(r'C:\Users\maru\dinprojects\dinamics\variant2\build\lib.win-amd64-3.8\_test.cp38-win_amd64.pyd')

import _test
import array
import numpy
import config as c
import pandas as pd
import numpy as np

    
start_time = time.time()

data = pd.read_csv(c.NAME_FILE, sep=',', header=None)

p_es = pd.to_numeric(data[0][(len(data) - c.N):len(data)])
# приводим массив значений в формат, удобный для работы с векторами
p_es = np.array(p_es)

#ms = [i + c.min_m for i in range(c.max_m) if (i + c.min_m) <= c.max_m]
#eps = []
#j = c.min_eps
#for i in range(500):
#    j = round(j * c.speed_eps, 2)
#    eps.append(j)
#    if j > c.max_eps:
#        break

#передаем массив в С
sample = array.array('d', p_es)
print('ret func_avg: ', _test.func_avg(sample))

# Время работы
print("--- {} seconds ---".format((time.time() - start_time)))

