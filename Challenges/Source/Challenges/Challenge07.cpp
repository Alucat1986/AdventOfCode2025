/**
 * @file
 * @brief Contains the Challenge07 class implementation.
 * @author Alunya
 * @date 07.12.2025
 */

// ****************************************************************************************************************** //
// ** DOCUMENTATION                                                                                                   //
// ****************************************************************************************************************** //

/**
 * @class aoc::Challenge07
 * @brief A class template.
 */

// ****************************************************************************************************************** //
// ** INCLUDES                                                                                                        //
// ****************************************************************************************************************** //

#include "Challenge07.hpp"

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
Challenge07::Challenge07(const std::filesystem::path& filePath)
        : BaseChallenge(filePath)
{
    if (!ReadFile()) {
        std::println("Challenge 07:: Initialisation failed: {} not loaded", m_FilePath.string());
        return;
    }

    std::println("Challenge 07:: Initialised with file: {}", m_FilePath.string());
}

/**
 * @brief Runs the challenge.
 * @return The result of the challenge including their execution times.
 */
ChallengeResult Challenge07::RunChallenge()
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
bool Challenge07::ReadFile()
{
    std::ifstream fileToRead(m_FilePath);
    std::string   line{};

    if (!fileToRead.is_open()) {
        std::println("Failed to open {}...", m_FilePath.string());
        return false;
    }

    std::println("Reading file {}...", m_FilePath.string());
    while (std::getline(fileToRead, line)) {
        std::println("Line: \"{}\", Length({})", line, line.size());
    }
    return true;
}

std::int64_t Challenge07::PartI()
{
    std::int64_t result{};

    return result;
}

std::int64_t Challenge07::PartII()
{
    std::int64_t result{};

    return result;
}

} // namespace aoc

// ****************************************************************************************************************** //
// ** END OF FILE                                                                                                     //
// ****************************************************************************************************************** //
