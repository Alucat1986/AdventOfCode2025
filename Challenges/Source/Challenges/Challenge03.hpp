/**
 * @file
 * @brief Contains the Challenge03 class declaration.
 * @author Alunya
 * @date 03.12.2025
 */

#ifndef AOC_CHALLENGE_03_HPP
#define AOC_CHALLENGE_03_HPP

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

class Challenge03 : public BaseChallenge {
public:
    Challenge03(const std::filesystem::path& filePath);

    ChallengeResult RunChallenge() override;

private:
    bool         ReadFile() override;
    std::int64_t PartI();
    std::int64_t PartII();

private:
    using BatteryBank = std::vector<char>;
    std::vector<BatteryBank> m_BatteryBanks;
};

} // namespace aoc

// ****************************************************************************************************************** //
// ** END OF FILE                                                                                                     //
// ****************************************************************************************************************** //

#endif // #ifndef AOC_CHALLENGE_03_HPP
