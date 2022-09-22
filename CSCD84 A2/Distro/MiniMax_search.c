/*
	CSC D84 - Unit 2 - MiniMax search and adversarial games

	This file contains stubs for implementing a MiniMax search
        procedure with alpha-beta pruning. Please read the assignment
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

	Starter code: F.J.E. Sep. 15
*/

#include "MiniMax_search.h"

int maxIdx(double childCosts[4]){
	double max = -1000;
	int maxidx = 0;
	for(int i = 0; i<4; i++){
		if (childCosts[i]>max && childCosts[i]!=-10000){
			max = childCosts[i];
			maxidx = i;
		}
	}
	return maxidx;
}

int minIdx(double childCosts[4]){
	double min = 1000;
	int minidx = 0;
	for(int i = 0; i<4; i++){
		if (childCosts[i]<min && childCosts[i]!=-10000){
			min = childCosts[i];
			minidx = i;
		}
	}
	return minidx;
}

double MiniMax(double gr[graph_size][4], int path[1][2], double minmax_cost[size_X][size_Y], int cat_loc[10][2], int cats, int cheese_loc[10][2], int cheeses, int mouse_loc[1][2], int mode, double (*utility)(int cat_loc[10][2], int cheese_loc[10][2], int mouse_loc[1][2], int cats, int cheeses, int depth, double gr[graph_size][4]), int agentId, int depth, int maxDepth, double alpha, double beta)
{
 /*
   This function is the interface between your solution for the assignment and the driver code. The driver code
   in MiniMax_search_core_GL will call this function once per frame, and provide the following data
   
   Board and game layout:

	Exactly the same as for Assignment 1 - have a look at your code if you need a reminder of how the adjacency
	list and agent positions are stored.	

	Note that in this case, the path will contain a single move - at the top level, this function will provide
	an agent with the 'optimal' mini-max move given the game state.


   IMPORTANT NOTE: Mini-max is a recursive procedure. This function will need to fill-in the mini-max values for 
	 	   all game states down to the maximum search depth specified by the user. In order to do that,
		   the function needs to be called with the correct state at each specific node in the mini-max
		   search tree.

		   The game state is composed of:

			* Mouse, cat, and cheese positions (and number of cats and cheeses)
			
		   At the top level (when this function is called by the mini-max driver code), the game state
		   correspond to the current situation of the game. But once you start recursively calling
		   this function for lower levels of the search tree the positions of agents will have changed.
		   
		   Therefore, you will need to define local variables to keep the game state at each node of the
		   mini-max search tree, and you will need to update this state when calling recursively so that
		   the search does the right thing.

		   This function *must check* whether:
			* A candidate move results in a terminal configuration (cat eats mouse, mouse eats cheese)
			  at which point it calls the utility function to get a value
	 		* Maximum search depth has been reached (depth==maxDepth), at which point it will also call
			  the utility function to get a value
			* Otherwise, call recursively using the candidate configuration to find out what happens
			  deeper into the mini-max tree.

   Arguments:
		gr[graph_size][4]   		- This is an adjacency list for the maze
		path[1][2] 			- Your function will return the optimal mini-max move in this array.
		minmax_cost[size_X][size_Y]	- An array in which your code will store the
						  minimax value for maze locations expanded by
						  the search *when called for the mouse, not
						  for the cats!*

						  This array will be used to provide a visual 
						  display of minimax values during the game.

		cat_loc[10][2], cats   - Location of cats and number of cats (we can have at most 10,
					 but there can be fewer). Only valid cat locations are 0 to (cats-1)
		cheese_loc[10][2], cheeses - Location and number of cheese chunks (again at most 10,
					     but possibly fewer). Valid locations are 0 to (cheeses-1)
		mouse_loc[1][2] - Mouse location - there can be only one!
		mode - Search mode selection:
					mode = 0 	- No alpha-beta pruning
					mode = 1	- Alpha-beta pruning

		(*utility)(int cat_loc[10][2], int cheese_loc[10][2], int mouse_loc[1][2], int cats, int cheeses, int depth, double gr[graph_size][4]);
				- This is a pointer to the utility function which returns a value for a specific game configuration

				   NOTE: Unlike the search assignment, this utility function also gets access to the graph so you can do any processing 					 that requires knowledge of the maze for computing the utility values.

				  * How to call the utility function from within this function : *
					- Like any other function:
						u = utility(cat_loc, cheese_loc, mouse_loc, cats, cheeses, depth, gr);
						
		agentId: Identifies which agent we are doing MiniMax for. agentId=0 for the mouse, agentId in [1, cats] for cats. Notice that recursive calls
                         to this function should increase the agentId to reflect the fact that the next level down corresponds to the next agent! For a game
                         with two cats and a mouse, the agentIds for the recursion should look like 0, 1, 2, 0, 1, 2, ...
	
		depth: Current search depth - whether this is a MIN or a MAX node depends both on depth and agentId.
		
		maxDepth: maximum desired search depth - once reached, your code should somehow return
			  a minimax utility value for this location.

		alpha. beta: alpha and beta values passed from the parent node to constrain search at this
			     level.

   Return values:
		Your search code will directly update data passed-in as arguments:
		
		- Mini-Max value	: Notice this function returns a double precision number. This is
					  the minimax value at this level of the tree. It will be used 
					  as the recursion backtracks filling-in the mini-max values back
					  from the leaves to the root of the search tree. 

		- path[1][2]		: Your MiniMax function will return the location for the agent's 
					  next location (i.e. the optimal move for the agent). 
		- minmax_cost[size_X][size_Y] 	:  Your search code will update this array to contain the
						   minimax value for locations that were expanded during
						   the search. This must be done *only* for the mouse.

						   Values in this array will be in the range returned by
						   your utility function.

		* Your code MUST NOT modify the locations or numbers of cats and/or cheeses, the graph,
	     	  or the location of the mouse - if you try, the driver code will know it *
			
		That's that, now, implement your solution!
 */

 /********************************************************************************************************
 * 
 * TO DO:	Implement code to perform a MiniMax search. This will involve a limited-depth BFS-like
 *              expansion. Once nodes below return values, your function will propagate minimax utilities
 *		as per the minimax algorithm.
 *	
 *		Note that if alpha-beta pruning is specified, you must keep track of alphas and betas
 *		along the path.
 *
 *		You can use helper functions if it seems reasonable. Add them to the MiniMax_search.h
 *		file and explain in your code why they are needed and how they are used.
 *
 *		Recursion should appear somewhere.
 *
 *		MiniMax cost: If the agentId=0 (Mouse), then once you have a MiniMax value for a location
 *		in the maze, you must update minmax_cost[][] for that location.
 *
 *		How you design your solution is up to you. But:
 *
 *		- Document your implementation by adding concise and clear comments in this file
 *		- Document your design (how you implemented the solution, and why) in the report
 *
 ********************************************************************************************************/
 //First attain the index of our current location
 int index = mouse_loc[0][0]+(mouse_loc[0][1]*32);
 if(agentId!=0){
	index = cat_loc[agentId-1][0]+(cat_loc[agentId-1][1]*32);
 }

 //Set up holders for child node information 
 //("children" are valid unvisited neighbours of current location)
 double childCosts[4]; //has the node values for each child
 for(int i = 0; i<4; i++){
	childCosts[i] = -10000;
 }
 int child_loc[4][2]; // has the x and y values for each child 

 //printf("\nMOUSE LOC x: %d, y: %d", mouse_loc[0][0], mouse_loc[0][1]);
 //printf("\nThis is our index: %d and our depth: %d with agent ID %d", index, depth, agentId);

 //check if we are dealing with a terminal node or if depth is at it's max
 if (checkForTerminal(mouse_loc, cat_loc, cheese_loc, cats, cheeses) == 1 || depth == maxDepth){
	double util = utility(cat_loc, cheese_loc, mouse_loc, cats, cheeses, depth, gr);
	minmax_cost[mouse_loc[0][0]][mouse_loc[0][1]] = util;

	//If ALPHA BETA PRUNING 
	if(mode == 1){
		// if it's a mouse (max node)
		if(agentId == 0){
			if (util > alpha){
				//update alpha
				alpha = util;
			}
			if (alpha >= beta){
				return alpha;
			}
		}
		else{// if it's a cat (min node)
			if (util < beta){
				//update beta
				beta = util;
			}
			if (beta <= alpha){
				return beta;
			}
		}
	}
	return util;
 }
//otherwise we continue the recursion
 else{
	 //for each neighbour of our current mouse location
	 for(int i=0; i<4; i++){
		 //check if the neighbour is a valid place to move
		if(gr[index][i]==(double)1 && index>0){
			//set current child node
			int curr_child[1][2];

			//Finding which neighbour we are on
			//TOP
			if(i==0 && ((index/32)-1) >= 0 && ((index/32)-1) < 32){
				child_loc[i][0] = index%32;
				child_loc[i][1] = (index/32)-1;
			}//RIGHT
			else if (i==1 && ((index%32)+1) >= 0 && ((index%32)+1) < 32){
				child_loc[i][0] = (index%32)+1;
				child_loc[i][1] = index/32;
			}//BOTTOM
			else if (i==2 && ((index/32)+1) >= 0 && ((index/32)+1) < 32){ 
				child_loc[i][0] = index%32;
				child_loc[i][1] = (index/32)+1;
			}//LEFT
			else if (i==3 && ((index%32)-1) >= 0 && ((index%32)-1) < 32){
				child_loc[i][0] = (index%32)-1;
				child_loc[i][1] = index/32;
			}

			//Set current child's x and y as well as index
			curr_child[0][0] = child_loc[i][0];
			curr_child[0][1] = child_loc[i][1];
			
			// if our current agent is a mouse
			if(agentId == 0){
				//next move would be a cat so we pass agentId+1 and the mouses new location
				childCosts[i] = MiniMax(gr, path, minmax_cost, cat_loc, cats, cheese_loc, cheeses, curr_child, mode, utility, agentId+1, depth+1, maxDepth, alpha, beta);
 			}// if our current move is a cat and there are multiple cats
			else if (agentId < cats && agentId > 0){
				//we continue passing the cats down 
				//use a temp holder for the cats next possible move
				int temp_cat_loc[cats][2];
				//fill with old cat locations
				for(int j = 0; j<cats; j++){
					temp_cat_loc[j][0] = cat_loc[j][0];
					temp_cat_loc[j][1] = cat_loc[j][1];
				}
				temp_cat_loc[agentId-1][0] = child_loc[i][0];
				temp_cat_loc[agentId-1][1] = child_loc[i][1];
				childCosts[i] = MiniMax(gr, path, minmax_cost, temp_cat_loc, cats, cheese_loc, cheeses, mouse_loc, mode, utility, agentId+1, depth+1, maxDepth, alpha, beta);
			}// if we are on our "last cat" then we pass the next move to a mouse
			else{
				//use a temp holder for the cats next possible move
				int temp_cat_loc[cats][2];
				//fill with old cat locations
				for(int j = 0; j<cats; j++){
					temp_cat_loc[j][0] = cat_loc[j][0];
					temp_cat_loc[j][1] = cat_loc[j][1];
				}
				temp_cat_loc[agentId-1][0] = child_loc[i][0];
				temp_cat_loc[agentId-1][1] = child_loc[i][1];
				childCosts[i] = MiniMax(gr, path, minmax_cost, temp_cat_loc, cats, cheese_loc, cheeses, mouse_loc, mode, utility, 0, depth+1, maxDepth, alpha, beta);
			}

		}
	}
 }
	
	//if its a max node (mouse node)
	if(agentId == 0){
		//get index of max value and use it to determine next steps
		int max = maxIdx(childCosts);
		double node_cost = childCosts[max];
		path[0][0] = child_loc[max][0];
		path[0][1] = child_loc[max][1];
		//set minmax_cost to be our found max
		minmax_cost[mouse_loc[0][0]][mouse_loc[0][1]] = node_cost;

		//If ALPHA BETA PRUNING 
		if(mode == 1){
			if (node_cost > alpha){
				//update alpha
				alpha = node_cost;
			}
			if (alpha >= beta){
				printf("ALPHA: %f", alpha);
				return alpha;
			}
		}
		return node_cost;
	} // otherwise if its a min node (cat node)
	int min = minIdx(childCosts);
	double node_cost = childCosts[min];
	path[0][0] = child_loc[min][0];
	path[0][1] = child_loc[min][1];

	//If ALPHA BETA PRUNING 
	if(mode == 1){
		if (node_cost < beta){
			//update beta
			beta = node_cost;
		}
		if (beta <= alpha){
			printf("UPDATE");
			return beta;
		}
	}
	return node_cost;
}

