#include <iostream>
#include <fstream>
#include <stdexcept>
#include <stdlib.h>

#define maxints 100
using namespace std;
int numVertices;
int maxVertices;
// Implement graph via adjacency matrix
void createMatrix(int* adjmatrix, int* edges, int numEdges){
       // find index of last vertex
        numVertices=0;
        for(int i=0; i<numEdges; i=i+3){
                if(edges[i] > numVertices) numVertices = edges[i];
                if(edges[i+1] > numVertices) numVertices = edges[i+1];
        }
        numVertices=numVertices+1; // find the number of vertices

	// fill the matrix with infinity, except fill with 0 for the path from a vertex to itself
	for(int k=0; k<numVertices; k++){
		for(int l=0; l<numVertices; l++){
			if(k==l){ adjmatrix[k*numVertices+l]=0; }
			else{ adjmatrix[k*numVertices+l]=100000; 
				adjmatrix[l*numVertices+k]=100000; }			
		}
	}

	// add values to edges not equal to zero or infinity
	// fill as if an undirected graph
	for(int i=0; i<numEdges; i=i+3){
		adjmatrix[edges[i]*numVertices+edges[i+1]]=edges[i+2];
		adjmatrix[edges[i+1]*numVertices+edges[i]]=edges[i+2];
	}
}

// Dijkstra's Algorithm
void shortestPath(int* edges, int n, int* predecessor, int* weights){ // n=number of vertices in the graph = count
	int vertexSet[n]; // create set vertexSet that is empty
	for(int k=0; k<n; k++){ // begin with all predecessors are zero and there are no vertices in the vertexSet
		vertexSet[k]=0;
		predecessor[k]=0;
	}
	vertexSet[0]=1; // add START to vertexSet
	// if vertex v is included in the set, vertexSet[v]=1
	// vertex START is at node 0

	// add weights from START to respective vertex i
	for(int i=0; i<n; i++){
		weights[i] = edges[i];
	}
	// find smallest weight out of vertices not in vertexSet
	int smallest;
	int smallestIndex;
	for(int i=0; i<n; i++){
		smallest = 100000;
		for(int j=0; j<numVertices; j++){
			if(weights[j] < smallest && vertexSet[j] == 0){
				smallestIndex=j; smallest=weights[j];
			}
		}
		int v = smallestIndex; // index of smallest weight[v] such that v is not in vertexset
		vertexSet[v] = 1; /// add v to vertexSet
		for(int u=0; u<n; u++){ // if the distance from newly added v to any vertex u is smaller than existing distance, relax the edge weight
			if(weights[u] > weights[v] + edges[v*numVertices+u]){
				weights[u] = weights[v] + edges[v*numVertices+u];
				predecessor[u] = v;
			}
		}
	}
}

// print the order
void printPath(int y, int* predecessors, int* weights){
	int order[20];
	int i=0;
	int n=y;
	while(n!=0){ // backtrack predecessors until 0
		order[i]=n;
		n = predecessors[n];
		i++;
	}
	order[i]=0; // 0 is always the starting location
	cout << '\n' << "The minimum path is: "; // print the minimum path in order from 0
	for(int j=i; j>=0; j--){ cout << order[j]; 
		 if(j>0) cout << "->"; }
	cout << '\n' << "The total distance of this path is: " << weights[y] << endl; // print distance of minimum path
}

// main function
int main(){
	ifstream inf; // open text file
	int count=0;
	int x;
	int list[maxints];
	inf.open("./weightsvnum.txt");
	
	// read text file and add to array
	if(inf.fail()){
		cerr << "Error: Could not open input file\n";
		exit(1);
	}
	inf.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	while(count < maxints){
		try{
			inf >> x;
		}
		catch(std::ifstream::failure e){
			break;
		}
		list[count++]=x;
	}
	maxVertices = count*2/3; // the maximum amount of vertices will never exceed Number of Edges*2/3
	int* adjmatrix= new int[maxVertices*maxVertices]; // initialize adjacency matrix
	createMatrix(adjmatrix, list, count); // fill values in adjacency matrix
	int* predecessors= new int[numVertices]; // initialize predecessors array
	int* weights = new int[numVertices]; // initialize weights array
	shortestPath(adjmatrix, numVertices, predecessors, weights); // use dijkstra's algorithm to determin shortest path

	int y; // ask for destination
	cout << "Please enter your destination from Snell library as a number: ";
	cin >> y;
	printPath(y,predecessors,weights); // print path to destination

	inf.close(); // close the file at the end of the program
	return 0;
}
