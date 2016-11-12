#include "mainSample.h"

int main(int argc, char **argv)
{
	ifstream inputFile;
	ifstream conFile;
	ofstream outputFile;

	std::cout.setf(std::ios_base::fixed, std::ios_base::floatfield);
	std::cout.precision(20);
	srand (time(NULL));

	/*if (argc > 1)
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
					//queryParameter = true;
				}

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
*/

	cout << "Welcome to Clustering testing simulation." << endl << endl;


	return 0;
}