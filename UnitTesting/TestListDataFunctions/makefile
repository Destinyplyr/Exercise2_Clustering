CXX = g++
INCLUDES= -I./
CXXFLAGS = -g $(INCLUDES)
SRCM= ListsFunctions.cpp MathFunctions.cpp
OBJM = $(SRCM:.cpp=.o)
LINKFLAGS= -lcppunit

testlistdata: TestListData.cpp ListsFunctions.cpp $(OBJM)
	$(CXX) $(CXXFLAGS) -o $@ TestListData.cpp $(OBJM) $(LINKFLAGS) $(LINKFLAGSLOG4) $(LIBLOG)

# Default compile

.cpp.o:
	$(CXX) $(CXXFLAGS) -c $< -o $@
