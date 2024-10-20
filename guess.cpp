#include <iostream>
#include <vector>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <fstream>


class Player {
private:
    std::string name;
    int guesses;

public:

    Player(const std::string& playerName = "", int numGuesses = 0) : name(playerName), guesses(numGuesses) {}

    void setName(const std::string& playerName) {
        name = playerName;
    }

    std::string getName() const {
        return name;
    }

    void setGuesses(int numGuesses) {
        guesses = numGuesses;
    }

    int getGuesses() const {
        return guesses;
    }

    void display() const {
        std::cout << "Player: " << name << ", Guesses: " << guesses << std::endl;
    }
};

class Leaderboard {
private:
    std::vector<Player> players;  

public:
   
    void addPlayer(const Player& player) {
        players.push_back(player);
    }

    void displayLeaderboard() const {
        std::cout << "\n--- Leaderboard ---\n";
        for (const Player& player : players) {
            player.display();
        }
    }

    void saveToFile(const std::string& filename) const {
        std::ofstream file(filename, std::ios::app);  
        if (!file) {
            std::cerr << "Error opening file\n";
            return;
        }

        for (const Player& player : players) {
            file << "Player: " << player.getName() << ", Guesses: " << player.getGuesses() << "\n";
        }

        file.close();
        std::cout << "Leaderboard saved to " << filename << std::endl;
    }
};

class GuessingGame {
private:
    int target;  

public:
    
    GuessingGame() {
        srand(static_cast<unsigned int>(time(0)));  
        target = rand() % (100 - 10 + 1) + 10;  
    }

    void playGame(Player& player) {
        int guess, attempts = 0;
        double root = sqrt(target);

        std::cout << "Hello " << player.getName() << "! Can you guess the number whose square root is: " << root << "?\n";
        
        do {
            guess = getGuess();  
            attempts++;

            if (guess == target) {
                std::cout << "Congratulations, you guessed the correct number in " << attempts << " attempts!\n";
                player.setGuesses(attempts);  
            } else if (guess > target) {
                std::cout << "Too high, try again.\n";
            } else {
                std::cout << "Too low, try again.\n";
            }
        } while (guess != target);
    }

    int getGuess() {
        int guess;
        std::cout << "Enter your guess (between 10 and 100): ";
        while (!(std::cin >> guess) || guess < 10 || guess > 100) {
            std::cout << "Invalid input. Please enter a number between 10 and 100: ";
            std::cin.clear();
        }
        return guess;
    }
};

int main() {
    Leaderboard leaderboard;
    char choice;
    bool game_over = false;

    while (!game_over) {
        std::cout << "Welcome! Press 'q' to quit or any other key to start a new game:\n";
        std::cin >> choice;

        if (choice == 'q') {
            game_over = true;
            leaderboard.saveToFile("leaderboard.txt");
            std::cout << "Goodbye!\n";
        } else {
          
            std::string playerName;
            std::cout << "Enter your name: ";
            std::cin >> playerName;

            Player player(playerName);

            GuessingGame game;
            game.playGame(player);
            leaderboard.addPlayer(player);
            leaderboard.displayLeaderboard();
        }
    }
}