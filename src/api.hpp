#pragma once
#include <string>
#include <vector>
#include <nlohmann/json.hpp>

struct Match {
    std::string homeTeam;
    std::string awayTeam;
    int homeGoals;
    int awayGoals;
    int winner; // winner:  1 = home, -1 = away, 0 = draw
    int round;
};

class Api {
public:
    static nlohmann::json get_fixtures(int leagueId, int season);

    static std::vector<Match> get_matches(int leagueId, int season);
};