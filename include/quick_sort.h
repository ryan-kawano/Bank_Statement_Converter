/**
 * @file quick_sort.h
 * @brief Header file for quick sort.
 */
#ifndef QUICK_SORT_H
#define QUICK_SORT_H

#include <random>
#include "transaction.h"

/**
 * @class QuickSort
 * @brief Implements the Quick Sort algorithm.
 */
class QuickSort {
public:
    /**
     * @brief Partitions the specified portion of the vector around a random pivot.
     * 
     * @param std::vector<Transaction*> The vector to sort.
     * @param int The lowest index of the portion to sort.
     * @param int The highest index of the portion to sort.
     * 
     * @return The pivot index.
     */
    static int partition(std::vector<Transaction*>&, int, int);

    /**
     * @brief Recursively executes the Quick Sort algorithm.
     * 
     * @param std::vector<Transaction*> The vector to sort.
     * @param int The lowest index of the portion to sort.
     * @param int The highest index of the portion to sort.
     */
    static void quickSort(std::vector<Transaction*>&, int, int);
};

#endif
