/*
	CSC D84 - Unit 3 - Reinforcement Learning
	
	This file contains stubs for implementing the Q-Learning method
	for reinforcement learning as discussed in lecture. You have to
	complete two versions of Q-Learning.
	
	* Standard Q-Learning, based on a full-state representation and
	  a large Q-Table
	* Feature based Q-Learning to handle problems too big to allow
	  for a full-state representation
	    
	Read the assignment handout carefully, then implement the
	required functions below. Sections where you have to add code
	are marked

	**************
	*** TO DO:
	**************

	If you add any helper functions, make sure you document them
	properly and indicate in the report.txt file what you added.
	
	Have fun!

	DO NOT FORGET TO 'valgrind' YOUR CODE - We will check for pointer
	management being done properly, and for memory leaks.

	Starter code: F.J.E. Jan. 16
*/

#include "QLearn.h"

void QLearn_update(int s, int a, double r, int s_new, double *QTable)
{
 /*
   This function implementes the Q-Learning update as stated in Lecture. It 
   receives as input a <s,a,r,s'> tuple, and updates the Q-table accordingly.
   
   Your work here is to calculate the required update for the Q-table entry
   for state s, and apply it to the Q-table
     
   The update involves two constants, alpha and lambda, which are defined in QLearn.h - you should not 
   have to change their values. Use them as they are.
     
   Details on how states are used for indexing into the QTable are shown
   below, in the comments for QLearn_action. Be sure to read those as well!
 */
 
  /***********************************************************************************************
   * TO DO: Complete this function
   ***********************************************************************************************/

  
}

int QLearn_action(double gr[max_graph_size][4], int mouse_pos[1][2], int cats[5][2], int cheeses[5][2], double pct, double *QTable, int size_X, int graph_size)
{
  /*
     This function decides the action the mouse will take. It receives as inputs
     - The graph - so you can check for walls! The mouse must never move through walls
     - The mouse position
     - The cat position
     - The chees position
     - A 'pct' value in [0,1] indicating the amount of time the mouse uses the QTable to decide its action,
       for example, if pct=.25, then 25% of the time the mouse uses the QTable to choose its action,
       the remaining 75% of the time it chooses randomly among the available actions.
       
     Remember that the training process involves random exploration initially, but as training
     proceeds we use the QTable more and more, in order to improve our QTable values around promising
     actions.
     
     The value of pct is controlled by QLearn_core_GL, and increases with each round of training.
     
     This function *must return* an action index in [0,3] where
        0 - move up
        1 - move right
        2 - move down
        3 - move left
        
     QLearn_core_GL will print a warning if your action makes the mouse cross a wall, or if it makes
     the mouse leave the map - this should not happen. If you see a warning, fix the code in this
     function!
     
   The Q-table has been pre-allocated and initialized to 0. The Q-table has
   a size of
   
        graph_size^3 x 4
        
   This is because the table requires one entry for each possible state, and
   the state is comprised of the position of the mouse, cat, and cheese. 
   Since each of these agents can be in one of graph_size positions, all
   possible combinations yield graph_size^3 states.
   
   Now, for each state, the mouse has up to 4 possible moves (up, right,
   down, and left). We ignore here the fact that some moves are not possible
   from some states (due to walls) - it is up to the QLearn_action() function
   to make sure the mouse never crosses a wall. 
   
   So all in all, you have a big table.
        
   For example, on an 8x8 maze, the Q-table will have a size of
   
       64^3 x 4  entries
       
       with 
       
       size_X = 8		<--- size of one side of the maze
       graph_size = 64		<--- Total number of nodes in the graph
       
   Indexing within the Q-table works as follows:
   
     say the mouse is at   i,j
         the cat is at     k,l
         the cheese is at  m,n
         
     state = (i+(j*size_X)) + ((k+(l*size_X))*graph_size) + ((m+(n*size_X))*graph_size*graph_size)
     ** Make sure you undestand the state encoding above!
     
     Entries in the Q-table for this state are

     *(QTable+(4*state)+a)      <-- here a is the action in [0,3]
     
     (yes, it's a linear array, no shorcuts with brackets!)
     
     NOTE: There is only one cat and once cheese, so you only need to use cats[0][:] and cheeses[0][:]
   */
  
  /***********************************************************************************************
   * TO DO: Complete this function
   ***********************************************************************************************/  

  return(0);		// <--- of course, you will change this!
  
}

