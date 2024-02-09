import matplotlib.pyplot as plt
import pandas as pd

df = pd.read_csv(r'C:\Users\mindl\Desktop\AlgoLab\1-B\normal_data.csv')

bins = []
for i in range(0, 101):
    bins.append(i)

plt.hist(df['values'], bins=bins, edgecolor='black')

plt.xticks(bins)

plt.ylabel('Frequency')

plt.title('Value Distribution')

plt.show()