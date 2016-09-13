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


def plot_2D_LWR(xx,yy,zz,title='LWR'):
    fig = plt.figure(facecolor='white')
    plt.rc('text', usetex=True)
    plt.rc('font', family='serif')  
    CS = plt.contourf(xx,yy,zz,cmap=plt.cm.seismic)
    plt.axis('equal')
    cbar = plt.colorbar(CS)
    plt.title(title,fontsize=20)
    return CS

#%% Exampl1
# Generate some test data (1D)

num_samples = 450
X  =  np.concatenate( (np.linspace(-10, -3, num_samples/2) , np.linspace(3, 10, num_samples/2)), axis=0)
y  = np.sin(0.5 * X) + np.random.normal(0, 0.1, num_samples)

# Test points
Xq = np.linspace(-10, 10, num_samples) 



lwr = LWR()

lwr.train(X,y)
yq = lwr.predict(Xq)

#%% Plot result

plt.close('all')
plot_1D_LWR(X,y,Xq,yq)


#%% EXAMPLE 2

lwr_opts        = lwr_options()
lwr_opts.D      = [0.01]
lwr_opts.k_bias = 50
lwr_opts.y_bias = -1
lwr_opts.print_param()

lwr             = LWR(lwr_opts)

lwr.train(X,y)
yq = lwr.predict(Xq)

plt.close('all')
plot_1D_LWR(X,y,Xq,yq)


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






