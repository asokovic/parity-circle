#include <iostream>
#include "graph.hpp"
#include "env.hpp"
#include "api.hpp"
#include "hamiltonian.hpp"

int main() {
    Env::load("../.env");

    int league = std::stoi(Env::get("LEAGUE_ID"));
    int season = std::stoi(Env::get("SEASON"));

    auto matches = Api::get_matches(league, season);

    Graph g;
    g.build(matches);

    auto cycle = Hamiltonian::findCycle(g);

    if (cycle.empty()) {
        std::cout << "No parity circle found.\n";
    } else {
    std::cout << "\nParity circle:\n";

    for (int i = 0; i + 1 < cycle.size(); i++) {
        int u = cycle[i];
        int v = cycle[i+1];

        auto e = g.getEdgeInfo(u, v);

        std::cout
            << g.indexTeam[u]
            << " → " << g.indexTeam[v]
            << "  (" << e.homeGoals << "-" << e.awayGoals
            << ", Round " << e.round << ")\n";
    }
    std::cout << std::endl;
}

    
    return 0;
}