double QLearn_reward(double gr[max_graph_size][4], int mouse_pos[1][2], int cats[5][2], int cheeses[5][2], int size_X, int graph_size)
{
  /*
    This function computes and returns a reward for the state represented by the input mouse, cat, and
    cheese position. 
    
    You can make this function as simple or as complex as you like. But it should return positive values
    for states that are favorable to the mouse, and negative values for states that are bad for the 
    mouse.
    
    I am providing you with the graph, in case you want to do some processing on the maze in order to
    decide the reward. 
        
    This function should return a maximim/minimum reward when the mouse eats/gets eaten respectively.      
   */

   /***********************************************************************************************
   * TO DO: Complete this function
   ***********************************************************************************************/ 

  return(0);		// <--- of course, you will change this as well!     
}

void feat_QLearn_update(double gr[max_graph_size][4],double weights[25], double reward, int mouse_pos[1][2], int cats[5][2], int cheeses[5][2], int size_X, int graph_size)
{
  /*
    This function performs the Q-learning adjustment to all the weights associated with your
    features. Unlike standard Q-learning, you don't receive a <s,a,r,s'> tuple, instead,
    you receive the current state (mouse, cats, and cheese potisions), and the reward 
    associated with this action (this is called immediately after the mouse makes a move,
    so implicit in this is the mouse having selected some action)
    
    Your code must then evaluate the update and apply it to the weights in the weight array.    
   */
  
   /***********************************************************************************************
   * TO DO: Complete this function
   ***********************************************************************************************/        
      
}

int feat_QLearn_action(double gr[max_graph_size][4],double weights[25], int mouse_pos[1][2], int cats[5][2], int cheeses[5][2], double pct, int size_X, int graph_size)
{
  /*
    Similar to its counterpart for standard Q-learning, this function returns the index of the next
    action to be taken by the mouse.
    
    Once more, the 'pct' value controls the percent of time that the function chooses an optimal
    action given the current policy.
    
    E.g. if 'pct' is .15, then 15% of the time the function uses the current weights and chooses
    the optimal action. The remaining 85% of the time, a random action is chosen.
    
    As before, the mouse must never select an action that causes it to walk through walls or leave
    the maze.    
   */

  /***********************************************************************************************
   * TO DO: Complete this function
   ***********************************************************************************************/        

  return(0);		// <--- replace this while you're at it!

}

/***********************************************************************************************
 * Helper Functions for Feature Building
 ***********************************************************************************************/        

//This function returns the number of closed edges in direction of a specific location (cheese or cat)
int blocked(double gr[max_graph_size][4], int cx, int cy, int mouse_pos[1][2]){
	int blocked_edges = 0;
	int index = mouse_pos[0][0]+(mouse_pos[0][1]*32);
	int c_index = cx+(cy*32);

	int mx = mouse_pos[0][0];
	int my = mouse_pos[0][1];

	//if cat is lower than the mouse
	if (cy < my){
		if (cx = mx){//directly above (check if cat is blocked under and if mouse is blocked on top)
			if (gr[index][0] == (double)0 || gr[c_index][2] == (double)0){// if the top is blocked
				blocked_edges = blocked_edges+1;
			}
		}
		else if (cx < mx){//in the top left corner
			if (gr[index][0] == (double)0 || gr[c_index][2] == (double)0){// if the top is blocked
				blocked_edges = blocked_edges+1;
			}
			if (gr[index][3] == (double)0 || gr[c_index][1] == (double)0){//if the left is blocked
				blocked_edges = blocked_edges+1;
			}
		}
		else{// in the top right corner
			if (gr[index][0] == (double)0 || gr[c_index][2] == (double)0){// if the top is blocked
				blocked_edges = blocked_edges+1;
			}
			if (gr[index][1] == (double)0 || gr[c_index][3] == (double)0){//if the right is blocked
				blocked_edges = blocked_edges+1;
			}
		}
	}
	else if (cy > my){//if the cat is higher than the mouse
		if (cx = mx){//directly below
			if (gr[index][2] == (double)0 || gr[c_index][0] == (double)0){// if the bottom is blocked
				blocked_edges = blocked_edges+1;
			}
		}
		else if (cx < mx){//in the bottom left corner
			if (gr[index][2] == (double)0 || gr[c_index][0] == (double)0){// if the bottom is blocked
				blocked_edges = blocked_edges+1;
			}
			if (gr[index][3] == (double)0 || gr[c_index][1] == (double)0){//if the left is blocked
				blocked_edges = blocked_edges+1;
			}
		}
		else{// in the bottom right corner
			if (gr[index][2] == (double)0 || gr[c_index][0] == (double)0){// if the bottom is blocked
				blocked_edges = blocked_edges+1;
			}
			if (gr[index][1] == (double)0 || gr[c_index][3] == (double)0){//if the right is blocked
				blocked_edges = blocked_edges+1;
			}
		}
	}
	else{//cy = my so they are on the same field on the y axis
		if (cx < mx){//on the left of the mouse
			if (gr[index][3] == (double)0 || gr[c_index][1] == (double)0){//if the left is blocked
				blocked_edges = blocked_edges+1;
			}
		}
		else{//on the right of the mouse
			if (gr[index][1] == (double)0 || gr[c_index][3] == (double)0){//if the right is blocked
				blocked_edges = blocked_edges+1;
			}
		}

	}
	return blocked_edges;
}

