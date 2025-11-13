#include "hamiltonian.hpp"
#include <iostream>

static bool dfs(
    const Graph& g,
    int current,
    std::vector<bool>& used,
    std::vector<int>& path,
    int start,
    int depth
) {
    int n = g.indexTeam.size();

    // Base case: we used all nodes
    if (depth == n) {
        // Check if there's an edge back to start
        for (const auto& e : g.edges[current]) {
            if (e.to == start) {
                path.push_back(start); // complete the cycle
                return true;
            }
        }
        return false;
    }

    // Try all outgoing edges
    for (const auto& e : g.edges[current]) {
        int next = e.to;

        if (!used[next]) {
            used[next] = true;
            path.push_back(next);

            if (dfs(g, next, used, path, start, depth + 1)) {
                return true;
            }

            // backtrack
            used[next] = false;
            path.pop_back();
        }
    }

    return false;
}


std::vector<int> Hamiltonian::findCycle(const Graph& g) {
    int n = g.indexTeam.size();
    std::vector<bool> used(n, false);
    std::vector<int> path;

    for (int start = 0; start < n; start++) {
        std::fill(used.begin(), used.end(), false);
        path.clear();
        used[start] = true;
        path.push_back(start);

        if (dfs(g, start, used, path, start, 1)) {
            return path;
        }
    }

    return {}; // no cycle found
}