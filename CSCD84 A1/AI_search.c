/*
	CSC D84 - Unit 1 - Search

	This file contains stubs for implementing the different search
	ealgorithms covered in the course. Please read the assignment
	handout carefully - it describes the game, the data you will
	have to handle, and the search functions you must provide.

	Once you have read the handout carefully, implement your search
	code in the sections below marked with

	**************
	*** TO DO:
	**************

	Make sure to add it to your report.txt file - it will be marked!

	Have fun!

	DO NOT FORGET TO 'valgrind' YOUR CODE - We will check for pointer
	management being done properly, and for memory leaks.

	Starter code: F.J.E., Jul. 15
	Updated: F.J.E., Jan. 18
*/

/**********************************************************************
% COMPLETE THIS TEXT BOX:
%
% 1) Student Name:	Alexia Tolentino	
%
% 1) Student number: 1006293967
% 
% 1) UtorID: tolent55
% 
% We hereby certify that the work contained here is our own
%
% Alexia Tolentino                  
% (sign with your name)            
***********************************************************************/

#include "AI_search.h"
#include <stdbool.h>


//Same Location function
/* Takes one location and another and compares their x and y values.
iterations is the number of comparisons being made with the second location(s)
If they are equal then it returns true, otherwise it returns false.
*/
bool same_location(int loc1[1][2], int iterations, int loc2[][2]){
	int i;
	for(i=0; i<iterations; i++){
		if (loc1[0][0] == loc2[i][0] && loc1[0][1] == loc2[i][1]){
		return true;
		}
	}
	
	//if none are detected then we return false
	return false;
}

//Creating node struct for A_star and BFS
struct node{
	int index; // index of the node
	int cost; // cost of getting there
	int pred_idx; // predecessor of node
	int visited = 0; //visited = 0 if false and 1 if true
};

//PRIORITY QUEUE for A_star and BFS
//queue is made of the node struct we created
struct node priority_queue[graph_size];
int size = -1;

//checks if the priority queue is empty
int pq_empty(){
	if (size == -1){
		return 1; // 1 = true
	}
	return 0;
}

//inserts a new node into the priority queue
void insert(int index, int cost, int pred_idx){
	size++;

	//setting values
	priority_queue[size].index = index;
	priority_queue[size].pred_idx = pred_idx;
	priority_queue[size].cost = cost;
	priority_queue[size].visited = 1;
}

//returns index of lowest cost node in the priority queue
int lowest_cost_node(){
	int lowest_cost = 2000; // max value
	int lowest_index = -1;

	for (int i=0; i<=size; i++){
		//if lowest_cost is larger than the cost found at index i
		if(lowest_cost > priority_queue[i].cost){
			lowest_cost = priority_queue[i].cost;
			lowest_index = i;
		}
	}
	return lowest_index;
}

//returns cost of specific index
int cost_of_idx(int index){
	int cost;
	for (int i=0; i<=size; i++){
		//if lowest_cost is larger than the cost found at index i
		if(index == priority_queue[i].index){
			cost = priority_queue[i].cost;
		}
	}
	return cost;
}

//dequeues a node from the queue
void dequeue(){
	int cheapest_node = lowest_cost_node();

	for (int i = cheapest_node; i<size; i++){
		priority_queue[i] = priority_queue[i+1];
	}
	size--;
}

