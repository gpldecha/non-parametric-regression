import numpy as np
from pylwr import *

import matplotlib.pyplot as plt

# Generate some test data (1D)

num_samples = 10
X = np.linspace(-np.pi, np.pi, num_samples) 
y = np.sin(X) + np.random.normal(0, 0.1, num_samples)



plt.close('all')
fig = plt.figure(facecolor='white')
plt.rc('text', usetex=True)
plt.rc('font', family='serif')    
plt.plot(X,y,'o') 


#%% train

lwr = LWR()
lwr.train(X,y)

#%% test

Xq = np.linspace(-np.pi, np.pi, num_samples) 

yq = lwr.predict(Xq)