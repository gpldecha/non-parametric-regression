from mpl_toolkits.mplot3d import *
import matplotlib.pyplot as plt
import numpy as np
from random import random, seed
from matplotlib import cm


#%% Generate training Data


num_samples = 100
X           = np.random.uniform(0,1,(2,num_samples))
y           = np.sin(5.0 * X[0,:]) * np.cos(5.0 * X[1,:])/5.0 + np.random.normal(0, 0.025, num_samples)




#%% Plot true function with training data

plt.close('all')
fig = plt.figure()
ax = fig.gca(projection='3d')               # to work in 3d
plt.hold(True)



x_surf=np.arange(0, 1, 0.01)                # generate a mesh
y_surf=np.arange(0, 1, 0.01)
x_surf, y_surf = np.meshgrid(x_surf, y_surf)
z_surf = np.sqrt(x_surf+y_surf)         
z_surf = np.sin(5.0 * x_surf) * np.cos(5.0 * y_surf)/5.0

    # ex. function, which depends on x and y
ax.plot_surface(x_surf, y_surf, z_surf, cmap=cm.hot,alpha=0.8);    # plot a 3d surface plot

ax.scatter(X[0,:], X[1,:], y, s=20)

ax.set_xlabel('x label')
ax.set_ylabel('y label')
ax.set_zlabel('z label')

plt.show()

#%% Learn LWR model and plot it


lwr_opts         = lwr_options()
lwr_opts.D       = [0.05, 0.05]
lwr_opts.K       = 50
lwr_opts.y_bias  = 0
lwr_opts.bUseKDT = False
lwr_opts.print_param()

lwr    = LWR(lwr_opts)

lwr.train(X,y)

# Predict data points (use training points for prediction)


#%% Plot result


plt.close('all')
fig = plt.figure()
ax = fig.gca(projection='3d')               # to work in 3d
plt.hold(True)


x_surf=np.arange(0, 1, 0.01)                # generate a mesh
y_surf=np.arange(0, 1, 0.01)
x_surf, y_surf = np.meshgrid(x_surf, y_surf)

Xq = np.vstack((x_surf.flatten(),y_surf.flatten()))
yq = lwr.predict(Xq)

    # ex. function, which depends on x and y
ax.plot_surface(x_surf, y_surf, yq.reshape(z_surf.shape), cmap=cm.hot,alpha=0.8);    # plot a 3d surface plot

ax.scatter(X[0,:], X[1,:], y, s=20)

ax.set_xlabel('x label')
ax.set_ylabel('y label')
ax.set_zlabel('z label')

plt.show()

























