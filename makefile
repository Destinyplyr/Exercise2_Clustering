# In order to execute this "makefile" just type "make"

OBJS 	=  mainSample.o Utilities.o MainFunctions.o ListsFunctions.o NodeFunctions.o
SOURCE	=  mainSample.cpp Utilities.cpp MainFunctions.cpp ListsFunctions.cpp NodeFunctions.cpp
HEADER  = mainSample.h UtilsH.h Headers.h Returns.h Node.h ListData.h
OUT  	= medoids
CC	= g++
FLAGS   = -g -c 

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT)

# create/compile the individual files


mainSample.o: mainSample.cpp
	$(CC) $(FLAGS) mainSample.cpp			

Utilities.o: Utilities.cpp
	$(CC) $(FLAGS) Utilities.cpp	

MainFunctions.o: MainFunctions.cpp
	$(CC) $(FLAGS) MainFunctions.cpp

ListsFunctions.o: ListsFunctions.cpp
	$(CC) $(FLAGS) ListsFunctions.cpp

NodeFunctions.o: NodeFunctions.cpp
	$(CC) $(FLAGS) NodeFunctions.cpp	

# clean 
clean:
	rm -f $(OBJS) $(OUT)

#accounting
count:
	wc $(SOURCE) $(HEADER)