# GuessMe

## Introduction
Guess me! is a five letter word guessing game requiring vocabulary knowledge and strategical thinking.

## Gameplay
~You are prompted to guess a 5-letter word, "the hidden word", which is chosen randomly from a local text file.

~If your guess contains letters that are in the hidden word, those letters will appear as Retained Letters, and if the letter is in the hidden word and in the right spot, it will also show up in one of the blank spaces.

~Unlike Wordle, this game does not require players to enter a valid word; you can input 5 random letters and it counts as a guess. However, it has to be 5 letters.

~You must guess the word in 6 tries. If you fail to do so, the hidden word will be revealed, the game will be over, and you will be returned to the menu.

~If you guess the hidden word, It will appear in your statistics, which can be viewed from the menu.

## Program Functions
~Play Game
>The program selects a random word from the text file, and the player can start guessing.

~View Stats
>Displays the total number of games played, number of correct guesses, and lists the words that are correctly guessed by the player.

~Delete Stats
>Deletes the list of correctly guessed words and resets the number of played games and correct guesses to 0.
