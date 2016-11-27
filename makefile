# In order to execute this "makefile" just type "make"

OBJS 	=  mainSample.o Utilities.o MainFunctions.o MathFunctions.o DistanceMatrixFunctions.o InitializationMedoids.o InitializationConcentrate.o ClusterNodeFunctions.o ClusterTableFunctions.o AssignmentPAM.o UpdateALaLoyds.o UpdateCLARANS.o CLARA.o PAM.o
SOURCE	=  mainSample.cpp Utilities.cpp MainFunctions.cpp MathFunctions.cpp DistanceMatrixFunctions.cpp InitializationMedoids.cpp InitializationConcentrate.cpp ClusterNodeFunctions.cpp ClusterTableFunctions.cpp AssignmentPAM.cpp UpdateALaLoyds.cpp UpdateCLARANS.cpp CLARA.cpp PAM.cpp
HEADER  = mainSample.h UtilsH.h Headers.h Returns.h MathFunctions.h DistanceMatrixFunctions.h Algorithms.h ClusterNode.h ClusterTable.h  
OUT  	= medoids
CC	= g++
FLAGS   = -g -c 
#INC = -I/googletest-master/googletest/include/gtest -I/googletest-master/googletest/include/gtest/internal
# $(INC)

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT)

# create/compile the individual files


mainSample.o: mainSample.cpp Node.h ListData.h Hash.h ListsFunctions.cpp NodeFunctions.cpp VectorHammingListManagement.cpp DBListManagement.cpp HammingListManagement.cpp DBHManagement.cpp HashFunctions.cpp HammingLSHManagement.cpp EuclideanList.cpp TrickFunctions.cpp
	$(CC) $(FLAGS) mainSample.cpp			

Utilities.o: Utilities.cpp
	$(CC) $(FLAGS) Utilities.cpp	

MainFunctions.o: MainFunctions.cpp
	$(CC) $(FLAGS) MainFunctions.cpp

MathFunctions.o: MathFunctions.cpp
	$(CC) $(FLAGS) MathFunctions.cpp

DistanceMatrixFunctions.o: DistanceMatrixFunctions.cpp
	$(CC) $(FLAGS) DistanceMatrixFunctions.cpp


InitializationMedoids.o: InitializationMedoids.cpp
	$(CC) $(FLAGS) InitializationMedoids.cpp

InitializationConcentrate.o: InitializationConcentrate.cpp
	$(CC) $(FLAGS) InitializationConcentrate.cpp			

ClusterNodeFunctions.o: ClusterNodeFunctions.cpp
	$(CC) $(FLAGS) ClusterNodeFunctions.cpp		

ClusterTableFunctions.o: ClusterTableFunctions.cpp
	$(CC) $(FLAGS) ClusterTableFunctions.cpp	

AssignmentPAM.o: AssignmentPAM.cpp
	$(CC) $(FLAGS) AssignmentPAM.cpp	

UpdateALaLoyds.o: UpdateALaLoyds.cpp
	$(CC) $(FLAGS) UpdateALaLoyds.cpp

UpdateCLARANS.o: UpdateCLARANS.cpp
	$(CC) $(FLAGS) UpdateCLARANS.cpp

CLARA.o: CLARA.cpp
	$(CC) $(FLAGS) CLARA.cpp

PAM.o: PAM.cpp
	$(CC) $(FLAGS) PAM.cpp

# clean 
clean:
	rm -f $(OBJS) $(OUT) ListsFunctions.o NodeFunctions.o VectorHammingListManagement.o DBListManagement.o HammingListManagement.o DBHManagement.o HashFunctions.o

#accounting
count:
	wc $(SOURCE) $(HEADER)