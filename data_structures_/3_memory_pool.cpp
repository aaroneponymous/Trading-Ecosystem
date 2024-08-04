#pragma once
#include <cstdint>
#include <vector>
#include <strings.h>
#include "1_macro.h"

namespace Common {
    template<typename T>
    class MemPool final {
    private:
        struct ObjectBlock {
            T object_;
            bool is_free_ = true;
        };
        std::vector<ObjectBlock> store_;
        size_t next_free_index = 0;

        auto upateNextFreeIndex() noexcept {
            const auto initial_free_index = next_free_index_;
            while (!store_[next_free_index_].is_free_) {
                ++next_free_index_;
                if (UNLIKELY(next_free_index_ == store.size())) {
                    // hardware branch predictor should almost always
                    // predict this to be false anyways
                    next_free_index_ = 0;
                }
                if (UNLIKELY(initial_free_index == next_free_index_)) {
                    ASSERT(initial_free_index != next_free_index,
                            "Memory Pool out of Space.");
                }
            }


    // Initialization of the Memory Pool
    // Add an assertion to make sure the actual object of type T
    // is the first one in the ObjectBlock struct (Handling Deallocations)

    public:
        explicit MemPool(std::size_t num_elems) :
            store_(num_elems, {T(), true}) /* pre-allocation of
                vector storage. */ {
                    ASSERT(reinterpret_cast<const ObjectBlock *>
                        (&(store_[0].object_)) == &(store_[0]), "T object should be first member of ObjectBlock.");
		    // store_[o].object compared to the entire 'first' struct object
		    // Checks if the first member of the struct is indeed store_[0].object 
                } 

        template<typename... Args>
        T *allocate(Args... args) noexcept {
            auto obj_block = &(store_[next_free_index]);
            ASSERT(obj_block->is_free_, "Expected free ObjectBlock at index:" + 
                std::to_string(next_free_index));
        T *ret = &(obj_block->object_);
        ret = new(ret) T(args...); // placement new
        updateNextFreeIndex();
        return ret;
        }

	    auto deallocate(const T *elem) noexcept {
            const auto elem_index = (reinterpret_cast<const ObjectBlock *>(elem) - &store_[0]);
            ASSERT(elem_index >= 0 && static_cast<size_t>(elem_index) < store.size(), "Element be deallocated does not belong to this Memory Pool.");
            ASSERT(!store_[elem_index].is_free_, "Expected in-use ObjectBlock at index:" + 
                    std::to_string(elem_index));
            store_[elem_index].is_free_ = true;
            // Delete the default constructor, the copy constructor, and the move constructor methods
            // Delete copy assignment and move assignment operator too
            // Reason why made the constructor explicit (to prevent implicit conversions)
            // Reason why we don't want to call these methods accidentally

            MemPoll() = delete;
            MemPool(const MemPool&) = delete; // copy constructor const Mempool&
            MemPool(const MemPool&&) = delete; // move constructor const Mempool&&
            MemPool& operator=(const MemPool&) = delete; // lvalue
            MemPool& operator=(const MemPool&&) = delete; //rvalue
        }
    };
