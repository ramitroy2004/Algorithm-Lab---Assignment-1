import pandas as pd
import matplotlib.pyplot as plt

choice = int(input("Enter 1 for uniform, 2 for normal: "))

# Load data from first CSV file
if(choice == 1):
    df1 = pd.read_csv(r'C:\Users\mindl\Desktop\AlgoLab\9\observation_uniform.csv')
else:
    df1 = pd.read_csv(r'C:\Users\mindl\Desktop\AlgoLab\9\observation_normal.csv')

# Load data from second CSV file
if(choice == 1):
    df2 = pd.read_csv(r'C:\Users\mindl\Desktop\AlgoLab\9\observation_uniform_MoM.csv')
else:
    df2 = pd.read_csv(r'C:\Users\mindl\Desktop\AlgoLab\9\observation_normal_MoM.csv')

# Create a new figure and axis object
fig, ax = plt.subplots()

# Plot the first data series on the axis
ax.plot(df1['Input size'], df1['Best'], label='Random Quick Sort')

# Plot the second data series on the same axis
ax.plot(df2['Input size'], df2['Best'], label='MOM Pivot QS')

# Set axis labels
ax.set_xlabel('Number of Inputs')
ax.set_ylabel('Best Comparison')

# Add a legend to the plot
ax.legend()

# Show the plot
plt.show()