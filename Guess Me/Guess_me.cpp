#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <string>
#include <ctime>
#include <algorithm>
#include <limits>
#include <cctype>

using namespace std;

// Structure to store each correct guess in a linked list
struct GuessNode {
    string guess;
    GuessNode* next;

    GuessNode(const string& word) : guess(word), next(NULL) {}
};

bool isGameOver, isAnsCorrect = false; // Flags to track game state
string wordArr; // The randomly selected word
string hiddenWord; // The word with hidden characters
GuessNode* correctGuessesHead = NULL; // Head pointer of the linked list to store correct guesses
int numCorrectGuesses = 0; // Number of correct guesses made
int numTotalGames = 0; // Total number of games played

// Function to retain the letters from the randomly selected word that are present in the guessed word
void retain_word(const string& guess)
{
    string retainedLetters;
    vector<int> wordCharCount(26, 0);

    // Count the occurrences of each character in the wordArr
    for (char c : wordArr) {
        wordCharCount[toupper(c) - 'A']++;
    }

    // Check each character in the guessed word
    for (char c : guess) {
        char upperC = toupper(c);
        if (wordCharCount[upperC - 'A'] > 0) {
            retainedLetters += upperC;
            wordCharCount[upperC - 'A']--;
        }
    }

    cout << "Retained letters: " << retainedLetters << endl;
}

// Function to update the hiddenWord with the correct letters guessed
void correct_letters(const string& guess)
{
    string retainedLetters;
    int length = wordArr.length();

    for (int i = 0; i < length; i++) {
        if (tolower(wordArr[i]) == tolower(guess[i])) {
            retainedLetters += wordArr[i];
            hiddenWord[i] = wordArr[i];
        }
    }
}

// Function to compare the guessed word with the randomly selected word
void compare_word(const string& guess)
{
    string upper_Guess = guess;
    string upper_WordArr = wordArr;

    // Convert both the guessed word and the selected word to uppercase for comparison
    for (char& c : upper_Guess) {
        c = toupper(c);
    }

    for (char& c : upper_WordArr) {
        c = toupper(c);
    }

    if (upper_WordArr == upper_Guess) {
        cout << "You are correct\n\n" << "CONGRATSSSSSSSSSSSS\n";
        isGameOver = true;
        isAnsCorrect = true;

        // Create a new node for the correct guess and add it to the linked list
        GuessNode* newNode = new GuessNode(guess);
        if (correctGuessesHead == NULL) {
            correctGuessesHead = newNode;
        }
        else {
            GuessNode* current = correctGuessesHead;
            while (current->next != NULL) {
                current = current->next;
            }
            current->next = newNode;
        }

        numCorrectGuesses++;
    }
    else {
        cout << "INCORRECT GUESS\n\n";
        retain_word(guess);
        correct_letters(guess);
    }
}

// Check if library is empty
int checkSize(int size)
{
    if (size == 0)
        throw "Error";
    else
        return size;
}

//function to check if guess if input is letter only
bool alpha(const string& strptr)
{
    for (size_t i = 0; i < strptr.size(); i++)
    {
        if (!isalpha(strptr[i]))
        {
            return false;
        }
    }
    return true;
}

void play()
{
    system("cls");
    string guess;
    int maxLength = 5;
    int numGuesses = 0;

    hiddenWord = "_____";

    while (numGuesses < 5 && !isGameOver) {
        cout << "Current Word:" << hiddenWord << endl;

        cout << wordArr;
        //end */

        printf("\nNumber of guesses: %d / %d\n", numGuesses, maxLength);
        cout << "Enter your guess:";
        cin >> guess;

       int length = guess.length();

        if (length > maxLength) {
            cout << "This word is too long.\n";
        }
        else if (length < maxLength) {
            cout << "This word is too short.\n";
        }
        else if (length == maxLength) {
             if(alpha(guess)){
                numGuesses++;
                compare_word(guess);
             }
             else{
                cout << "Input has invalid characters. Input only letters.\n";
             }
        }
    }

    if (numGuesses == 5) {
        isGameOver = true;
        if (isGameOver == true && isAnsCorrect == false) {
            system("cls");
            cout << "\n\nGAME OVER\n\n";
            cout << "The word was: " << wordArr << endl; // Display the word
            isGameOver, isAnsCorrect = false;
        }
    }
}