/*
BFS CODE ----------------------------------------------------------------
additional parameters other than starting parameters
expanded: a list of indexxes that have been expanded (0 - False, 1 - True)
visited: a list of nodes that have been visited (0 - False, 1 - True)
iteration: the current iteration the search is on
bfs_finished: If the search has completed (0 - False, 1 - True)
-------------------------------------------------------------------------
*/
int BFS(double gr[graph_size][4], int path[graph_size][2], 
			int visit_order[size_X][size_Y], int expanded[graph_size], struct node visited[graph_size],
			int curr_loc[1][2], int destination[1][2], int cat_loc[10][2], 
			int iteration, int bfs_finished){

	int index = curr_loc[0][0]+(curr_loc[0][1]*32);
	int mouseindex = index; //storing first index
	
	//add first start node to queue
	insert(index, 0, index); // it's is own parent and it has 0 cost
	//create new location and new index which will change based on the queue
	int new_loc[1][2];
	int new_index;
	int new_cost;

	//get index value of destination
	int dest_index = destination[0][0] + (destination[0][1]*32);

	//while the stack isnt empty and the destination hasn't been expanded
	while(expanded[dest_index] == 0){ //!pq_empty() && expanded[dest_index] == 0 && bfs_finished == 0
	/* NOTES:
		- In this loop index is referring to the current location
		- Current location is changed depending on what index is popped from the stack
	*/
		//set new location to be the neighbour
		if(((index/32)-1) >= 0 && ((index/32)-1) < 32){ //top
			new_loc[0][0] = index%32;
			new_loc[0][1] = (index/32)-1;
			new_index = new_loc[0][0]+(new_loc[0][1]*32);
			//BASE: if the neighbour is the destination node
			if(same_location(new_loc, 1, destination) && visited[new_index].visited==0 
			&& gr[index][0]==(double)1 && !same_location(new_loc,10,cat_loc)){
				
				visited[new_index].visited = 1; 
				visit_order[new_loc[0][0]][new_loc[0][1]] = iteration;
				iteration++;

				//set predecessor
				visited[new_index].pred_idx = index; 
				insert(new_index, 0, index);
				bfs_finished = 1;
			} //otherwise you add it to the stack and don't change finished
			else if (visited[new_index].visited==0 && gr[index][0]==(double)1 && !same_location(new_loc,10,cat_loc)){
				visited[new_index].visited = 1; 
				visit_order[new_loc[0][0]][new_loc[0][1]] = iteration;
				iteration++;

				//set predecessor
				visited[new_index].pred_idx = index; 
				insert(new_index, 0, index);
			}
		}
		if (((index%32)+1) >= 0 && ((index%32)+1) < 32){ //right
			new_loc[0][0] = (index%32)+1;
			new_loc[0][1] = index/32;
			new_index = new_loc[0][0]+(new_loc[0][1]*32);
			//BASE: if the neighbour is the destination node
			if(same_location(new_loc, 1, destination) && visited[new_index].visited==0 
			&& gr[index][1]==(double)1 && !same_location(new_loc,10,cat_loc)){
				visited[new_index].visited = 1; 
				visit_order[new_loc[0][0]][new_loc[0][1]] = iteration;
				iteration++;

				//set predecessor
				visited[new_index].pred_idx = index; 
				insert(new_index, 0, index);
				bfs_finished = 1;
			} //otherwise you add it to the stack and don't change finished
			else if (visited[new_index].visited==0 && gr[index][1]==(double)1 && !same_location(new_loc,10,cat_loc)){
				visited[new_index].visited = 1; 
				visit_order[new_loc[0][0]][new_loc[0][1]] = iteration;
				iteration++;

				//set predecessor
				visited[new_index].pred_idx = index; 
				insert(new_index, 0, index);
			}
		}
		if (((index/32)+1) >= 0 && ((index/32)+1) < 32){ //bottom
			new_loc[0][0] = index%32;
			new_loc[0][1] = (index/32)+1;
			new_index = new_loc[0][0]+(new_loc[0][1]*32);
			//BASE: if the neighbour is the destination node
			if(same_location(new_loc, 1, destination) && visited[new_index].visited==0 
			&& gr[index][2]==(double)1 && !same_location(new_loc,10,cat_loc)){
				visited[new_index].visited = 1; 
				visit_order[new_loc[0][0]][new_loc[0][1]] = iteration;
				iteration++;

				//set predecessor
				visited[new_index].pred_idx = index; 
				insert(new_index, 0, index);
				bfs_finished = 1;
			} //otherwise you add it to the stack and don't change finished
			else if (visited[new_index].visited==0 && gr[index][2]==(double)1 && !same_location(new_loc,10,cat_loc)){
				visited[new_index].visited = 1; 
				visit_order[new_loc[0][0]][new_loc[0][1]] = iteration;
				iteration++;

				//set predecessor
				visited[new_index].pred_idx = index; 
				insert(new_index, 0, index);
			}
		}
		if (((index%32)-1) >= 0 && ((index%32)-1) < 32){ //left
			new_loc[0][0] = (index%32)-1;
			new_loc[0][1] = index/32;
			new_index = new_loc[0][0]+(new_loc[0][1]*32);
			//BASE: if the neighbour is the destination node
			if(same_location(new_loc, 1, destination) && visited[new_index].visited==0 
			&& gr[index][3]==(double)1 && !same_location(new_loc,10,cat_loc)){
				visited[new_index].visited = 1; 
				visit_order[new_loc[0][0]][new_loc[0][1]] = iteration;
				iteration++;

				//set predecessor
				visited[new_index].pred_idx = index; 
				insert(new_index, 0, index);
				bfs_finished = 1;
			} //otherwise you add it to the stack and don't change finished
			else if (visited[new_index].visited==0 && gr[index][3]==(double)1 && !same_location(new_loc,10,cat_loc)){
				visited[new_index].visited = 1; 
				visit_order[new_loc[0][0]][new_loc[0][1]] = iteration;
				iteration++;

				//set predecessor
				visited[new_index].pred_idx = index; 
				insert(new_index, 0, index);
			}
		}
		//at the end of checking all neighbours
		//mark index as expanded
		expanded[index] = 1;
		index = priority_queue[0].index; 
		dequeue();
	}
	
	//setting starting position for mouse
	int steps = 0;
	int nextindex = dest_index;
	int pred;

	//build the path by dequeuing and getting predecessors!
	while(nextindex!=mouseindex){ //getting number of steps needed
		steps++;
		pred = visited[nextindex].pred_idx;
		nextindex=pred;
	}

	path[steps][0] = dest_index%32;
	path[steps][1] = dest_index/32;
	
	//building the path
	nextindex = dest_index;
	while(steps!=0){
		pred = visited[nextindex].pred_idx;
		path[steps-1][0] = pred%32;
		path[steps-1][1] = pred/32;
		nextindex=pred;
		steps--;
	}

	//clear queue
	while(pq_empty()==0){
		dequeue();
	}

	//clear expanded for next rotation
	for(int i = 0; i<graph_size; i++){
		expanded[i] == 0;
		visited[i].pred_idx == 0;
	}

	return bfs_finished;
}



