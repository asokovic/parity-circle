#include <iostream>
#include "env.hpp"

int main() {
    Env::load(); // loads .env in project root

    std::string api_key = Env::get("API_FOOTBALL_KEY");
    std::string league = Env::get("LEAGUE_ID");
    std::string season = Env::get("SEASON");

    std::cout << "API key: " << api_key << std::endl;
    std::cout << "League: " << league << std::endl;
    std::cout << "Season: " << season << std::endl;

    return 0;
}