# ECE 309 - Program 3: Maze Problem

## Assignment Overview

### Learning Objectives
- Implement graph algorithms.
- Map problems into data structures.
- Solve problems in an object-oriented manner.

### Associated Files
- Assignment description (this document).
- Test input files (e.g., `maze.txt`, `coordinates.txt`).

### Description
This program requires you to find a valid path in a maze from a starting point to a destination using three different search algorithms: Breadth First Search (BFS), Depth First Search (DFS), and Best-First Search (GBFS).

#### Input Files
1. **Maze File**: Contains an m x n maze structure with values 0 (walls) and 1 (empty spaces).
2. **Coordinates File**: Contains the coordinates of the starting point and the destination.

#### Output Format
- Print `#` at every location with value 0.
- Print `s` and `e` as the starting point and endpoint, respectively.
- Print the path using `+` and leave the rest as `-`.

### Implementation Steps
1. Parse the input parameters to determine the maze, coordinates, and search method.
2. Implement a `Maze` class to store the maze structure.
3. Implement methods for BFS, DFS, and GBFS to find the path:
   - `BFS_searchpath`
   - `DFS_searchpath`
   - `GBFS_searchpath`
4. Print the path found by each method in the specified format.

### Best-First Search
Utilizes heuristic values (Manhattan distance) to select the “best” node to proceed with.

### Report Format
Include the output of each search method in the report:
- Output of BFS
- Output of DFS
- Output of GBFS

### Submission Format
Submit `main.cpp` and `report.pdf`.

### Grading Criteria
- 10 points: Proper file submission.
- 10 points: Program completeness and correct output format.
- 10 points: Proper coding style and comments.
- 60 points: Correct implementation of all functions:
  - `Maze` class correctly stores data (15 pts).
  - BFS method (15 pts).
  - DFS method (15 pts).
  - GBFS method (15 pts).
- 10 points: Report.