//STACK for DFS
int stack[graph_size];
int top = -1;

//checks if stack is empty
int stack_isempty() {
	if(top == -1){
		return 1;
	}
 return 0;
}

//pushes new indexes on the stack
void push(int data) {
    top++;   
    stack[top] = data;
}

//pops indexes off the stack
void pop() {
   if(!stack_isempty()) {
      stack[top];
      top--;   
   }
}

//pops indexes off the stack retrieving a value
int pop_w_value(){
	int val;
   if(!stack_isempty()) {
      val = stack[top];
      top--;
   }
   return val;
}

/*
DFS CODE ----------------------------------------------------------------
additional parameters other than starting parameters
expanded: a list of indexxes that have been expanded (0 - False, 1 - True)
iteration: the current iteration the search is on
dfs_finished: If the search has completed (0 - False, 1 - True)
-------------------------------------------------------------------------
*/
int DFS(double gr[graph_size][4], int path[graph_size][2], 
			int visit_order[size_X][size_Y], int expanded[graph_size], 
			int curr_loc[1][2], int destination[1][2], int cat_loc[10][2], 
			int iteration, int dfs_finished){
	
	//note that x = curr_loc[0][0] and y = curr_loc[0][1]
	//therefore we define index = x + (y*32) as below
	int index = curr_loc[0][0]+(curr_loc[0][1]*32);
	push(index);

	//BASE CASE: if the mouse is already at the cheese:
	if (same_location(curr_loc, 1, destination)){
		//we set dfs as finished
		dfs_finished = 1;

		//get last index
		int path_idx = top;
		//clear stack and set path
		while(!stack_isempty()) {
      		int val = pop_w_value();
			path[path_idx][0] = val%32;
			path[path_idx][1] = val/32;
			path_idx = path_idx-1;
   		}
		return dfs_finished;
	}
	//OTHERWISE: continue to search
	//let j be our index for neighbours
	int j = 0;
	//mark expanded index as 1 (1 indicates it has been expanded)
	expanded[index] = 1;
	visit_order[curr_loc[0][0]][curr_loc[0][1]] = iteration;
	
	//for top, right, bottom, and left neighbours
	for(j=0;j<4;j++){
		//if there is a neighbour and it's not visited
		if(gr[index][j]==(double)1 && index >=0){
			//set new location to be the neighbour
			int new_loc[1][2];
			if(j==0 && ((index/32)-1) >= 0 && ((index/32)-1) < 32){ //top
				new_loc[0][0] = index%32;
				new_loc[0][1] = (index/32)-1;
				iteration++;
			}
			else if (j==1 && ((index%32)+1) >= 0 && ((index%32)+1) < 32){ //right
				new_loc[0][0] = (index%32)+1;
				new_loc[0][1] = index/32;
				iteration++;
			}
			else if (j==2 && ((index/32)+1) >= 0 && ((index/32)+1) < 32){ //bottom
				new_loc[0][0] = index%32;
				new_loc[0][1] = (index/32)+1;
				iteration++;
			}
			else if (j==3 && ((index%32)-1) >= 0 && ((index%32)-1) < 32){ //left
				new_loc[0][0] = (index%32)-1;
				new_loc[0][1] = index/32;
				iteration++;
			}
			
			//get newindex
			int new_index = new_loc[0][0]+(new_loc[0][1]*32);

			//Make sure that new location isn't running into a cat
			if (!same_location(new_loc, 10, cat_loc) && expanded[new_index]==0){
				//run DFS on the neighbour
				dfs_finished = DFS(gr, path, visit_order, expanded, new_loc, destination, cat_loc, iteration, dfs_finished);

				//if its not finished we continue
				if(dfs_finished){
					return dfs_finished;
				}
			}
		}
	}
	//pop unhelpful nodes
	pop();
	return dfs_finished;
}


