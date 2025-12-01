/**
 * @file
 * @author Alunya
 * @brief Contains the day 01 challenge declaration.
 * @date 01.12.2025
 */

#ifndef AOC_CHALLENGE_01_HPP
#define AOC_CHALLENGE_01_HPP

#include "BaseChallenge.hpp"
#include "../Utils/ChallengeResult.hpp"

#include <cstdint>
#include <filesystem>
#include <queue>
#include <string>

namespace aoc {

/**
 * @class Challenge01
 * @brief Class for the day 01 challenge.
 *
 * The Challenge01 class implements the first challenge of the 'Advent of Code 2024'.
 */
class Challenge01 : public BaseChallenge {
public:
    Challenge01(const std::filesystem::path& filePath);
    virtual ~Challenge01() = default;

    ChallengeResult RunChallenge() override;

private:
    bool         ReadFile() override;
    std::int64_t PartI();
    void         RotateRightPI(std::int32_t amount);
    void         RotateLeftPI(std::int32_t amount);
    std::int64_t PartII();
    std::int64_t RotateRightPII(std::int32_t amount);
    std::int64_t RotateLeftPII(std::int32_t amount);

private:
    std::queue<std::string> m_Rotations;
    std::int32_t            m_CurrentNumber{50};
    bool                    m_StoppedOnZero{false};
};

} // namespace aoc

#endif // ifndef AOC_CHALLENGE_01_HPP
