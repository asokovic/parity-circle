#include "api.hpp"
#include "env.hpp"
#include <cpr/cpr.h>
#include <iostream>

int extractRound(const std::string& s) {
    int result = 0;
    std::string digits;

    for (char c : s) {
        if (std::isdigit(c)) {
            digits += c;
        } else if (!digits.empty()) {
            break; // stop when the number ends
        }
    }

    if (!digits.empty()) {
        result = std::stoi(digits);
    }

    return result;
}

nlohmann::json Api::get_fixtures(int leagueId, int season) {
    std::string apiKey = Env::get("API_FOOTBALL_KEY");

    if (apiKey.empty()) {
        std::cerr << "Error: API key is missing in .env\n";
        return {};
    }

    std::string url =
        "https://v3.football.api-sports.io/fixtures?league=" +
        std::to_string(leagueId) +
        "&season=" +
        std::to_string(season);

    auto response = cpr::Get(
        cpr::Url{url},
        cpr::Header{{"x-apisports-key", apiKey}}
    );

    if (response.status_code != 200) {
        std::cerr << "HTTP error: " << response.status_code << "\n";
        std::cerr << response.text << "\n";
        return {};
    }

    return nlohmann::json::parse(response.text);
}

std::vector<Match> Api::get_matches(int leagueId, int season) {
    nlohmann::json fixtures = get_fixtures(leagueId, season);
    std::vector<Match> matches;

    if (!fixtures.contains("response") || !fixtures["response"].is_array()) {
        std::cerr << "Unexpected JSON format: no 'response' array\n";
        return matches;
    }

    for (const auto& f : fixtures["response"]) {
        try {
            Match m;

            m.homeTeam = f["teams"]["home"]["name"].get<std::string>();
            m.awayTeam = f["teams"]["away"]["name"].get<std::string>();

            auto hg = f["goals"]["home"];
            auto ag = f["goals"]["away"];

            m.homeGoals = hg.is_number() ? hg.get<int>() : 0;
            m.awayGoals = ag.is_number() ? ag.get<int>() : 0;

            // determine winner
            bool homeWinner = f["teams"]["home"]["winner"].is_boolean()
                              ? f["teams"]["home"]["winner"].get<bool>()
                              : false;
            bool awayWinner = f["teams"]["away"]["winner"].is_boolean()
                              ? f["teams"]["away"]["winner"].get<bool>()
                              : false;

            if (homeWinner && !awayWinner) m.winner = 1;
            else if (!homeWinner && awayWinner) m.winner = -1;
            else m.winner = 0; // draw or no winner info

            if (f["league"]["round"].is_string()) {
                std::string roundStr = f["league"]["round"].get<std::string>();
                m.round = extractRound(roundStr);
            } else {
                m.round = 0;
            }
            matches.push_back(m);
        } catch (const std::exception& e) {
            std::cerr << "Error parsing fixture: " << e.what() << "\n";
        }
    }

    return matches;
}