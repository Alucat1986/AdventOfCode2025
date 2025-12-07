/**
 * @file
 * @brief Contains the Challenge07 class declaration.
 * @author Alunya
 * @date 07.12.2025
 */

#ifndef AOC_CHALLENGE_07_HPP
#define AOC_CHALLENGE_07_HPP

// ****************************************************************************************************************** //
// ** INCLUDES                                                                                                        //
// ****************************************************************************************************************** //

#include "BaseChallenge.hpp"
#include "../Utils/ChallengeResult.hpp"

#include <cstdint>
#include <filesystem>
#include <utility>
#include <vector>

// ****************************************************************************************************************** //
// ** DECLARATIONS                                                                                                    //
// ****************************************************************************************************************** //

namespace aoc {

class Challenge07 : public BaseChallenge {
public:
    Challenge07(const std::filesystem::path& filePath);

    ChallengeResult RunChallenge() override;

private:
    bool         ReadFile() override;
    std::int64_t PartI();
    std::int64_t PartII();

private:
    struct Size {
        std::int64_t Width{};
        std::int64_t Height{};
    };

    struct Position {
        std::int64_t X{};
        std::int64_t Y{};

        Position     Advance() const { return {X, Y + 1}; }

        std::size_t  ToIndex(const Size& size) const { return static_cast<std::size_t>(Y * size.Width + X); }
    };

    std::vector<char> m_TachyonManifold;
    Size              m_ManifoldSize{};
    Position          m_StartPosition{};
};

} // namespace aoc

// ****************************************************************************************************************** //
// ** END OF FILE                                                                                                     //
// ****************************************************************************************************************** //

#endif // #ifndef AOC_CHALLENGE_07_HPP
