# -*- coding: utf-8 -*-
"""
Created on Mon Jan 30 14:01:20 2017

@author: guillaume
"""

import sys
import numpy as np
from pylwr import *

import matplotlib.pyplot as plt

def plot_2D_LWR(xx,yy,zz,title='LWR'):
    fig = plt.figure(facecolor='white')
    plt.rc('text', usetex=True)
    plt.rc('font', family='serif')  
    CS = plt.contourf(xx,yy,zz,cmap=plt.cm.seismic)
    plt.axis('equal')
    cbar = plt.colorbar(CS)
    plt.title(title,fontsize=20)
    return CS


#%% EXAMPLE 3 (2 D)


lwr_opts         = lwr_options()
lwr_opts.D       = [1, 1]
lwr_opts.K       = 50
lwr_opts.k_bias  = 50
lwr_opts.y_bias  = -1
lwr_opts.bUseKDT = True
lwr_opts.print_param()

xx1, yy1 = np.meshgrid(np.arange(-5, 5, 0.1), np.arange(-5, 5, 0.1), sparse=False)
shape1   = xx1.shape

y        = np.sin(2 * xx1) * np.cos(2 * yy1)
y        = y.flatten(1)
X        = np.vstack((xx1.flatten(1),yy1.flatten(1)))

idx      = np.sqrt(np.sum(X**2,axis=0)) > 4
y[idx]   = 0

xx2, yy2 = np.meshgrid(np.arange(-5, 5, 0.2), np.arange(-5, 5, 0.2), sparse=False)
Xq       = np.vstack((xx2.flatten(1),yy2.flatten(1)))
shape2   = xx2.shape


#%%

lwr    = LWR(lwr_opts)

lwr.train(X,y)
yq = lwr.predict(Xq)



#%% Plot

plt.close('all')
plot_2D_LWR(xx1,yy1,y.reshape(shape1),'Training data')

plot_2D_LWR(xx2,yy2,yq.reshape(shape2),'Test data')
