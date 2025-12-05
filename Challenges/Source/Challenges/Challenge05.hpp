/**
 * @file
 * @brief Contains the Challenge05 class declaration.
 * @author Alunya
 * @date 05.12.2025
 */

#ifndef AOC_CHALLENGE_05_HPP
#define AOC_CHALLENGE_05_HPP

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

struct ProductRange {
    std::int64_t From{};
    std::int64_t Till{};

    bool         IsZeroRange() const { return From == 0 && Till == 0; }

    std::int64_t NumberOfElements() const
    {
        if (Till >= From) {
            return Till - From + 1;
        }
        else {
            return From - Till + 1;
        }
    }

    bool operator==(ProductRange& other) { return From == other.From && Till == other.Till; }
};

class Challenge05 : public BaseChallenge {
public:
    Challenge05(const std::filesystem::path& filePath);

    ChallengeResult RunChallenge() override;

private:
    bool         ReadFile() override;
    std::int64_t PartI();
    bool         IsProductFresh(const std::int64_t productID) const;
    std::int64_t PartII();
    void         PruneRanges();
    void         MergeRanges();
    void         CleanRanges();

private:
    std::vector<ProductRange> m_ProductRanges;
    std::vector<std::int64_t> m_Products;
};

} // namespace aoc

// ****************************************************************************************************************** //
// ** END OF FILE                                                                                                     //
// ****************************************************************************************************************** //

#endif // #ifndef AOC_CHALLENGE_05_HPP
