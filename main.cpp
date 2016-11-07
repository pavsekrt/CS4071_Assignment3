/*
//Assignment 3
//Group 8
//Ryan Pavsek & Sean Kennedy
*/
#include <iostream>
#include <vector>
#include <list>
#include <queue>
#include <stack>
#include <string>

using namespace std;

struct edge {
  int i;
  int j;
};
void printMatrix(int** g, int n){
  int i,j;
  for(i = 0;i < n;i++){
    for(j = 0; j < n; j++){
      cout<<g[i][j]<<"\t";
    }
    cout<<endl;
  }
}

class Graph{
  private:
    int **adjMatrix;
    list<int> *adjLL;
    int n;//V
  public:
    Graph(int n){
      this->n = n;
      adjLL = new list<int>[n];
      adjMatrix = new int* [n];
      for (int i = 0; i < n; i++){//nxn matrix of 0's
        adjMatrix[i] = new int [n];
        for(int j = 0; j < n; j++){
            adjMatrix[i][j] = 0;
        }
      }
    }
    Graph(const vector<edge> E, int n){
      this->n = n;
      adjLL = new list<int>[n];
      adjMatrix = new int* [n];
      for (int i = 0; i < n; i++){//nxn matrix of 0's
        adjMatrix[i] = new int [n];
        for(int j = 0; j < n; j++){
            adjMatrix[i][j] = 0;
        }
      }
      addEdges(E);
    }
    void addEdges(const vector<edge> E){
      for (size_t i = 0; i < E.size(); i++) {
        addEdge(E.at(i).i, E.at(i).j);
      }
    }
    void addEdge(int i, int j){//adds edges to Adjacency Matrix
      if( i > n || j > n || i < 0 || j < 0){
        cout<<"Invalid edge!\n";
      }else{
        adjMatrix[i][j] += 1;
        adjMatrix[j][i] += 1;
        adjLL[i].push_back(j);
        adjLL[j].push_back(i);
      }
    }
    void print(){
      printMatrix(adjMatrix, n);
    }
    int** getGraph(){
      return adjMatrix;
    }
    int getN(){
      return n;
    }
    list<int>* &getAdjLL(){
      return adjLL;
    }
};

int BFS(int** g, int start, int end, int numOfVertices) {
  queue<int> verts;
  queue<int> dist;
  vector<bool> visited(numOfVertices);
  visited.at(start) = true;
  verts.push(start);
  dist.push(0);

  int curVert;
  int distance;
  while (!verts.empty()) {
    vector<int> neighbors;
    curVert = verts.front();
    distance = dist.front();
    // return distance
    if (curVert == end) {
      return distance;
    }
    verts.pop();
    dist.pop();
    // get the neighbors of current vertex
    for (int i = 0; i < numOfVertices; i++) {
      if (g[i][curVert] == true) {
        // add the vertex
        neighbors.push_back(i);
      }
    }
    // add neighbors & distance to queues
    for (int i = 0; i < neighbors.size(); i++) {
      if (!visited.at(neighbors[i])) {
        visited.at(neighbors[i]) = true;
        verts.push(neighbors[i]);
        dist.push(distance + 1);
      }
    }
  }
  return -1;
}

int** distanceMatrix(int** g, int numOfVertices) {
  int **matrix;

  // BFS computes the distances for all elements
  matrix = new int* [numOfVertices];
  for (int i = 0; i < numOfVertices; i++) {
    matrix[i] = new int [numOfVertices];
    for (int j = 0; j < numOfVertices; j++) {
      matrix[i][j] = BFS(g, i, j, numOfVertices);
    }
  }

  return matrix;
}

int diameter(int** g, int numOfVertices) {
  // get distance matrix
  int** matrix = distanceMatrix(g, numOfVertices);
  // graph connected?
  for (int i = 0; i < numOfVertices; i++) {
    for (int j = 0; j < numOfVertices; j++) {
      if (matrix[i][j] == -1) {
        return -1;
      }
    }
  }
  // find max distance in distance matrix
  int max = 0;
  for (int i = 0; i < numOfVertices; i++) {
    for (int j = 0; j < numOfVertices; j++) {
      if (matrix[i][j] > max) {
        max = matrix[i][j];
      }
    }
  }
  return max;
}
void DFS(list<int>* &g, int v, bool visited[])
{
    // Mark the current node  visited
    visited[v] = true;
    cout << v << " ";

    list<int>::iterator i;
    for (i = g[v].begin(); i != g[v].end(); ++i)
      if (!visited[*i])
        DFS(g, *i, visited);
}
void order(list<int>* &g, int v, bool visited[], stack<int> &Stack)
{
  // current node visited
  visited[v] = true;

  list<int>::iterator i;
  for(i = g[v].begin(); i != g[v].end(); ++i)
    if(!visited[*i])
      order(g, *i, visited, Stack);

  Stack.push(v);
}

void Components(list<int>* &g, int numOfVertices)
{
  stack<int> Stack;
  // vertices not visited
  bool *visited = new bool[numOfVertices];
  for(int i = 0; i < numOfVertices; i++)
    visited[i] = false;
  // Fill vertices in stack
  for(int i = 0; i < numOfVertices; i++)
    if(visited[i] == false){
      order(g, i, visited, Stack);
    }

  // vertices as not visited
  for(int i = 0; i < numOfVertices; i++){
    visited[i] = false;
  }

  // process all vertices
  while (Stack.empty() == false)
  {
    // Pop from stack
    int v = Stack.top();
    Stack.pop();
    // Print connected component
    if (visited[v] == false)
    {
      DFS(g, v, visited);
      cout << endl;
    }
  }
}


int main(int argc, char* argv[])
{
  int numOfVertices;
  vector<int> V;
  vector<edge> E;
  //Usage Test & setting V,E
  try{
    numOfVertices = atoi(argv[1]);
    if ((argc < 5)||(*argv[argc-1] != '-')||(argc%2==0)||(numOfVertices != ((argc-3)/2))) {
      throw(0);
    }
    for(size_t i = 0; i < numOfVertices; i++){V.push_back(i);}// V
    for (size_t i = 2; i < (argc-1); i+=2) { // E
      int x = atoi(argv[i]);
      int y = atoi(argv[i+1]);
      if (x > numOfVertices || x < 0 || y > numOfVertices || y < 0){
        throw(0);
      }
      edge t = {x, y};
      E.push_back(t);
    }
  }catch (int e){
    cerr << endl << "Usage: " << argv[0] << " n i j (i j i j ...) -1" << endl;
    cerr << "n = number of vertices, i j = sequence of pairs (integers between 0 and n)" << endl << endl;
    return 1;
  }
  //END
  Graph a = Graph(E, numOfVertices);
  cout << endl << "Adjacency Matrix: " << endl;
  a.print();
  cout << endl << endl << "Distance Matrix: " << endl;
  int **dMatrix = distanceMatrix(a.getGraph() , numOfVertices);
  printMatrix(dMatrix, numOfVertices);
  cout << endl << endl << "Diameter: " << endl;
  cout << diameter(a.getGraph(), numOfVertices) << endl;
  cout << endl << endl << "Components: " << endl;
  Components(a.getAdjLL(), numOfVertices);





  return 0;
}
