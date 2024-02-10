import matplotlib.pyplot as plt
import pandas as pd

df = pd.read_csv(r'C:\Users\mindl\Desktop\AlgoLab\5\Data generator\normalized_normal_data.csv')

#ranges for the x-axis
bins = []
i = 0.00
while(i < 1):
    bins.append(i)
    i += 0.01

show_bins = []
i = 0.00
while(i < 1):
    show_bins.append(i)
    i += 0.1

plt.hist(df['values'], bins=bins, edgecolor='black')

plt.xticks(show_bins)

plt.ylabel('Frequency')

plt.title('Value Distribution')

plt.show()