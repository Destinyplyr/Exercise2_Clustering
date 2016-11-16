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


mainSample.o: mainSample.cpp Node.h ListData.h Algorithms.h ListsFunctions.cpp NodeFunctions.cpp VectorHammingListManagement.cpp DBListManagement.cpp InitializationMedoids.cpp
	$(CC) $(FLAGS) mainSample.cpp			

Utilities.o: Utilities.cpp
	$(CC) $(FLAGS) Utilities.cpp	

MainFunctions.o: MainFunctions.cpp
	$(CC) $(FLAGS) MainFunctions.cpp

MathFunctions.o: MathFunctions.cpp
	$(CC) $(FLAGS) MathFunctions.cpp

# clean 
clean:
	rm -f $(OBJS) $(OUT)

#accounting
count:
	wc $(SOURCE) $(HEADER)