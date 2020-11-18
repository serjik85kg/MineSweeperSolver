#include "solver.h"

namespace solver
{
	//namespace
	//{
		auto operateGroups(std::vector<Group>& groups)->bool
		{
			auto result = false;
			int kg = 0;
			auto size = groups.size();
			int i = 0;
			//std::cout << "second while" << std::endl;
			while (i < size - 1)
			{
				int j = i;
				while (j + 1 < size)
				{
					//std::cout << "global iteration = " << kg << std::endl; bylo
					//showGroups(groups);
					kg++;
					++j;
					auto g1 = groups[i];
					auto g2 = groups[j];
					if (g1.Cells() == g2.Cells())
					{
						if (g1.Weight() == g2.Weight())
						{
							//std::cout << "DELETE" << std::endl;
							groups.erase(groups.begin() + i);
							--j;
							--size;
							result = true;
							continue;
						}
						else
						{
							for (const auto & p : g1.Cells())
							{
								std::cout << p.second << ' ' << p.first << std::endl;
							}
							throw SolveException("Conflict in groups");
						}
					}

					Group parent = g1;
					Group child = g2;
					if (g1.Cells().size() >= g2.Cells().size())
					{
						parent = g1;
						child = g2;
					}
					else
					{
						parent = g2;
						child = g1;
					}
					if (utils::is_subset_of(child.Cells(), parent.Cells())) // WARNING // OK
					{
						parent.subtract(child);
						if (g1.Cells().size() >= g2.Cells().size())
						{
							groups[i] = parent;
						}
						else
						{
							groups[j] = parent;
						}
						//std::cout << "parent.substract(child), j = " << j << std::endl;
						//std::cout << groups.size() << std::endl;
						result = true;
						continue;
					}

					if (g1.Weight() >= g2.Weight())
					{
						parent = g1;
						child = g2;
					}
					else
					{
						parent = g2;
						child = g1;
					}
					unordered_cells intersection;
					utils::get_intersection(intersection, parent.Cells(), child.Cells());
					//std::cout << "INTERSECTION SIZE = " << intersection.size() << std::endl;
					//std::cout << "intersection size : " << intersection.size() << "\n"; bylo
					if ((intersection.size() != 0) &&
						((parent.Weight() - child.Weight()) == (parent.Cells().size() - intersection.size())))
					{
						auto newGroup = Group(intersection, child.Weight());
						//std::cout << "NEW GROUP: " << std::endl;
	/*					for (const auto& p : newGroup.Cells())
						{
							std::cout << "{" << p.first << ' ' << p.second << "}";
						}*/
						//std::cout << std::endl; bylo
						//std::cout << "||||||||||||||||||||||||||||||||||||||||||||||||||||||||||" << std::endl;
						parent.subtract(newGroup);
						child.subtract(newGroup);
						groups.push_back(newGroup);
						//std::cout << "inter case: j = " << j << std::endl;
						result = true;
						continue;
					}
				}
				++i;
			}

			return result;
		}

		auto getReliableCells(const std::vector<Group>& groups)->std::pair<unordered_cells, unordered_cells>
		{
			unordered_cells mines, notmines;
			for (const auto& group : groups)
			{
				if (group.allMines())
				{
					for (const auto& c : group.Cells())
					{
						mines.emplace(c);
					}
				}
				else if (group.allNotMines())
				{
					for (const auto& c : group.Cells())
					{
						notmines.emplace(c);
					}// |=
				}
			}
			return std::make_pair(mines, notmines);
		}
	//}

	auto solve(std::vector<Group>& groups)->std::pair<unordered_cells, unordered_cells>
	{
		while (true)
		{
			auto changed = operateGroups(groups);
			if (changed == false)
				break;
		}
		return getReliableCells(groups);
	}


	auto mainsolver(const std::string& input, const std::string& output)->void
	{
		auto game = parsik::parseGame(input);
		auto minesData = solver::solve(game.mGroups);
		auto mines = minesData.first;
		auto notMines = minesData.second;
		if (notMines.size() != 0)
		{
			// Show full set of solutions //
			//for (const auto& p : notMines)
			//{
			//	std::cout << p.second << ' ' << p.first << std::endl;
			//}
			auto randomPair = *std::begin(notMines);

			if (output.size() == 0) {
				// Write answer to console
				std::cout << randomPair.second << ", " << randomPair.first << '\n';
			}
			else
			{
				// Write answer to file
				parsik::writeToFile(randomPair, output);
			}
		}
		else
		{
			auto probs = probs::getProbs(game.mGroups);
			std::map<float, std::pair<int,int>/*, std::greater<float>*/> ordered; // if we want more than one solution with the same prob, use multimap
			for (const auto& p : probs)
			{
				ordered.emplace(p.second, p.first);
			}
			// Show full set of exclusive prob solutions //
			//for (const auto& p : ordered)
			//{
			//	std::cout << "probs = " << p.first << " " << p.second.second << ' ' << p.second.first << std::endl;
			//}
			auto randomPair = *std::begin(ordered);
			if (output.size() == 0) {
				//std::cout << "success prob: " << 1 - randomPair.first << std::endl;
				std::cout << randomPair.second.second << ", " << randomPair.second.first << '\n';
			}
			else
			{
				parsik::writeToFile(randomPair.second, output);
			}
		}
	}
}