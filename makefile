# In order to execute this "makefile" just type "make"

OBJS 	=  mainSample.o Utilities.o MainFunctions.o MathFunctions.o 
SOURCE	=  mainSample.cpp Utilities.cpp MainFunctions.cpp MathFunctions.cpp 
HEADER  = mainSample.h UtilsH.h Headers.h Returns.h MathFunctions.h
OUT  	= medoids
CC	= g++
FLAGS   = -g -c 

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT)

# create/compile the individual files


mainSample.o: mainSample.cpp Node.h ListData.h ListsFunctions.cpp NodeFunctions.cpp VectorListManagement.cpp
	$(CC) $(FLAGS) mainSample.cpp			

Utilities.o: Utilities.cpp
	$(CC) $(FLAGS) Utilities.cpp	

MainFunctions.o: MainFunctions.cpp
	$(CC) $(FLAGS) MainFunctions.cpp

ListsFunctions.o: ListsFunctions.cpp
	$(CC) $(FLAGS) ListsFunctions.cpp

NodeFunctions.o: NodeFunctions.cpp
	$(CC) $(FLAGS) NodeFunctions.cpp

VectorListManagement.o: VectorListManagement.cpp
	$(CC) $(FLAGS) VectorListManagement.cpp	

MathFunctions.o: MathFunctions.cpp
	$(CC) $(FLAGS) MathFunctions.cpp

# clean 
clean:
	rm -f $(OBJS) $(OUT)

#accounting
count:
	wc $(SOURCE) $(HEADER)