/*
A* CODE ----------------------------------------------------------------
additional parameters other than starting parameters
expanded: a list of indexxes that have been expanded (0 - False, 1 - True)
visited: a list of nodes that have been visited (0 - False, 1 - True)
iteration: the current iteration the search is on
finished: If the search has completed (0 - False, 1 - True)
-------------------------------------------------------------------------
*/
int A_star(double gr[graph_size][4], int path[graph_size][2], 
			int visit_order[size_X][size_Y], int expanded[graph_size], struct node visited[graph_size], 
			int curr_loc[1][2], int destination[1][2], int cat_loc[10][2], 
			int iteration, int finished, int cats, int cheeses,
			int (*heuristic)(int x, int y, int cat_loc[10][2], int cheese_loc[10][2], int mouse_loc[1][2], int cats, int cheeses, double gr[graph_size][4])){

	int index = curr_loc[0][0]+(curr_loc[0][1]*32);
	int mouseindex = index; //storing first index
	
	//add first start node to queue
	insert(index, 0, index); // it's is own parent and it has 0 cost
	//create new location and new index which will change based on the queue
	int new_loc[1][2];
	int new_index;
	int new_cost;

	//get index value of destination
	int dest_index = destination[0][0] + (destination[0][1]*32);


	//while the stack isnt empty and the destination hasn't been expanded
	while(!pq_empty() && expanded[dest_index] == 0){
	/* NOTES:
		- In this loop index is referring to the current location
		- Current location is changed depending on what index is popped from the stack
	*/
		//TOP neighbour
		if(gr[index][0]==(double)1 && index >=0){
			if(((index/32)-1) >= 0 && ((index/32)-1) < 32){ //top
					//get new info for neighbour
					new_loc[0][0] = index%32;
					new_loc[0][1] = (index/32)-1;
					new_index = new_loc[0][0]+(new_loc[0][1]*32);
				
				//if the new index has NOT been expanded yet
				if(expanded[new_index]!= 1){

					//increase iterations
					iteration++;
					visit_order[new_loc[0][0]][new_loc[0][1]] = iteration;

					//set predecessor
					visited[new_index].pred_idx = index; 

					//BASE: if the neighbour is the destination node
					if(same_location(new_loc, 1, destination)){
						new_cost = heuristic(new_loc[0][0], new_loc[0][1], cat_loc, destination, curr_loc, cats, cheeses, gr); 
						insert(new_index, new_cost, index);
						finished = 1;
					} //otherwise you add it to the stack and don't change finished
					else{
						new_cost = heuristic(new_loc[0][0], new_loc[0][1], cat_loc, destination, curr_loc, cats, cheeses, gr);
						insert(new_index, new_cost, index);
					}
				}//othwesise if it HAS been visited
				else{
					//potentially update cost
					new_cost = heuristic(new_loc[0][0], new_loc[0][1], cat_loc, destination, curr_loc, cats, cheeses, gr);
					if (new_cost < cost_of_idx(new_index)){
						//change old cost to new cost
						priority_queue[new_index].cost = new_cost;

						//change predecessor
						visited[new_index].pred_idx = index; 
					}
				}
			}
		}
		if(gr[index][1]==(double)1 && index >=0){
			//RIGHT neighbour
			if(((index%32)+1) >= 0 && ((index%32)+1) < 32){ //top
					//get new info for neighbour
					new_loc[0][0] = index%32+1;
					new_loc[0][1] = (index/32);
					new_index = new_loc[0][0]+(new_loc[0][1]*32);
				
				//if the new index has NOT been expanded yet
				if(expanded[new_index]!= 1){

					//increase iterations
					iteration++;
					visit_order[new_loc[0][0]][new_loc[0][1]] = iteration;

					//set predecessor
					visited[new_index].pred_idx = index; 

					//BASE: if the neighbour is the destination node
					if(same_location(new_loc, 1, destination)){
						new_cost = heuristic(new_loc[0][0], new_loc[0][1], cat_loc, destination, curr_loc, cats, cheeses, gr);
						insert(new_index, new_cost, index);
						finished = 1;
					} //otherwise you add it to the stack and don't change finished
					else{
						new_cost = heuristic(new_loc[0][0], new_loc[0][1], cat_loc, destination, curr_loc, cats, cheeses, gr);
						insert(new_index, new_cost, index);
					}
				}//othwesise if it HAS been visited
				else{
					//potentially update cost
					new_cost = heuristic(new_loc[0][0], new_loc[0][1], cat_loc, destination, curr_loc, cats, cheeses, gr);
					if (new_cost < cost_of_idx(new_index)){
						//change old cost to new cost
						priority_queue[new_index].cost = new_cost;

						//change predecessor
						visited[new_index].pred_idx = index; 
					}
				}
			}
		}
		if(gr[index][2]==(double)1 && index >=0){
			//BOTTOM neighbour
			if(((index/32)+1) >= 0 && ((index/32)+1) < 32){ //top
					//get new info for neighbour
					new_loc[0][0] = index%32;
					new_loc[0][1] = (index/32)+1;
					new_index = new_loc[0][0]+(new_loc[0][1]*32);
				
				//if the new index has NOT been expanded yet
				if(expanded[new_index]!= 1){

					//increase iterations
					iteration++;
					visit_order[new_loc[0][0]][new_loc[0][1]] = iteration;

					//set predecessor
					visited[new_index].pred_idx = index; 

					//BASE: if the neighbour is the destination node
					if(same_location(new_loc, 1, destination)){
						new_cost = heuristic(new_loc[0][0], new_loc[0][1], cat_loc, destination, curr_loc, cats, cheeses, gr); // 10 and 1 are temp numbers
						insert(new_index, new_cost, index);
						finished = 1;
					} //otherwise you add it to the stack and don't change finished
					else{
						new_cost = heuristic(new_loc[0][0], new_loc[0][1], cat_loc, destination, curr_loc, cats, cheeses, gr);
						insert(new_index, new_cost, index);
					}
				}//othwesise if it HAS been visited
				else{
					//potentially update cost
					new_cost = heuristic(new_loc[0][0], new_loc[0][1], cat_loc, destination, curr_loc, cats, cheeses, gr);
					if (new_cost < cost_of_idx(new_index)){
						//change old cost to new cost
						priority_queue[new_index].cost = new_cost;

						//change predecessor
						visited[new_index].pred_idx = index; 
					}
				}
			}
		}
		if(gr[index][3]==(double)1 && index >=0){
			//LEFT neighbour
			if(((index%32)-1) >= 0 && ((index%32)-1) < 32){ //top
					//get new info for neighbour
					new_loc[0][0] = index%32-1;
					new_loc[0][1] = (index/32);
					new_index = new_loc[0][0]+(new_loc[0][1]*32);
				
				//if the new index has NOT been expanded yet
				if(expanded[new_index]!= 1){

					//increase iterations
					iteration++;
					visit_order[new_loc[0][0]][new_loc[0][1]] = iteration;

					//set predecessor
					visited[new_index].pred_idx = index; 

					//BASE: if the neighbour is the destination node
					if(same_location(new_loc, 1, destination)){
						new_cost = heuristic(new_loc[0][0], new_loc[0][1], cat_loc, destination, curr_loc, cats, cheeses, gr); // 10 and 1 are temp numbers
						insert(new_index, new_cost, index);
						finished = 1;
					} //otherwise you add it to the stack and don't change finished
					else{
						new_cost = heuristic(new_loc[0][0], new_loc[0][1], cat_loc, destination, curr_loc, cats, cheeses, gr);
						insert(new_index, new_cost, index);
					}
				}//othwesise if it HAS been visited
				else{
					//potentially update cost
					new_cost = heuristic(new_loc[0][0], new_loc[0][1], cat_loc, destination, curr_loc, cats, cheeses, gr);
					if (new_cost < cost_of_idx(new_index)){
						//change old cost to new cost
						priority_queue[new_index].cost = new_cost;

						//change predecessor
						visited[new_index].pred_idx = index; 
					}
				}
			}
		}
		//at the end of checking all neighbours
		//mark index as expanded
		expanded[index] = 1;
		//change index to next with lowest cost
		int pqindx = lowest_cost_node(); // function returns index in the queue of the lowest cost
		index = priority_queue[pqindx].index; // new index is the value at lowest cost
		dequeue(); //dequeue lowest cost node
	}

	//setting starting position for mouse
	int steps = 0;
	int nextindex = dest_index;
	int pred;

	//build the path by dequeuing and getting predecessors!
	while(nextindex!=mouseindex){ //getting number of steps needed
		steps++;
		pred = visited[nextindex].pred_idx;
		nextindex=pred;
		
	}

	path[steps][0] = dest_index%32;
	path[steps][1] = dest_index/32;
	
	//building the path
	nextindex = dest_index;
	while(steps!=0){
		pred = visited[nextindex].pred_idx;
		path[steps-1][0] = pred%32;
		path[steps-1][1] = pred/32;
		nextindex=pred;
		steps--;
	}

	//clear queue
	while(pq_empty()==0){
		dequeue();
	}

	//clear expanded for next rotation
	for(int i = 0; i<graph_size; i++){
		expanded[i] == 0;
		visited[i].pred_idx == 0;
	}
	return finished;
}

