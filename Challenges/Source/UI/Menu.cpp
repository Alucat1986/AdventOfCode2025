/**
 * @file
 * @author Alunya
 * @brief Contains the menu class implementation.
 * @date 01.12.2025
 */

#include "Menu.hpp"

#include "../Debug/Debug.hpp"

#include <cstdint>
#include <iostream>

namespace aoc {

/**
 * @brief Constructor.
 */
Menu::Menu()
        : mTotalPages((mTotalChallenges + mChallengesPerPage - 1u) / mChallengesPerPage)
{
}

/**
 * @brief Displays the console menu.
 */
void Menu::showMenu() const
{
    std::cout << "\033[H\033[J";
    std::cout << "=============================================================\n";
    std::cout << "==================== Advent of Code 2024 ====================\n";
    std::cout << "=============================================================\n";
    std::cout << "\n";
    std::cout << "=============== Next Page(n), Previous Page(p) ==============\n";
    std::cout << "=================  Run Challenge(r),Quit(q) =================\n";
    std::cout << "\n";
    displayChallenges();
    std::cout << "-------------------------------------------------------------\n";
    std::cout << "Page (" << mCurrentPage + 1 << "/" << mTotalPages << ") - ";
    std::cout << "Selected challenge: " << mSelectedChallenge << "\n";
    std::cout << "=============================================================\n";
}

/**
 * @brief Navigates to the next page.
 */
void Menu::nextPage()
{
    if (mCurrentPage < mTotalPages - 1) {
        mCurrentPage++;
    }
    else if (mCurrentPage == mTotalPages - 1) {
        mCurrentPage = 0;
    }
}

/**
 * @brief Navigates to the previous page.
 */
void Menu::previousPage()
{
    if (mCurrentPage > 0) {
        mCurrentPage--;
    }
    else if (mCurrentPage == 0) {
        mCurrentPage = static_cast<std::uint16_t>(mTotalPages - 1);
    }
}

/**
 * @brief Selects a challenge.
 * @param[in] challengeNumber The number of the challenge to select.
 * @return True if the challenge was selected successfully, false otherwise.
 */
bool Menu::selectChallenge(int challengeNumber)
{
    if (challengeNumber + (mCurrentPage * mChallengesPerPage) > mTotalChallenges - 1) {
        return false;
    }

    mSelectedChallenge = static_cast<std::uint16_t>(challengeNumber + (mCurrentPage * mChallengesPerPage) + 1);
    debug::logMessage("Selected challenge: ", mSelectedChallenge);
    return true;
}

/**
 * @brief Gets the currently selected challenge.
 * @return The currently selected challenge.
 */
std::uint16_t Menu::getSelectedChallenge() const
{
    return mSelectedChallenge;
}

/**
 * @brief Displays the challenges on the current page.
 */
void Menu::displayChallenges() const
{
    for (std::uint16_t i = 0; i < mChallengesPerPage && (mCurrentPage * mChallengesPerPage + i) < mTotalChallenges;
         ++i) {
        std::cout << i << ": Challenge " << (mCurrentPage * mChallengesPerPage + i + 1) << "\n";
    }
}

} // namespace aoc
