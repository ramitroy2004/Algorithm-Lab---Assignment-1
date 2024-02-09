import matplotlib.pyplot as plt
import pandas as pd
import numpy as np

choice = int(input('Enter 1 for uniform, 2 for normal: '))

if choice == 1:
    data = pd.read_csv(r'C:\Users\mindl\Desktop\AlgoLab\3\Quick Sort\observation_uniform_n.csv')
elif choice == 2:
    data = pd.read_csv(r'C:\Users\mindl\Desktop\AlgoLab\3\Quick Sort\observation_normal_n.csv')

elements = data['Input size'].to_numpy()
comp = data["Comparisons"].to_numpy()
time = data["Time (ms)"].to_numpy()

comp_ratio = comp / ((elements*np.log2(elements)))
time_ratio = time / ((elements*np.log2(elements)))

# Create a figure with two subplots (ax1 and ax2)
fig, (ax1, ax2) = plt.subplots(1, 2, figsize=(12, 6))

# Plot number of inputs vs number of comparisons in the first subplot
ax1.plot(elements, comp_ratio, 'bo-',label='Comparisons')
ax1.set_xlabel('Number of inputs')
ax1.set_ylabel(r'$\frac{comparisons}{n*lgn}$')
ax1.set_title('Number of inputs vs number of comparisons')

# Plot number of inputs vs time taken in the second subplot
ax2.plot(elements, time_ratio, 'ro-',label='Time')
ax2.set_xlabel('Number of inputs')
ax2.set_ylabel(r'$\frac{time}{n*lgn}$')
ax2.set_title('Number of inputs vs time taken')

plt.legend()
plt.show()