//This function returns the number of open edges
int open_edges(double gr[max_graph_size][4], int loc[1][2]){
	int open_edge_count = 0;
	int index = loc[0][0]+(loc[0][1]*32);
	for(int i=0; i<4; i++){
		 //check if the neighbour is a valid place to move
		if(gr[index][i]==(double)1 && index>0){
			//Finding which neighbour we are on
			//TOP
			if(i==0 && ((index/32)-1) >= 0 && ((index/32)-1) < 32){
				open_edge_count = open_edge_count+1;
			}//RIGHT
			else if (i==1 && ((index%32)+1) >= 0 && ((index%32)+1) < 32){
				open_edge_count = open_edge_count+1;
			}//BOTTOM
			else if (i==2 && ((index/32)+1) >= 0 && ((index/32)+1) < 32){ 
				open_edge_count = open_edge_count+1;
			}//LEFT
			else if (i==3 && ((index%32)-1) >= 0 && ((index%32)-1) < 32){
				open_edge_count = open_edge_count+1;
			}
		}
	}
	return open_edge_count;
}

//Returns the longest amount of spaces you can travel in one direction from mouse starting point
int longest_tunnel(double gr[max_graph_size][4], int mouse_pos[1][2]){
  //Setting variables
  int curr_index = mouse_pos[0][0]+(mouse_pos[0][1]*32);
  int count[4];

  int new_x = mouse_pos[0][0];
  int new_y = mouse_pos[0][1];

  //Going in each direction
  for(int i=0; i<4; i++){
    //reset values for next direction
    curr_index = mouse_pos[0][0]+(mouse_pos[0][1]*32);
    new_x = mouse_pos[0][0];
    new_y = mouse_pos[0][1];

    //while moving in that direction is valid
    while(gr[curr_index][i]==(double)1 && curr_index>0){
      //add to count for that direction
      count[i] = count[i]+1;
      if(i==0){ //Top Direction
        new_x = curr_index%32;
        new_y = (curr_index/32)-1;
      }
      else if(i==1){//Right Direction
        new_x = (curr_index%32)+1;
        new_y = curr_index/32;
      }
      else if(i==2){//Bottom Direction
        new_x = curr_index%32;
        new_y = (curr_index/32)+1;
      }
      else{//Left Direction
        new_x = (curr_index%32)-1;
      new_y = curr_index/32;
      }
      //update index
      curr_index = new_x + new_y*32;
    }
  }

  //Get max tunnel value
  int max = 0;
  for(int i = 0; i<4; i++)
  {
    if (count[i]>max){
      max = count[i];
    }
  }
  return max;
}


//Returns the minimum value of 2 options
int min_val(int option1, int option2){
  if (option1<option2){
    return option1;
  }
  return option2;
}


