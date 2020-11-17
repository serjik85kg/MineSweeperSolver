#include "parsik.h"

namespace parsik
{
	auto getArea(int x, int y, int m, int n)->std::vector<std::pair<int, int>>
	{
		std::vector<std::pair<int, int>> area;
		if ((x < 0) || (y < 0) || (x >= m) || (y >= n))
		{
			return area;
		}

		auto xBegin = std::max(0, x - 1);
		auto xEnd = std::min(m - 1, x + 1) + 1;
		auto yBegin = std::max(0, y - 1);
		auto yEnd = std::min(n - 1, y + 1) + 1;
		for (int i = xBegin; i < xEnd; ++i)
		{
			for (int j = yBegin; j < yEnd; ++j)
			{
				if ((i == x) && (j == y))
					continue;
				area.emplace_back(std::make_pair(i, j));
			}
		}
		return area;
	}

	namespace
	{
		auto createGroup(int ** field,
			const std::vector<std::pair<int, int>>& area, int w)->Group
		{
			unordered_cells cells;
			for (const auto& p : area)
			{
				int i = p.first;
				int j = p.second;
				if (field[i][j] == -1) // UNOPENED_CELL
					cells.emplace(std::make_pair(i, j));
				// logic for mines
			}

			if (w < 0)
				throw ParseException("LOW_CORRECTED_WEIGHT");

			return Group(cells, w);
		}
	}

	auto getGroups(int ** field, int m, int n)->std::vector<Group>
	{
		std::vector<Group> groups;
		for (int i = 0; i < m; ++i)
		{
			for (int j = 0; j < n; ++j)
			{
				if (field[i][j] > 0)
				{
					auto g = createGroup(field, getArea(i, j, m, n), field[i][j]);
					if (g.Cells().size() > 0)
						groups.push_back(g);
				}
			}
		}
		return groups;
	}

	auto parseField(/*std::istream& is*/)->std::tuple<int, int, int, int**>
	{
		int N, M, mines;
		// M - width, N - height
		const char zap = ',';
		char razdel;
		std::cin >> M >> razdel >> N >> mines;

		// Add exception in future //

		int ** field = new int*[N];
		for (int i = 0; i < N; ++i)
			field[i] = new int[M];
		for (int i = 0; i < N; ++i)
			for (int j = 0; j < M; ++j)
			{
				char cellInp;
				std::cin >> cellInp;
				if (cellInp == 'X')
				{
					field[i][j] = -1;
				}
				else
				{
					field[i][j] = cellInp - 48;
				}
				
			}

		if ((M <= 0) || (N <= 0) || (mines <= 0))
			throw ParseException("NEGATIVE_PROPERTIES");

		return std::make_tuple(M, N, mines, field);
	}

	auto parseGame()->Game
	{
		auto fieldData = parseField();
		auto field = std::get<3>(fieldData);
		auto M = std::get<0>(fieldData);
		auto N = std::get<1>(fieldData);
		auto mines = std::get<2>(fieldData);
		auto groups = getGroups(field, N, M);
		return Game(field, N, M, groups, mines);
	}
}