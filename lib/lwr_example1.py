import numpy as np
from pylwr import *


a = np.arange(15,dtype=np.double).reshape(3, 5)
print a

lwr = LWR()

lwr.set_X(a)