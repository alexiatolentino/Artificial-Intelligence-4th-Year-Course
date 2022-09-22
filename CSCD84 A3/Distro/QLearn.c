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

// Debugging
#define DEBUG 0
#define debug_print(fmt, ...)                             \
    do                                                    \
    {                                                     \
        if (DEBUG)                                        \
            fprintf(stderr, "%s:%d:%s(): " fmt, __FILE__, \
                    __LINE__, __func__, __VA_ARGS__);     \
    } while (0)

// # of Features
#define NUM_FEATURES 8

#include "QLearn.h"
#include <limits.h>
#include <time.h>
#include <float.h>

/***********************************************************************************************
 * QLEARN FUNCTIONS
 ***********************************************************************************************/        

void QLearn_update(int s, int a, double r, int s_new, double *QTable)
{
    /*
      This function implements the Q-Learning update as stated in Lecture. It
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
    // Q(s, a) += alpha[r + lambda(max_a Q(s', a')) - Q(s, a)]
    double cur_QSA = get_QTable_entry(QTable, s, a);
    double max_QSA_SNew = INT_MIN;
    int i = 0;
    for (i = 0; i < 4; i++)
    {
        if (max_QSA_SNew < get_QTable_entry(QTable, s_new, i))
        {
            max_QSA_SNew = get_QTable_entry(QTable, s_new, i);
        }
    }
    double new_QSA = cur_QSA + alpha * (r + lambda * (max_QSA_SNew)-cur_QSA);
    set_QTable_entry(QTable, s, a, new_QSA);
}

int QLearn_action(double gr[max_graph_size][4], int mouse_pos[1][2], int cats[5][2], int cheeses[5][2], double pct, double *QTable, int size_X, int graph_size)
{
    /*
       This function decides the action the mouse will take. It receives as inputs
       - The graph - so you can check for walls! The mouse must never move through walls
       - The mouse position
       - The cat position
       - The cheese position
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
       ** Make sure you understand the state encoding above!

       Entries in the Q-table for this state are

       *(QTable+(4*state)+a)      <-- here a is the action in [0,3]

       (yes, it's a linear array, no shortcuts with brackets!)

       NOTE: There is only one cat and one cheese, so you only need to use cats[0][:] and cheeses[0][:]
     */

    /***********************************************************************************************
     * TO DO: Complete this function
     ***********************************************************************************************/
    // Initialize state
    int s = get_state(mouse_pos, cats, cheeses, size_X, graph_size);
    // Pick random number c in [0,1]
    srand(time(NULL));
	//srand(101);
    double c = (double)rand() / (double)RAND_MAX;
    int a; // a in [0, 3]
    if (c <= pct)
    {
        a = QLearn_policy(s, mouse_pos, gr, QTable, size_X);
    }
    else
    {
        a = get_random_action(mouse_pos, gr, size_X);
    }
    return a;
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

      This function should return a maximum/minimum reward when the mouse eats/gets eaten respectively.
     */

    /***********************************************************************************************
     * TO DO: Complete this function
     ***********************************************************************************************/
    // Mouse eats cheese
    if (mouse_pos[0][0] == cheeses[0][0] && mouse_pos[0][1] == cheeses[0][1])
        return (10);

    // Cat eats mouse
    if (mouse_pos[0][0] == cats[0][0] && mouse_pos[0][1] == cats[0][1])
        return (-10);

    return (0);
}

/***********************************************************************************************
 * FEAT QLEARN FUNCTIONS
 ***********************************************************************************************/        

void feat_QLearn_update(double gr[max_graph_size][4], double weights[25], double reward, int mouse_pos[1][2], int cats[5][2], int cheeses[5][2], int size_X, int graph_size)
{
    /*
      This function performs the Q-learning adjustment to all the weights associated with your
      features. Unlike standard Q-learning, you don't receive a <s,a,r,s'> tuple, instead,
      you receive the current state (mouse, cats, and cheese positions), and the reward
      associated with this action (this is called immediately after the mouse makes a move,
      so implicit in this is the mouse having selected some action)

      Your code must then evaluate the update and apply it to the weights in the weight array.
     */

    /***********************************************************************************************
     * TO DO: Complete this function
     ***********************************************************************************************/

    // w_i += alpha[r + lambda(Q(s')) - Q(s)]*f_i(s)
    double features[NUM_FEATURES];
    evaluateFeatures(gr, features, mouse_pos, cats, cheeses, size_X, graph_size);
    double cur_QSA = Qsa(weights, features);

    double max_QSA;
    int maxA; // unused
    maxQsa(gr, weights, mouse_pos, cats, cheeses, size_X, graph_size, &max_QSA, &maxA);

    int i = 0;
    for (i = 0; i < NUM_FEATURES; i++)
    {
        weights[i] += alpha * (reward + lambda * (max_QSA)-cur_QSA) * features[i];
        //checking for blowing up:
        if (weights[i] > INT_MAX || weights[i] < INT_MIN){
          
            // Pick random reset_val in [-1,1]
            srand(time(NULL));
		    //srand(101);
            double reset_val = rand_init_weight((double)-1, (double)1);
            weights[i] = reset_val;
        }
    }
}

