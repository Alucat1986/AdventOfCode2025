/**
 * @file
 * @brief Main entry point for the Advent of Code 2025 Challenges.
 * @author Alunya
 * @date 01.12.2025
 *
 * For includeguards I will use the abbrevation AOC for Advent of Code as a prefix. For example: AOC_SOMETHING_HPP
 * Headerfiles have the suffix .hpp, source files .cpp.
 * A little naming and coding convention:
 * - Main namespace will be as the prefix for includeguards, here: namespace aoc
 * - Classes, Structs, Enums, Typedefs: PascalCase
 * - Public Member: PascalCase
 * - Private Member: m_PascalCase
 * - Methods: PascalCase(), Setter/Getter: Set-/PascalCase() [int m_HP;-> void SetHP(int hp); int HP() const;]
 * - Variables, Functions: camelCase
 * - Constants: ALL_CAPS_WITH_UNDERSCORES
 *
 * Doxygen is used for documentation:
 * - Public accessible methods and classes/structs are required to have documentation
 * - Private ones are not required, only if the developer thinks they need explanation
 * - Each file should have a header documentation block
 *
 * This project uses C++23.
 */

// ****************************************************************************************************************** //
// ** DOCUMENTATION                                                                                                   //
// ****************************************************************************************************************** //

/**
 * @namespace aoc
 * @brief It's the Advent of Code 2025 main namespace.
 */

// ****************************************************************************************************************** //
// ** INCLUDES                                                                                                        //
// ****************************************************************************************************************** //

#include "../System/App.hpp"

// ****************************************************************************************************************** //
// ** MAIN                                                                                                            //
// ****************************************************************************************************************** //

/**
 * @brief C++ main function.
 * @param[in] argc Argument count.
 * @param[in] argv Argument values.
 */
int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[])
{
    aoc::App app;
    app.Run();
} // int main(...)

// ****************************************************************************************************************** //
// ** END OF FILE                                                                                                     //
// ****************************************************************************************************************** //
