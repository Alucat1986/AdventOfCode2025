/**
 * @file
 * @brief Contains the Challenge05 class implementation.
 * @author Alunya
 * @date 05.12.2025
 */

// ****************************************************************************************************************** //
// ** DOCUMENTATION                                                                                                   //
// ****************************************************************************************************************** //

/**
 * @class aoc::Challenge05
 * @brief A class template.
 */

// ****************************************************************************************************************** //
// ** INCLUDES                                                                                                        //
// ****************************************************************************************************************** //

#include "Challenge05.hpp"

#include "BaseChallenge.hpp"
#include "../Utils/ChallengeResult.hpp"

#include <charconv>
#include <chrono>
#include <cstdint>
#include <format>
#include <fstream>
#include <iterator>
#include <print>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

// ****************************************************************************************************************** //
// ** HELPER                                                                                                          //
// ****************************************************************************************************************** //

template<>
struct std::formatter<aoc::ProductRange> : std::formatter<std::string_view> {
    constexpr auto parse(std::format_parse_context& ctx) { return ctx.begin(); }

    auto           format(const aoc::ProductRange& range, std::format_context& ctx) const
    {
        std::string temp{};
        std::format_to(std::back_inserter(temp), "R[{},{}]", range.From, range.Till);
        return std::formatter<std::string_view>::format(temp, ctx);
    }
};

// ****************************************************************************************************************** //
// ** IMPLEMENTATIONS                                                                                                 //
// ****************************************************************************************************************** //

