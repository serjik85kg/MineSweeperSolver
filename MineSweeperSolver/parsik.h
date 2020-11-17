#pragma once
#include "utils.h"
#include <string>
#include "group.h"
#include "game.h"

class ParseException : public std::exception
{
	std::string info;
public:
	ParseException(std::string e = "Default Parse Error Message.") : info(e)
	{}
	const char * what() const noexcept
	{
		return info.c_str();
	}
};

//struct ErrorMessages
//{
//	std::string PROPERTIES = "Input mistake";
//	std::string NEGATIVE_PROPERTIES = "Numbers must be more than 0";
//	std::string SHORT_ROW = "Row is too short";
//	std::string LOW_CORRECTED_WEIGHT = "Number of mines in area is more than weight of cell";
//	std::string UNKNOWN_SYMBOL = "Unknown symbol";
//	std::string WEIGHT_BOUNDS = "Digital cell should have weight in range {0, 8}";
//};

namespace parsik
{
	auto parseField(/*std::istream& is*/)->std::tuple<int, int, int, int**>;
	auto getArea(int x, int y, int m, int n)->std::vector<std::pair<int, int>>;
	auto getGroups(int ** field, int m, int n)->std::vector<Group>;

	auto parseGame()->Game;
}