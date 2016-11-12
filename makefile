# In order to execute this "makefile" just type "make"

OBJS 	=  mainSample.o
SOURCE	=  mainSample.cpp
HEADER  = mainSample.h
OUT  	= medoids
CC	= g++
FLAGS   = -g -c 

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT)

# create/compile the individual files


PointFunctions.o: PointFunctions.cpp
	$(CC) $(FLAGS) PointFunctions.cpp			


# clean 
clean:
	rm -f $(OBJS) $(OUT)

#accounting
count:
	wc $(SOURCE) $(HEADER)