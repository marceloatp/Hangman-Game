#include <iostream>
#include <time.h>

using namespace std;

void cleanScreen() {
	system("CLS");
}

string returnRandomWord() {
	//Vector w/ available words
	string words[3] = { "pineapple", "mango", "banana" };

	//Generate Index on interval [0,1,2]
	int randomIndex = rand() % 3;

	//Shows a random word
	//cout << words[randomIndex];
	return words[randomIndex];
}

string returnHideWord(string word, int wordSize) {
	int count = 0;
	string hideWord;

	//Hide the word
	while (count < wordSize)
	{
		hideWord += "_";
		count++;
	}
	return hideWord;
}
void showStatus(string hideWord, int wordSize, int maxTries, int tries, string triedLetters, string message) {
	//cout << "The secret word is " << word << "(Size:" << wordSize << ")";
	cout << message;
	cout << "\nThe secret Word: " << hideWord << "(Size:" << wordSize << ")";
	cout << "\nLefting Tries: " << maxTries - tries;

	//Show tried Letters
	int count;
	cout << "\n Tried Letter: ";
	for (count = 0; count < triedLetters.size(); count++) {
		cout << triedLetters[count] << ", ";
	}

}
int static singlePlayer() {

	//word to discover
	string word = returnRandomWord();

	//size of the word
	int wordSize = word.size();

	//Hidden word
	string hideWord = returnHideWord(word, wordSize);

	///Main Variables
	int tries = 0, maxTries = 10;   //Number of tries and errors
	int count = 0;					
	char letter;					//tried letter by the user
	string triedLetters;			//Letters used by user
	bool usedLetter = false, guessLetter = false;		//Aux to know if the letter was used
	string message = "Welcome to the Hangman Game";					//User feedback
	string guessWord;				//Try to guess the entire word
	int option;					    //Final options
	while (maxTries - tries > 0 && word != hideWord)
	{
		cleanScreen();

		//Show live status
		showStatus(hideWord, wordSize, maxTries, tries, triedLetters, message);

		//Make a try
		cout << "\nWrite a letter (or press 1 to guess the entire word):\n";
		cin >> letter;
		//if pressing 1, gives to the user an opportunity to guess the word
		if (letter == '1') {
			cin >> guessWord;
			if (guessWord == word) {
				hideWord = guessWord;
			}
			else {
				tries = maxTries;
			}
		}
		for (count=0; count < tries; count++) {
			if (triedLetters[count] == letter) {
				message = "That letter is already used!\n";
				usedLetter = true;
			}
		}
		// if is a new letter
		if (usedLetter == false) {
			triedLetters += tolower(letter);

			//Percorrer the word 
			for (count = 0; count < wordSize; count++) {
				//and if the letter exists change the hidden word
				if (word[count] == tolower(letter)) {
					//Make the letter appears in the Hideen Word
					hideWord[count] = word[count];

					guessLetter = true;
				}
			}
			//Increase number of tries
			tries++;

			if (guessLetter == false) {
				message = "You got a letter wrong\n";
			}
			else {
				message = "You guessed a letter right\n";
				guessLetter = false;
			}
		}
		//Reboot bool variables
		usedLetter = false;
	}

	if (word == hideWord) {
		cleanScreen();
		cout << "Congratulations!!!! YOU WIN !!!!!";
		cout << "\n Play Again?";
		cout << "\n1 - Yes.";
		cout << "\n2 No.";
		cin >> option;
		return option;
	}
	else {
		cleanScreen();
		cout << "GAME OVER";
		cout << "\n Play Again?";
		cout << "\n1 - Yes.";
		cout << "\n2 No.\n";
		cin >> option;
		return option;
	}

}

void mainMenu() {
	int option = 0;

	while (option < 1 || option >3)
	{
		cleanScreen();
		cout << "Welcome to HangMan Game";
		cout << "\n1 - Play";
		cout << "\n2 - About";
		cout << "\n3 - Quit";
		cout << "\n Select a option an press Enter: \n";

		cin >> option;


		switch (option)
		{
		case 1:
			//Iniciar o jogo
			if (singlePlayer() == 1) {
				mainMenu();
			};
			break;
		case 2:
			cleanScreen();
			cout << "Made By Marcelo Pereira";
			break;
		case 3:
			break;

		}
		
	}
}
int main() {
	//Generate random numbers
	srand((unsigned)time(NULL));

	mainMenu();
	return 0;
}