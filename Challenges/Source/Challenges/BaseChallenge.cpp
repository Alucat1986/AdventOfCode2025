/**
 * @file
 * @author Alunya
 * @brief Contains the abstract base challenge class implementation.
 * @date 01.12.2025
 */

#include "BaseChallenge.hpp"

#include <chrono>
#include <filesystem>

namespace aoc {

// ****************************************************************************************************************** //
//                                                      PUBLIC                                                        //
// ****************************************************************************************************************** //

/**
 * @brief Constructor.
 * @param[in] filePath The path to the input file.
 */
BaseChallenge::BaseChallenge(const std::filesystem::path& filePath)
        : m_Result({0, 0, std::chrono::microseconds(0), std::chrono::microseconds(0)})
        , m_FilePath(filePath)
{
}

// ****************************************************************************************************************** //
//                                                       END                                                          //
// ****************************************************************************************************************** //

} // namespace aoc
