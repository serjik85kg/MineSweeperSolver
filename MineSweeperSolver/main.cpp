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

int main()
{
	solver::mainsolver();
	std::cout << std::endl;
	system("pause");
}



int main_0()
{
	//std::unordered_set<int> set1{ 0,1,2,3,4,5 };
	//std::unordered_set<int> set2{ 0,1,2 };

	//unordered_pairs p1{ {1,1}, {1,2} };
	//unordered_pairs p2{ {1,1}, {1,2}, {1, 3} };

	//unordered_pairs p3{ {0,0}, {1,1}, {2,2}, {3,3} , {3, 4}, {5, 4} };
	//unordered_pairs p4{ {2,2}, {3,3}, {4,4}, {5,5} };

	//auto pai = std::make_pair(1, 2);
	//auto pai2 = std::make_pair(1, 2);

	//auto b = (pai == pai2);

	//utils::subtract(p2, p1);
	//utils::get_intersection(p1, p3, p4);

	////auto b = utils::is_subset_of(p2, p1);
	////utils::substract_uset(p2, p1);
	//for (const auto& p : p1)
	//	std::cout << p.first << ' ' << p.second << std::endl;
	//std::cout << b << std::endl;

	auto tuple = parsik::parseField();
	auto M = std::get<0>(tuple);
	auto N = std::get<1>(tuple);
	auto mines = std::get<2>(tuple);
	auto field = std::get<3>(tuple);

	for (int i = 0; i < N; ++i)
{
	std::cout << std::endl;
	for (int j = 0; j < M; ++j)
		std::cout << field[i][j] << ' ';
}
	std::cout << std::endl;

	auto groups = parsik::getGroups(field, N, M);
	std::cout << groups.size() << std::endl;
	for (const auto& p : groups)
	{
		std::cout << p.Weight() << ": " << p.Cells().size() << std::endl;
		for (const auto& x : p.Cells())
		{
			std::cout << "(" << x.first << ", " << x.second << "), ";
		}
		std::cout << std::endl;
	}

	auto solution = solver::solve(groups);
	/*for (int i = 0; i < 7; ++i)
		solver::operateGroups(groups);*/
	//solver::operateGroups(groups);
	//solver::operateGroups(groups);
	//std::cout << solution.first.size() << ' ' << solution.second.size() << std::endl;
	system("pause");

	return 0;

}