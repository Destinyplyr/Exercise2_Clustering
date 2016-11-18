# In order to execute this "makefile" just type "make"

OBJS 	=  mainSample.o Utilities.o MainFunctions.o MathFunctions.o DistanceMatrixFunctions.o
SOURCE	=  mainSample.cpp Utilities.cpp MainFunctions.cpp MathFunctions.cpp DistanceMatrixFunctions.cpp
HEADER  = mainSample.h UtilsH.h Headers.h Returns.h MathFunctions.h DistanceMatrixFunctions.h
OUT  	= medoids
CC	= g++
FLAGS   = -g -c 
#INC = -I/googletest-master/googletest/include/gtest -I/googletest-master/googletest/include/gtest/internal
# $(INC)

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT)

# create/compile the individual files


mainSample.o: mainSample.cpp Node.h ListData.h Algorithms.h ListsFunctions.cpp NodeFunctions.cpp VectorHammingListManagement.cpp DBListManagement.cpp InitializationMedoids.cpp AssignmentPAM.cpp
	$(CC) $(FLAGS) mainSample.cpp			

Utilities.o: Utilities.cpp
	$(CC) $(FLAGS) Utilities.cpp	

MainFunctions.o: MainFunctions.cpp
	$(CC) $(FLAGS) MainFunctions.cpp

MathFunctions.o: MathFunctions.cpp
	$(CC) $(FLAGS) MathFunctions.cpp

DistanceMatrixFunctions.o: DistanceMatrixFunctions.cpp
	$(CC) $(FLAGS) DistanceMatrixFunctions.cpp

# clean 
clean:
	rm -f $(OBJS) $(OUT)

#accounting
count:
	wc $(SOURCE) $(HEADER)