// Function to select a random word and start the game
void game()
{
    vector<string> words;

    srand(time(0));

    ifstream file("wordlib.txt");
    string line;
    while (getline(file, line))
        words.push_back(line);
    int size = words.size();
    try {
        if (checkSize(size)) {
            string rndWord = words[rand() % size];

            wordArr = rndWord;

            play();
        }
    }
    catch (...) {
        cout << "Exception occurred";
    }
}

// Function to display game statistics
void stats()
{
    system("CLS");
    cout << "Number of total games played: " << numTotalGames << endl;

    if (correctGuessesHead == NULL) {
        cout << "Number of correct guesses: " << numCorrectGuesses << endl;
        cout << "Correct Guesses: None\n";
    }
    else {
        cout << "Number of correct guesses: " << numCorrectGuesses << endl;
        cout << "Correct Guesses:\n";
        GuessNode* current = correctGuessesHead;
        while (current != NULL) {
            cout << current->guess << endl;
            current = current->next;
        }
    }

    // create local file for game statistics
    if(numTotalGames != 0 && numCorrectGuesses != 0)
    {
        ofstream outFile("game_stats.txt");
        outFile << "Number of total games played: " << numTotalGames << endl;

        if (correctGuessesHead == NULL) {
            outFile << "Number of correct guesses: " << numCorrectGuesses << endl;
            outFile << "Correct Guesses: None\n";
        }
        else {
            outFile << "Number of correct guesses: " << numCorrectGuesses << endl;
            outFile << "Correct Guesses:\n";
            GuessNode* current = correctGuessesHead;
            while (current != NULL) {
                outFile << current->guess << endl;
                current = current->next;
            }
        }
        outFile.close();
    }


    cout << "\nPress enter to return to the menu.";
    cin.ignore();
    cin.get();
}

// Function to delete game statistics and reset variables
void delStat()
{
    system("CLS");
    GuessNode* current = correctGuessesHead;

    while (current != NULL) {
        GuessNode* temp = current;
        current = current->next;
        delete temp;
    }

    correctGuessesHead = NULL;
    numCorrectGuesses = 0;
    numTotalGames = 0;
    remove("game_stats.txt");

    cout << "Stats Deleted!";
    cout << "\nPress enter to return to the menu.";
    cin.ignore();
    cin.get();
}

// Function to load game statistics from a file
void loadStatsFromFile()
{
    ifstream inFile("game_stats.txt");
    if (inFile.is_open()) {
        string line;
        while (getline(inFile, line)) {
            if (line.find("Number of total games played: ") != string::npos) {
                numTotalGames = stoi(line.substr(line.find_last_of(' ') + 1));
            }
            else if (line.find("Number of correct guesses: ") != string::npos) {
                numCorrectGuesses = stoi(line.substr(line.find_last_of(' ') + 1));
            }
            else if (line == "Correct Guesses:") {
                string guess;
                while (getline(inFile, guess)) {
                    if (guess.empty())
                        break;
                    GuessNode* newNode = new GuessNode(guess);
                    if (correctGuessesHead == NULL) {
                        correctGuessesHead = newNode;
                    }
                    else {
                        GuessNode* current = correctGuessesHead;
                        while (current->next != NULL) {
                            current = current->next;
                        }
                        current->next = newNode;
                    }
                }
            }
        }
        inFile.close();
    }
}

int main()
{
    loadStatsFromFile();

    bool flag = false;
    int opt;

    while (!flag || isGameOver == true) {
        // Main menu
        cout << "GUESS ME";
        cout << "\n 1 - Play Game \n 2 - View Stats \n 3 - Delete Stats \n 4 - Exit \n\nEnter your choice: ";

        cin >> opt;

        if (cin.fail()) {
            cout << "\nError. Invalid input. Please enter a valid integer.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        switch (opt) {
        case 1:
            isGameOver = false;
            numTotalGames++;
            game();
            flag = true;
            break;
        case 2:
            stats();
            flag = false;
            break;
        case 3:
            delStat();
            flag = false;
            break;
        case 4:
            stats();
            return 0;
        default:
            cout << "\nError. Invalid value. Please try again.\n";
            continue;
        }
    }

    return 0;
}
