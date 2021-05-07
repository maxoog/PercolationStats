#include "PercolationStats.h"

#include "Random_gen.h"
#include "cmath"

PercolationStats::PercolationStats(const size_t dimension, const size_t trials)
    : size(dimension)
    , num_of_trials(trials)
{
    execute();
}

double PercolationStats::get_mean() const
{
    return avg_result;
}

double PercolationStats::get_standard_deviation() const
{
    return standard_deviation;
}

double PercolationStats::get_confidence_low() const
{
    return confidence_interval.first;
}

double PercolationStats::get_confidence_high() const
{
    return confidence_interval.second;
}

void PercolationStats::execute()
{
    double sum_of_results = 0;
    for (size_t trial = 0; trial < num_of_trials; trial++) {
        const double result = take_result();
        sum_of_results += result;
        results.push_back(result);
    }
    avg_result = sum_of_results / num_of_trials;
    standard_deviation = execute_st_deviation();
    double eps = 1.96 * standard_deviation / sqrt(num_of_trials);
    confidence_interval = {avg_result - eps, avg_result + eps};
}

double PercolationStats::take_result()
{
    Percolation frame(size);
    while (!frame.has_percolation()) {
        size_t rand_row = static_cast<size_t>(get_random_number() * (size));
        size_t rand_column = static_cast<size_t>(get_random_number() * (size));
        if (!frame.is_open(rand_row, rand_column)) {
            frame.open(rand_row, rand_column);
        }
    }
    size_t num_of_open = frame.get_numbet_of_open_cells();
    return static_cast<double>(num_of_open) / pow(size, 2);
}

double PercolationStats::execute_st_deviation()
{
    double sum_of_deviations = 0;
    for (const double result : results) {
        sum_of_deviations += pow(result - avg_result, 2);
    }
    return sqrt(sum_of_deviations / (num_of_trials - 1));
}
