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
	if (argc > 2) {
		std::cerr << "error" << std::endl;
		return -1;
	}
	else if (argc == 2)
		inputfile = argv[1];
	else
		std::cout << argc << std::endl;

	//const std::string testpath = "003.txt";
	try
	{
		solver::mainsolver(inputfile);
	}
	catch (ParseException e)
	{
		std::cerr << e.what() << std::endl;
	}
	catch (SolveException e)
	{
		std::cerr << e.what() << std::endl;
	}
	catch (FileException e)
	{
		std::cerr << e.what() << std::endl;
	}
	catch (...)
	{
	}
	//std::cout << std::endl;
	system("pause");
}