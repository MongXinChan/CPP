# Computer Mmeory Hierarchy
- Register
- Cache
- Memory
- How to measure?
    - Latency
- Bandwidth
  [](./md-png/图片1.png)
- The huge performance gap between Cache and Memory
    -   Latency (e.g. Intel i9-9900k) 
    -   [x] L1 Cache 0.8 ns
    -   [x] Cache 2.4 ns
    -   [x] Shared L3 Cache 11 ns
    -   [x] Memory above 80ns and higher (depends on memory chip)
    -   Bandwidth
    -   [x] L1 Cache 2.3 TB/s
     -   [x] Shared L3 Cache 370GB/s
     - [x] Memory 40GB/s (depends on memory chip)

**Note**: The performance gap between cache and memory is `significant` and `not linear`. Cache provides much lower latency and higher bandwidth compared to main memory, which is crucial for improving overall system performance.

## Cache

- Matrix Addition
    - Adding the corresponding entries
    - 2-loop
    ```cpp
    for (size_t i = 0; i < n; i++)
    {
        for (size_t j = 0; j < n; j++)
        {
            C[i][j] = A[i][j] + B[i][j]
        }
    }
    //better
    /****
     * Because the memory access is sequential 
     * and the cache is designed to access the memory in a sequential manner,
     * the cache hit rate is higher.
     */
    ```


- i-j loop and j-i loop
    - Diferenct loop level
    - Which loop is faster?
    ```cpp
    for (size_t j = 0; j < n; j++)
    {
        for (size_t i = 0; i < n; i++)
        {
            C[i][j] = A[i][j] + B[i][j]
        }
    }
    //bad
    ```

- i-j loop is faster
    - 2D array in C
    - Inner j loop: continuously memory access
    - Cache higher hit rate
    - Matrix element is already in Cache 


## State-of-the-art Computer Memory Hierarchy

- Multi-cores CPU
    - Every core has private L1: Data L1D, Instruction L1I, **they are indipendent**, D means Data,I means Instruction. 
    - Every core has private L2：Unified
    - Shared L3 in CPU

The complexity of the memory is **more than** we can imagine from the `computer composition`.

[](./md-png/图片2.png)
[](./md-png/图片3.jpg)


Heterogeneous Computing(异构计算)

- GPU
    - Register: Thread Private
    - Shared Memory：SM
    - L1 Cache：SM private ，we can share between threads in the same SM in the processor.
    - Read only：SM private，instruction cache, texture, const.
    - L2 Cache：SM shared
    - Global Memory


## Locality of reference

- Memory access is not randomly in most case
    - Temporal locality: the same location will be referenced again in the near future.
    - Spatial locality: nearby memory locations will be referenced in the near future.
- Hardware Cache
    - Use locality
    - Keep the referenced data in Cache (Temporal locality )
    - Cache line and Hardware Prefetch the near cache line (Spatial locality)

- Good locality in Program—> Good Cache hit rate—>Good Performance



