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

#include <chrono>
#include <cstdint>
#include <fstream>
#include <print>
#include <stack>
#include <string>
#include <unordered_map>
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
        m_ManifoldSize.Width = static_cast<std::int64_t>(line.size());
        if (line.contains("S")) {
            m_StartPosition.X = static_cast<std::int64_t>(line.find_first_of("S"));
            m_StartPosition.Y = m_ManifoldSize.Height;
        }

        m_ManifoldSize.Height++;
        m_TachyonManifold.insert_range(m_TachyonManifold.end(), line);
    }
    return true;
}

std::int64_t Challenge07::PartI()
{
    std::int64_t                          result{};

    std::stack<Position>                  beams;
    std::unordered_map<std::size_t, bool> visited;

    beams.push(m_StartPosition);

    std::println("Part I starts...");

    while (!beams.empty()) {
        Position beam{beams.top()};
        beams.pop();

        // std::println("Beam at ({}|{}).", beam.X, beam.Y);

        if (beam.X < 0 || beam.X > m_ManifoldSize.Width - 1) {
            continue;
        }
        if (visited.contains(beam.ToIndex(m_ManifoldSize))) {
            continue;
        }

        visited.emplace(beam.ToIndex(m_ManifoldSize), true);
        beam = beam.Advance();
        if (beam.Y > m_ManifoldSize.Height - 1) {
            continue;
        }

        if (m_TachyonManifold.at(beam.ToIndex(m_ManifoldSize)) == '^') {
            beams.push({beam.X - 1, beam.Y});
            beams.push({beam.X + 1, beam.Y});
            result++;
        }
        else {
            beams.push(beam);
        }
    }

    return result;
}

std::int64_t Challenge07::PartII()
{
    std::int64_t result{};

    std::println("Part II starts...");
    // Maybe something like, going down the tree from S, counting the amount of Paths a path has at anytime, for example
    // the pathCount would be 1 until the first splitter, then it splits into 2 paths with each having only 1 pathCount,
    // but when they reach a splitter again where a merge happens the newly splitted path would be prevPath + prevPath.
    // e.g.:
    // .....1.....
    // ....1^1....
    // ...1^2^1...
    // ...12^3^1..

    return result;
}

} // namespace aoc

// ****************************************************************************************************************** //
// ** END OF FILE                                                                                                     //
// ****************************************************************************************************************** //
