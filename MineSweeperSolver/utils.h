#pragma once
#include <iostream>
#include <sstream>
#include <unordered_set>
#include <vector>
#include <algorithm>
#include <tuple>

// helper functions
namespace utils
{
	struct pair_hash
	{
		template <class T1, class T2>
		std::size_t operator() (const std::pair<T1, T2> &pair) const
		{
			return std::hash<T1>()(pair.first) ^ std::hash<T2>()(pair.second);
		}
	};

	template <typename T, typename H>
	bool is_subset_of(const std::unordered_set<T, H>& a, const std::unordered_set<T, H>& b)
	{
		// return true if all members of a are also in b
		auto const is_in_b = [&b](auto const& x) { return b.find(x) != b.end(); };

		return a.size() <= b.size() && std::all_of(a.begin(), a.end(), is_in_b);
	}

	template<typename T, typename H>
	void subtract(std::unordered_set<T, H>& bigger, const std::unordered_set<T, H>& smaller)
	{
		for (const auto& p : smaller)
		{
			bigger.erase(p);
		}
	}

	template<typename T, typename H>
	void get_intersection(std::unordered_set<T, H> &out,
		const std::unordered_set<T, H> &in1,
		const std::unordered_set<T, H> &in2)
	{
		out.clear();
		if (in2.size() < in1.size()) {
			get_intersection(out, in2, in1);
			return;
		}
		for (typename std::unordered_set<T, H>::const_iterator it = in1.begin(); it != in1.end(); it++)
		{
			if (in2.find(*it) != in2.end())
				out.insert(*it);
		}
	}
}