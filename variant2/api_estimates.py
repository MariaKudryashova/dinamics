#!/usr/bin/python3
# -*- coding: utf-8 -*-

import sys
import time

# пути до модуля _test
sys.path.append(r'C:\Users\maru\pyprojects\math_attractors2\build\lib.win-amd64-3.8')

import _test
import array
import numpy
import estimates as est
import config as c
import mathportrait as mp

start_time = time.time()

p_es = est.load_data(c.NAME_FILE)
ms, eps = est.estimate_params(c.min_m, c.max_m)

#передаем массив в С
sample = array.array('d', p_es)
print('ret func_avg: ', _test.func_avg(sample))


'''
print("Python")

for m in ms:
    v = mp.get_vektors(sample, 3, m)
    M = len(v)
    if M > 2:
        for ep in eps:
            C = mp.corr_integral(ep, v)
            print(f"python: m = {m}, ep = {ep}, C = {C}")
'''
# Время работы
print("--- {} seconds ---".format((time.time() - start_time)))

