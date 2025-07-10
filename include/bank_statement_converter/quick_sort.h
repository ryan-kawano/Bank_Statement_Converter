/**
 * @file quick_sort.h
 * @brief Header file for quick sort.
 */
#ifndef QUICK_SORT_H
#define QUICK_SORT_H

#include <random>

/**
 * @class QuickSort
 * @brief Implements the Quick Sort algorithm.
 */
template<typename T>
class QuickSort {
public:
    /**
     * @brief Partitions the specified portion of the vector around a random pivot.
     * 
     * Chooses a random pivot by using the std::mt19937 random-number generator. Moves everything less than or equal
     * to the pivot, to the left of the pivot by using std::swap.
     * 
     * @param std::vector<T*> The vector to sort.
     * @param int The lowest index of the portion to sort.
     * @param int The highest index of the portion to sort.
     * 
     * @return The pivot index.
     */
    static int partition(std::vector<T*>& vec, int lower, int higher) {
        RK_LOG("Entering partition func\n");

        std::random_device rd; // For generating random pivot. Optimize this later
        std::mt19937 gen(rd()); // For generating random pivot. Optimize this later

        std::uniform_int_distribution<> dist(lower, higher);
        int randomPivotIdx = dist(gen);

        std::swap(vec[randomPivotIdx], vec[higher]); // Move pivot to the end
        T* pivot = vec[higher];
        int i = lower - 1; // For tracking lower numbers

        // Go through vector and move numbers less than or equal to the pivot, to the left of pivot
        for (int j = lower; j < higher; j++) {
            if (*vec[j] <= *pivot) {
                i++;
                std::swap(vec[i], vec[j]);
            }
        }

        // Move pivot to its correct position
        std::swap(vec[i + 1], vec[higher]);

        // Return pivot index
        return i + 1;
    };

    /**
     * @brief Recursively executes the Quick Sort algorithm.
     * 
     * @param std::vector<T*> The vector to sort.
     * @param int The lowest index of the portion to sort.
     * @param int The highest index of the portion to sort.
     */
    static void quickSort(std::vector<T*>& vec, int lower, int higher) {
        RK_LOG("Entering quickSort func\n");

        if (lower < higher) {
            int pivotIndex = partition(vec, lower, higher);

            quickSort(vec, lower, pivotIndex - 1); // Left of pivot
            quickSort(vec, pivotIndex + 1, higher); // Right of pivot
        }
    };
};

#endif
