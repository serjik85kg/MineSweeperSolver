#pragma once
#include "config.h"
#include "group.h"
#include <unordered_map>
#include <map>

typedef std::unordered_map<std::pair<int, int>, float, utils::pair_hash> unordered_probs;
//typedef std::map<std::pair<int, int>, float> ordered_probs;

namespace probs
{
	auto sumInd(float a, float b) ->float;
	auto getRawProbs(const std::vector<Group>& groups)->unordered_probs;
	auto correctProbs(unordered_probs& probs, const std::vector<Group>& groups)->void;
	auto getProbs(const std::vector<Group>& groups)->unordered_probs;

}