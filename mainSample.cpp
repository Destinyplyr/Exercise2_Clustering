#include "mainSample.h"

int main(int argc, char **argv)
{

	int numOfClusters;
	int k = 4;
	int L = 5;
	int claransFraction;
	int claransIterations;
	string GARBAGE;
	string initAlgo;
	string assignAlgo;
	string updateAlgo;
	string choice;
	string filename;
	ifstream inputFile;
	ifstream conFile;
	ofstream outputFile;

	//bool outParameter = false, inParameter = false, confParameter = false;

	std::cout.setf(std::ios_base::fixed, std::ios_base::floatfield);
	std::cout.precision(20);
	srand (time(NULL));

	if (argc > 1)
	{
		if (argc % 2 == 0)
		{
			cout << "Missing the correct number of parameters" << endl;
			cout << "Suggested use: $./medoids –d <input file> –c <configuration file> -ο <output file>" << endl;
			return -1;
		}
		for (int i = 1; i < argc; i++)
		{
			if (strcmp(argv[i], "-d") == 0)
			{
				inputFile.open(argv[i+1]);	//Input file comes next on argv
				if (inputFile == NULL)
				{
					cout << "You've given a wrong input file. " << endl;
					exit(1);
				}
				else
				{
					cout << "File : " << argv[i+1] << " opened successfully!" << endl << endl;
					//inParameter = true;
				}
				
				//inputFile >> metric_space;  //Read "@metric space"
				//inputFile >> metric_space;	//Read etc, "hamming"

				// if (strcmp(metric_space.c_str(), "euclidean") == 0)
				// {
				// 	inputFile >> metric;  	//Read "@metric space"
				// 	inputFile >> metric;	//Read etc, "hamming"
				// }

				i++;
			}
			else if (strcmp(argv[i], "-c") == 0)
			{
				conFile.open(argv[i+1]);	//Configuration file comes next on argv
				if (conFile == NULL)
				{
					cout << "You've given a wrong configuration file. " << endl;
					exit(1);
				}
				else
				{
					cout << "File : " << argv[i+1] << " opened successfully!" << endl << endl;
					//confParameter = true;
				}

				conFile >> GARBAGE;
				conFile >> numOfClusters;
				conFile >> GARBAGE;
				conFile >> k;
				conFile >> GARBAGE;
				conFile >> L;
				conFile >> GARBAGE;
				conFile >> claransFraction;
				conFile >> GARBAGE;
				conFile >> claransIterations;
				cout << "Information read from configuration file." << endl;

				i++;
			}
			else if (strcmp(argv[i], "-o") == 0)
			{
				outputFile.open(argv[i+1]);		//Output file comes next on argv
				if (outputFile == NULL)
				{
					cout << "You've given a wrong output file. " << endl;
					exit(1);
				}
				else
				{
					cout << "File : " << argv[i+1] << " opened successfully!" << endl << endl;
					//outParameter = true;
				}

				i++;
			}
			else
			{
				cout << "You've given wrong input" <<endl;
				return -1;
			}
		}
	}


	cout << "Welcome to Clustering testing simulation." << endl << endl;



	//INTERFACE FOR CHOOSING FILES (?)
	/*do
	{
		//If input file is given from command line.
		if (inParameter) 
		{
			inParameter = false;
		}
		else 
		{
			cout << "Please give an input file: ";
			cin >> filename;
			inputFile.open(filename.c_str());
			if (inputFile == NULL)
			{
				cout << "You've given a wrong input file. " << endl;
				exit(1);
			}
			else
			{
				cout << "File : " << filename << " opened successfully!" << endl << endl;
			}
			inputFile >> metric_space;  //Read "@metric space"
			inputFile >> metric_space;	//Read etc, "hamming"

			if (strcmp(metric_space.c_str(), "euclidean") == 0)
			{
				inputFile >> metric;  	//Read "@metric space"
				inputFile >> metric;	//Read etc, "hamming"
			}
		}
		//If configuration file is given from command line.
		if (confParameter) 
		{
			confParameter = false;
		}
		else 
		{
			cout << "Please give a configuration file: ";
			cin >> filename;
			conFile.open(filename.c_str());		
			if (conFile == NULL)
			{
				cout << "You've given a wrong configuration file. " << endl;
				exit(1);
			}
			else
			{
				cout << "File : " << filename << " opened successfully!" << endl << endl;
			}
		}
		//If output file is given from command line.
		if (outParameter) 
		{
			outParameter = false;
		}
		else
		{
			cout << "Please give an output file: ";
			cin >> filename;
			outputFile.open(filename.c_str());
			if (outputFile == NULL)
			{
				cout << "You've given a wrong input file. " << endl;
				exit(1);
			}
			else
			{
				cout << "File : " << filename << " opened successfully!" << endl << endl;
			}
		}


	}while...
*/

	cout << "Please type an algorithm for Initialization : " << endl;
	cout << "1. K-medoids++" << endl;
	cout << "2. Concentrate" << endl;
	cin >> initAlgo;
	cout << endl;
	cout << "Please type an algorithm for Assignment : " << endl;
	cout << "1. PAM" << endl;
	cout << "2. LSHReverse" << endl;
	cin >> assignAlgo;
	cout << endl;
	cout << "Please select an algorithm for Update : " << endl;
	cout << "1. Llyod's" << endl;
	cout << "2. CLARANS" << endl;
	cin >> updateAlgo;
	cout << endl;

	return 0;
}