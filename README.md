#### Introduction
This is the third and fourth assignment for the "Algorithms" course at NSYSU.

#### Assignment 3: Implement Dynamic Programing
- Breaking down complex problems (here the knapsack problem) into different subproblems, solving these subproblems quickly, and then combining their solutions to solve the original problem efficiently.
- Usually, the same subproblems recur, and by storing the answers to these subproblems, the overall computation time is reduced, making it faster than brute-force search.
 
#### Assignment 4: Implement Simulated Annealing
- This belongs to a metaheuristic algorithm.
- During the acceptance of solutions, there is a certain probability of accepting worse solutions to achieve the global optimal solution.
- Formula：<img src="https://github.com/SuNsHiNe-75/Algo_hw3-4/assets/137618272/188acd48-2c8c-4278-a9fb-7fe011166ae8" width="30%" height="30%">
   - 𝑓(𝑛): Fitness value of the solution, 𝑇: Temperature (user-defined).
- 𝑇 gradually decreases with each iteration, causing the acceptance probability under the same conditions to decrease.
