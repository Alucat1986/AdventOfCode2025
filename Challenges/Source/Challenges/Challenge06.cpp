/**
 * @file
 * @brief Contains the Challenge06 class implementation.
 * @author Alunya
 * @date 06.12.2025
 */

// ****************************************************************************************************************** //
// ** DOCUMENTATION                                                                                                   //
// ****************************************************************************************************************** //

/**
 * @class aoc::Challenge06
 * @brief A class template.
 */

// ****************************************************************************************************************** //
// ** INCLUDES                                                                                                        //
// ****************************************************************************************************************** //

#include "Challenge06.hpp"

#include "BaseChallenge.hpp"
#include "../Utils/ChallengeResult.hpp"

#include <algorithm>
#include <charconv>
#include <chrono>
#include <cstdint>
#include <fstream>
#include <functional>
#include <iterator>
#include <print>
#include <string>
#include <unordered_map>
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
Challenge06::Challenge06(const std::filesystem::path& filePath)
        : BaseChallenge(filePath)
{
    if (!ReadFile()) {
        std::println("Challenge 06:: Initialisation failed: {} not loaded", m_FilePath.string());
        return;
    }

    std::println("Challenge 06:: Initialised with file: {}", m_FilePath.string());
}

/**
 * @brief Runs the challenge.
 * @return The result of the challenge including their execution times.
 */
ChallengeResult Challenge06::RunChallenge()
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
bool Challenge06::ReadFile()
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

        std::size_t posOfNum   = line.find_first_not_of(' ');
        std::size_t posOfSpace = line.find_first_of(' ');

        if (posOfNum > posOfSpace) {
            line       = line.substr(posOfNum);
            posOfSpace = line.find_first_of(' ');
        }

        std::size_t problemCounter{};
        while (posOfNum != std::string::npos) {
            if (line.contains("+") || line.contains("*")) {
                // Ugly, but I don't know else currently.
                if (posOfSpace == std::string::npos && posOfNum == 0) {
                    break;
                }

                m_Operands.emplace_back(line[posOfNum]);

                if (posOfSpace != std::string::npos) {
                    line = line.substr(posOfSpace);
                }
                posOfNum = line.find_first_not_of(' ');
                if (posOfNum != std::string::npos) {
                    line = line.substr(posOfNum);
                }
                posOfSpace = line.find_first_of(' ');
                posOfNum   = line.find_first_not_of(' ');
                continue;
            }
            std::int64_t num{};
            std::string  temp{line.substr(0, posOfSpace)};
            std::from_chars(temp.data(), temp.data() + temp.size(), num);

            // Ugly, but I don't know else currently.
            if (posOfSpace == std::string::npos && posOfNum == 0) {
                break;
            }

            m_Problems[problemCounter].emplace_back(num);
            problemCounter++;

            if (posOfSpace != std::string::npos) {
                line = line.substr(posOfSpace);
            }
            posOfNum = line.find_first_not_of(' ');
            if (posOfNum != std::string::npos) {
                line = line.substr(posOfNum);
            }
            posOfSpace = line.find_first_of(' ');
        }
    }
    return true;
}

std::int64_t Challenge06::PartI()
{
    std::int64_t result{};

    for (auto& [index, range] : m_Problems) {
        if (m_Operands[index] == '+') {
            std::int64_t temp = std::ranges::fold_left_first(range, std::plus()).value();
            std::println("{} = {}, {}", temp, range, m_Operands[index]);
            result += std::ranges::fold_left_first(range, std::plus()).value();
        }
        else if (m_Operands[index] == '*') {
            std::int64_t temp = std::ranges::fold_left_first(range, std::multiplies()).value();
            std::println("{} = {}, {}", temp, range, m_Operands[index]);
            result += std::ranges::fold_left_first(range, std::multiplies()).value();
        }
        std::println("Result {}", result);
    }

    return result;
}

std::int64_t Challenge06::PartII()
{
    std::int64_t result{};

    return result;
}

} // namespace aoc

// ****************************************************************************************************************** //
// ** END OF FILE                                                                                                     //
// ****************************************************************************************************************** //
