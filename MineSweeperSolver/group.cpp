#include "group.h"

Group::Group() {}

Group::Group(unordered_cells cells, int weight)
	: mCells(cells), mWeight(weight) {}

int& Group::Weight()
{
	return mWeight;
}

int Group::Weight() const
{
	return mWeight;
}

unordered_cells& Group::Cells()
{
	return mCells;
}

unordered_cells Group::Cells() const
{
	return mCells;
}

void Group::subtract(const Group& other)
{
	utils::subtract(mCells, other.mCells);
	mWeight -= other.Weight();
}

bool Group::allMines() const
{
	return mCells.size() == mWeight;
}

bool Group::allNotMines() const
{
	return mWeight == 0;
}

bool operator==(const Group& g1, const Group& g2)
{
	return (g1.Cells() == g2.Cells()) && (g1.Weight() == g2.Weight());
}




void showGroups(std::vector<Group>& groups)
{
	std::cout << "Groups size: " << groups.size() << std::endl;
	for (const auto& p : groups)
	{
		std::cout << p.Weight() << ": ";
		std::cout << "{";
		for (const auto& x : p.Cells())
		{
			std::cout << "(" << x.first << ", " << x.second << "),";
		}
		std::cout << "}  ";
	}
	std::cout << std::endl;
}