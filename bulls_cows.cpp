#include <iostream>     // std::cout && cin
#include <string>       // conversion from int to char
#include <random>       // random generator
#include <algorithm>    // find, sort, remove_if, unique
#include <regex>        // to check user input
#include <cctype>       // tolower
#include <limits>       // numeric limit to clean std::cin
#define NUMBERS_TO_GUESS 4

void                        generate_random_sequence(std::string &random_seq);     // Generates random values
void                        print_sequence(const std::string &user_input);         // Testing purposes
bool                        is_unique(const std::string &user_input);                // Check if all numbers are unique
std::string                 get_input(void);                                       // Gets input from user and tests if it's appropriate
void                        guessing_game(std::string &random_seq);                // Start the loop until user guess correctly and then asks if user wants to continue, if not quits

int main(void) {
    std::string    random_seq;

    generate_random_sequence(random_seq);

    // Cheatcode
    // print_sequence(random_seq);

    guessing_game(random_seq);
    std::cout << "Thanks for playing!\n";
    return 0;
}

/**
 * @brief Generates random NUMBERS_TO_GUESS
 * This function generates a random number from [0 to 9] 
 * Converts its to string 
 * Checks if the number is already in the random_seq if not adds it
 */
void    generate_random_sequence(std::string &random_seq) {
    int                                                         current_number = 0;
    std::random_device                                          dev;
    std::mt19937                                                rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type>    dist9(0,9);
    
    random_seq.clear(); // just to make sure that random_seq is empty

    while (random_seq.size() != NUMBERS_TO_GUESS) {
        current_number = dist9(rng);
        if (random_seq.find(std::to_string(current_number)) == std::string::npos)
            random_seq += std::to_string(current_number);
    }
}

void    print_sequence(const std::string &user_input) {
    if (user_input.empty())
        return ;

    for (auto str : user_input) {
        std::cout << str << " ";
    }
    std::cout << "\n";
}

/**
 * Takes a copy of user input
 * Sorts it and checks if the neighbors are equal.
 */
 bool   is_unique(const std::string& user_input) {
    std::string copy = user_input;
    std::sort(copy.begin(), copy.end());
    return std::unique(copy.begin(), copy.end()) == copy.end();
}

std::string get_input(void) {
    std::string                 user_input, guess_seq; 
    static const std::regex     re("^\\s*\\d\\s*\\d\\s*\\d\\s*\\d\\s*$");

    std::getline(std::cin, user_input);
    if (std::regex_match(user_input, re)) {
        // if user added spaces i need to remove them from original string
        user_input.erase(std::remove_if(user_input.begin(), user_input.end(), [](unsigned char x) { return std::isspace(x);}), user_input.end());
        if (is_unique(user_input)) {
                guess_seq = user_input;
        }
    }
    return guess_seq;
}

/**
 * Starting the game and looping
 * Until user guesses correct sequence
 * After each user input there is feedback on 'bulls' and 'cows'
 */
void    guessing_game(std::string &random_seq) {
    int            bulls = 0, cows = 0;
    std::string    user_input;

    std::cout << "Welcome to Bulls and Cows.\n"
        << "Rules are simple i have sequence of numbers from 0 to 9 (including 0 and 9)"
        << " and you need to guess it.\n"
        << "Give me 4 numbers (ex. 4103) and i will tell you something like 2 bulls and 1 cow.\n"
        << "Bull means you guessed number exactly where it's supposed to be "
        << "and cow means you guessed the number but unfortunately not in the correct positions.\n"
        << "Let's start:\n";

    // Loop runs until there is 4 bulls
    while (true) {
        // At the start of guessing bulls and cows always 0
        bulls = 0;
        cows = 0;
        // cleaning std::cin
        std::cout << "Give me your sequence of numbers: ";
        user_input = get_input();
        if (user_input.empty()) {
            std::cerr << "Something is not right. Please use only unique numbers from 0 to 9.\n";
            continue ;
        }

        for (size_t i = 0; i < user_input.size(); ++i) {
            if (user_input[i] == random_seq[i]) 
                bulls++;
            if (std::find(random_seq.begin(), random_seq.end(), user_input[i]) != random_seq.end()) {
                cows++;
            }
        }
        // I need to show cows separate from bulls and in current approach above it includes it
        cows -= bulls;

        // if 4 bulls then the user won. Games stops unless user wants to play again
        if (bulls == NUMBERS_TO_GUESS){
            std::string answer;
            std::cout << "Congratulation! YOU GUESSED CORRECTLY!\n";
            std::cout << "Do you wanna play again? If so write yes: ";
            std::cin >> answer;

            for (size_t i = 0; i < answer.size(); ++i) {
                answer[i] = std::tolower(answer[i]);
            }
            if (answer == "y" || answer == "yes" ) {
                generate_random_sequence(random_seq);
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
                continue;
            }
        }
        else {
        std::cout << bulls << " bull" << (bulls == 1 ? "" : "s") << " and "
                << cows << " cow" << (cows == 1 ? "" : "s") << "\n";
        }
    }
}
