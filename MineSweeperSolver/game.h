#pragma once

#include "group.h"

class Game
{
public:
	int ** mField;
	int mM;
	int mN;
	int mMines;
	std::vector<Group> mGroups;
public:
	Game(int ** field, int m, int n, std::vector<Group> groups, int mines)
		: mField(field), mM(m), mN(n), mGroups(groups), mMines(mines) {}
};