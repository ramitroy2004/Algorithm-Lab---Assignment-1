import matplotlib.pyplot as plt
import pandas as pd

df = pd.read_csv(r'C:\Users\mindl\Desktop\AlgoLab\1-A\uniform_data.csv')

#ranges for the x-axis
bins = []
i = 0
while(i < 100):
    bins.append(i)
    i += 10

plt.hist(df['values'], bins=bins, edgecolor='black')

plt.xticks(bins)

plt.ylabel('Frequency')

plt.title('Value Distribution')

plt.show()