/**
 * @file
 * @brief Contains the Challenge03 class implementation.
 * @author Alunya
 * @date 03.12.2025
 */

// ****************************************************************************************************************** //
// ** DOCUMENTATION                                                                                                   //
// ****************************************************************************************************************** //

/**
 * @class aoc::Challenge03
 * @brief A class template.
 */

// ****************************************************************************************************************** //
// ** INCLUDES                                                                                                        //
// ****************************************************************************************************************** //

#include "Challenge03.hpp"

#include "BaseChallenge.hpp"
#include "../Utils/ChallengeResult.hpp"

#include <algorithm>
#include <chrono>
#include <cstdint>
#include <fstream>
#include <iterator>
#include <print>
#include <string>
#include <utility>
#include <vector>

// ****************************************************************************************************************** //
// ** PUBLIC                                                                                                          //
// ****************************************************************************************************************** //

namespace aoc {

/**
 * @brief Constructor.
 * @param[in] filePath The path to the input file.
 */
Challenge03::Challenge03(const std::filesystem::path& filePath)
        : BaseChallenge(filePath)
{
    if (!ReadFile()) {
        std::println("Challenge 03:: Initialisation failed: {} not loaded", m_FilePath.string());
        return;
    }

    std::println("Challenge 03 initialised with file: {}", m_FilePath.string());
}

/**
 * @brief Runs the challenge.
 * @return The result of the challenge including their execution times.
 */
ChallengeResult Challenge03::RunChallenge()
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
bool Challenge03::ReadFile()
{
    std::ifstream fileToRead(m_FilePath);
    std::string   line{};
    m_BatteryBanks.clear();
    m_BatteryBanks.reserve(200);

    if (!fileToRead.is_open()) {
        std::println("Failed to open {}...", m_FilePath.string());
        return false;
    }

    std::println("Reading file {}...", m_FilePath.string());
    while (std::getline(fileToRead, line)) {
        std::println("Line: \"{}\", Length({})", line, line.size());
        BatteryBank batteries;

        for (const auto& letter : line) {
            batteries.emplace_back(letter);
        }

        m_BatteryBanks.emplace_back(std::move(batteries));
        // std::println("Added: {}.", m_BatteryBanks.back());
    }
    return true;
}

std::int64_t Challenge03::PartI()
{
    std::int64_t result{};

    for (const auto& batteries : m_BatteryBanks) {
        auto maxIter    = std::ranges::max_element(batteries.begin(), std::prev(batteries.end(), 1));
        auto secondIter = std::ranges::max_element(std::next(maxIter, 1), batteries.end());

        std::println("Max: {}{}", *maxIter, *secondIter);
        std::int64_t number =
            static_cast<std::int64_t>(*maxIter - '0') * 10 + static_cast<std::int64_t>(*secondIter - '0');
        result += number;
        std::println("Result: {}", result);
    }

    return result;
}

std::int64_t Challenge03::PartII()
{
    std::int64_t result{};
    std::int64_t number{};

    for (const auto& batteries : m_BatteryBanks) {
        std::int64_t digit{100'000'000'000};

        std::println("Bank: {}", batteries);
        auto iter  = std::ranges::max_element(batteries.begin(), std::prev(batteries.end(), 11));
        number    += (*iter - '0') * digit;

        for (std::size_t i = 11; i > 0; i--) {
            digit  /= 10;
            iter    = std::ranges::max_element(std::next(iter, 1),
                                               std::prev(batteries.end(), static_cast<std::ptrdiff_t>(i - 1)));

            number += (*iter - '0') * digit;
            std::println("Max {}: {}", i, number);
        }

        result += number;
        number  = 0;
        std::println("Result: {}", result);
    }

    return result;
}

} // namespace aoc

// ****************************************************************************************************************** //
// ** END OF FILE                                                                                                     //
// ****************************************************************************************************************** //
