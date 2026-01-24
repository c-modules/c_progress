/**
 * \file math_utils.c
 * \brief Mathematical utility functions for C Progress Bar library.
 *
 * \author Ching-Yin Ng
 */

#include <stdint.h>

#include "c_progress_bar.h"
#include "internal/math_utils.h"

double calculate_percentage(const CPB_ProgressBar *restrict progress_bar)
{
    const int64_t start = progress_bar->start;
    const int64_t total = progress_bar->total - start;
    const int64_t current = progress_bar->current - start;

    if (total <= 0 || current <= 0)
    {
        return 0.0;
    }
    if (current >= total)
    {
        return 100.0;
    }

    const double percentage = ((double)current / (double)total) * 100.0;
    return percentage > progress_bar->max_percent ? progress_bar->max_percent
                                                  : percentage;
}