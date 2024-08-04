#pragma once
#include <iostream>
#include <vector>
#include <atomic>

namespace Common {
    template<typename T>
    class LFQueue final {
        private:
        std::vector<T> store_;
        // Following variables need to be of type std::atomic<>
        // because the reading and writing operations are performed
        // from different threads (thread-safe)
        std::atomic<size_t> next_write_index_ = {0};
        std::atomic<size_t> next_read_index_ = {0};
        std::atomic<size_t> num_elements_ = {0};

        public:
            LFQueue(std::size_t num_elems) : 
                store_(num_elems, T()) // pre-allocation of vector storage
                {

            }

            // Default constructor, copy and move constructors
            // and assignment operators : delete 
            LFQueue () = delete;
            LFQueue (const LFQueue&) = delete;
            LFQueue (const LFQueue&&) = delete;
            LFQueue& operator=(const LFQueue&) = delete;
            LFQueue& operator=(const LFQueue&&) = delete;

            auto getNextToWriteTo() noexcept {
                return &store_[next_write_index_];
            }

            auto updateWriteIndex() noexcept {
                next_write_index_ = (next_write_index_ + 1) % store_.size();
                num_elements_++;
            }

            auto getNextToRead() const noexcept -> const T * {
                return (next_read_index_ == next_write_index_) ?
                nullptr : &store_[next_read_index_];
            }

            auto updateReadIndex() noexcept {
                next_read_index_ = (next_read_index_ + 1) % store_.size();
                ASSERT(num_elements_ != 0, "Read an invalid element in: "
                + std::to_string(pthread_self()));
                num_elements_--;
            }

            auto size() const noexcept {
                return num_elements_.load();
            }
    };
    
}