import matplotlib.pyplot as plt
import pandas as pd

data = pd.read_csv(r'C:\Users\mindl\Desktop\AlgoLab\8\MoM_obs.csv')

# Plot number of divide vs number of comparisons in the first subplot
plt.plot(data['partitions'], data['time'], 'bo-',label='Comparisons')
plt.xlabel('Partitions')
plt.ylabel('time')
plt.title('Partitions vs time')

plt.legend()
plt.show()