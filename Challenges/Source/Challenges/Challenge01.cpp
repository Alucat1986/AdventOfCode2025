/**
 * @file
 * @author Alunya
 * @brief Contains the day 01 challenge implementation.
 * @date 01.12.2025
 */

#include "Challenge01.hpp"

#include "BaseChallenge.hpp"
#include "../Debug/Debug.hpp"
#include "../Utils/ChallengeResult.hpp"

#include <chrono>
#include <cmath>
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <print>
#include <queue>
#include <string>

namespace aoc {

// ****************************************************************************************************************** //
//                                                      PUBLIC                                                        //
// ****************************************************************************************************************** //

/**
 * @brief Constructor.
 * @param[in] filePath The path to the input file.
 */
Challenge01::Challenge01(const std::filesystem::path& filePath)
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
ChallengeResult Challenge01::RunChallenge()
{
    const auto partOneStart     = std::chrono::system_clock::now();
    m_Result.partI              = PartI();
    const auto partOneEnd       = std::chrono::system_clock::now();
    m_Result.executionTimePartI = std::chrono::duration_cast<std::chrono::microseconds>(partOneEnd - partOneStart);

    m_Rotations                 = {};
    if (!ReadFile()) {
        debug::logMessage("Challenge 01:: Initialisation failed: File not loaded", m_FilePath);
    }
    m_CurrentNumber              = 50;

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
bool Challenge01::ReadFile()
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

        m_Rotations.emplace(line);
    }
    return true;
}

std::int64_t Challenge01::PartI()
{
    std::string  instruction{};
    std::int64_t zeroCount{};

    while (!m_Rotations.empty()) {
        instruction = m_Rotations.front();
        if (instruction.starts_with('R')) {
            RotateRightPI(std::stoi(instruction.substr(1)));
        }
        else if (instruction.starts_with('L')) {
            RotateLeftPI(std::stoi(instruction.substr(1)));
        }
        else {
            std::println("Unknown Instruction: {}", instruction);
        }

        if (m_CurrentNumber == 0) {
            zeroCount++;
        }

        m_Rotations.pop();
    }
    return zeroCount;
}

void Challenge01::RotateRightPI(std::int32_t amount)
{
    m_CurrentNumber += amount;
    m_CurrentNumber  = m_CurrentNumber % 100;
}

void Challenge01::RotateLeftPI(std::int32_t amount)
{
    m_CurrentNumber -= amount;
    while (m_CurrentNumber < 0) {
        m_CurrentNumber = 100 + m_CurrentNumber;
    }
}

std::int64_t Challenge01::PartII()
{
    std::string  instruction{};
    std::int64_t zeroClicks{};

    while (!m_Rotations.empty()) {
        instruction = m_Rotations.front();
        if (instruction.starts_with('R')) {
            zeroClicks += RotateRightPII(std::stoi(instruction.substr(1)));
        }
        else if (instruction.starts_with('L')) {
            zeroClicks += RotateLeftPII(std::stoi(instruction.substr(1)));
        }
        else {
            std::println("Unknown Instruction: {}", instruction);
        }

        m_StoppedOnZero = m_CurrentNumber == 0;

        m_Rotations.pop();
    }

    return zeroClicks;
}

std::int64_t Challenge01::RotateRightPII(std::int32_t amount)
{
    std::int64_t zeroClicks{};

    if (amount == 0) {
        std::println("Zero Moves! Right.");
        return zeroClicks;
    }

    m_CurrentNumber += amount;
    m_StoppedOnZero  = false;
    while (m_CurrentNumber > 99) {
        zeroClicks++;
        m_CurrentNumber -= 100;
    }

    return zeroClicks;
}

std::int64_t Challenge01::RotateLeftPII(std::int32_t amount)
{
    std::int64_t zeroClicks{};

    if (amount == 0) {
        std::println("Zero Moves! Left.");
        return zeroClicks;
    }

    m_CurrentNumber -= amount;
    while (m_CurrentNumber < 0) {
        m_CurrentNumber = 100 + m_CurrentNumber;
        if (m_StoppedOnZero) {
            m_StoppedOnZero = false;
            continue;
        }
        zeroClicks++;
    }

    if (m_CurrentNumber == 0) {
        zeroClicks++;
    }

    return zeroClicks;
}

} // namespace aoc
