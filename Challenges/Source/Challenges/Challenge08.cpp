/**
 * @file
 * @brief Contains the Challenge08 class implementation.
 * @author Alunya
 * @date 08.12.2025
 */

// ****************************************************************************************************************** //
// ** DOCUMENTATION                                                                                                   //
// ****************************************************************************************************************** //

/**
 * @class aoc::Challenge08
 * @brief A class template.
 */

// ****************************************************************************************************************** //
// ** INCLUDES                                                                                                        //
// ****************************************************************************************************************** //

#include "Challenge08.hpp"

#include "BaseChallenge.hpp"
#include "../Utils/ChallengeResult.hpp"

#include <algorithm>
#include <charconv>
#include <chrono>
#include <cmath>
#include <cstdint>
#include <filesystem>
#include <format>
#include <fstream>
#include <functional>
#include <iterator>
#include <print>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

// ****************************************************************************************************************** //
// ** HELPER                                                                                                          //
// ****************************************************************************************************************** //

// https://www.cppstories.com/2022/custom-stdformat-cpp20/
template<>
struct std::formatter<aoc::Vec3> : std::formatter<std::string_view> {
    constexpr auto parse(std::format_parse_context& ctx) { return ctx.begin(); }

    auto           format(const aoc::Vec3& vec, std::format_context& ctx) const
    {
        std::string temp{};
        std::format_to(std::back_inserter(temp), "V({:>6}, {:>6}, {:>6})", vec.X, vec.Y, vec.Z);
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

bool Vec3::operator==(const Vec3& other) const
{
    return X == other.X && Y == other.Y && Z == other.Z;
}

bool Pair::IsSame(const Pair& other) const
{
    bool sameFirst  = First == other.First || First == other.Second;
    bool sameSecond = Second == other.First || Second == other.Second;
    bool sameDist   = Distance == other.Distance;
    return sameFirst && sameSecond && sameDist;
}

float euclideanDistance(const Vec3& first, const Vec3& second)
{
    float distX = static_cast<float>(first.X - second.X);
    float distY = static_cast<float>(first.Y - second.Y);
    float distZ = static_cast<float>(first.Z - second.Z);
    return std::sqrtf((distX * distX) + (distY * distY) + (distZ * distZ));
}

/**
 * @brief Constructor.
 * @param[in] filePath The path to the input file.
 */
Challenge08::Challenge08(const std::filesystem::path& filePath)
        : BaseChallenge(filePath)
{
    if (!ReadFile()) {
        std::println("Challenge 08:: Initialisation failed: {} not loaded", m_FilePath.string());
        return;
    }

    std::println("Challenge 08:: Initialised with file: {}", m_FilePath.string());
}

/**
 * @brief Runs the challenge.
 * @return The result of the challenge including their execution times.
 */
ChallengeResult Challenge08::RunChallenge()
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
bool Challenge08::ReadFile()
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

        Vec3        box{};
        std::size_t comma = line.find_first_of(',');
        std::from_chars(line.data(), line.data() + comma, box.X);
        line  = line.substr(comma + 1);
        comma = line.find_first_of(',');
        std::from_chars(line.data(), line.data() + comma, box.Y);
        line = line.substr(comma + 1);
        std::from_chars(line.data(), line.data() + line.size(), box.Z);

        m_JunctionBoxes.emplace_back(std::move(box));
    }
    return true;
}

std::int64_t Challenge08::PartI()
{
    std::int64_t      result{};
    std::vector<Pair> pairs;
    for (auto& boxOne : m_JunctionBoxes) {
        for (auto& boxTwo : m_JunctionBoxes) {
            if (&boxOne == &boxTwo) {
                continue;
            }
            Pair newPair{boxOne, boxTwo, euclideanDistance(boxOne, boxTwo)};
            bool alreadyIn{false};
            for (auto& pair : pairs) {
                if (pair.IsSame(newPair)) {
                    alreadyIn = true;
                    break;
                }
            }
            if (!alreadyIn) {
                pairs.emplace_back(std::move(newPair));
            }
        }
    }

    std::ranges::sort(pairs, std::ranges::less{}, &Pair::Distance);

    for (const auto& pair : pairs) {
        std::println("Distance {} to {} -> {:8.2f}", pair.First, pair.Second, pair.Distance);
    }

    for (const auto& pair : pairs) {
        for (const auto& circuit : m_Circuits) {
            // if (std::ranges::find_if(circuit, pair.First)) {}
        }
    }

    return result;
}

std::int64_t Challenge08::PartII()
{
    std::int64_t result{};

    return result;
}

} // namespace aoc

// ****************************************************************************************************************** //
// ** END OF FILE                                                                                                     //
// ****************************************************************************************************************** //
