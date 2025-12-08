/**
 * @file
 * @brief Contains the Challenge08 class declaration.
 * @author Alunya
 * @date 04.12.2025
 */

#ifndef AOC_CHALLENGE_08_HPP
#define AOC_CHALLENGE_08_HPP

// ****************************************************************************************************************** //
// ** INCLUDES                                                                                                        //
// ****************************************************************************************************************** //

#include "BaseChallenge.hpp"
#include "../Utils/ChallengeResult.hpp"

#include <cstdint>
#include <filesystem>
#include <vector>

// ****************************************************************************************************************** //
// ** DECLARATIONS                                                                                                    //
// ****************************************************************************************************************** //

namespace aoc {

struct Vec3 {
    std::int64_t X{};
    std::int64_t Y{};
    std::int64_t Z{};

    bool         operator==(const Vec3& other) const;
};

struct Pair {
    Vec3  First{};
    Vec3  Second{};
    float Distance{};

    bool  IsSame(const Pair& other) const;
};

float euclideanDistance(const Vec3& first, const Vec3& second);

class Challenge08 : public BaseChallenge {
public:
    Challenge08(const std::filesystem::path& filePath);

    ChallengeResult RunChallenge() override;

private:
    bool         ReadFile() override;
    std::int64_t PartI();
    std::int64_t PartII();

private:
    std::vector<std::vector<Vec3>> m_Circuits;
    std::vector<Vec3>              m_JunctionBoxes;
};

} // namespace aoc

// ****************************************************************************************************************** //
// ** END OF FILE                                                                                                     //
// ****************************************************************************************************************** //

#endif // #ifndef AOC_CHALLENGE_08_HPP
