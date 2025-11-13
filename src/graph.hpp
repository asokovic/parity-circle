#pragma once
#include <string>
#include <unordered_map>
#include <vector>
#include "api.hpp"

struct EdgeInfo {
    int to;
    int homeGoals;
    int awayGoals;
    int round;
};

class Graph {
public:
    std::unordered_map<std::string, int> teamIndex;

    std::vector<std::string> indexTeam;

    std::vector<std::vector<EdgeInfo>> edges;

    void build(const std::vector<Match>& matches);
    
    EdgeInfo getEdgeInfo(int from, int to) const;
};
