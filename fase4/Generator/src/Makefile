generator: main.o writer.o box.o plane.o cone.o sphere.o patch.o Point.o
		   g++ main.o writer.o box.o plane.o cone.o sphere.o patch.o Point.o -o generator
		   
main.o: main.cpp
		g++ -c main.cpp $ ../headers/sphere.h $ ../headers/cone.h $ ../headers/plane.h $ ../headers/box.h $ ../headers/writer.h $ ../headers/patch.h
		
		
writer.o: writer.cpp
		  g++ -c writer.cpp $ ../headers/writer.h $ ../../Common/Point.h
		  
box.o: box.cpp
	   g++ -c box.cpp $ ../headers/box.h $ ../../Common/Point.h
	   
plane.o: plane.cpp
		 g++ -c plane.cpp $ ../headers/plane.h $ ../../Common/Point.h
		 
cone.o: cone.cpp
		g++ -c cone.cpp $ ../headers/cone.h $ ../../Common/Point.h
		
sphere.o: sphere.cpp
		  g++ -c sphere.cpp $ ../headers/sphere.h $ ../../Common/Point.h

patch.o: patch.cpp
		g++ -c patch.cpp $ ../headers/patch.h $ ../../Common/Point.h
		  
Point.o: ../../Common/Point.cpp
		 g++ -c ../../Common/Point.cpp $ ../../Common/Point.h


clean :
		rm *.o