int feat_QLearn_action(double gr[max_graph_size][4], double weights[25], int mouse_pos[1][2], int cats[5][2], int cheeses[5][2], double pct, int size_X, int graph_size)
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

    // Pick random number c in [0,1]
    srand(time(NULL));
	//srand(101);
    double c = (double)rand() / (double)RAND_MAX;
    int a; // a in [0, 3]
    if (c <= pct)
    {
        double maxU; // unused
        maxQsa(gr, weights, mouse_pos, cats, cheeses, size_X, graph_size, &maxU, &a);
    }
    else
    {
        a = get_random_action(mouse_pos, gr, size_X);
    }
    return a;
}

void evaluateFeatures(double gr[max_graph_size][4], double features[25], int mouse_pos[1][2], int cats[5][2], int cheeses[5][2], int size_X, int graph_size)
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

   int num_cheese = 0;
   int num_cats = 0;

   for(int i = 0; i < 5; i++){
	   if (cats[i][0] != -1 && cats[i][0] != -1){
		   num_cats++;
	   }
	   if (cheeses[i][0] != -1 && cheeses[i][0] != -1){
		   num_cheese++;
	   }
   }

	/******************************************
	 * CHEESE RELATED FEATURES
	 ******************************************/      

	//Feature 1: Distance to all cheeses
	//Feature 2: Closest cheese distance
	
	double total_cheese_dist = 0;
	double closest_cheese = graph_size;
	int min_cheese[2];
		for (int i = 0; i < num_cheese; i++)
		{
			double cur_dist = abs(cheeses[i][0] - mouse_pos[0][0]) + abs(cheeses[i][1] - mouse_pos[0][1]);
			total_cheese_dist = total_cheese_dist+cur_dist;
			if (cur_dist < closest_cheese)
			{
				closest_cheese = cur_dist;
				min_cheese[0] = cheeses[i][0];
				min_cheese[1] = cheeses[i][1];
			}
		}
	
	//setting them to be percentages based on their distances (max distance should be graph_size)
	features[0] = 2*(total_cheese_dist-graph_size)/graph_size;
	features[1] =  2*(closest_cheese-graph_size)/graph_size;
	
	//Feature 3: Num Blocked Edges to Closest Cheese
	int blocked_min_cheese = blocked(gr, min_cheese[0], min_cheese[1], mouse_pos, size_X);
	//max blocked edges would be 7
	features[2] = 2*(blocked_min_cheese-4)/4;

	/******************************************
	 * CAT RELATED FEATURES
	 ******************************************/ 
	
	//Feature 4: Distance to all cats
	//Feature 5: Closest cat distance
	double total_cat_dist = 0;
	double closest_cat = graph_size;
	int min_cat[2];
	for (int i = 0; i < num_cats; i++)
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

	//setting them to be percentages based on their distances (max distance should be graph_size)
  	features[3] =  2*(total_cat_dist-graph_size)/graph_size;
  	features[4] =  2*(closest_cat-graph_size)/graph_size;

  	//Feature 6: Num Blocked Edges to Closest Cat
  	int blocked_min_cat = blocked(gr, min_cat[0], min_cat[1], mouse_pos, size_X);
	//max blocked edges would be 7
  	features[5] = 2*(blocked_min_cat-4)/4;

  	/******************************************
   	* MAZE RELATED FEATURES
   	******************************************/ 

  	//Feature 7: Dead ends
  	int open_edge_count = open_edges(gr, mouse_pos, size_X);
	//open_edge_count should be 4 at max
  	features[6] = 2*(open_edge_count-4)/4;
	
  	//Feature 8: Sanity Check
    double random = (double)rand() / (double)RAND_MAX;
	
    features[7] = random;

}

