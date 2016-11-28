#include <iostream>
#include <string>
#include <list>
#include <cppunit/TestCase.h>
#include <cppunit/TestFixture.h>
#include <cppunit/ui/text/TextTestRunner.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/TestRunner.h>
#include <cppunit/BriefTestProgressListener.h>
#include <cppunit/CompilerOutputter.h>
#include <cppunit/XmlOutputter.h>
#include <netinet/in.h>

#include "ListData.h"
#include "ListsFunctions.cpp"
#include "NodeFunctions.cpp"
#include "Headers.h"

using namespace CppUnit;
using namespace std;

//-----------------------------------------------------------------------------
template <typename T>
class TestListData : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(TestListData);
	CPPUNIT_TEST(testListDataCon0);
	//ListData();

	//~ListData();
	//CPPUNIT_TEST(testgetHead);
 	// Node<T>* ReturnHead();
	//same as above
 	// Node<T>* getNode();
	CPPUNIT_TEST(testExistsOnce);
	// void PrintData();
	CPPUNIT_TEST(testInsert);
	// void Insert(T item, int itemno, std::string itemName);
	
	// void initEuclideanList(Conf* myConf, ifstream& inputFile, double** distanceMatrix, int k, int L, int* dataLengthPointNumber, int* hashCreationDone, Hash<double* >* hashTableList, int* centroids, int** clusterAssign);
	
	// void initCosineList(Conf* myConf, ifstream& inputFile, double** distanceMatrix, int k, int L, int* dataLengthPointNumber, int* hashCreationDone, Hash<double* >* hashTableList, int* centroids, int** clusterAssign);
	
	// void initDBHManagement(Conf* myConf, ifstream& inputFile, double** distanceMatrix, int k, int L, int* dataLength, int* hashCreationDone, Hash<double>* hashTableList, int* centroids, int** clusterAssign);
	
	// void initHammingLSHManagement(Conf* myConf, ifstream& inputFile, double** distanceMatrix, int k, int L, int* dataLength, int* hashCreationDone, Hash<bitset<64> >* hashTableList, int* centroids, int** clusterAssign);
	CPPUNIT_TEST(testDistance);
	// int Distance(T item1, T item2);
	
	// bool ListData<T>::ExistsOnce(int itemno, Node<T>* header_out)
	CPPUNIT_TEST(testCosineDistance);
	// double CosineDistance(double p1[], double p2[], int size);
	CPPUNIT_TEST(testHammingDuplicate);
	// bool HammingDuplicate(T item);
	CPPUNIT_TEST(testHammingB2BDuplicate);
	// bool HammingB2BDuplicate(T item);
	CPPUNIT_TEST(testEuclideanDuplicate);
	// bool EuclideanDuplicate(T item, int size);
	
	// void ListInsertionVector(std::ifstream& inputFile, Metrics* myMetric);
	
	// void DistanceMatrixComputationVector(Metrics* myMetric, double** distance_matrix);
	
	// void ListInsertionDB(std::ifstream& inputFile, Metrics* myMetric);
	
	// void DistanceMatrixComputationDB(std::ifstream& inputFile, Metrics* myMetric, double** distance_matrix);
	
	// void ListInsertionHamming(std::ifstream& inputFile, Metrics* myMetric);
	CPPUNIT_TEST(testDistanceB2BHamming);
	// double DistanceB2BHamming(T item1, T item2);
	
	// void DistanceMatrixComputationHamming(Metrics* myMetric, double** distance_matrix);
	CPPUNIT_TEST_SUITE_END();

public:
	void setUp(void);
	void tearDown(void);

protected:
	void testListDataCon0(void);
	//void testgetHead(void);
	void testInsert(void);
	void testDistance(void);
	void testExistsOnce(void);
	void testCosineDistance(void);
	void testHammingDuplicate(void);
	void testHammingB2BDuplicate(void);
	void testEuclideanDuplicate(void);
	void testDistanceB2BHamming(void);
		
	/*void testNodeCon0(void);
	void testNodeCon1(void);
	void testNodeCon2(void);
	void testsetNext(void);
	void testsetKey(void);
	void testsetG(void);
	void testsetItemName(void);
	void testgetG(void);
	void testsetCentroid(void);*/

private:

	ListData<T> *mTestObj;
};

/*class TestBasicMath2 : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(TestBasicMath2);
	CPPUNIT_TEST(testAddition);
	CPPUNIT_TEST(testMultiply);
	CPPUNIT_TEST_SUITE_END();

public:
	void setUp(void);
	void tearDown(void);

protected:
	void testAddition(void);
	void testMultiply(void);

private:

	CBasicMath2 *mTestObj;
};*/

//-----------------------------------------------------------------------------


template <typename T>
void TestListData<T>::testListDataCon0(void)
{
	mTestObj = new ListData<int>();
	CPPUNIT_ASSERT(NULL == mTestObj->getNode());
}

/*template <typename T>
void TestListData<T>::testgetHead(void)
{
	Node<T> *newNode = new Node<T>;
	mTestObj->set(newNode);
	CPPUNIT_ASSERT(newNode == mTestObj->getNext());
}
*/
template <typename T>
void TestListData<T>::testInsert(void)
{
	//Node<T> *newNode = new Node<T>;
	int key = 1;
	int itemno = 678;
	string itemName = "item679";
	mTestObj->Insert(key,  itemno, itemName);
	CPPUNIT_ASSERT(true == mTestObj->ExistsOnce(itemno, mTestObj->ReturnHead()));

}

