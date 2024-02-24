#! /usr/bin/python3

# Solve the "_tkinter.TclError: no display name and no $DISPLAY environment variable"
# From: 
# https://stackoverflow.com/questions/37604289/tkinter-tclerror-no-display-name-and-no-display-environment-variable
import matplotlib
matplotlib.use('Agg')

from matplotlib import pyplot as plt
import numpy as np

m = np.loadtxt('line.csv', delimiter=',')
x = m[:,0]
y = m[:,1]

plt.plot(x, y)
plt.savefig('line.png')
plt.close()

m = np.loadtxt('curve.csv', delimiter=',')
x = m[:,0]
y = m[:,1]

plt.plot(x, y)
plt.savefig('curve.png')
plt.close()