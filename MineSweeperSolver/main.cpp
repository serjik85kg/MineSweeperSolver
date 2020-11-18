#include "config.h"
#include <iostream>
#include <sstream>
#include <unordered_set>
#include <vector>
#include <algorithm>
#include <tuple>

#include "utils.h"
#include "parsik.h"
#include "solver.h"


int main(int argc, char** argv)
{
	std::string inputfile;
	std::string outputfile;
	if (argc > 3) {
		std::cerr << "Error command line arguments." << std::endl;
		return -1;
	}
	else if (argc == 2)
		inputfile = argv[1];
	else if (argc == 3)
	{
		inputfile = argv[1];
		outputfile = argv[2];
	}

	try
	{
		solver::mainsolver(inputfile, outputfile);
	}
	catch (ParseException& e)
	{
		std::cerr << e.what() << std::endl;
	}
	catch (SolveException& e)
	{
		std::cerr << e.what() << std::endl;
	}
	catch (FileException& e)
	{
		std::cerr << e.what() << std::endl;
	}
	catch (...)
	{
	}
	system("pause");
}