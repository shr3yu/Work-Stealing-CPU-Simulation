# Work-Stealing CPU Scheduler Simulator
A C++ simulator of a multi-core CPU scheduler that balances load across cores using **work stealing**, the scheduling strategy behind runtimes like Cilk, Intel TBB, Go and Tokio. Each core owns a task queue built on a custom circular-buffer deque with manual memory management, and idle cores steal work from the busiest core to keep every core utilized.

Design rationale, complexity analysis and test plan: [design document](spmamidi_design_p1.pdf)

## Highlights
* **Work-stealing scheduler**: when a core runs out of tasks, it steals from the *back* of the most-loaded core's queue while that core keeps consuming from the *front*, so owner and thief work on opposite ends of the deque
* **Least-loaded task placement**: new tasks go to the core with the shortest queue, with deterministic lowest-index tie-breaking
* **Core sleep / migration**: putting a core to sleep drains its queue and migrates each task to the least-loaded remaining core
* **Custom deque from scratch**: circular buffer on a raw heap array (no STL containers), with wrap-around indexing and explicit `new[]`/`delete[]` ownership
* **Adaptive memory footprint**: each queue doubles when full and halves at 25% occupancy (minimum capacity 2), so memory tracks the live workload and push/pop stay amortized O(1)

## Architecture
```
              SPAWN task
                  │  placed on least-loaded core
                  ▼
 ┌──────────┐ ┌──────────┐ ┌──────────┐ ┌──────────┐
 │  Core 0  │ │  Core 1  │ │  Core 2  │ │  Core 3  │
 │  deque   │ │  deque   │ │  deque   │ │  deque   │
 │front→back│ │front→back│ │front→back│ │front→back│
 └────┬─────┘ └──────────┘ └────┬─────┘ └──────────┘
      │ RUN: pop_front()        │
      ▼                         │ idle core steals
   execute task                 │ pop_back() of busiest core
```
* `Core`: one task queue. Circular-buffer deque with `insert` (back), `pop_front`, `pop_back`, and automatic grow/shrink
* `CPU`: owns the array of cores and implements the scheduling policy: placement, execution, stealing, sleep migration and shutdown
* `CPU_driver.cpp`: command interpreter that drives the simulator from stdin

## Complexity
| Operation | Cost | Notes |
|---|---|---|
| Deque push / pop (front or back) | O(1) amortized | O(capacity) only on the step that triggers a resize |
| Task placement / steal target | O(C) | linear scan over C cores for least / most loaded |
| Sleep a core with k tasks | O(k · C) | each migrated task picks the least-loaded core |
| Shutdown | O(total tasks) | drains every queue |

The grow-at-full / shrink-at-quarter policy leaves a gap between the two thresholds, so alternating pushes and pops can't cause repeated resizes (no thrashing).

## Build & Run
```
make          # builds ./cpu
make test     # runs the sample command script in test.txt
```

### Commands
| Command | Effect |
|---|---|
| `ON n` | Power on a CPU with `n` cores |
| `SPAWN id` | Create task `id` (> 0) and place it on the least-loaded core |
| `RUN c` | Core `c` executes its next task; steals work if it ends up empty |
| `SLEEP c` | Put core `c` to sleep and migrate its tasks to the other cores |
| `SIZE c` / `CAPACITY c` | Inspect queue length / allocated capacity of core `c` |
| `SHUTDOWN` | Clear every queue |
| `EXIT` | Quit |

### Example
```
ON 4                success
SPAWN 1 ... 8       core 0 assigned task 1 ... core 3 assigned task 8   (round-robin by load)
SLEEP 1             task 6 assigned to core 0 task 2 assigned to core 2
SIZE 1              size is 0
CAPACITY 1          capacity is 2      (queue shrank after draining)
RUN 2               core 2 is running task 3
```

## Tech Stack
* C++ (raw arrays, manual memory management, no STL containers)
* Object-oriented design: `Core` / `CPU` separation of mechanism and policy

## Roadmap
1. Run each core on a real OS thread and replace the deque with a lock-free Chase-Lev work-stealing deque
2. Keep per-core load counts in a min/max heap to make placement and steal-target selection O(log C)
3. Add random-victim stealing and compare it against busiest-core stealing on throughput and balance
4. Benchmark scheduling throughput and core utilization under skewed workloads