void evaluateFeatures(double gr[max_graph_size][4],double features[25], int mouse_pos[1][2], int cats[5][2], int cheeses[5][2], int size_X, int graph_size)
{
  /*
   This function evaluates all the features you defined for the game configuration given by the input
   mouse, cats, and cheese positions. You are free to define up to 25 features. This function will
   evaluate each, and return all the feature values in the features[] array.
   
   Take some time to think about what features would be useful to have, the better your features, the
   smarter your mouse!
   
   Note that instead of passing down the number of cats and the number of cheese chunks (too many parms!)
   the arrays themselves will tell you what are valid cat/cheese locations.
   
   You can have up to 5 cats and up to 5 cheese chunks, and array entries for the remaining cats/cheese
   will have a value of -1 - check this when evaluating your features!
  */

   /******************************************
   * CHEESE RELATED FEATURES
   ******************************************/      

  //Feature 1: Distance to all cheeses
  //Feature 2: Closest cheese distance
 
  int total_cheese_dist = 0;
  int closest_cheese = graph_size;
  int min_cheese[2];
	for (int i = 0; i < 5; i++)
	{
		int cur_dist = abs(cheeses[i][0] - mouse_pos[0][0]) + abs(cheeses[i][1] - mouse_pos[0][1]);
    total_cheese_dist = total_cheese_dist+cur_dist;
		if (cur_dist < closest_cheese)
		{
			closest_cheese = cur_dist;
      min_cheese[0] = cheeses[i][0];
			min_cheese[1] = cheeses[i][1];
		}
	}
  features[0] = total_cheese_dist;
  features[1] = closest_cheese; 
  
  //Feature 3: Num Blocked Edges to Closest Cheese
  int blocked_min_cheese = blocked(gr, min_cheese[0], min_cheese[1], mouse_pos);
  features[2] = blocked_min_cheese;

  /******************************************
   * CAT RELATED FEATURES
   ******************************************/ 

  //Feature 4: Distance to all cats
  //Feature 5: Closest cat distance
  int total_cat_dist = 0;
  int closest_cat = graph_size;
  int min_cat[2];
  for (int i = 0; i < 5; i++)
	{
		int cur_dist = abs(cats[i][0] - mouse_pos[0][0]) + abs(cats[i][1] - mouse_pos[0][1]);
    total_cat_dist = total_cat_dist+cur_dist;
		if (cur_dist < closest_cat)
		{
			closest_cat = cur_dist;
      min_cat[0] = cheeses[i][0];
			min_cat[1] = cheeses[i][1];
		}
	}

  features[3] = total_cat_dist;
  features[4] = closest_cat;

  //Feature 6: Num Blocked Edges to Closest Cat
  int blocked_min_cat = blocked(gr, min_cat[0], min_cat[1], mouse_pos);
  features[5] = blocked_min_cheese;

  /******************************************
   * MAZE RELATED FEATURES
   ******************************************/ 

  //Feature 7: Dead ends
  int open_edge_count = open_edges(gr, mouse_pos);
  features[6] = open_edge_count;

  //Feature 8: Longest Tunnel Passage
  int max_tunnel = longest_tunnel(gr, mouse_pos);
  features[7] = max_tunnel;

  //Feature 9: Proximity to edge of graph
  //get minimum x distance and minimum y distance
  int min_x = min_val(abs(32 - mouse_pos[0][0]), abs(0 - mouse_pos[0][0]));
  int min_y = min_val(abs(32 - mouse_pos[0][1]), abs(0 - mouse_pos[0][1]));
  int border_proximity = min_x + min_y;
  features[8] = border_proximity;
}

double Qsa(double weights[25], double features[25])
{
  /*
    Compute and return the Qsa value given the input features and current weights
   */

  /***********************************************************************************************
  * TO DO: Complete this function
  ***********************************************************************************************/  
  
  return(0);		// <--- stub! compute and return the Qsa value
}

void maxQsa(double gr[max_graph_size][4],double weights[25],int mouse_pos[1][2], int cats[5][2], int cheeses[5][2], int size_X, int graph_size, double *maxU, int *maxA)
{
 /*
   Given the state represented by the input positions for mouse, cats, and cheese, this function evaluates
   the Q-value at all possible neighbour states and returns the max. The maximum value is returned in maxU
   and the index of the action corresponding to this value is returned in maxA.
   
   You should make sure the function does not evaluate moves that would make the mouse walk through a
   wall. 
  */
 
   /***********************************************************************************************
   * TO DO: Complete this function
   ***********************************************************************************************/  
 
  *maxU=0;	// <--- stubs! your code will compute actual values for these two variables!
  *maxA=0;
  return;
   
}

/***************************************************************************************************
 *  Add any functions needed to compute your features below 
 *                 ---->  THIS BOX <-----
 * *************************************************************************************************/
