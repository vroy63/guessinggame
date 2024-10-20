#include <iostream>
#include <vector>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <fstream>

struct Player {
    std::string name;
    int guesses;
};

std::vector<Player> board;

void GetName(Player &player) {
    std::cout << "Please enter your name to start: ";
    std::cin >> player.name;
    std::cout << "Hello " << player.name << std::endl;
}

int GetGuess() {
    int guess;
    std::cout << "Guess a value between 10 and 100: ";
    while (!(std::cin >> guess) || guess < 10 || guess > 100) {
        std::cout << "Make sure your guess is between 10 and 100: ";
        std::cin.clear(); // Clear error flag // Discard bad input
    }
    return guess;
}

int PlayGuessingGame(Player &player) {
    int target = rand() % (100 - 10 + 1) + 10;  
    double root = sqrt(target);
    std::cout << root << " is the square root of what number? Guess a value between 10 and 100:\n";

    int guess;
    int count = 0;

    do {
        guess = GetGuess();
        count++;

        if (guess == target) {
            std::cout << "Congratulations, you guessed the correct number in " << count << " attempts!\n";
            player.guesses = count;
        } else if (guess > target) {
            std::cout << "Too high, guess again:\n";
        } else {
            std::cout << "Too low, guess again:\n";
        }
    } while (guess != target);

    return count;
}

void DisplayScore() {
    std::cout << "\nScoreboard:\n";
    std::cout << "*Quit game to see scores on file** \n";
    for (size_t i = 0; i < board.size(); ++i) {
        std::cout << "Player " << i + 1 << ": Name: " << board[i].name << ", Guesses: " << board[i].guesses << std::endl;
    }
}

void WriteToFile() {
    std::ofstream file("guess.txt", std::ios::app); // Open in append mode
    if (!file) {
        std::cerr << "Error opening file\n";
        return;
    }

    for (size_t i = 0; i < board.size(); ++i) {
        file << "Player " << i + 1 << ": Name: " << board[i].name << ", Guesses: " << board[i].guesses << std::endl;
    }

    file.close();
    std::cout << "Scoreboard written successfully to file\n";
}

int main() {
    srand(static_cast<unsigned int>(time(0)));
    std::cout << "Welcome! Press 'q' to quit or any other key to continue\n";

    char c;
    bool game_over = false;

    while (!game_over) {
        std::cin >> c;

        if (c == 'q') {
            game_over = true;
            WriteToFile();
            std::cout << "Bye Bye!\n";
        } else {
            Player player;
            GetName(player);
            PlayGuessingGame(player);
            board.push_back(player);
            DisplayScore();
            std::cout << "Press 'q' to quit or any other key to continue:\n";
        }
    }

    return 0;
}