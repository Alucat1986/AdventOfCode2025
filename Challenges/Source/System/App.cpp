/**
 * @file
 * @author Alunya
 * @brief Contains the app class implementation.
 * @date 01.12.2025
 */

#include "App.hpp"

#include "../Challenges/Challenge01.hpp"
#include "../Debug/Debug.hpp"
#include "../UI/Menu.hpp"
#include "../Utils/ChallengeResult.hpp"

#include <cstdint>
#include <filesystem>
#include <iomanip>
#include <ios>
#include <iostream>
#include <limits>
#include <string>

namespace aoc {

/**
 * @brief Runs the main loop of the application.
 */
void App::Run()
{
    while (m_Running) {
        m_Menu.showMenu();
        std::cout << "Select a challenge: ";
        std::cin >> m_Input;
        std::cout << "\n\n";

        HandleUserInput();
    }
}

// ****************************************************************************************************************** //
//                                                      PRIVATE                                                       //
// ****************************************************************************************************************** //

/**
 * @brief Handles user input.
 */
void App::HandleUserInput()
{
    if (m_Input == 'q' || m_Input == 'Q') {
        m_Running = false;
        debug::logMessage("Exiting program...");
        return;
    }

    if (m_Input == 'n' || m_Input == 'N') {
        m_Menu.nextPage();
    }
    else if (m_Input == 'p' || m_Input == 'P') {
        m_Menu.previousPage();
    }
    else if (m_Input == 'r' || m_Input == 'R') {
        StartChallenge(m_Menu.getSelectedChallenge());
    }
    else if (m_Input >= '0' && m_Input <= '9') {
        m_Menu.selectChallenge(m_Input - '0');
    }

    m_Input = 'o';
}

/**
 * @brief Starts the selected challenge.
 * @param[in] challengeNumber The number of the challenge to start.
 */
void App::StartChallenge(std::uint16_t challengeNumber)
{
    std::string           tmpFile{"d"};
    std::filesystem::path path = "Data";
    if (challengeNumber < 10) {
        tmpFile += "0";
    }
    tmpFile += std::to_string(challengeNumber) + "_input.txt";
    path     = path / tmpFile;

    ChallengeResult result;

    switch (challengeNumber) {
        case 1: {
            Challenge01 challenge(path);
            result = challenge.RunChallenge();
            break;
        }
        case 2: {
            break;
        }
        case 3: {
            break;
        }
        default:
            debug::logMessage("Well I shouldn't be here, means this Challenge is not implemented yet.");
            break;
    }

    PrintResults(result);

    std::cout << "\nPress Enter to continue...\n";
    // "Flush" the leftover input from the previous call of std::cin
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
}

/**
 * @brief Prints the results of the challenge to the screen.
 * @param[in] result The results to be printed.
 */
void App::PrintResults(const ChallengeResult& result) const
{
    std::cout << "\n===========================================================\n";
    std::cout << std::left << std::setw(8) << "PartI:" << std::right << std::setw(10) << result.partI << std::left
              << std::setw(14) << "  Time of execution:" << std::right << std::setw(10)
              << std::chrono::duration_cast<std::chrono::microseconds>(result.executionTimePartI) << "\n";
    std::cout << std::left << std::setw(8) << "PartII:" << std::right << std::setw(10) << result.partII << std::left
              << std::setw(14) << "  Time of execution:" << std::right << std::setw(10)
              << std::chrono::duration_cast<std::chrono::microseconds>(result.executionTimePartII) << "\n";
    std::cout << "===========================================================\n";
}

} // namespace aoc
