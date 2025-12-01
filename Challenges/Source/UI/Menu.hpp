/**
 * @file
 * @author Alunya
 * @brief Contains the menu class declaration.
 * @date 01.12.2025
 */

#ifndef AOC_MENU_HPP
#define AOC_MENU_HPP

#include <cstdint>

namespace aoc {

/**
 * @class Menu
 * @brief Manages the console menu.
 */
class Menu {
public:
    Menu();
    ~Menu() = default;

    void          showMenu() const;
    void          nextPage();
    void          previousPage();
    bool          selectChallenge(int challengeNumber);
    std::uint16_t getSelectedChallenge() const;

private:
    void displayChallenges() const;

private:
    std::uint16_t       mCurrentPage{0};
    std::uint16_t       mSelectedChallenge{1};
    const std::uint16_t mChallengesPerPage{10};
    const std::uint16_t mTotalChallenges{12};
    const std::uint16_t mTotalPages;
}; // class Menu

} // namespace aoc

#endif // ifndef AOC_MENU_HPP