void search(double gr[graph_size][4], int path[graph_size][2], int visit_order[size_X][size_Y], int cat_loc[10][2], int cats, int cheese_loc[10][2], int cheeses, int mouse_loc[1][2], int mode, int (*heuristic)(int x, int y, int cat_loc[10][2], int cheese_loc[10][2], int mouse_loc[1][2], int cats, int cheeses, double gr[graph_size][4]))
{
 /*
   This function is the interface between your solution for the assignment and the driver code. The driver code
   in AI_search_core_GL will call this function once per frame, and provide the following data
   
   Board and game layout:
	
	The game takes place on a grid of size 32x32, the file board_layout.h specifies the size and defines two
	constants 'size_X' and 'size_Y' for the horizontal and vertical size of the board, respectively. For our
	purposes, the grid of locations is represented by a graph with one node per grid location, so given
	the 32x32 cells, the graph has 1024 nodes. 

	To create a maze, we connect cell locations in the grid in such a way that a) there is a path from any
	grid location to any other grid location (i.e. there are no disconnected subsets of nodes in the graph),
	and b) there are loops.

	Since each node represents a grid location, each node can be connected to up to 4 neighbours in the
	top, right, bottom, and left directions respectively:

			node at (i,j-1)
				^
				|
	(node at i-1, j) <- node at (i,j) -> node at (i+1, j)
				|
				v
			node at (i,j+1)

	The graph is therefore stored as an adjacency list with size 1024 x 4, with one row per node in the
	graph, and 4 columns corresponding to the weight of an edge linking the node with each of its 4
	possible neighbours in the order towp, right, bottom, left (clockwise from top).

	Since all we care is whether nodes are connected. Weights will be either 0 or 1, if the weight is
	1, then the neighbouring nodes are connected, if the weight is 0, they are not. For example, if

	graph[i][0] = 0 
	graph[i][1] = 1
	graph[i][2] = 0
	graph[i][3] = 1

	then node i is connected to the right and left neighbours, but not to top or bottom.

	The index in the graph for the node corresponding to grid location (x,y) is

	index = x + (y*size_X) 		or in this case		index = x + (y*32)

	Conversely, if you have the index and want to figure out the grid location,

	x = index % size_X		or in this case		x = index % 32
	y = index / size_Y		or in this case		y = index / 32

	(all of the above are *integer* operations!)

	A path is a sequence of (x,y) grid locations. We store it using an array of size	
	1024 x 2 (since there are 1024 locations, this is the maximum length of any
	path that visits locations only once).

	Agent locations are coordinate pairs (x,y)	

   Arguments:
		gr[graph_size][4]   - This is an adjacency list for the maze
		path[graph_size][2] - An initially empty path for your code to fill.
				      In this case, empty means all entries are initially -1
		visit_order[size_X][size_Y]	- An array in which your code will store the
						  *order* in which grid locations were 
						  visited during search. For example, while
						  doing BFS, the initial location is the
						  start location, it's visit order is 1.
						  Then the search would expand the immediate
						  neighbours of the initial node in some order,
						  these would get a visit order of 2, 3, 4, and
						  5 respectively, and so on.
					
						  This array will be used to display the search
						  pattern generated by each search method.

		cat_loc[10][2], cats   - Location of cats and number of cats (we can have at most 10,
					 but there can be fewer). Only valid cat locations are 0 to (cats-1)
		cheese_loc[10][2], cheeses - Location and number of cheese chunks (again at most 10,
					     but possibly fewer). Valid locations are 0 to (cheeses-1)
		mouse_loc[1][2] - Mouse location - there can be only one!
		mode - Search mode selection:
					mode = 0 	- BFS
					mode = 1	- DFS
					mode = 2	- A*

		(*heuristic)(int x, int y, int cat_loc[10][2], int cheese_loc[10][2], int mouse_loc[10][2], int cats, int cheeses)
				- This is a pointer to one of the heuristic functions you will implement, either H_cost()
				  or H_cost_nokitty(). The driver in AI_search_core_GL will pass the appropriate pointer
				  depending on what search the user wants to run.
			
				  If the mode is 0 or 1, this pointer is NULL

				  * How to call the heuristic function from within this function : *
					- Like any other function:
						h = heuristic( x, y, cat_loc, cheese_loc, mouse_loc, cats, cheeses);

   Return values:
		Your search code will directly update data passed-in as arguments:

		- path[graph_size][2]	: Your search code will update this array to contain the path from
					  the mouse to one of the cheese chunks. The order matters, so
					  path[0][:] must be the mouse's current location, path[1][:]
					  is the next move for the mouse. Each successive row will contain
					  the next move toward the cheese, and the path ends at a location
					  whose coordinates correspond to one of the cheese chunks.
					  Any entries beyond that must remain set to -1
		- visit_order[size_X][size_Y] 	:  Your search code will update this array to contain the
						   order in which each location in the grid was expanded
						   during search. This means, when that particular location
						   was checked for being a goal, and if not a goal, had its
						   neighbours added as candidates for future expansion (in
						   whatever order is dictated by the search mode).

						   Note that since there are 1024 locations, the values in 
						   this array must always be in [0, 1023]. The driver code
						   will then display search order as a yellow-colored
						   brightness map where nodes expanded earlier will look
						   brighter.

		* Your code MUST NOT modify the locations or numbers of cats and/or cheeses, the graph,
	     	  or the location of the mouse - if you try, the driver code will know it *
			
		That's that, now, implement your solution!
 */

 /********************************************************************************************************
 * 
 * TO DO:	Implement code to carry out the different types of search depending on the
 *		mode.
 *
 *		You can do this by writing code within this single function (and being clever about it!)
 *		Or, you can use this function as a wrapper that calls a different search function
 *		 (BFS, DFS, A*) depending on the mode. Note that in the latter case, you will have
 *	    	  to inform your A* function somehow of what heuristic it's supposed to use.
 *
 *		Visiting Order: When adding the neighbours of a node to your list of candidates for
 *				expansion, do so in the order top, right, bottom, left.
 *
 *		NOTE: Your search functions should be smart enough to not choose a path that goes
 *		      through a cat! this is easily done without any heuristics.
 * 
 *		How you design your solution is up to you. But:
 *
 *		- Document your implementation by adding concise and clear comments in this file
 *		- Document your design (how you implemented the solution, and why) in the report
 *
 ********************************************************************************************************/

 // Stub so that the code compiles/runs - The code below will be removed and replaced by your code!


 //finished = 0 if no and 1 if yes
 int bfs_finished = 0;
 int dfs_finished = 0;
 int A_finished = 0;

 if (mode == 0){
	 int *expanded_bfs;
 	 expanded_bfs = (int*)calloc(graph_size, sizeof(int));
 	 int iteration = 1;

 	 struct node *visited_bfs;
 	 visited_bfs = (struct node*)calloc(graph_size, sizeof(struct node));
	 BFS(gr, path, visit_order, expanded_bfs, visited_bfs, mouse_loc, cheese_loc, cat_loc, iteration, bfs_finished);
 }
 else if (mode == 1){
	 int *expanded;
 	 expanded = (int*)calloc(graph_size, sizeof(int));
 	 int iteration = 1;

     struct node *visited;
     visited = (struct node*)calloc(graph_size, sizeof(struct node));
	 dfs_finished = DFS(gr, path, visit_order, expanded, mouse_loc, cheese_loc, cat_loc, iteration, dfs_finished);
}
 else if (mode == 2){
	 int *expanded;
 	 expanded = (int*)calloc(graph_size, sizeof(int));
 	 int iteration = 1;

 	 struct node *visited;
 	 visited = (struct node*)calloc(graph_size, sizeof(struct node));
	 A_star(gr, path, visit_order, expanded, visited, mouse_loc, cheese_loc, cat_loc, iteration, A_finished, cats, cheeses, heuristic);
 }
 else{
	 printf("That is not a valid option! Please choose either 1,2, or 3 for mode!");
 }

 return;
}


