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

#include "Node.h"

using namespace CppUnit;
using namespace std;

//-----------------------------------------------------------------------------
template <typename T>
class TestNode : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(TestNode);
	CPPUNIT_TEST(testNodeCon0);
	//Node();
	CPPUNIT_TEST(testNodeCon1);
	//Node(T key);
	CPPUNIT_TEST(testNodeCon2);
	//Node(T key, int g, int itemno, std::string itemName);

	//~Node();

	//Node<T>* getNext();
	CPPUNIT_TEST(testsetNext);
	//void setNext(Node<T>* next);
	CPPUNIT_TEST(testsetKey);
	//void setKey(T key);
	CPPUNIT_TEST(testsetG);
	//void setG(int g);
	CPPUNIT_TEST(testsetItemName);
	//void setItemName(std::string itemName);
	CPPUNIT_TEST(testgetG);
	//int getG();

	//int getItemNo();

	//T getKey();

	//std::string getItemName();

	//int getFlagForAssignment();

	//void setFlagForAssignment(int flagged_for_assignment);

	//int getFlagAsAssigned();

	//void setFlagAsAssigned(int flagged_as_assigned);

	//double getDistanceFromCentroid();

	//void setDistanceFromCentroid(double distance_from_centroid);

	//int getCentroid();
	CPPUNIT_TEST(testsetCentroid);
	//void setCentroid(int centroid);

	//void setSecondBestCentroid(int second_best_centroid);

	//int getSecondBestCentroid();

	//void setSecondBestDistance(int second_best_distance);

	//int getSecondBestDistance();
	CPPUNIT_TEST_SUITE_END();

public:
	void setUp(void);
	void tearDown(void);

protected:
	void testNodeCon0(void);
	CPPUNIT_TEST(testNodeCon1);
	CPPUNIT_TEST(testNodeCon2);
	CPPUNIT_TEST(testsetNext);
	CPPUNIT_TEST(testsetKey);
	CPPUNIT_TEST(testsetG);
	CPPUNIT_TEST(testsetItemName);
	CPPUNIT_TEST(testgetG);
	CPPUNIT_TEST(testsetCentroid);
	void testAddition(void);
	void testMultiply(void);

private:

	Node<T> *mTestObj;
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

void
TestNode::testNodeCon0(void)
{
	mTestObj = new Node<int>();
	CPPUNIT_ASSERT(-1 == mTestObj->getFlagForAssignment());
	CPPUNIT_ASSERT(-1 == mTestObj->getFlagAsAssigned());
	CPPUNIT_ASSERT(INT_MAX == mTestObj->getDistanceFromCentroid());
	CPPUNIT_ASSERT(-1 == mTestObj->getCentroid());
	CPPUNIT_ASSERT(-1 == mTestObj->getItemNo());
	CPPUNIT_ASSERT(NULL == mTestObj->getNext());
}

void
TestNode::testNodeCon1(void)
{
	int i = 5;
	mTestObj = new Node<int>(i);
	CPPUNIT_ASSERT(-1 == mTestObj->getFlagForAssignment());
	CPPUNIT_ASSERT(-1 == mTestObj->getFlagAsAssigned());
	CPPUNIT_ASSERT(INT_MAX == mTestObj->getDistanceFromCentroid());
	CPPUNIT_ASSERT(-1 == mTestObj->getCentroid());
	CPPUNIT_ASSERT(-1 == mTestObj->getItemNo());
	CPPUNIT_ASSERT(NULL == mTestObj->getNext());
	CPPUNIT_ASSERT(5 == mTestObj->getKey());
}

void
TestNode::testNodeCon2(void)
{
	int i = 5;      				//key
	int g = 7;                      //g
	int itemno = 567;				//itemno
	string itemName = "item568";	//itemname
	mTestObj = new Node<int>(i, g, itemno, itemName);
	CPPUNIT_ASSERT(-1 == mTestObj->getFlagForAssignment());
	CPPUNIT_ASSERT(-1 == mTestObj->getFlagAsAssigned());
	CPPUNIT_ASSERT(INT_MAX == mTestObj->getDistanceFromCentroid());
	CPPUNIT_ASSERT(-1 == mTestObj->getCentroid());
	CPPUNIT_ASSERT(567 == mTestObj->getItemNo());
	CPPUNIT_ASSERT(NULL == mTestObj->getNext());
	CPPUNIT_ASSERT(5 == mTestObj->getKey());
	CPPUNIT_ASSERT(7 == mTestObj->getG());
	CPPUNIT_ASSERT(0 == strcmp(mTestObj->getItemName(), "item568"));

}

TestNode::testSetNext(void)
{
	mTestObj->setNext(-1);
	CPPUNIT_ASSERT(-1 == mTestObj->getNext());
}

TestNode::testsetKey(void)
{
	mTestObj->setKey(1);
	CPPUNIT_ASSERT(1 == mTestObj->getKey());
}

TestNode::testsetG(void)
{
	mTestObj->setG(1);
	CPPUNIT_ASSERT(1 == mTestObj->getNext());
}

TestNode::testsetItemName(void)
{
	mTestObj->setItemName("test");
	CPPUNIT_ASSERT(0 == strcmp(mTestObj->getItemName(), "test"));
}

TestNode::testgetG(void)
{
	mTestObj->setG(1);
	CPPUNIT_ASSERT(1 == mTestObj->getG());
}

TestNode::testsetCentroid(void)
{
	mTestObj->setCentroid(678);
	CPPUNIT_ASSERT(678 == mTestObj->getCentroid());
}

/*void
TestBasicMath::testMultiply(void)
{
	CPPUNIT_ASSERT(6 == mTestObj->Multiply(2,3));
}
*/
void TestNode::setUp(void)
{
	mTestObj = new Node<int>();


}

void TestNode::tearDown(void)
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

CPPUNIT_TEST_SUITE_REGISTRATION( TestBasicMath );
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
	ofstream xmlFileOut("cppTestNodeResults.xml");
	XmlOutputter xmlOut(&collectedresults, xmlFileOut);
	xmlOut.write();

	// return 0 if tests were successful
	return collectedresults.wasSuccessful() ? 0 : 1;
}
