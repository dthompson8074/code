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

N = 3
z = np.random.rand(N)
w = np.random.rand(N)

i =0
plt.scatter(x, y, alpha=0.5)
plt.scatter(z,w,c=colors)
plt.ion()
plt.clf()
while(i < 5):
    z = np.random.rand(N)
    w = np.random.rand(N)
    plt.scatter(x, y, color = 'black')
    plt.scatter(z,w,color = 'red')
    plt.draw()
    plt.pause(1)
    plt.clf()
    
   
    i+=1