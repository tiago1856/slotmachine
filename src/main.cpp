/************************************************************************
 *
 *
 * Main game file
 *
 * NOTES:
 *      1 - use Makefile to compile: game
 *      2 - C++11 required
 *      3 - game configuration in config.h
 *
 ************************************************************************/

#include <iostream>
#include <memory>
#include <ctime>
#include <stdexcept>
#include <iomanip>


#include "config.h"
#include "cylinder.h"
#include "slotmachine.h"


const static char* FILENAME_RESULTS = "results.txt";


//
/**
 * String to integer conversion.
 *
 * @param in String reference to be converted.
 * @param out Int reference that will hold the converted value.
 * @return true if the conversion was successful else false.
 */
bool Parse(std::string& in, int& out) {
    try{
        out = std::stoi(in);
    } catch (std::invalid_argument) {
        return false;
    }
    return true;
}

/**
 * Slotmachine game.
 *
 *
 * If bet < 1 => bet = 1
 * If bet > 10 => bet = 10
 *
 * @param init_wallet Starting credit.
 * @param showLastResults If true after each play,the last five results will be displayed.
 * @param saveLastResults If true after end game,the last five results will be saved in a
 *        textfile, specified by FILENAME_RESULTS
 * @return whatever credit remains.
 */
int GameOn(int init_wallet, bool showLastResults = false, bool saveLastResults = false)
{
    std::unique_ptr<SlotMachine> slotmachine(new SlotMachine);

    int wallet = init_wallet;

    std::cout << "*** FMQ SLOT MACHINE ***" << std::endl;
    std::cout << "Wallet: " << wallet << std::endl;

    int bet = 0;
    bool exit = false;
    std::string str_bet;
    do {
        // bet with input validation
        do {
            std::cout << "Bet (1 to 10) -> ";
            std::cin >> str_bet;
        } while (!Parse(str_bet, bet));

        bet = slotmachine->setBet(bet);
        wallet -= bet;
        // bet validation - if not enough money then bet the difference
        if (wallet < 0){
            wallet = 0;
            bet = slotmachine->setBet(wallet-bet);
        }

        std::cout << std::endl;

        slotmachine->play();

        std::cout << "Resultado: " << slotmachine->getOutcomeStr() << std::endl;
        std::cout << "Prize: " << slotmachine->getWinnings();
        if (slotmachine->hasWon())
        {
            wallet += slotmachine->getWinnings();
            std::cout << " (" << slotmachine->getPrizeValue()
                    <<" X " << slotmachine->getBet() << ")";
        }
        std::cout << std::endl;
        std::cout << "Wallet: " << wallet << std::endl << std::endl;

        if (wallet <= 0)
        {
            std::cout << "You have no more money." << std::endl;
            std::cout << "Get some and get back ASAP!" << std::endl;
            break;
        }

        // show the last MEMORY_LIST_SIZE results?
        if (showLastResults)
        {
            std::cout << std::endl << "Last results:" << std::endl;
            std::cout << std::setw(10) << "SYMBOLS"
                        << std::setw(10) << "BET"
                        << std::setw(10) << "PRIZE"
                        << std::setw(10) << "WINNINGS" << std::endl;
            std::cout << "------------------------------------------" << std::endl;

            for (auto a: slotmachine->getLastNResults())
            {
                std::cout << a << std::endl;
            }
            std::cout << std::endl << std::endl;
        }

        // play again or exit?
        char again = 0;
        do {
            std::cout << "Play again (S/N) -> ";
            std::cin >> again;
            again = tolower(again);
            if (again =='n')
                exit = true;
        } while (again !='n' && again !='s');

    } while (true && !exit);
    std::cout << std::endl << "*** Thanks for playing ***" << std::endl;

    // save results in file
    if (saveLastResults)
    {
        slotmachine->saveLastNResults(FILENAME_RESULTS);
        std::cout << std::endl << "All the data about your last 5 rolls were save in ["
                    << FILENAME_RESULTS << "]" << std::endl;
    }

    return wallet;
}



int main()
{
    int wallet = 10000;
    GameOn(wallet, true, true);
    return 0;
}
