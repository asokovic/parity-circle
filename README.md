# parity-circle
**Parity circle** (or **circle of parity**) is a circular ordering of teams in a league such that **each team has defeated the team immediately before it** in the sequence.

More formally: 
Let $A$ be an array of teams of length $n$. 
A permutation $P = (a_0,a_1,...,a_{n-1})$ of $A$ is considered a parity circle if and only if:

 - for every $0 \le i <  n-1$,  team $a_i$ lost to team $a_{i+1}$, and
 -  team $a_n$ lost the match against the team $a_0$.

  In other words, the permutation forms a directed cycle of wins:
  $$a_0\to a_1\to ...\to a_{n-1}\to a_0$$