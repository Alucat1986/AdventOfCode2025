/**
 * @file
 * @brief Contains the Challenge06 class declaration.
 * @author Alunya
 * @date 06.12.2025
 */

#ifndef AOC_CHALLENGE_06_HPP
#define AOC_CHALLENGE_06_HPP

// ****************************************************************************************************************** //
// ** INCLUDES                                                                                                        //
// ****************************************************************************************************************** //

#include "BaseChallenge.hpp"
#include "../Utils/ChallengeResult.hpp"

#include <cstdint>
#include <filesystem>
#include <string>
#include <unordered_map>
#include <vector>

// ****************************************************************************************************************** //
// ** DECLARATIONS                                                                                                    //
// ****************************************************************************************************************** //

namespace aoc {

class Challenge06 : public BaseChallenge {
public:
    Challenge06(const std::filesystem::path& filePath);

    ChallengeResult RunChallenge() override;

private:
    bool         ReadFile() override;
    std::int64_t PartI();
    std::int64_t PartII();

private:
    std::unordered_map<std::size_t, std::vector<std::int64_t>> m_ProblemsOne;
    std::vector<std::string>                                   m_ProblemsTwo;
    std::vector<char>                                          m_Operands;
};

} // namespace aoc

// ****************************************************************************************************************** //
// ** END OF FILE                                                                                                     //
// ****************************************************************************************************************** //

#endif // #ifndef AOC_CHALLENGE_06_HPP
