# Richard Bustamante & Paul Brodhead
## CSC345-01 
## project2
### Description: 
C program to fetch Sudoku table from an input file and validate the game with the use of 2 methodologies: utilizing 3 threads (one for columns, rows, and 3x3 squares) and the other utilizing 27 threads (nine for columns, rows, and 3x3 squares). These two methods were compared based on average computation time. 
### Get Started: 

### Fulfilled Requirements: 
* Program successfully fetches Sudoku table from an input file and transfers it to a 2D array (9x9 matrix) 
* Program successfully outputs board state and validates the game, along with a computation time in seconds 
* Program can run both methods: with three threads (one for columns, rows, and squares) and 27 threads (nine for columns, rows, and squares) 
* A separate script was made to execute the original script 50 times on the desired option and output the average computation time. Input board was correct for one iteration and incorrect for the other, allowing for a total of 100 runs per option. The averages and standard deviations of computation time for the separate correct and incorrect input boards for the two methods are shown below in the bar graph. The results below show that option 1 was the significantly quicker method. It can be deduced that it is significantly quicker to simply have three threads doing repetitive tasks rather than having 27 threads for each repetition of the task, at least on the provided virtual machines. 
### Results: 
![alt text](https://github.com/sancher6/project2/blob/master/Media/bargraph.png)
*Figure 1.* Bar graph for average computation times of options 1&2 with confidence intervals
