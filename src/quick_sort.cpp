/**
 * @file quick_sort.cpp
 * @brief Source file for the Quick Sort class/algorithm.
 */
#include <random>
#include "quick_sort.h"
#include "transaction.h"
#include "logger/log.h"

/**
 * Chooses a random pivot by using the std::mt19937 random-number generator. Moves everything less than or equal
 * to the pivot, to the left of the pivot by using std::swap.
 */
int QuickSort::partition(std::vector<Transaction*>& vec, int lower, int higher) {
    LOG("Entering partition func\n");

    std::random_device rd; // For generating random pivot. Optimize this later
    std::mt19937 gen(rd()); // For generating random pivot. Optimize this later

    // Get random pivot index
    std::uniform_int_distribution<> dist(lower, higher); // Random integer between lower and higher
    int pivotIdx = dist(gen);
    std::swap(vec[pivotIdx], vec[higher]); // Move pivot to the end
    Transaction* pivot = vec[higher];
    int i = lower - 1; // For tracking lower numbers

    // Go through vector and move numbers less than or equal to the pivot, to the left of pivot
    for (int j = lower; j < higher; j++) {
        if (vec[j]->getDate() <= pivot->getDate()) {
            i++;
            std::swap(vec[i], vec[j]);
        }
    }

    // Move pivot to its correct position
    std::swap(vec[i + 1], vec[higher]);

    // Return pivot index
    return i + 1;
}

void QuickSort::quickSort(std::vector<Transaction*>& vec, int lower, int higher) {
    LOG("Entering quickSort func\n");

    if (lower < higher) {
        int pivotIndex = partition(vec, lower, higher);

        quickSort(vec, lower, pivotIndex - 1); // Left of pivot
        quickSort(vec, pivotIndex + 1, higher); // Right of pivot
    }
}