//This function returns the number of open edges
int openEdges(double gr[graph_size][4], int loc[1][2]){
	int openEdgeCount = 0;
	int index = loc[0][0]+(loc[0][1]*32);
	for(int i=0; i<4; i++){
		 //check if the neighbour is a valid place to move
		if(gr[index][i]==(double)1 && index>0){
			//Finding which neighbour we are on
			//TOP
			if(i==0 && ((index/32)-1) >= 0 && ((index/32)-1) < 32){
				openEdgeCount = openEdgeCount+1;
			}//RIGHT
			else if (i==1 && ((index%32)+1) >= 0 && ((index%32)+1) < 32){
				openEdgeCount = openEdgeCount+1;
			}//BOTTOM
			else if (i==2 && ((index/32)+1) >= 0 && ((index/32)+1) < 32){ 
				openEdgeCount = openEdgeCount+1;
			}//LEFT
			else if (i==3 && ((index%32)-1) >= 0 && ((index%32)-1) < 32){
				openEdgeCount = openEdgeCount+1;
			}
		}
	}
	return openEdgeCount;
}

//This function returns the number of closed edges in direction of a specific location (cheese or cat)
int blocked(double gr[graph_size][4], int cx, int cy, int mouse_loc[1][2]){
	int blockedEdges = 0;
	int index = mouse_loc[0][0]+(mouse_loc[0][1]*32);
	int c_index = cx+(cy*32);

	int mx = mouse_loc[0][0];
	int my = mouse_loc[0][1];

	//if cat is lower than the mouse
	if (cy < my){
		if (cx = mx){//directly above (check if cat is blocked under and if mouse is blocked on top)
			if (gr[index][0] == (double)0 || gr[c_index][2] == (double)0){// if the top is blocked
				blockedEdges = blockedEdges+1;
			}
		}
		else if (cx < mx){//in the top left corner
			if (gr[index][0] == (double)0 || gr[c_index][2] == (double)0){// if the top is blocked
				blockedEdges = blockedEdges+1;
			}
			if (gr[index][3] == (double)0 || gr[c_index][1] == (double)0){//if the left is blocked
				blockedEdges = blockedEdges+1;
			}
		}
		else{// in the top right corner
			if (gr[index][0] == (double)0 || gr[c_index][2] == (double)0){// if the top is blocked
				blockedEdges = blockedEdges+1;
			}
			if (gr[index][1] == (double)0 || gr[c_index][3] == (double)0){//if the right is blocked
				blockedEdges = blockedEdges+1;
			}
		}
	}
	else if (cy > my){//if the cat is higher than the mouse
		if (cx = mx){//directly below
			if (gr[index][2] == (double)0 || gr[c_index][0] == (double)0){// if the bottom is blocked
				blockedEdges = blockedEdges+1;
			}
		}
		else if (cx < mx){//in the bottom left corner
			if (gr[index][2] == (double)0 || gr[c_index][0] == (double)0){// if the bottom is blocked
				blockedEdges = blockedEdges+1;
			}
			if (gr[index][3] == (double)0 || gr[c_index][1] == (double)0){//if the left is blocked
				blockedEdges = blockedEdges+1;
			}
		}
		else{// in the bottom right corner
			if (gr[index][2] == (double)0 || gr[c_index][0] == (double)0){// if the bottom is blocked
				blockedEdges = blockedEdges+1;
			}
			if (gr[index][1] == (double)0 || gr[c_index][3] == (double)0){//if the right is blocked
				blockedEdges = blockedEdges+1;
			}
		}
	}
	else{//cy = my so they are on the same field on the y axis
		if (cx < mx){//on the left of the mouse
			if (gr[index][3] == (double)0 || gr[c_index][1] == (double)0){//if the left is blocked
				blockedEdges = blockedEdges+1;
			}
		}
		else{//on the right of the mouse
			if (gr[index][1] == (double)0 || gr[c_index][3] == (double)0){//if the right is blocked
				blockedEdges = blockedEdges+1;
			}
		}

	}
	return blockedEdges;
}

