# libraries
import numpy as np
import matplotlib.pyplot as plt

#opens the option 1 text file and parses it 
with open("output1.txt", "r") as my_file:
    for line in my_file:
        str = line.split()
#turns the strings to floats 
str = [float(i) for i in str]
avg1 = 0
#calculates the average for option 1 
for i in str: 
    avg1 += i
avg1 /= len(str) 
std1 = np.std(str)
#opens the option 2 text file and parses it 
with open("output2.txt", "r") as my_file:
    for line in my_file:
        str = line.split()
#turns the strings to floats 
str = [float(i) for i in str]
avg2 = 0 
#calculates the average for option 2 
for i in str: 
    avg2 += i 
avg2 /= len(str) 
std2 = np.std(str) 
# width of the bars
barWidth = 0.3

# Choose the height of the blue bars
bars1 = [avg1, avg2]

# Choose the height of the error bars (bars1)
yer1 = [std1,std2]

# The x position of bars
r1 = np.arange(len(bars1))
r2 = [x + barWidth for x in r1]

# Create blue bars
plt.bar(r1, bars1, width = barWidth, color = 'blue', edgecolor = 'black', yerr=yer1, capsize=7, label='Averages for Options 1 & 2')

# general layout
plt.xticks(np.arange(len(bars1)), ['Option 1', 'Option 2'])
plt.ylabel('Time (s)')
plt.legend()

# Show graphic
plt.show()
