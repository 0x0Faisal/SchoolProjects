# Draw Graph
To draw weighted undirected graph𝐺=(𝑉,𝐸), that reads input using text file.
The information of the graph are in the following format:
    5               // First line is for number of vertices  |V|
    1,10            /*  from line 2
    8,10             *  to |V|+1 
    10,8             *  (x, y) coordinates
  7,4              *  starting from v0  
  3,1              */
  0,1,10          /*  from |V|+2
  1,2,5            *  to last line
  2,3,25           *  containing i, j, k
  0,3,3            *  edge between vi and vj
  3,4,8            *  its weight = k

