// A unit test suite

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "stlastar.h"

class ImageSearchNode
{
public:
	int x;	 // the (x,y) positions of the node
	int y;

//    static int MAP_WIDTH;
//    static int MAP_HEIGHT;
//	static int* world_map;

	const static int MAP_WIDTH = 20;
const static int MAP_HEIGHT = 20;
//    int* world_map;
int world_map[ MAP_WIDTH * MAP_HEIGHT ] =
{

// 0001020304050607080910111213141516171819
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,   // 00
	1,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,1,   // 01
	1,9,9,1,1,9,9,9,1,9,1,9,1,9,1,9,9,9,1,1,   // 02
	1,9,9,1,1,9,9,9,1,9,1,9,1,9,1,9,9,9,1,1,   // 03
	1,9,1,1,1,1,9,9,1,9,1,9,1,1,1,1,9,9,1,1,   // 04
	1,9,1,1,9,1,1,1,1,9,1,1,1,1,9,1,1,1,1,1,   // 05
	1,9,9,9,9,1,1,1,1,1,1,9,9,9,9,1,1,1,1,1,   // 06
	1,9,9,9,9,9,9,9,9,1,1,1,9,9,9,9,9,9,9,1,   // 07
	1,9,1,1,1,1,1,1,1,1,1,9,1,1,1,1,1,1,1,1,   // 08
	1,9,1,9,9,9,9,9,9,9,1,1,9,9,9,9,9,9,9,1,   // 09
	1,9,1,1,1,1,9,1,1,9,1,1,1,1,1,1,1,1,1,1,   // 10
	1,9,9,9,9,9,1,9,1,9,1,9,9,9,9,9,1,1,1,1,   // 11
	1,9,1,9,1,9,9,9,1,9,1,9,1,9,1,9,9,9,1,1,   // 12
	1,9,1,9,1,9,9,9,1,9,1,9,1,9,1,9,9,9,1,1,   // 13
	1,9,1,1,1,1,9,9,1,9,1,9,1,1,1,1,9,9,1,1,   // 14
	1,9,1,1,9,1,1,1,1,9,1,1,1,1,9,1,1,1,1,1,   // 15
	1,9,9,9,9,1,1,1,1,1,1,9,9,9,9,1,1,1,1,1,   // 16
	1,1,9,9,9,9,9,9,9,1,1,1,9,9,9,1,9,9,9,9,   // 17
	1,9,1,1,1,1,1,1,1,1,1,9,1,1,1,1,1,1,1,1,   // 18
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,   // 19

};


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

Path apply2img(int* gridmap, int width, int height) {

	AStarSearch<ImageSearchNode> astarsearch;

//    ImageSearchNode::MAP_WIDTH = width;
//    ImageSearchNode::MAP_HEIGHT = height;
//    ImageSearchNode::world_map = gridmap;
//        static int MAP_WIDTH;
//    static int MAP_HEIGHT;
//	static int* world_map;

	unsigned int SearchCount = 0;

	const unsigned int NumSearches = 1;

	while(SearchCount < NumSearches)
	{

		// Create a start state
		ImageSearchNode nodeStart;
		nodeStart.x = 0;
		nodeStart.y = 0;

		// Define the goal state
		ImageSearchNode nodeEnd;
		nodeEnd.x = 3;
		nodeEnd.y = 3;

		// Set Start and goal states

		astarsearch.SetStartAndGoalStates( nodeStart, nodeEnd );

		unsigned int SearchState;
		unsigned int SearchSteps = 0;

		do
		{
			SearchState = astarsearch.SearchStep();

			SearchSteps++;

	#if DEBUG_LISTS

			cout << "Steps:" << SearchSteps << "\n";

			int len = 0;

			cout << "Open:\n";
			ImageSearchNode *p = astarsearch.GetOpenListStart();
			while( p )
			{
				len++;
	#if !DEBUG_LIST_LENGTHS_ONLY
				((ImageSearchNode *)p)->PrintNodeInfo();
	#endif
				p = astarsearch.GetOpenListNext();

			}

			cout << "Open list has " << len << " nodes\n";

			len = 0;

			cout << "Closed:\n";
			p = astarsearch.GetClosedListStart();
			while( p )
			{
				len++;
	#if !DEBUG_LIST_LENGTHS_ONLY
				p->PrintNodeInfo();
	#endif
				p = astarsearch.GetClosedListNext();
			}

			cout << "Closed list has " << len << " nodes\n";
	#endif

		}
		while( SearchState == AStarSearch<ImageSearchNode>::SEARCH_STATE_SEARCHING );

		if( SearchState == AStarSearch<ImageSearchNode>::SEARCH_STATE_SUCCEEDED )
		{
			cout << "Search found goal state\n";

				ImageSearchNode *node = astarsearch.GetSolutionStart();

	#if DISPLAY_SOLUTION
				cout << "Displaying solution\n";
	#endif
				int steps = 0;

				node->PrintNodeInfo();
				for( ;; )
				{
					node = astarsearch.GetSolutionNext();

					if( !node )
					{
						break;
					}

					node->PrintNodeInfo();
					steps ++;

				};

				cout << "Solution steps " << steps << endl;

				// Once you're done with the solution you can free the nodes up
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

	printf("Tests succeeded\n");
                Path path;
            path.length = 3;
            int arr [] = {0, 1, 0, 2, 1, 2};
            path.data = arr;
    return path;
}
