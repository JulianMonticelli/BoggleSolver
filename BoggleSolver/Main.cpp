#include "Main.h"

const int MAX_COLUMNS = 4;
const int MAX_ROWS = 4;

std::set<std::string> wordSet;

int main() {
	DLBTrie * scrabbleDlb = new DLBTrie();
	populateScrabbleDlb(scrabbleDlb);

	char boggleBoard[MAX_COLUMNS][MAX_ROWS];
	bool hasChecked[MAX_COLUMNS][MAX_ROWS];
	char string[MAX_COLUMNS*MAX_ROWS+1];

	memset(hasChecked, false, MAX_COLUMNS*MAX_ROWS*sizeof(bool));
	memset(string, 0, 17 * sizeof(char));

	for (int y = 0; y < MAX_ROWS; y++) {
		for (int x = 0; x < MAX_COLUMNS; x++) {
			char buffChar = '\n';
			while (buffChar == '\n' || buffChar == ' ' || buffChar == '\r' || buffChar == '\t') {
				std::cin >> buffChar;
			}
			if (static_cast<int>(buffChar) > 97) {
				buffChar -= 32;
			}
			boggleBoard[x][y] = buffChar;
		}
	}

	boggleSolve<MAX_COLUMNS, MAX_ROWS>(boggleBoard, hasChecked, string, scrabbleDlb, 0, 0, 0);

	for (auto it = wordSet.cbegin(); it != wordSet.cend(); it++)
	{
		std::cout << *it << std::endl;
	}

	delete(scrabbleDlb);
}

template <size_t columns, size_t rows>
void boggleSolve(char (&boggleBoard)[columns][rows], bool (&hasChecked)[columns][rows], char (&str)[columns*rows+1], DLBTrie * dlb, int currentColumn, int currentRow, int markedChars)
{
	// Recursive base case
	if (markedChars >= rows*columns)
	{
		return;
	}

	// Since we are considering this boggle tile, mark tile as currently checked
	hasChecked[currentColumn][currentRow] = true;
	str[markedChars] = boggleBoard[currentColumn][currentRow];

	
	if (!dlb->isValidTriePath(str)) {
		// Today marks a landmark occurrence -
		// This is the first time I have ever used
		// a goto in several years of programming experience
		// I never thought today would come <@:^)
		goto Skip;
	}

	// Dump the word if it's an acceptable word
	if (dlb->wordExists(str))
	{
		addToSet(str);
	}

	// Check if we can go to the left
	if (currentColumn > 0)
	{
		// Check immediate left
		if (!hasChecked[currentColumn - 1][currentRow])
		{
			boggleSolve(boggleBoard, hasChecked, str, dlb, currentColumn - 1, currentRow, markedChars + 1);
		}
		// Check upper left
		if (currentRow > 0)
		{
			if (!hasChecked[currentColumn - 1][currentRow - 1])
			{
				boggleSolve(boggleBoard, hasChecked, str, dlb, currentColumn - 1, currentRow - 1, markedChars + 1);
			}
		}
		if (currentRow < MAX_ROWS - 1)
		{
			if (!hasChecked[currentColumn - 1][currentRow + 1])
			{
				boggleSolve(boggleBoard, hasChecked, str, dlb, currentColumn - 1, currentRow + 1, markedChars + 1);
			}
		}
	}
	// Check if we can go to the right
	if (currentColumn < MAX_COLUMNS - 1) {
		// Check immediate right
		if (!hasChecked[currentColumn + 1][currentRow])
		{
			boggleSolve(boggleBoard, hasChecked, str, dlb, currentColumn + 1, currentRow, markedChars + 1);
		}
		// Check upper left
		if (currentRow > 0)
		{
			if (!hasChecked[currentColumn + 1][currentRow - 1])
			{
				boggleSolve(boggleBoard, hasChecked, str, dlb, currentColumn + 1, currentRow - 1, markedChars + 1);
			}
		}
		if (currentRow < MAX_ROWS - 1)
		{
			if (!hasChecked[currentColumn + 1][currentRow + 1])
			{
				boggleSolve(boggleBoard, hasChecked, str, dlb, currentColumn + 1, currentRow + 1, markedChars + 1);
			}
		}
	}
	// Check if we can go up
	if (currentRow > 0) {
		if (!hasChecked[currentColumn][currentRow - 1])
		{
			boggleSolve(boggleBoard, hasChecked, str, dlb, currentColumn, currentRow - 1, markedChars + 1);
		}
	}
	// Check if we can go down
	if (currentRow < MAX_ROWS - 1) {
		if (!hasChecked[currentColumn][currentRow + 1])
		{
			boggleSolve(boggleBoard, hasChecked, str, dlb, currentColumn, currentRow + 1, markedChars + 1);
		}
	}


Skip:
	// Unset checked flag of current boggle tile
	hasChecked[currentColumn][currentRow] = false;

	if (markedChars == 0) {
		if (currentColumn < MAX_COLUMNS - 1) {
			boggleSolve(boggleBoard, hasChecked, str, dlb, currentColumn + 1, currentRow, 0);
		}
		else if (currentRow < MAX_ROWS - 1) {
			boggleSolve(boggleBoard, hasChecked, str, dlb, 0, currentRow + 1, 0);
		}
	}
	str[markedChars] = '\0'; // Nullify character
}

void populateScrabbleDlb(DLBTrie * dlb)
{
	std::ifstream scrabbleDict("twl06.txt");

	std::string line;

	while (std::getline(scrabbleDict, line))
	{
		for (auto & c : line) {
			c = toupper(c);
		}
		dlb->addWord(line);
	}
}

template<size_t wordSize>
void addToSet(char (&word)[wordSize])
{
	std::string str(word);
	wordSet.insert(str);
}

