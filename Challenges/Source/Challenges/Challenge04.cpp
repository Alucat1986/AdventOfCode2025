/**
 * @file
 * @brief Contains the Challenge04 class implementation.
 * @author Alunya
 * @date 04.12.2025
 */

// ****************************************************************************************************************** //
// ** DOCUMENTATION                                                                                                   //
// ****************************************************************************************************************** //

/**
 * @class aoc::Challenge04
 * @brief A class template.
 */

// ****************************************************************************************************************** //
// ** INCLUDES                                                                                                        //
// ****************************************************************************************************************** //

#include "Challenge04.hpp"

#include "BaseChallenge.hpp"
#include "../Utils/ChallengeResult.hpp"

#include <chrono>
#include <cstdint>
#include <fstream>
#include <print>
#include <string>
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
Challenge04::Challenge04(const std::filesystem::path& filePath)
        : BaseChallenge(filePath)
{
    if (!ReadFile()) {
        std::println("Challenge 04:: Initialisation failed: {} not loaded", m_FilePath.string());
        return;
    }

    std::println("Challenge 04:: Initialised with file: {}", m_FilePath.string());
}

/**
 * @brief Runs the challenge.
 * @return The result of the challenge including their execution times.
 */
ChallengeResult Challenge04::RunChallenge()
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
bool Challenge04::ReadFile()
{
    std::ifstream fileToRead(m_FilePath);
    std::string   line{};

    if (!fileToRead.is_open()) {
        std::println("Failed to open {}...", m_FilePath.string());
        return false;
    }

    std::println("Reading file {}...", m_FilePath.string());

    std::int64_t rows{};
    while (std::getline(fileToRead, line)) {
        std::println("Line: \"{}\", Length({})", line, line.size());
        rows++;
        for (const auto letter : line) {
            m_Warehouse.emplace_back(letter);
        }
    }
    m_Width  = static_cast<std::int64_t>(line.size());
    m_Height = rows;
    return true;
}

std::int64_t Challenge04::PartI()
{
    std::int64_t result{};

    PrintWarehouse();
    for (std::int64_t row{}; row < m_Height; row++) {
        for (std::int64_t column{}; column < m_Width; column++) {
            std::size_t index = static_cast<std::size_t>(row * m_Width + column);
            if (m_Warehouse.at(index) == '.') {
                continue;
            }
            std::int64_t neighbours{FindNeighbours(row, column)};
            std::println("({}/{}) has {} neighbours.", column, row, neighbours);
            if (neighbours < 4) {
                result++;
            }
        }
    }

    return result;
}

std::int64_t Challenge04::FindNeighbours(const std::int64_t currentRow, const std::int64_t currentColumn) const
{
    std::int64_t neighbours{};

    for (std::int64_t row{currentRow - 1}; row <= currentRow + 1; row++) {
        if (row < 0 || row >= m_Height) {
            continue;
        }
        for (std::int64_t column{currentColumn - 1}; column <= currentColumn + 1; column++) {
            if ((column < 0 || column >= m_Width) || (row == currentRow && column == currentColumn)) {
                continue;
            }

            std::size_t index = static_cast<std::size_t>(row * m_Width + column);
            if (m_Warehouse.at(index) == '@') {
                neighbours++;
                // std::println("({}/{}) neighbour at ({}/{})", currentColumn, currentRow, column, row);
            }
        }
    }

    return neighbours;
}

std::int64_t Challenge04::PartII()
{
    std::int64_t result{};
    bool         paperRemoved{false};

    PrintWarehouse();
    do {
        paperRemoved = false;
        for (std::int64_t row{}; row < m_Height; row++) {
            for (std::int64_t column{}; column < m_Width; column++) {
                std::size_t index = static_cast<std::size_t>(row * m_Width + column);
                if (m_Warehouse.at(index) == '.' || m_Warehouse.at(index) == 'x') {
                    continue;
                }
                std::int64_t neighbours{FindNeighbours(row, column)};
                std::println("({}/{}) has {} neighbours.", column, row, neighbours);
                if (neighbours < 4) {
                    m_Warehouse.at(index) = 'x';
                    paperRemoved          = true;
                    result++;
                }
            }
        }
    } while (paperRemoved);

    return result;
}

void Challenge04::PrintWarehouse() const
{
    for (std::int64_t row{}; row < m_Height; row++) {
        for (std::int64_t column{}; column < m_Width; column++) {
            std::size_t index = static_cast<std::size_t>(row * m_Width + column);
            std::print("{}", m_Warehouse.at(index));
        }
        std::println();
    }
}

} // namespace aoc

// ****************************************************************************************************************** //
// ** END OF FILE                                                                                                     //
// ****************************************************************************************************************** //
