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

#include <chrono>
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>

namespace aoc {

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
    std::string   line{};

    if (!fileToRead.is_open()) {
        std::cout << "Failed to open " << m_FilePath << " ...\n";
        return false;
    }

    std::cout << "Reading file " << m_FilePath << " ...\n\n";
    while (std::getline(fileToRead, line)) {
        debug::logMessage("Line read: ", line, " Length(", line.size(), "): ");

        /** @todo Do something. */
    }
    return true;
}

std::int64_t Challenge02::PartI()
{
    std::int64_t result{};

    return result;
}

std::int64_t Challenge02::PartII()
{
    std::int64_t result{};

    return result;
}

} // namespace aoc
