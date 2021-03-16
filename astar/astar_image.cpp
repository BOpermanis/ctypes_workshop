// A unit test suite

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <list>
#include "stlastar.h"

int MAP_WIDTH;
int MAP_HEIGHT;

int* world_map;

class ImageSearchNode
{
public:
	int x;	 // the (x,y) positions of the node
	int y;

	ImageSearchNode() { x = y = 0; }
	ImageSearchNode( int px, int py ) { x=px; y=py; }

    int GetMap( int x, int y) {
	    if( x < 0 || x >= MAP_WIDTH || y < 0 || y >= MAP_HEIGHT ) return 9;
	        return world_map[(y*MAP_WIDTH)+x];
    }

	float GoalDistanceEstimate( ImageSearchNode &nodeGoal ){ return abs(x - nodeGoal.x) + abs(y - nodeGoal.y); }
	bool IsGoal( ImageSearchNode &nodeGoal ) {
	    if( (x == nodeGoal.x) && (y == nodeGoal.y) )
		    return true;
        return false;
    }
	bool GetSuccessors( AStarSearch<ImageSearchNode> *astarsearch, ImageSearchNode *parent_node ){
	    int parent_x = -1;
	    int parent_y = -1;

	    if( parent_node ) {
		    parent_x = parent_node->x;
		    parent_y = parent_node->y;
	    }
	    ImageSearchNode NewNode;
        if( (GetMap( x-1, y) < 9) && !((parent_x == x-1) && (parent_y == y))) {
		    NewNode = ImageSearchNode( x-1, y );
		    astarsearch->AddSuccessor( NewNode );
	    }
	    if( (GetMap( x, y-1 ) < 9) && !((parent_x == x) && (parent_y == y-1))) {
		    NewNode = ImageSearchNode( x, y-1 );
		    astarsearch->AddSuccessor( NewNode );
	    }
	    if( (GetMap( x+1, y) < 9) && !((parent_x == x+1) && (parent_y == y))) {
		    NewNode = ImageSearchNode( x+1, y );
		    astarsearch->AddSuccessor( NewNode );
	    }
    	if( (GetMap( x, y+1) < 9) && !((parent_x == x) && (parent_y == y+1)) ) {
		    NewNode = ImageSearchNode( x, y+1 );
		    astarsearch->AddSuccessor( NewNode );
	    }
	    return true;
    }
	float GetCost( ImageSearchNode &successor ){ return (float) GetMap( x, y);}

	bool IsSameState( ImageSearchNode &rhs ) {
	    // same state in a maze search is simply when (x,y) are the same
	    if( (x == rhs.x) && (y == rhs.y) ) {
		    return true;
	    } else {
		    return false;
	    }
}
	void PrintNodeInfo() {
	    char str[100];
	    sprintf( str, "Node position : (%d,%d)\n", x,y );
	    cout << str;
    }
};


struct Path {
    int length;
    int* data;
};

Path apply2img(int* gridmap, int width, int height, int* start, int* finish) {

    world_map = gridmap;
    MAP_WIDTH = width;
    MAP_HEIGHT = height;

    Path path;
    path.length = 0;

	AStarSearch<ImageSearchNode> astarsearch;

	unsigned int SearchCount = 0;

	const unsigned int NumSearches = 1;

	while(SearchCount < NumSearches)
	{
		// Create a start state
		ImageSearchNode nodeStart;
		nodeStart.x = start[0];
		nodeStart.y = start[1];

		// Define the goal state
		ImageSearchNode nodeEnd;
		nodeEnd.x = finish[0];
		nodeEnd.y = finish[1];
		// Set Start and goal states

		astarsearch.SetStartAndGoalStates( nodeStart, nodeEnd );

		unsigned int SearchState;
		unsigned int SearchSteps = 0;
		do {
			SearchState = astarsearch.SearchStep();
			SearchSteps++;
			int len = 0;
			ImageSearchNode *p = astarsearch.GetOpenListStart();
//			((ImageSearchNode *)p)->PrintNodeInfo();
			while( p ) {
				len++;
//                ((ImageSearchNode *)p)->PrintNodeInfo();
				p = astarsearch.GetOpenListNext();
			}
			len = 0;
			p = astarsearch.GetClosedListStart();
			while( p )
			{
				len++;
//				p->PrintNodeInfo();
				p = astarsearch.GetClosedListNext();
			}
		}
		while( SearchState == AStarSearch<ImageSearchNode>::SEARCH_STATE_SEARCHING );

		if( SearchState == AStarSearch<ImageSearchNode>::SEARCH_STATE_SUCCEEDED ) {
		    ImageSearchNode *node = astarsearch.GetSolutionStart();
			int steps = 0;
//            node->PrintNodeInfo();
			list<int> output;
			for( ;; ) {
				node = astarsearch.GetSolutionNext();
				if( !node ) break;
//				node->PrintNodeInfo();
				output.push_back(node->x);
				output.push_back(node->y);
				steps ++;
			};

			int arr[output.size()];
            int k = 0;

            for (auto ii: output){
                arr[k] = ii;
                k += 1;
            }

//			cout << "Solution steps " << steps << endl;
			path.length = steps;
			path.data = arr;
			astarsearch.FreeSolutionNodes();
		}
		else if( SearchState == AStarSearch<ImageSearchNode>::SEARCH_STATE_FAILED )
		{
			cout << "Search terminated. Did not find goal state\n";
		}

		// Display the number of loops the search went through
		cout << "SearchSteps : " << SearchSteps << "\n";
		SearchCount ++;
		astarsearch.EnsureMemoryFreed();
	}

	assert(true && "failed to be true");
//    Path path;
//    path.length = 3;
//    int arr [] = {0, 1, 0, 2, 1, 2};
//    path.data = arr;
    return path;
}

//g++ astar_image.cpp stlastar.h fsa.h
//int main() {
//    apply2img();
//    return 0;
//}