namespace aoc {

// ****************************************************************************************************************** //
// ** PUBLIC                                                                                                          //
// ****************************************************************************************************************** //

/**
 * @brief Constructor.
 * @param[in] filePath The path to the input file.
 */
Challenge05::Challenge05(const std::filesystem::path& filePath)
        : BaseChallenge(filePath)
{
    if (!ReadFile()) {
        std::println("Challenge 05:: Initialisation failed: {} not loaded", m_FilePath.string());
        return;
    }

    std::println("Challenge 05:: Initialised with file: {}", m_FilePath.string());
}

/**
 * @brief Runs the challenge.
 * @return The result of the challenge including their execution times.
 */
ChallengeResult Challenge05::RunChallenge()
{
    const auto partOneStart      = std::chrono::system_clock::now();
    m_Result.partI               = PartI();
    const auto partOneEnd        = std::chrono::system_clock::now();
    m_Result.executionTimePartI  = std::chrono::duration_cast<std::chrono::microseconds>(partOneEnd - partOneStart);

    const auto partTwoStart      = std::chrono::system_clock::now();
    m_Result.partII              = PartII();
    const auto partTwoEnd        = std::chrono::system_clock::now();
    m_Result.executionTimePartII = std::chrono::duration_cast<std::chrono::microseconds>(partTwoEnd - partTwoStart);

    return m_Result;
}

// ****************************************************************************************************************** //
// ** PROTECTED                                                                                                       //
// ****************************************************************************************************************** //

/** Do some protected implementations here. */

// ****************************************************************************************************************** //
// ** PRIVATE                                                                                                         //
// ****************************************************************************************************************** //

/**
 * @brief Reads the input file and populates the left and right vectors.
 * @return true When the file was read successfully, otherwise false.
 */
bool Challenge05::ReadFile()
{
    std::ifstream fileToRead(m_FilePath);
    std::string   line{};

    if (!fileToRead.is_open()) {
        std::println("Failed to open {}...", m_FilePath.string());
        return false;
    }

    std::println("Reading file {}...", m_FilePath.string());
    bool products{false};
    while (std::getline(fileToRead, line)) {
        std::println("Line: \"{}\", Length({})", line, line.size());
        if (line.empty()) {
            products = true;
            continue;
        }

        if (products) {
            std::int64_t productID{};
            std::from_chars(line.data(), line.data() + line.size(), productID);
            // std::println("Adding {} to Products.", productID);
            m_Products.emplace_back(std::move(productID));
            continue;
        }

        ProductRange range{};
        std::size_t  pos = line.find_first_of("-");
        if (pos == std::string::npos) {
            std::println("No \"-\" found.");
            continue;
        }
        std::string from{line.substr(0, pos)};
        std::string till{line.substr(pos + 1)};
        std::from_chars(from.data(), from.data() + from.size(), range.From);
        std::from_chars(till.data(), till.data() + till.size(), range.Till);

        // std::println("Appending {} till {}.", range.From, range.Till);
        m_ProductRanges.emplace_back(std::move(range));
    }
    return true;
}

std::int64_t Challenge05::PartI()
{
    std::int64_t result{};

    for (const auto& product : m_Products) {
        if (IsProductFresh(product)) {
            result++;
        }
    }

    return result;
}

bool Challenge05::IsProductFresh(const std::int64_t productID) const
{
    for (const auto& range : m_ProductRanges) {
        if (productID < range.From || productID > range.Till) {
            continue;
        }

        return true;
    }
    return false;
}

std::int64_t Challenge05::PartII()
{
    std::int64_t result{};
    /** @note Uses way too much memory
    std::set<std::int64_t> freshProducts;

    for (const auto& range : m_ProductRanges) {
        std::println("Inserting Range {} - {}", range.From, range.Till);
        freshProducts.insert_range(std::ranges::views::iota(range.From, range.Till + 1));
    }

    result = static_cast<std::int64_t>(freshProducts.size());
    */

    PruneRanges();

    for (const auto& range : m_ProductRanges) {
        result += range.NumberOfElements();
        ;
    }

    return result;
}

void Challenge05::PruneRanges()
{
    bool mergeHappened{false};
    std::println("Pruning... {}", m_ProductRanges.size());
    do {
        mergeHappened = false;
        for (auto& rangeToPrune : m_ProductRanges) {
            if (rangeToPrune.IsZeroRange()) {
                continue;
            }
            for (auto& rangeToCheck : m_ProductRanges) {
                if (rangeToPrune == rangeToCheck) {
                    continue;
                }
                if (rangeToCheck.IsZeroRange()) {
                    continue;
                }
                if (rangeToPrune.From >= rangeToCheck.From && rangeToPrune.From <= rangeToCheck.Till) {
                    if (rangeToPrune.Till >= rangeToCheck.From && rangeToPrune.Till <= rangeToCheck.Till) {
                        std::println("Range {} within {}", rangeToPrune, rangeToCheck);
                        rangeToPrune  = {0, 0};
                        mergeHappened = true;
                        std::println("New Ranges {} and {}", rangeToPrune, rangeToCheck);
                        continue;
                    }

                    std::println("Range {} shortened because partially in {}", rangeToPrune, rangeToCheck);
                    rangeToCheck.Till = rangeToPrune.Till;
                    rangeToPrune      = {0, 0};
                    mergeHappened     = true;
                    std::println("New Ranges {} and {}", rangeToPrune, rangeToCheck);
                    continue;
                }
                else if (rangeToPrune.From < rangeToCheck.From &&
                         (rangeToPrune.Till >= rangeToCheck.From && rangeToPrune.Till <= rangeToCheck.Till)) {
                    std::println("Range {} shortened because partially in {}", rangeToPrune, rangeToCheck);
                    rangeToPrune.Till = rangeToCheck.Till;
                    rangeToCheck      = {0, 0};
                    mergeHappened     = true;
                    std::println("New Ranges {} and {}", rangeToPrune, rangeToCheck);
                    continue;
                }
            }
        }
    } while (mergeHappened);
    std::erase_if(m_ProductRanges, [](ProductRange range) { return range.IsZeroRange(); });
    std::println("Erased removed ranges! {}", m_ProductRanges.size());
}

} // namespace aoc

// ****************************************************************************************************************** //
// ** END OF FILE                                                                                                     //
// ****************************************************************************************************************** //
