# Parity circle
**Parity circle** (or **circle of parity**) is a circular ordering of teams in a league such that **each team has defeated the team immediately before it** in the sequence.

More formally: 
Let $A$ be an array of teams of length $n$. 
A permutation $P = (a_0,a_1,...,a_{n-1})$ of $A$ is considered a parity circle if and only if:

 - for every $0 \le i <  n-1$,  team $a_i$ lost to team $a_{i+1}$, and
 - team $a_{n-1}$ lost to team $a_0$.

  In other words, the permutation forms a directed cycle of wins:
  $$a_0\to a_1\to ...\to a_{n-1}\to a_0$$

## Idea
 
Inspired by [this](https://www.reddit.com/r/soccer/comments/1ov0ij4/) Reddit post about the circle of parity in Spanish LaLiga.

## Solution

It's easy to conclude that for the circle of parity to exist in a league/competition it is necessary for each team to have at least one win and one loss (otherwise circle cannot be formed). Nevertheless, this alone is not enough for us to prove that a circle of parity was formed.

After a bit of thinking, we can come to the realization that the problem of finding a circle of parity in a sports competition is equivalent to finding a Hamiltonian cycle in a directed graph where each vertex represents a team and each edge represents a win.

Since the problem of determining if a graph contains a Hamiltonian cycle is NP complete (and problem of finding a Hamiltonian cycle is FNP) we are left with using DFS with backtracking to find a Hamiltonian cycle and by doing this form the circle of parity. This algorithm is, in it's worst case scenario, very inefficient with the time complexity $O(n!)$.

Graph representing outcomes of the matches in a league typically has a size of $n \approx 20$ and the number of matches is $n*(n-1)$. Since the draws are not represented in our graph and the prevalence of draws in professional football leagues ranges from $20\%$ to $30\%$ the number of edges in our graph is $|E| \approx0,75 * n*(n-1)$.

In real-life scenario the graph representing the outcomes of matches in a football league is far from the worst case scenario structure since it usually contains both the vertices with high number of outgoing edges (strong teams which win most of their matches) and vertices with low number of outgoing edges (weak teams that loose most of their matches). This uneven distribution greatly reduces the branching factor during the search: most paths become invalid within just a few steps, enabling strong pruning and making the Hamiltonian cycle search practical despite its worst-case exponential complexity.

## A better soultion?
There theoretically exists a better solution for our problem.

According to the Ore's theorem which states:

Let $G$ be a finite and simple graph with $N\ge3$ vertices we denote with $deg$ $v$ the degree of a vertex $v$ in $G$

If $deg$ $v$ $+$ $deg$ $w$ $\ge n$ for every pair of ditinct non-adjacent verices $v$ and $w$ of $G$ then $G$ contains a Hamiltonian cycle

Since our graph representing results of a sports league is directed we cannot directly apply Ore's law but instead Woodwall's (1972) version of Ore's theorem which can be applied to directed graphs and states:

If in a directed graph $G$ with $n$ vertices for every pair of vertices $u$ and $v$ there is either an edge from $u$ to $v$ or $out$ $deg$ $u$ $+$ $in$ $deg$ $v$ $\ge$ $n$, $G$ contains a directed Hamiltonian cycle.

Eventhough this theorem could lead to a much faster worst case scenario algorithm it cannot be used for our graph since the graphs representing outcomes of matches in a football league rarely fulfill the condition. It's rare that the sum of wins of the worst team in a league ($out$ $deg$ $u$) and loses of the best team in a league ($in$ $deg$ $v$) exceeds total number of teams in a league. 

In the last 15 seasons of the English Premier League there were multiple pairs of teams that didn't fulfill the condition needed to apply Wodall's theorem every year, but it's important to note that this theorem may be applicable in other sports where teams play more game and where the game cannot finish in a draw (e.g. basketball).

## About

This program is written in C++ and analyzes the results of a football league and determines whether a parity circle exists among the participating teams. Match data is converted into a directed graph in which each vertex represents a team and each directed edge represents a victory (winner → loser). The program then searches this graph for a Hamiltonian cycle, which corresponds to a parity circle and displays the result of the search. If the parity circle is found it will display the ordering of teams along with the results of the games which formed a cycle.

## Dependencies

Following packages are required:

`CPR`

`nlohmann-json`

## Data source
The program uses API-Football REST API to retrive data about the teams, matches, and league. 

They offer a free tier with access to a limited selection of leagues and seasons, and a paid tier that provides coverage of nearly all leagues worldwide. They also offer APIs for other sports but be aware that the program would maybe need to be slightly modified since the structure of the API responses is probably not the same for all sports.

More info can be found on their [website](https://www.api-football.com)

## Running the program

1. Get your [API-Football](https://www.api-football.com) API key

2. Create `.env` file (use .env.example as a template)

3. Enter your API key in `.env`
```sh
API_FOOTBALL_KEY=YOUR_API_KEY_HERE
```
4. Enter season year and league id which can be found at API-Football website
```sh
LEAGUE_ID=39
SEASON=2021
```
This example will run the program for Premier League (league id: 39) 2021/2022 season.

5. Run the following commands from the project root folder to build
```sh
mkdir build
cd build
cmake ..
make
```

6. Run the program
```sh
./parity-circle
```