# Checking your python path

import sys
import numpy as np
from pylwr import *

import matplotlib.pyplot as plt

def plot_1D_LWR(X,y,Xq,yq):
    fig = plt.figure(facecolor='white')
    plt.rc('text', usetex=True)
    plt.rc('font', family='serif')    
    plt.plot(X,y,'o') 
    plt.plot(Xq,yq,'-r',lw=2) 
    plt.tick_params(axis='both', which='major', labelsize=20)
    plt.title('LWR',fontsize=20)


#%% Example 1 (1D)

# Generate some test data (1D)
num_samples = 200
X           =  np.concatenate( (np.linspace(-10, -3, num_samples/2) , np.linspace(3, 10, num_samples/2)), axis=0)
y           =  np.sin(0.5 * X) + np.random.normal(0, 0.1, num_samples)

# Test points
Xq = np.linspace(-10, 10, num_samples) 


lwr = LWR()

lwr.train(X,y)
yq = lwr.predict(Xq)

#%% Plot result

plt.close('all')
plot_1D_LWR(X,y,Xq,yq)


