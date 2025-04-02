#include <iostream>     // cout
#include <vector>       // vector
#include <algorithm>    // sort
#include <sstream>      // stream
#include <numeric>      // accumulate
#include <limits>       // numeric_limits
#include <optional>     // optional
#include <iomanip>      // setprecision
#include <regex>        // regex

std::optional<double>   safe_stod(const std::string& input);
bool                    parseDouble(const std::string &user_input, std::vector<double> &distances);
void                    printStats(const std::vector<double> &distances,const struct distanceStatistic stat_dist);

struct distanceStatistic {
    double sum_dist = 0;
    double greatest_dist = 0;
    double median_dist = 0;
    double mean_dist = 0;
    double smallest_dist = std::numeric_limits<double>::max(); 
};

int main() {
    std::string                 user_input;
    std::vector<double>         distances; 
    struct distanceStatistic    stat_dist;

    // Getting input from user
    std::cout << "Write sequence of numbers that represent distance (only positive numbers): ";
    getline(std::cin, user_input);

    // Parsing input from user and checking if it's valid (meaning only double values)
    if (user_input.empty() || !parseDouble(user_input, distances)) {
        std::cerr << "Error with the input\n";
        return 1;
    }

    // Getting statistic for distance
    std::sort(distances.begin(), distances.end());
    stat_dist.smallest_dist = distances[0];
    stat_dist.greatest_dist = distances[distances.size() - 1];

    stat_dist.sum_dist = std::accumulate(distances.begin(), distances.end(), 0.0);
    stat_dist.mean_dist = stat_dist.sum_dist / distances.size();
    if (distances.size() % 2 == 0) {
        stat_dist.median_dist = (distances[distances.size() / 2 - 1] + distances[distances.size() / 2]) / 2;
    }
    else {
        stat_dist.median_dist = distances[distances.size() / 2];
    }


    // Printing vector distances
    printStats(distances, stat_dist);
    
    return 0;
}

// Parsing to original vector using istringstream and checkign for non-numbers via safe_stod function. 
bool    parseDouble(const std::string &user_input, std::vector<double> &distances) {

    std::string             num_str;
    std::istringstream      input_stream(user_input);
    static const std::regex number_pattern(R"(^-?(0|[1-9]\d*)(\.\d+)?$)");

    while (input_stream >> num_str) {
        if (!std::regex_match(num_str, number_pattern)) 
            return false;
        auto num = safe_stod(num_str);
        if (!num) return false;
        distances.push_back(*num);
    }
    if (distances.empty()) return false;

    return input_stream.eof();
}

void    printStats(const std::vector<double> &distances, const struct distanceStatistic stat_dist) {
    std::cout << "Based on the input: ";
    std::cout << std::fixed << std::setprecision(2);
    for (auto d : distances) {
        std::cout << d << " ";
    }
    std::cout << "\n";
    std::cout << "The sum of distances is " << stat_dist.sum_dist << "\n"
                << "The greatest distance is " << stat_dist.greatest_dist << "\n"
                << "The smallest distance is " << stat_dist.smallest_dist << "\n"
                << "The mean is " << stat_dist.mean_dist << "\n"
                << "The median is " << stat_dist.median_dist << "\n";
    std::cout << std::defaultfloat;
}

// adding safe guards for non_numbers
std::optional<double> safe_stod(const std::string& input) {
    try {
        return std::stod(input);
    } catch (...) {
        return std::nullopt;
    }
}
