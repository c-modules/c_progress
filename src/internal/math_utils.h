/**
 * \file math_utils.h
 * \brief Mathematical utility functions for C Progress Bar library.
 *
 * \author Ching-Yin Ng
 */

#ifndef C_PROGRESS_BAR_INTERNAL_MATH_UTILS_H
#define C_PROGRESS_BAR_INTERNAL_MATH_UTILS_H

#include <stdint.h>

#include "c_progress_bar.h"

/**
 * \brief Calculate the percentage of completion.
 *
 * \param[in] progress_bar Pointer to the progress bar structure.
 *
 * \return The percentage of completion as a double.
 */
double calculate_percentage(const CPB_ProgressBar *restrict progress_bar);

#endif /* C_PROGRESS_BAR_INTERNAL_MATH_UTILS_H */
