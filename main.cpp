#include <iostream>
#include <vector>
#include <fstream>
#include <queue>
#include <stack>
#include <cmath>





using namespace std;




// Define constants for maze values
const char WALL = '0';
const char EMPTY = '1';
const char START = 's';
const char END = 'e';
const char PATH = '+';
const char VISITED = '-'; // Mark visited cells
const char SPACE = ' ';


// Define a structure for coordinates
struct Coordinates {
    int x, y;
    bool operator<(const Coordinates& other) const {
        // Here, you can define how Coordinates should be compared
        // For example, you might compare based on x first, and then y
        if (x != other.x) {
            return x < other.x;
        }
        // If x is equal, compare based on y
        return y < other.y;
    }
};


// Define a class for the maze
class Maze {
private:
    vector<vector<char>> maze; // To store the maze
    vector<vector<Coordinates>> parent; // To store parent of each cell
    int rows, cols;

public:
    Coordinates start, end;

    //make start coordinates and end coordinates from coordinates file
    Maze(const string &filename, const string &coordinatesFilename) {
        //create a 2D vector without the spaces
        ifstream file(filename);
        ifstream coordinatesFile(coordinatesFilename);
        string line;
        vector<char> row;
        while (getline(file, line)) {
            for (int i = 0; i < line.length(); i++) {
                if (line[i] != SPACE) {
                    row.push_back(line[i]);
                }
            }
            maze.push_back(row);
            row.clear();
        }
        rows = maze.size();
        cols = maze[0].size();
        //printIt();
        //read the coordinates file
        string startCoordinates;
        string endCoordinates;
        getline(coordinatesFile, startCoordinates);
        getline(coordinatesFile, endCoordinates);
        //cout << startCoordinates << endl;
        //cout << endCoordinates << endl;
        start.x = startCoordinates[0] - '0';
        start.y = startCoordinates[2] - '0';
        end.x = endCoordinates[0] - '0';
        end.y = endCoordinates[2] - '0';
        //cout << start.x << "," << start.y << endl;
        //cout << end.x << "," << end.y << endl;
    }

    //Branch First Search
    void BFS_searchpath() {
        // Initialize a queue for BFS
        cout<<"BFS output: "<<endl;
        queue<Coordinates> q;
        // Initialize a 2D vector to store parent information
        parent.assign(rows, vector<Coordinates>(cols, {-1, -1}));

        // Enqueue the starting cell
        q.push(start);
        // Mark the starting cell as visited
        maze[start.x][start.y] = VISITED;

        // Perform BFS
        while (!q.empty()) {
            // Dequeue a cell
            Coordinates current = q.front();
            q.pop();

            // Check if we reached the destination
            if (current.x == end.x && current.y == end.y) {
                // Reconstruct the shortest path
                Coordinates traceBack = current;
                while (!(traceBack.x == start.x && traceBack.y == start.y)) {
                    maze[traceBack.x][traceBack.y] = PATH;
                    traceBack = parent[traceBack.x][traceBack.y];
                }
                maze[start.x][start.y] = START; // Mark start cell
                maze[end.x][end.y] = END; // Mark end cell
                printMaze();
                return;
            }

            // Explore neighbors (up, down, left, right)
            vector<Coordinates> neighbors = {{current.x - 1, current.y}, {current.x + 1, current.y},
                                             {current.x, current.y - 1}, {current.x, current.y + 1}};
            for (const auto &neighbor : neighbors) {
                int nx = neighbor.x, ny = neighbor.y;
                if (nx >= 0 && nx < rows && ny >= 0 && ny < cols && maze[nx][ny] == EMPTY) {
                    // Mark neighbor as visited
                    maze[nx][ny] = VISITED;
                    // Set parent of neighbor
                    parent[nx][ny] = current;
                    // Enqueue neighbor
                    q.push(neighbor);
                }
            }
        }
        cout << "No path found!" << endl;
    }

