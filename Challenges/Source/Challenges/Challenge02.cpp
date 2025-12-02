/**
 * @file
 * @author Alunya
 * @brief Contains the day 02 challenge implementation.
 * @date 02.12.2025
 */

#include "Challenge02.hpp"

#include "BaseChallenge.hpp"
#include "../Debug/Debug.hpp"
#include "../Utils/ChallengeResult.hpp"

#include <charconv>
#include <chrono>
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <print>
#include <ranges>
#include <string>
#include <string_view>
#include <system_error>

namespace aoc {

// ****************************************************************************************************************** //
//                                                      HELPER                                                        //
// ****************************************************************************************************************** //

namespace {

bool IsInvalid(std::string_view id)
{
    bool invalid{false};
    if ((id.size() % 2) != 0) {
        return invalid;
    }

    std::size_t middle = id.size() / 2;
    if (id.substr(0, middle) == id.substr(middle)) {
        invalid = true;
    }

    // std::println("Cmp: {:>16}|{:<16} -> {:>5}", id.substr(0, middle), id.substr(middle), invalid);
    return invalid;
}

std::int64_t convertViewToInt(std::string_view viewToConvert)
{
    std::int64_t converted{};

    auto [ptr, ec] = std::from_chars(viewToConvert.data(), viewToConvert.data() + viewToConvert.size(), converted);
    if (ec == std::errc()) {
        return converted;
    }
    else if (ec == std::errc::invalid_argument) {
        std::println("This is not a number.");
        return 0;
    }
    else if (ec == std::errc::result_out_of_range) {
        std::println("This number is larger than an std::int64_t.");
        return 0;
    }
    return converted;
}

} // namespace

// ****************************************************************************************************************** //
//                                                      PUBLIC                                                        //
// ****************************************************************************************************************** //

/**
 * @brief Constructor.
 * @param[in] filePath The path to the input file.
 */
Challenge02::Challenge02(const std::filesystem::path& filePath)
        : BaseChallenge(filePath)
{
    if (!ReadFile()) {
        debug::logMessage("Challenge 01:: Initialisation failed: File not loaded", m_FilePath);
        return;
    }

    debug::logMessage("Challenge 01 initialised with file: ", m_FilePath);
}

/**
 * @brief Runs the challenge.
 * @return The result of the challenge including their execution times.
 */
ChallengeResult Challenge02::RunChallenge()
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
//                                                      PRIVATE                                                       //
// ****************************************************************************************************************** //

/**
 * @brief Reads the input file and populates the left and right vectors.
 * @return true When the file was read successfully, otherwise false.
 */
bool Challenge02::ReadFile()
{
    std::ifstream fileToRead(m_FilePath);

    if (!fileToRead.is_open()) {
        std::cout << "Failed to open " << m_FilePath << " ...\n";
        return false;
    }

    std::cout << "Reading file " << m_FilePath << " ...\n\n";
    while (std::getline(fileToRead, m_ProductRanges)) {
        debug::logMessage("Line read: ", m_ProductRanges, " Length(", m_ProductRanges.size(), ")");
    }
    return true;
}

std::int64_t Challenge02::PartI()
{
    std::int64_t result{};

    using std::operator""sv;
    for (const auto range : std::ranges::views::split(m_ProductRanges, ","sv)) {
        /** @todo Things happen in here. */
        std::string_view rangeView{range};
        std::size_t      posOfHyphen{rangeView.find_first_of('-')};
        std::string_view from{rangeView.substr(0, posOfHyphen)};
        std::string_view to{rangeView.substr(posOfHyphen + 1)};
        // std::println("Rng: {:^32}, Pos: {:>3}, From: {:>10}, To: {:>10}", rangeView, posOfHyphen, from, to);
        result += SumInvalidProductIDsOfRange(from, to);
        // std::println("Res: {:>16}", result);
    }

    return result;
}

std::int64_t Challenge02::SumInvalidProductIDsOfRange(const std::string_view fromView,
                                                      const std::string_view toView) const
{
    std::int64_t sumOfInvalidIDs{};

    if (fromView == toView) {
        sumOfInvalidIDs += convertViewToInt(fromView) * static_cast<std::int64_t>(IsInvalid(fromView));

        return sumOfInvalidIDs;
    }

    struct Range {
        const std::int64_t From{};
        const std::int64_t To{};
    };

    const Range range{convertViewToInt(fromView), convertViewToInt(toView)};

    for (std::int64_t current = range.From; current <= range.To; current++) {
        if (IsInvalid(std::to_string(current))) {
            sumOfInvalidIDs += current;
        }
        // std::println("Psm: {:>16}", sumOfInvalidIDs);
    }

    return sumOfInvalidIDs;
}

std::int64_t Challenge02::PartII()
{
    std::int64_t result{};

    return result;
}

} // namespace aoc