int H_cost(int x, int y, int cat_loc[10][2], int cheese_loc[10][2], int mouse_loc[1][2], int cats, int cheeses, double gr[graph_size][4])
{
 /*
	This function computes and returns the heuristic cost for location x,y.
	As discussed in lecture, this means estimating the cost of getting from x,y to the goal. 
	The goal is cheese. Which cheese is up to you.
	Whatever you code here, your heuristic must be admissible.

	Input arguments:

		x,y - Location for which this function will compute a heuristic search cost
		cat_loc - Cat locations
		cheese_loc - Cheese locations
		mouse_loc - Mouse location
		cats - # of cats
		cheeses - # of cheeses
		gr - The graph's adjacency list for the maze

		These arguments are as described in the search() function above
 */
 
 //hcost is the distance between the cheese and the mouse
 //mincost is the minimum cost out of all the cheeses
 int hcost = abs(cheese_loc[0][0]-mouse_loc[0][0]) + abs(cheese_loc[0][1]-mouse_loc[0][1]);
 int mincost = hcost;

 //for comparing mouse and cheese distances
 int mouse_cheesedistx = 0;
 int mouse_cheesedisty = 0;
 int n_cheesedistx = 0;
 int n_cheesedisty = 0;

 //for all the cheeses we find the minimum distance between our node and a local cheese
 for (int i = 0; i<cheeses; i++){
	mouse_cheesedistx = abs(cheese_loc[i][0]-mouse_loc[0][0]);
 	mouse_cheesedisty = abs(cheese_loc[i][1]-mouse_loc[0][1]);
 	n_cheesedistx = abs(cheese_loc[i][0]-x);
 	n_cheesedisty = abs(cheese_loc[i][1]-y);
	 //if moving to the neighbour makes the cheese closer than we lower the cost
	 if (n_cheesedistx < mouse_cheesedistx && n_cheesedisty < mouse_cheesedisty){
		hcost = abs(cheese_loc[i][0]-x) + abs(cheese_loc[i][1]-y);
	 }
	 //if this cost is better than min then we keep it
	 if(hcost < mincost){
		 mincost = hcost;
	 }
 }

 //return minimum cost found to bring mouse closer to closest cheese
 return(mincost);
}

