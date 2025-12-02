/**
 * @file
 * @author Alunya
 * @brief Contains the day 02 challenge declaration.
 * @date 02.12.2025
 */

#ifndef AOC_CHALLENGE_02_HPP
#define AOC_CHALLENGE_02_HPP

#include "BaseChallenge.hpp"
#include "../Utils/ChallengeResult.hpp"

#include <cstdint>
#include <filesystem>

namespace aoc {

/**
 * @class Challenge02
 * @brief Class for the day 02 challenge.
 *
 * The Challenge01 class implements the first challenge of the 'Advent of Code 2024'.
 */
class Challenge02 : public BaseChallenge {
public:
    Challenge02(const std::filesystem::path& filePath);

    ChallengeResult RunChallenge() override;

private:
    bool         ReadFile() override;
    std::int64_t PartI();
    std::int64_t PartII();

private:
};

} // namespace aoc

#endif // ifndef AOC_CHALLENGE_02_HPP
