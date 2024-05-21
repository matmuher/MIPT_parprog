import numpy as np
import matplotlib.pyplot as plt

# Data points
data_sizes = [24, 48, 97, 195]  # Amount of data in Mb
times = [24, 46, 90, 179]  # Time in seconds

# Create a new figure
plt.figure(figsize=(10, 6))

# Plot the data
plt.plot(data_sizes, times, marker='o', linestyle='-')

# Set labels and title
plt.xlabel('Data Size (Mb)')
plt.ylabel('Time (ms)')
plt.title('Time vs Data Size')

# Grid for better readability
plt.grid(True)

# Show the plot
plt.show()

print(np.polyfit(data_sizes, times, 1))