    //Depth First Search
    void DFS_searchpath() {
        // Start DFS from the starting coordinates
        cout<<"DFS output: "<<endl;
        stack<Coordinates> s;
        s.push(start);

        //while the stack is not empty
        while(!s.empty()){
            //get the top of the stack
            Coordinates current = s.top();
            //mark the current cell as visited
            maze[current.x][current.y] = VISITED;
            //check if the current cell is the end cell
            //cout<<end.y;
            if(current.x == end.x && current.y == end.y){
                //go through the stack and set each cell to PATH
                while(!s.empty()){
                    Coordinates path = s.top();
                    maze[path.x][path.y] = PATH;
                    s.pop();
                }
                printMaze();
            }
            //check if the cell to the right is empty
            if(current.y + 1 < cols && maze[current.x][current.y + 1] == EMPTY){
                //push the cell to the right onto the stack
                s.push({current.x, current.y + 1});
            }
            //check if the cell below is empty
            else if(current.x + 1 < rows && maze[current.x + 1][current.y] == EMPTY){
                //push the cell below onto the stack
                s.push({current.x + 1, current.y});
            }
            //check if the cell to the left is empty
            else if(current.y - 1 >= 0 && maze[current.x][current.y - 1] == EMPTY){
                //push the cell to the left onto the stack
                s.push({current.x, current.y - 1});
            }
            //check if the cell above is empty
            else if(current.x - 1 >= 0 && maze[current.x - 1][current.y] == EMPTY){
                //push the cell above onto the stack
                s.push({current.x - 1, current.y});
            }
            //if there are no empty cells around the current cell, pop the current cell off the stack
            else{
                s.pop();
            }
        }
    }



    // Greedy Best First Search
    void GBFS_searchpath() {
        cout<<"GBFS output: "<<endl;
        // Initialize a priority queue for GBFS
        priority_queue<pair<int, Coordinates>, vector<pair<int, Coordinates>>, greater<>> pq;
        // Initialize a 2D vector to store parent information
        parent.assign(rows, vector<Coordinates>(cols, {-1, -1}));

        // Define a heuristic function - Euclidean distance
        auto heuristic = [&](Coordinates a, Coordinates b) {
            // Calculate the Euclidean distance
            int distance = sqrt(pow((a.x - b.x), 2) + pow((a.y - b.y), 2));
            return distance;
        };

        // Enqueue the starting cell with its heuristic value
        pq.push({heuristic(start, end), start});

        // Perform GBFS
        while (!pq.empty()) {
            // Dequeue a cell
            Coordinates current = pq.top().second;
            pq.pop();

            // Check if we reached the destination
            if (current.x == end.x && current.y == end.y) {
                // Reconstruct the shortest path
                Coordinates traceBack = current;
                while (!(traceBack.x == start.x && traceBack.y == start.y)) {
                    maze[traceBack.x][traceBack.y] = PATH;
                    traceBack = parent[traceBack.x][traceBack.y];
                }
                maze[start.x][start.y] = START; // Mark start cell
                maze[end.x][end.y] = END;       // Mark end cell
                printMaze();
                return;
            }

            // Explore neighbors (up, down, left, right)
            vector<Coordinates> neighbors = {{current.x - 1, current.y}, {current.x + 1, current.y},
                                             {current.x, current.y - 1}, {current.x, current.y + 1}};
            for (const auto &neighbor : neighbors) {
                int nx = neighbor.x, ny = neighbor.y;
                if (nx >= 0 && nx < rows && ny >= 0 && ny < cols && maze[nx][ny] == EMPTY) {
                    // Mark neighbor as visited
                    maze[nx][ny] = VISITED;
                    // Set parent of neighbor
                    parent[nx][ny] = current;
                    // Enqueue neighbor with its heuristic value
                    pq.push({heuristic(neighbor, end), neighbor});
                }
            }
        }
        cout << "No path found!" << endl;
    }

    void printMaze() {
        // Print the maze
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if (i == start.x && j == start.y) {
                    cout << "s";
                } else if (i == end.x && j == end.y) {
                    cout << "e";
                } else if (maze[i][j] == WALL) {
                    cout << "#";
                } else if (maze[i][j] == EMPTY) {
                    cout << "-";
                } else if (maze[i][j] == VISITED) {
                    cout << "-";
                } else if (maze[i][j] == PATH) {
                    cout << "+";
                }else if (maze[i][j] == SPACE && j % 2 == 0) {
                    cout << " ";
                }
                cout<< " ";
            }
            cout << endl;
        }
    }};


int main(int argc, char* argv[]) {
    string mazeFilename = argv[1];
    string coordinatesFilename = argv[2];
    string searchMethod = argv[3];

    //print the maze


    Maze maze(mazeFilename, coordinatesFilename);
    if (searchMethod == "DFS") {
        // Start DFS from the specified start coordinates
        maze.DFS_searchpath();
    } else if (searchMethod == "BFS") {
        // Start BFS from the specified start coordinates
        maze.BFS_searchpath();
    } else if (searchMethod == "GBFS") {
        maze.GBFS_searchpath();
    } else {
        cout << "Invalid search method." << endl;
        return 1;
    }
    return 1;
}




