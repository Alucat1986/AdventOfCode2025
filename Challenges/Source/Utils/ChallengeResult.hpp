/**
 * @file
 * @author Alunya
 * @brief Contains the declaration of the ChallengeResult struct.
 * @date 01.12.2025
 */

#ifndef AOC_CHALLENGERESULT_HPP
#define AOC_CHALLENGERESULT_HPP

#include <chrono>
#include <cstdint>

namespace aoc {

struct ChallengeResult {
    std::int64_t              partI{0};
    std::int64_t              partII{0};
    std::chrono::microseconds executionTimePartI{0};
    std::chrono::microseconds executionTimePartII{0};
}; // struct ChallengeResult

} // namespace aoc

#endif // ifndef AOC_CHALLENGERESULT_HPP