double utility(int cat_loc[10][2], int cheese_loc[10][2], int mouse_loc[1][2], int cats, int cheeses, int depth, double gr[graph_size][4])
{
 /*
	This function computes and returns the utility value for a given game configuration.
	As discussed in lecture, this should return a positive value for configurations that are 'good'
	for the mouse, and a negative value for locations that are 'bad' for the mouse.

	Arguments for utility function:
	Things to be minimized in the function
	1) total_chm: This is the total distance between the mouse and all cheeses
	2) min_cheese: The minimum distance between a cheese and the mouse
	3) min_cheese_blocked: if there is a direct block between the cheese and the mouse 
		(goal is to favor unblocked cheese rather than blocked)

	Things to be maximized in the function
	1) total_ctm: The total distance between the mouse and all cats
	2) min_cat: The minimum distance between a cat and the mouse (this is most important bc we want the mouse to focus on this as a threat)
	3) min_cat_blocked: if there is a direct block between a cat and the mouse
		(goal is to use this to allow the mouse to take advantage of the blocking)

	Dead end detection:
	open_edge_count: the number of open edges in any given position
		(positions with 1 open edge should be considered a dead end and should be avoided unless there is a cheese there)
 */
	double min_cheese = 1024;
	int min_cheese_blocked = 0;
	double total_chm = 0;
	int emphasis = 0;


	//getting total distances of cheeses and the distance of the closest cheese
	double cheese_mouse[cheeses];
	for (int i = 0; i<cheeses; i++){
		cheese_mouse[i] = abs(cheese_loc[i][0]-mouse_loc[0][0]) + abs(cheese_loc[i][1]-mouse_loc[0][1]);
		total_chm = total_chm+cheese_mouse[i];
		if (cheese_mouse[i]<min_cheese){
			min_cheese = cheese_mouse[i];
			min_cheese_blocked = blocked(gr, cheese_loc[i][0], cheese_loc[i][1], mouse_loc);
		}
	}


	double min_cat = 1024;
	int min_cat_blocked = 0;
	double total_ctm = 0;

	//getting total distances of cats and the distance of the closest cat
	double cat_mouse[cats];
	for (int i = 0; i<cats; i++){
		cat_mouse[i] = abs(cat_loc[i][0]-mouse_loc[0][0]) + abs(cat_loc[i][1]-mouse_loc[0][1]);
		total_ctm = total_ctm+cat_mouse[i];
		if (cat_mouse[i]<min_cat){
			min_cat = cat_mouse[i];
			min_cat_blocked = blocked(gr, cat_loc[i][0], cat_loc[i][1], mouse_loc);
		}
	}

	int open_edge_count = openEdges(gr, mouse_loc);

	return (total_ctm + 5*min_cat + 3*min_cat_blocked) - (total_chm + 5*min_cheese + 3*min_cheese_blocked) - 4*(4-open_edge_count);
}

int checkForTerminal(int mouse_loc[1][2],int cat_loc[10][2],int cheese_loc[10][2],int cats,int cheeses)
{
 /* 
   This function determines whether a given configuration constitutes a terminal node.
   Terminal nodes are those for which:
     - A cat eats the mouse
     or
     - The mouse eats a cheese
   
   If the node is a terminal, the function returns 1, else it returns 0
 */

 // Check for cats having lunch
 for (int i=0; i<cats; i++)
  if (mouse_loc[0][0]==cat_loc[i][0]&&mouse_loc[0][1]==cat_loc[i][1]) return(1);

 // Check for mouse having lunch
 for (int i=0; i<cheeses; i++)
  if (mouse_loc[0][0]==cheese_loc[i][0]&&mouse_loc[0][1]==cheese_loc[i][1]) return(1);

 return(0);

}

