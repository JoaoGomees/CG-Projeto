LIBS= -framework GLUT -framework OpenGL -framework Cocoa -lGLEW


engine: main.o renderer.o reader.o catmull.o Point.o Object.o tinyxml2.o
		g++ main.o renderer.o reader.o catmull.o Point.o Object.o tinyxml2.o -o engine $(LIBS)
		
main.o: main.cpp
	    g++ -c main.cpp ./renderer.cpp ./catmull.cpp $ ../../Common/Object.h
	   
renderer.o: renderer.cpp
			g++ -c renderer.cpp $ ../../Common/Point.h $ ../../Common/Object.h

reader.o: reader.cpp
		  g++ -c reader.cpp $ ../headers/reader.h $ ../../Common/Point.h

catmull.o: catmull.cpp
			g++ -c catmull.cpp
		  
Point.o: ../../Common/Point.cpp
		 g++ -c ../../Common/Point.cpp $ ../../Common/Point.h

Object.o: ../../Common/Object.cpp
		  g++ -c ../../Common/Object.cpp $ ../../Common/Object.h 
		 
tinyxml2.o: ../../Common/tinyxml2.cpp
		    g++ -c ../../Common/tinyxml2.cpp $ ../../Common/tinyxml2.h
		 
clean:
	rm *.o
		  
