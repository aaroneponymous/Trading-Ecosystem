# Blogging

## 08/09/2024

### Branch Misprediction Optimization(s) | 5ns

- [[likely]] [[unlikely]] C++ 20 Attributes 
  - Enable the compiler to perform spot optimizations on asm associated with likely execution paths


- Semi-Static Conditions (Novel Language Construct - August 2023) | Refer: https://arxiv.org/pdf/2308.14185 | https://github.com/maxlucuta/semi-static-conditions
  - "Enable programmers to dynamically modify the direction of a branch at run-time by modifying the assembly code within the underlying executable"


### Data Model: Hashmaps

 - Choice of Data Structure:
    - Array Hashmap (Default in Book) & unordered_map for benchmarks

    - std::vector<T> 
        - Iterator Invalidations upon Resizing
        - But Element Contiguity

        - stable_vector with boost::container::static_vector<T, Chunk_Size>
        - boost::container::dequeue (Check for the configuration of chunk_size / block size feature implementation)

    - stable_vector<T, size_t chunk_size>
        - std::vector<std::unique_ptr<boost::container::static_vector<T, Chunk_Size>>
        - with Chunk_Size as multiple of 2

        - Power of 2
        - Quadratic Hashing: Table Half Empty && Table Size Prime, then guaranteed to be able to insert a new object
        - Cuckoo Hashing?
        - Hopscotch Hashing?
        - Custom Type

    - Other DS&A Choices?


### Kernel Bypassing and Networking
  
  - AF_XDP patch set by Bjorn Topel
    - Any bypasses to it still requiring a sendmsg() sys call on transmit side?

  - Posix has asynchronous aio_read(3) and aio_write(3) (Poor Performance)

  - IO with io_uring for Async-IO
    - Read the reference to utilize

### AF_XDP
// struct xdp_rxtx_ring {
//  __u32 *producer;
//  __u32 *consumer;
//  struct xdp_desc *desc;
// };

// struct xdp_umem_ring {
//  __u32 *producer;
//  __u32 *consumer;
//  __u64 *desc;
// };

// typedef struct xdp_rxtx_ring RING;
// typedef struct xdp_umem_ring RING;

// typedef struct xdp_desc RING_TYPE;
// typedef __u64 RING_TYPE;

int dequeue_one(RING *ring, RING_TYPE *item)
{
    __u32 entries = *ring->producer - *ring->consumer;

    if (entries == 0)
        return -1;

    // read-barrier!

    *item = ring->desc[*ring->consumer & (RING_SIZE - 1)];
    (*ring->consumer)++;
    return 0;
}

int enqueue_one(RING *ring, const RING_TYPE *item)
{
    u32 free_entries = RING_SIZE - (*ring->producer - *ring->consumer);

    if (free_entries == 0)
        return -1;

    ring->desc[*ring->producer & (RING_SIZE - 1)] = *item;

    // write-barrier!

    (*ring->producer)++;
    return 0;
}
