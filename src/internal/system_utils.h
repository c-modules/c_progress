/**
 * \file system_utils.h
 * \brief System utility functions for C Progress Bar library.
 *
 * \author Ching-Yin Ng
 */

#ifndef C_PROGRESS_BAR_INTERNAL_SYSTEM_UTILS_H
#define C_PROGRESS_BAR_INTERNAL_SYSTEM_UTILS_H

#include <stdbool.h>

/**
 * \brief Determine if we should use UTF-8 encoding for the given output stream.
 *
 * \param[in] stream The output stream (e.g., stdout, stderr).
 * \return true if UTF-8 encoding should be used, false otherwise.
 */
bool should_use_utf8(FILE *stream);

/**
 * \brief Determine if ANSI color codes should be used for the given output stream.
 *
 * \param[in] stream The output stream (e.g., stdout, stderr).
 * \return true if ANSI color codes should be used, false otherwise.
 */
bool should_use_color(FILE *stream);

/**
 * \brief Get the width of the terminal for the given output stream.
 *
 * \param[in] stream The output stream (e.g., stdout, stderr), or NULL for files.
 * \return The width of the terminal in characters.
 */
int get_terminal_width(FILE *stream);

/**
 * \brief Get the inverse of the timer frequency (for Windows).
 *
 * \return The inverse of the timer frequency.
 */
double get_timer_freq_inv(void);

/**
 * \brief Get the current monotonic time in seconds.
 *
 * \param[in] progress_bar Pointer to the progress bar structure (for timer frequency on
 * Windows).
 *
 * \return The current monotonic time in seconds.
 */
double get_monotonic_time(const CPB_ProgressBar *restrict progress_bar);

#endif /* C_PROGRESS_BAR_INTERNAL_SYSTEM_UTILS_H */
