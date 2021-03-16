all : 8puzzle findpath minpathbucharest tests image

clean :
	rm 8puzzle findpath minpathbucharest tests image

minpathbucharest : min_path_to_Bucharest.cpp stlastar.h
	g++ -Wall min_path_to_Bucharest.cpp -o minpathbucharest

8puzzle : 8puzzle.cpp stlastar.h
	g++ -Wall 8puzzle.cpp -o 8puzzle

findpath : findpath.cpp stlastar.h
	g++ -Wall findpath.cpp -o findpath

tests : tests.cpp 8puzzle findpath minpathbucharest
	g++ -Wall tests.cpp -o tests

image : stlastar.h
	g++ -Wall astar_image.cpp -o astar_image

test: tests
	./tests






