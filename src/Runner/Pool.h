#pragma once

#include <vector>
#include <memory>
#include <GCSR.h>
#include <iostream>
#include <vector>
#include <memory>
#include <type_traits>
#include <utility>

template<typename T>
class Pool {
public:
    template<typename U, typename... Args>
    U* Acquire(Args&&... args) {
        static_assert(std::is_base_of_v<T, U>, "U doit hériter de T");

        if (!freeList.empty()) {
            T* obj = freeList.back();
            freeList.pop_back();
            occupiedList.push_back(obj);
            return static_cast<U*>(obj);
        }

        pool.emplace_back(std::make_unique<U>(std::forward<Args>(args)...));
        T* obj = pool.back().get();
        occupiedList.push_back(obj);
        return static_cast<U*>(obj);
    }

    void Release(T* obj) {
        auto it = std::find(occupiedList.begin(), occupiedList.end(), obj);
        if (it != occupiedList.end()) {
            occupiedList.erase(it);
            freeList.push_back(obj);
        }
    }

private:
    std::vector<std::unique_ptr<T>> pool;
    std::vector<T*> occupiedList;
    std::vector<T*> freeList;
};