struct catinfo{
	int threat = 0;
	int catindx;
	int xdist;
	int ydist;
};

int H_cost_nokitty(int x, int y, int cat_loc[10][2], int cheese_loc[10][2], int mouse_loc[1][2], int cats, int cheeses, double gr[graph_size][4])
{
 /*
	This function computes and returns the heuristic cost for location x,y.
	As discussed in lecture, this means estimating the cost of getting from x,y to the goal. 
	The goal is cheese. 

	However - this time you want your heuristic function to help the mouse avoid being eaten.
	Therefore: You have to somehow incorporate knowledge of the cats' locations into your
	heuristic cost estimate. How well you do this will determine how well your mouse behaves
	and how good it is at escaping kitties.

	This heuristic *does not have to* be admissible.

	Input arguments have the same meaning as in the H_cost() function above.
 */

 //hcost is the distance between the cheese and the given x and y value
 //mincheese is the minimum cost to get to a cheese out of all the cheeses
 int hcost = abs(cheese_loc[0][0]-x) + abs(cheese_loc[0][1]-y);
 int mincheese = hcost;

 //for comparing mouse and cheese distances
 int mouse_cheesedistx = 0;
 int mouse_cheesedisty = 0;
 int n_cheesedistx = 0;
 int n_cheesedisty = 0;

 //for all the cheeses we find the minimum distance between our node and a local cheese
 for (int i = 0; i<cheeses; i++){
	mouse_cheesedistx = abs(cheese_loc[i][0]-mouse_loc[0][0]);
 	mouse_cheesedisty = abs(cheese_loc[i][1]-mouse_loc[0][1]);
 	n_cheesedistx = abs(cheese_loc[i][0]-x);
 	n_cheesedisty = abs(cheese_loc[i][1]-y);
	 //if moving to the neighbour makes the cheese closer than we lower the cost
	 if (n_cheesedistx < mouse_cheesedistx && n_cheesedisty < mouse_cheesedisty){
		hcost = n_cheesedistx + n_cheesedisty;
	 }
	 //if this cost is better than min then we keep it
	 if(hcost < mincheese){
		 mincheese = hcost;
	 }
 }

 //checking for threat from kitten
 int maxkitty = mincheese;
 for (int i = 0; i<cats; i++){
	int catdist = abs(cat_loc[i][0]-x) + abs(cat_loc[i][1]-y);
	int mouse_catdistx = abs(mouse_loc[0][0]-cat_loc[i][0]);
	int mouse_catdisty = abs(mouse_loc[0][1]-cat_loc[i][1]);
	int xdist = abs(cat_loc[i][0]-x);
	int ydist = abs(cat_loc[i][1]-y);

	if(xdist < mouse_catdistx || ydist < mouse_catdisty){
		if(xdist < 5 && ydist < 5){
			hcost = mincheese + abs(20-(xdist*xdist)) + abs(20-(ydist*ydist));
		}
	}
	if (hcost > maxkitty){
		maxkitty = hcost;
	}
 } 
 return(maxkitty);		// <-- Evidently you will need to update this.
}

