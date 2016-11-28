#ifndef RETURNS_H
#define RETURNS_H 

//#include <string>

struct Conf
{
	int number_of_clusters;
	int number_of_hash_functions;
	int number_of_hash_tables;
	int clarans_set_fraction;
	int clarans_iterations;	
};


struct Metrics
{
	std::string metric_space;
	std::string metric;
	int point_dimension;
	int point_number;	
};


#endif