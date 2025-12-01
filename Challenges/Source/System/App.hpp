/**
 * @file
 * @author Alunya
 * @brief Contains the app class declaration.
 * @date 01.12.2025
 */

#ifndef AOC_APP_HPP
#define AOC_APP_HPP

#include "../UI/Menu.hpp"
#include "../Utils/ChallengeResult.hpp"

#include <cstdint>

namespace aoc {

/**
 * @class App
 * @brief Manages the main loop and state of the program.
 *
 * The App class is responsible for managing the main loop and state of
 * the program. It initializes the menu, starts the corresponding challenges
 * and times them.
 */
class App {
public:
    void Run();

private:
    void HandleUserInput();
    void StartChallenge(std::uint16_t challengeNumber);
    void PrintResults(const ChallengeResult& result) const;

private:
    bool m_Running{true};
    char m_Input{'o'};

    Menu m_Menu;
};

} // namespace aoc

#endif // ifndef AOC_APP_HPP
