# -*- coding: utf-8 -*-
"""
Created on Mon Jan 30 13:59:34 2017

@author: guillaume
"""

import sys
import numpy as np
from pynpr.pylwr import *

import matplotlib.pyplot as plt

def plot_1D_LWR(X,y,Xq,yq):
    fig = plt.figure(facecolor='white')
    plt.rc('text', usetex=True)
    plt.rc('font', family='serif')    
    plt.plot(X,y,'o') 
    plt.plot(Xq,yq,'-r',lw=2) 
    plt.tick_params(axis='both', which='major', labelsize=20)
    plt.title('LWR',fontsize=20)


#%% EXAMPLE 2

lwr_opts        = lwr_options()
lwr_opts.D      = [1]
lwr_opts.y_bias = -1
lwr_opts.print_param()

lwr             = LWR(lwr_opts)

lwr.train(X,y)
yq = lwr.predict(Xq)

plt.close('all')
plot_1D_LWR(X,y,Xq,yq)