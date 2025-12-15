# Work Stealing CPU Simulation

## Overview
Multi-core CPU simulator implementing work-stealing scheduling algorithms using custom deque data structures. 
The system distributes tasks across CPU cores, dynamically balancing workload by stealing tasks from busy cores when idle cores need work. 
Supports core management operations including task spawning, execution, sleep states, and system shutdown.

## Concepts Applied
1. Data Structures
    - Custom deque implementation using resizable arrays with dynamic capacity management (doubles at full capacity, halves at 25% utilization, minimum capacity of 2)
    - Efficient O(1) front and back operations for task queue management

2. Algorithms
    - #### Work-stealing schedule:
       * Idle cores steal tasks from the back of the busiest core's queue
    - #### Load balancing:
       * New tasks assigned to core with minimum workload, with index-based tie-breaking
 
3. System Design
    - Object-oriented architecture
    - Minimizing worst case runtime (O(1))

  
