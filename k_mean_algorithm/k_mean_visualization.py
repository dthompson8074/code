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
import math 

np.random.RandomState()
# Distance function
def distance(xi,xii,yi,yii):
    sq1 = (xi-xii)*(xi-xii)
    sq2 = (yi-yii)*(yi-yii)
    return math.sqrt(sq1 + sq2)
#kmean recalculate

#k-mean parameters
dim = 2
N = 8000
nxdim = 2400
k = 6
kxdim = 8
precision = .001

count=0

close_k = 0
cluster_assign = np.random.rand(N)
color_assign = []
cluster_size = np.random.rand(k)
cluster_sum_z = np.random.rand(k)
cluster_sum_w = np.random.rand(k)

center_z = 0
center_w = 0

#data randomization
x = np.random.rand(N)
y = np.random.rand(N)

#clusters
#colors_cluster = ['red','green','blue','orange']
colors_cluster = ['red','green','blue','orange','black','purple']
#colors_cluster = np.random.rand(k)*10
z = np.random.rand(k)
w = np.random.rand(k)
for i in range(len(x)):
    color_assign.append('grey')


#initialize plot
plt.scatter(x, y, c= color_assign,alpha=0.3)
plt.scatter(z,w, c=colors_cluster, s=200)
plt.title('k - means clustering')
plt.ion()
plt.pause(5)
plt.clf()

while(count < 500):
    flag = 1

    for i in range(len(x)):
        min_dist = 1000.0
        cur_dist = 0.0
        
        for j in range(len(z)):
            cur_dist = distance(x[i],z[j],y[i],w[j])
            if(cur_dist < min_dist):
                    min_dist = cur_dist
                    cluster_assign[i] = j
                    close_k = j
                    
        cluster_size[close_k]+=1
        color_assign[i] = colors_cluster[close_k]

    
    plt.scatter(x, y, c= color_assign,alpha=0.2)
    plt.scatter(z,w,c=colors_cluster, s=200)
    plt.title('k - means clustering')
    plt.draw()
    plt.pause(.2)
    plt.clf()

    for i in range(len(x)):          
            cluster_sum_z[int(cluster_assign[i])] += x[i]
            cluster_sum_w[int(cluster_assign[i])] += y[i]    

    for i in range(len(z)):
            prev_z = z[i]
            prev_w = w[i]
            z[i] = cluster_sum_z[i]/cluster_size[i]
            w[i] = cluster_sum_w[i]/cluster_size[i]
            prev_z = abs(prev_z - z[i])
            prev_w = abs(prev_w - w[i])
            if (prev_z > .001 or prev_w > .001):
                flag = 0
            
    count+=1
    if (flag == 1):
        break
    
   
    
plt.scatter(x, y, c= color_assign,alpha=0.2 )
plt.scatter(z,w,c=colors_cluster, s=200)
plt.title('k - means clustering')
plt.draw()
plt.pause(10)   