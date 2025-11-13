#pragma once
#include <vector>
#include "graph.hpp"

class Hamiltonian {
public:
    static std::vector<int> findCycle(const Graph& g);
};