double Qsa(double weights[25], double features[25])
{
    /*
      Compute and return the Qsa value given the input features and current weights
     */

    /***********************************************************************************************
     * TO DO: Complete this function
     ***********************************************************************************************/
    // Q(s) = sum(w_i*f_i)
    double Qsa = 0;
    int i = 0;
    for (i = 0; i < NUM_FEATURES; i++)
    {  
        Qsa += weights[i] * features[i];
    }
    

    return (Qsa);
}

void maxQsa(double gr[max_graph_size][4], double weights[25], int mouse_pos[1][2], int cats[5][2], int cheeses[5][2], int size_X, int graph_size, double *maxU, int *maxA)
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
    // Keep mouseX and mouseY for resetting pos
    int mouseX = mouse_pos[0][0];
    int mouseY = mouse_pos[0][1];
    int mouseRM = xyToRowMajor(mouseX, mouseY, size_X);

    double features[NUM_FEATURES];
    double Qsa_values[4];
    int directions[4];
    int size = 0;
    int i;

    // Get up to 4 actions but mind the edges
    for (i = 0; i < 4; i++)
    {
        if (gr[mouseRM][i])
        {
            update_mouse_pos(mouse_pos, i);
            evaluateFeatures(gr, features, mouse_pos, cats, cheeses, size_X, graph_size);
            Qsa_values[size] = Qsa(weights, features);
            directions[size++] = i;
            // Reset mouse_pos
            mouse_pos[0][0] = mouseX;
            mouse_pos[0][1] = mouseY;
        }
    }
    
    // Find argmax
    double Qsa_max = -DBL_MAX;
    int argmax = -1;

    for (i = 0; i < size; i++)
    {   
        if (Qsa_values[i] > Qsa_max)
        {
            Qsa_max = Qsa_values[i];
            argmax = directions[i];

        }
    }
    *maxU = Qsa_max;
    *maxA = argmax;

    return;
}

/***************************************************************************************************
 *  Add any functions needed to compute your features below
 *                 ---->  THIS BOX <-----
 * *************************************************************************************************/

int xyToRowMajor(int x, int y, int size_X)
{
    return x + (y * size_X);
}

// int rowMajorToX(int rm)
// {
//     return rm % size_X;
// }

// int rowMajorToY(int rm)
// {
//     return rm / size_Y;
// }

double get_QTable_entry(double *QTable, int s, int a)
{
    return *(QTable + (4 * s) + a);
}

void set_QTable_entry(double *QTable, int s, int a, double val)
{
    *(QTable + (4 * s) + a) = val;
}

int QLearn_policy(int s, int mouse_pos[1][2], double gr[max_graph_size][4], double *QTable, int size_X)
{

    // Get up to 4 actions in QTable in row s. Mind the edges
    int mouseRM = xyToRowMajor(mouse_pos[0][0], mouse_pos[0][1], size_X);
    double QTable_entries[4];
    int directions[4];
    int size = 0;
    // print_graph_array(gr, mouseRM);
    for (int i = 0; i < 4; i++)
    {
        if (gr[mouseRM][i])
        {
            QTable_entries[size] = get_QTable_entry(QTable, s, i);
            directions[size++] = i;
        }
    }

    // Find argmax
    double QTable_max = INT_MIN;
    int argmax = -1;
    int i = 0;

    for (i = 0; i < size; i++)
    {
        if (QTable_entries[i] > QTable_max)
        {
            QTable_max = QTable_entries[i];
            argmax = directions[i];
        }
    }
    return argmax;
}

int get_random_action(int mouse_pos[1][2], double gr[max_graph_size][4], int size_X)
{
    // Get up to 4 actions around the mouse. Mind the edges
    int mouseRM = xyToRowMajor(mouse_pos[0][0], mouse_pos[0][1], size_X);
    int directions[4];
    int size = 0;
    if (gr[mouseRM][0])
    {
        directions[size++] = 0;
    }
    if (gr[mouseRM][1])
    {
        directions[size++] = 1;
    }
    if (gr[mouseRM][2])
    {
        directions[size++] = 2;
    }
    if (gr[mouseRM][3])
    {
        directions[size++] = 3;
    }
    // Pick a random possible action
    int r = rand() % size;
    return directions[r];
}


int get_state(int mouse_pos[1][2], int cats[5][2], int cheeses[5][2], int size_X, int graph_size)
{
    int i = mouse_pos[0][0];
    int j = mouse_pos[0][1];
    int k = cats[0][0];
    int l = cats[0][1];
    int m = cheeses[0][0];
    int n = cheeses[0][1];

    return (i + (j * size_X)) + ((k + (l * size_X)) * graph_size) + ((m + (n * size_X)) * graph_size * graph_size);
}

