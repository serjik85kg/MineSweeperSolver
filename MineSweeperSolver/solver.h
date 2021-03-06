#pragma once
#include "group.h"
#include "parsik.h"
#include "probs.h"


class SolveException : public std::exception
{
	std::string info;
public:
	SolveException(std::string e = "Default Parse Error Message.") : info(e)
	{}
	const char * what() const noexcept
	{
		return info.c_str();
	}
};

namespace solver
{
	auto operateGroups(std::vector<Group>& groups)->bool;
	auto getReliableCells(const std::vector<Group>& groups)->std::pair<unordered_cells, unordered_cells>;
	auto solve(std::vector<Group>& groups)->std::pair<unordered_cells, unordered_cells>;

	auto mainsolver(const std::string& input = std::string(), const std::string& output = std::string())->void;

}
