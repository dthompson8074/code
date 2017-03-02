# -*- coding: utf-8 -*-
"""
Created on Wed Mar  1 16:48:23 2017

@author: davidthompson
"""

"""
Simple demo of a scatter plot.
"""
#!/usr/bin/python
import numpy as np
import matplotlib.pyplot as plt
import time

N = 50
x = np.random.rand(N)
y = np.random.rand(N)
colors = np.random.rand(3)
area = np.pi * (15 * np.random.rand(N))**2  # 0 to 15 point radii

z = [.5,.7,.9]
w = [.5,.7,.9]

i =0

while(i < 25):
    plt.scatter(x, y, alpha=0.5)
    plt.scatter(z,w,c=colors)
    plt.show()
    time.sleep(2)
    i+=1