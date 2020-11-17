#include "probs.h"

namespace probs
{
	auto sumInd(float a, float b) ->float
	{
		return 1 - (1 - a) * (1 - b);
	}

	auto getRawProbs(const std::vector<Group>& groups)->unordered_probs
	{
		unordered_probs probs;
		for (const auto& group : groups)
		{
			for (const auto& cell : group.Cells())
			{
				//std::cout << group.Weight() << ' ' << group.Cells().size() << std::endl;
				float prob = (float)group.Weight() / group.Cells().size();
				unordered_probs::const_iterator got = probs.find(cell);
				if (got != probs.end())
				{
					probs.emplace(cell, sumInd(probs[cell], prob));
				}
				else
				{
					probs.emplace(cell, prob);
				}
			}
		}
		return probs;
	}

	auto correctProbs(unordered_probs& probs, const std::vector<Group>& groups)->void
	{
		while (true)
		{
			bool changed = false;
			for (const auto& group : groups)
			{
				float s = 0;
				for (const auto& cell : group.Cells())
				{
					s += probs[cell];
				}
				if (!((std::abs(s - group.Weight())) < EPS))
				{
					changed = true;
					auto k = group.Weight() / s;
					for (const auto& cell : group.Cells())
					{
						probs[cell] *= k;
					}
				}
			}

			if (changed == false)
				break;
		}
	}

	auto getProbs(const std::vector<Group>& groups)->unordered_probs
	{
		auto probs = getRawProbs(groups);
		//for (const auto& p : probs)
		//{
		//	std::cout << "raw probs = " << p.first.second << " " << p.first.first << " || " << p.second << std::endl;
		//}
		correctProbs(probs, groups);
		return probs;
	}
}