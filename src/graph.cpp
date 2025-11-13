#include "graph.hpp"
#include <iostream>

void Graph::build(const std::vector<Match>& matches) {

    for (const auto& m : matches) {
        if (!teamIndex.count(m.homeTeam)) {
            int id = teamIndex.size();
            teamIndex[m.homeTeam] = id;
            indexTeam.push_back(m.homeTeam);
        }
        if (!teamIndex.count(m.awayTeam)) {
            int id = teamIndex.size();
            teamIndex[m.awayTeam] = id;
            indexTeam.push_back(m.awayTeam);
        }
    }

    int n = teamIndex.size();
    edges.assign(n, {});

    for (const auto& m : matches) {
        int home = teamIndex[m.homeTeam];
        int away = teamIndex[m.awayTeam];

        if (m.winner == 1) {
            edges[home].push_back({away, m.homeGoals, m.awayGoals, m.round});
        }

        else if (m.winner == -1) {
            edges[away].push_back({home, m.awayGoals, m.homeGoals, m.round});
        }
    }
}

EdgeInfo Graph::getEdgeInfo(int from, int to) const {
    for (const auto& e : edges[from]) {
        if (e.to == to) {
            return e;
        }
    }
    return {-1, 0, 0, 0};
}
