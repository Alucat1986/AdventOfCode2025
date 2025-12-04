/**
 * @file
 * @brief Contains the Challenge04 class declaration.
 * @author Alunya
 * @date 04.12.2025
 */

#ifndef AOC_CHALLENGE_04_HPP
#define AOC_CHALLENGE_04_HPP

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

class Challenge04 : public BaseChallenge {
public:
    Challenge04(const std::filesystem::path& filePath);

    ChallengeResult RunChallenge() override;

private:
    bool         ReadFile() override;
    std::int64_t PartI();
    std::int64_t FindNeighbours(const std::int64_t currentRow, const std::int64_t currentColumn) const;
    std::int64_t PartII();
    void         PrintWarehouse() const;

private:
    std::vector<char> m_Warehouse;
    std::int64_t      m_Width{};
    std::int64_t      m_Height{};
};

} // namespace aoc

// ****************************************************************************************************************** //
// ** END OF FILE                                                                                                     //
// ****************************************************************************************************************** //

#endif // #ifndef AOC_CHALLENGE_04_HPP