void print_graph_array(double gr[max_graph_size][4], int curRM)
{
    for (int i = 0; i < 4; i++)
    {
        debug_print("%f %f %f %f\n", gr[curRM][0], gr[curRM][1], gr[curRM][2], gr[curRM][3]);
    }
}

void update_mouse_pos(int mouse_pos[1][2], int direction)
{
    int mouseX = mouse_pos[0][0];
    int mouseY = mouse_pos[0][1];
    // Top
    if (direction == 0)
    {
        mouse_pos[0][0] = mouseX;
        mouse_pos[0][1] = mouseY - 1;
    }
    // Right
    else if (direction == 1)
    {
        mouse_pos[0][0] = mouseX + 1;
        mouse_pos[0][1] = mouseY;
    }
    // Bot
    else if (direction == 2)
    {
        mouse_pos[0][0] = mouseX;
        mouse_pos[0][1] = mouseY + 1;
    }
    // Left
    else if (direction == 3)
    {
        mouse_pos[0][0] = mouseX - 1;
        mouse_pos[0][1] = mouseY;
    }
}

/***********************************************************************************************
 * Helper Functions for Feature Building
 ***********************************************************************************************/        

//This function returns the number of closed edges in direction of a specific location (cheese or cat)
int blocked(double gr[max_graph_size][4], int cx, int cy, int mouse_pos[1][2], int size_X){
	int blocked_edges = 0;
	int index = mouse_pos[0][0]+(mouse_pos[0][1]*size_X);
	int c_index = cx+(cy*size_X);

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
			if (gr[c_index][1] == (double)0 && gr[c_index][2] == (double)0){// if c is blocked
				blocked_edges = blocked_edges+2;
			}
			if (gr[index][3] == (double)0 && gr[index][0] == (double)0 ){//if m is blocked
				blocked_edges = blocked_edges+2;
			}
		}
		else{// in the top right corner
			if (gr[c_index][3] == (double)0 && gr[c_index][2] == (double)0){// if c is blocked
				blocked_edges = blocked_edges+2;
			}
			if (gr[index][1] == (double)0 && gr[index][0] == (double)0 ){//if m is blocked
				blocked_edges = blocked_edges+2;
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
			if (gr[c_index][1] == (double)0 && gr[c_index][0] == (double)0){// if c is blocked
				blocked_edges = blocked_edges+2;
			}
			if (gr[index][3] == (double)0 && gr[index][2] == (double)0){//if m is blocked
				blocked_edges = blocked_edges+2;
			}
		}
		else{// in the bottom right corner
			if (gr[c_index][3] == (double)0 && gr[c_index][0] == (double)0){// if c is blocked
				blocked_edges = blocked_edges+2;
			}
			if (gr[index][1] == (double)0 && gr[index][2] == (double)0 ){//if m is blocked
				blocked_edges = blocked_edges+2;
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
int open_edges(double gr[max_graph_size][4], int loc[1][2], int size_X){
	int open_edge_count = 0;
	int index = loc[0][0]+(loc[0][1]*size_X);
	for(int i=0; i<4; i++){
		 //check if the neighbour is a valid place to move
		if(gr[index][i]==(double)1 && index>0){
			//Finding which neighbour we are on
			//TOP
			if(i==0 && ((index/size_X)-1) >= 0 && ((index/size_X)-1) < size_X){
				open_edge_count = open_edge_count+1;
			}//RIGHT
			else if (i==1 && ((index%size_X)+1) >= 0 && ((index%size_X)+1) < size_X){
				open_edge_count = open_edge_count+1;
			}//BOTTOM
			else if (i==2 && ((index/size_X)+1) >= 0 && ((index/size_X)+1) < size_X){ 
				open_edge_count = open_edge_count+1;
			}//LEFT
			else if (i==3 && ((index%size_X)-1) >= 0 && ((index%size_X)-1) < size_X){
				open_edge_count = open_edge_count+1;
			}
		}
	}
	return open_edge_count;
}


//Returns the minimum value of 2 options
int min_val(int option1, int option2){
  if (option1<option2){
    return option1;
  }
  return option2;
}

//gets random weight between min and max
double rand_init_weight(double min, double max){
  double range = (max - min);
  double div = RAND_MAX/range;
  double weight = min + (rand()/div);
  return weight;
}