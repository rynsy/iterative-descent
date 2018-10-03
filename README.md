# TopSpin solver
    This program solves a [TopSpin](https://www.amazon.com/Binary-Arts-Top-Spin-Top-Spin/dp/B001SDX244) puzzle using the IDA* algorithm.
    I'd written this a few years ago and just found it on an old hard drive, so I thought I'd throw it on Github.

Program:
    I've represented the TopSpin puzzle as an array of numbers with
    pointers that correspond to the edges of the wheel. The program
    has a simple menu that allows you to generate new random puzzles,
    and traverse a tree of legal moves you can make on the puzzle to 
    reach a solution.
    This program can solve randomized puzzles using the IDA* algorithm,
    and print off a list of moves needed to get to a solution. The 
    first move is always ('x','x'), which indicates the starting 
    position of the puzzle.

Data Structure:
    For my IDA* implementation I used a Node class to wrap around the
    class I'm using to represent my puzzle. The Node class handles 
    things like generating children of a node, tracking the move made
    to reach this node and the depth and heuristic value of the puzzle.
   
    The Node class is used by the IDA* function, which generates a 
    solution for a randomized puzzle with a starting bound equal
    to the number of random moves made on the puzzle. The function uses
    a helper function called search to traverse the tree.  
   
Heuristic:
    I used a variation of the "butterknife heuristic". For the butter- 
    knife heuristic I find  the largest number of rotations needed to
    get any element in the puzzle back to its correct position. I make
    this calculation, and then I spin the wheel of the puzzle, take
    the butterknife distance again, and then spin the wheel back. 
    In other words, I look ahead one move and see if spinning the wheel
    would get us closer to a solution. This heuristic isn't perfect, 
    but it works for randomized puzzles that are randomized between 
    k = 10, and k = 35. 
    I've tried to run more than 35 random moves, but IDA* uses considerably
    more memory than SMA* so the program usually
    crashes. 

