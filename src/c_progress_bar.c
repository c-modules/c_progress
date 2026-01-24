#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

#include "c_progress_bar.h"
#include "internal/math_utils.h"
#include "internal/system_utils.h"

void cpb_init(CPB_ProgressBar *progress_bar, int64_t start, int64_t total)
{
    if (!progress_bar)
    {
        return;
    }

    progress_bar->_timer_freq_inv =
        get_timer_freq_inv(); // Must call before using timer

    progress_bar->start = start;
    progress_bar->total = total;
    progress_bar->current = start;

    progress_bar->is_started = false;
    progress_bar->is_finished = false;

    progress_bar->unique_updates_count = 0;
    progress_bar->window_index = 0;
    progress_bar->time_start = 0.0;
    progress_bar->eta_time_last_update = 0.0;
    progress_bar->eta_percent_last_update = 0.0;
    for (int i = 0; i < 5; i++)
    {
        progress_bar->eta_time_diffs[i] = 0.0;
        progress_bar->eta_percent_diffs[i] = 0.0;
    }

    progress_bar->max_percent = 100.0;
    progress_bar->min_refresh_time = 0.1;
}

void cpb_start(CPB_ProgressBar *restrict progress_bar)
{
    if (!progress_bar)
    {
        return;
    }

    progress_bar->is_started = true;
    progress_bar->time_start = get_monotonic_time(progress_bar);
    progress_bar->eta_time_last_update = progress_bar->time_start;
    progress_bar->eta_percent_last_update = calculate_percentage(progress_bar);
}

void cpb_update(CPB_ProgressBar *restrict progress_bar, int64_t current)
{
    if (!progress_bar)
    {
        return;
    }

    progress_bar->current = current;
    const int progress_percent = calculate_percentage(progress_bar);

    // WARNING: zu is wrong, should remove later
    printf(
        "\r\033[?25lProgress: %zu / %zu %3d%%",
        progress_bar->current,
        progress_bar->total,
        progress_percent
    );
}

void cpb_finish(CPB_ProgressBar *restrict progress_bar)
{
    if (!progress_bar)
    {
        return;
    }

    progress_bar->is_finished = true;
}