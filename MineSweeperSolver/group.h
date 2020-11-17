#pragma once
#include "utils.h"

typedef std::unordered_set<std::pair<int, int>, utils::pair_hash> unordered_cells;

struct Group
{
	Group();
	Group(unordered_cells cells, int w);

	unordered_cells& Cells();
	unordered_cells Cells() const;
	int& Weight();
	int Weight() const;

	void subtract(const Group& other);
	bool allMines() const;
	bool allNotMines() const;

private:
	unordered_cells mCells;
	int mWeight;
};

bool operator==(const Group& p1, const Group& p2);

struct pair_hash
{
	template <class T1, class T2>
	std::size_t operator() (const std::pair<T1, T2> &pair) const
	{
		return std::hash<T1>()(pair.first) ^ std::hash<T2>()(pair.second);
	}
};

// bad hash
struct group_hash
{
	std::size_t operator() (const Group& g) const
	{
		return std::hash<size_t>()(g.Cells().size()) ^ std::hash<int>()(g.Weight());
	}
};

// debug
void showGroups(std::vector<Group>& groups);