/**
 * @file
 * @author Alunya
 * @brief Contains the abstract base challenge class declaration.
 * @date 01.12.2025
 */

#ifndef AOC_BASECHALLENGE_HPP
#define AOC_BASECHALLENGE_HPP

#include "../Utils/ChallengeResult.hpp"

#include <filesystem>

namespace aoc {

/**
 * @class BaseChallenge
 * @brief Abstract class for challenges.
 *
 * The BaseChallenge class serves as a blueprint for all challenge implementations.
 * It provides a common interface and shared functionality for reading input files,
 * running challenges, and storing results.
 */
class BaseChallenge {
public:
    BaseChallenge(const std::filesystem::path& filePath);

    virtual ChallengeResult RunChallenge() = 0;

protected:
    virtual bool ReadFile() = 0;

protected:
    ChallengeResult             m_Result;
    const std::filesystem::path m_FilePath;
};

} // namespace aoc

#endif // ifndef AOC_BASECHALLENGE_HPP
