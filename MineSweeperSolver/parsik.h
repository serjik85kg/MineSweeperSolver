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

class FileException : public std::exception
{
	std::string info;
public:
	FileException(std::string e = "Default File Error Message.") : info(e)
	{}
	const char * what() const noexcept
	{
		return info.c_str();
	}
};

namespace parsik
{
	auto parseFile(const std::string& filename)->std::tuple<int, int, int, int**>;

	auto parseField()->std::tuple<int, int, int, int**>;

	auto getArea(int x, int y, int m, int n)->std::vector<std::pair<int, int>>;

	auto getGroups(int ** field, int m, int n)->std::vector<Group>;

	auto parseGame(const std::string& filename = std::string())->Game;

	auto writeToFile(const std::pair<int, int>& cellData, const std::string& output)->void;
}