template <typename T>
void TestListData<T>::testDistance(void)
{
	ListData<string>* newListData = new ListData<string>();
	string Hamming1 = "0011";
	string Hamming2 = "0101";
	CPPUNIT_ASSERT(2 == newListData->Distance(Hamming1, Hamming2));
}

template <typename T>
void TestListData<T>::testExistsOnce(void)
{
	int key = 1;
	int itemno = 678;
	string itemName = "item679";
	mTestObj->Insert(key,  itemno, itemName);
	key = 2;
	mTestObj->Insert(key,  itemno, itemName);
	CPPUNIT_ASSERT(false == mTestObj->ExistsOnce(678, mTestObj->ReturnHead()));
	ListData<int>* mTestObj2 = new ListData<int>();
	key = 1;
	itemno = 678;
	itemName = "item679";
	mTestObj2->Insert(key,  itemno, itemName);
	CPPUNIT_ASSERT(true == mTestObj2->ExistsOnce(678, mTestObj2->ReturnHead()));
}

template <typename T>
void TestListData<T>::testCosineDistance(void)
{
	double item1[3];
	double item2[3];
	item1[0] = 1.5; item1[1] = 2.5; item1[2] = 1.5;
	item2[0] = 2.5; item2[1] = 1.5; item2[2] = 2.5; 
	//cout <<endl<< "cosinedis: "<<mTestObj->CosineDistance(item1, item2, 3) << " - " << 0.106587 << endl;
	//CPPUNIT_ASSERT(0.106587 == mTestObj->CosineDistance(item1, item2, 3));
	CPPUNIT_ASSERT_EQUAL((double)0.106587,mTestObj->CosineDistance(item1, item2, 3) );
}

template <typename T>
void TestListData<T>::testHammingDuplicate(void)
{
	//mTestObj->setG(1);
	//Node<T> * newNode = new Node<T>(1, 1, 657, "test");
	ListData<string>* newListData = new ListData<string>();
	string Hamming1 = "0011";
	string Hamming2 = "0011";
	newListData->Insert(Hamming1, 657, "test");
	CPPUNIT_ASSERT(true == newListData->HammingDuplicate(Hamming2));
}

template <typename T>
void TestListData<T>::testHammingB2BDuplicate(void)
{
	ListData<bitset<64> >* newListData = new ListData<bitset<64> >();
	bitset<64> bitset1(string("0011"));
	bitset<64> bitset2(string("0011"));
	newListData->Insert(bitset1, 1, "item1");
	CPPUNIT_ASSERT(true == newListData->HammingB2BDuplicate(bitset2));
}

template <typename T>
void TestListData<T>::testEuclideanDuplicate(void)
{
	ListData<double*>* newListData = new ListData<double*>();
	double item1[3] = {3, 4, 1.5};
	double item2[3] = {3, 4, 1.5};
	newListData->Insert(item1, 657, "test");
	CPPUNIT_ASSERT(true == newListData->EuclideanDuplicate(item2, 3));
}

template <typename T>
void TestListData<T>::testDistanceB2BHamming(void)
{
	ListData<bitset<64> >* newListData = new ListData<bitset<64> >();
	bitset<64> bitset1(string("0011"));
	bitset<64> bitset2(string("0101"));
	CPPUNIT_ASSERT(2 == newListData->DistanceB2BHamming(bitset1, bitset2));
}

/*void
TestBasicMath::testMultiply(void)
{
	CPPUNIT_ASSERT(6 == mTestObj->Multiply(2,3));
}
*/
template <typename T>
void TestListData<T>::setUp(void)
{
	mTestObj = new ListData<int>();


}

template <typename T>
void TestListData<T>::tearDown(void)
{
	delete mTestObj;
}

/*void
TestBasicMath2::testAddition(void)
{
	CPPUNIT_ASSERT(5 == mTestObj->Addition(2,3));
}

void
TestBasicMath2::testMultiply(void)
{
	CPPUNIT_ASSERT(6 == mTestObj->Multiply(2,3));
}

void TestBasicMath2::setUp(void)
{
	mTestObj = new CBasicMath2();
}

void TestBasicMath2::tearDown(void)
{
	delete mTestObj;
}
*/
//-----------------------------------------------------------------------------

CPPUNIT_TEST_SUITE_REGISTRATION( TestListData<int> );
//CPPUNIT_TEST_SUITE_REGISTRATION( TestBasicMath2 );

int main(int argc, char* argv[])
{
	// informs test-listener about testresults
	CPPUNIT_NS::TestResult testresult;

	// register listener for collecting the test-results
	CPPUNIT_NS::TestResultCollector collectedresults;
	testresult.addListener (&collectedresults);

	// register listener for per-test progress output
	CPPUNIT_NS::BriefTestProgressListener progress;
	testresult.addListener (&progress);

	// insert test-suite at test-runner by registry
	CPPUNIT_NS::TestRunner testrunner;
	testrunner.addTest (CPPUNIT_NS::TestFactoryRegistry::getRegistry().makeTest ());
	testrunner.run(testresult);

	// output results in compiler-format
	CPPUNIT_NS::CompilerOutputter compileroutputter(&collectedresults, std::cerr);
	compileroutputter.write ();

	// Output XML for Jenkins CPPunit plugin
	ofstream xmlFileOut("cppTestListDataResults.xml");
	XmlOutputter xmlOut(&collectedresults, xmlFileOut);
	xmlOut.write();

	// return 0 if tests were successful
	return collectedresults.wasSuccessful() ? 0 : 1;
}
