#include <iostream>
#include <fstream>
#include "GlobalVariables.h"
using namespace std;

//Helper function to create a copy of char array
void copyCharArray(char* arr1, char* arr2)
{
    int index = 0;
    while (arr1[index] != '\0')
    {
        arr2[index] = arr1[index];
        ++index;
    }
    arr2[index] = '\0';
}
//Helper function to xawp two char arrays
void swapCharArrays(char* a, char* b)
{
    char temp[100];
    copyCharArray(a, temp);
    copyCharArray(b, a);
    copyCharArray(temp, b);
}
//Helper function to create a file that will collect the score of the players
void createFileWithScore(const long scoreList[], const char scoreFile[], long score)
{
    ofstream fileWithScore;
    fileWithScore.open(scoreFile, ios::app);
    if (fileWithScore.is_open())
    {
        fileWithScore << score << endl;
    }
    else
    {
        cout << "ERROR! Failed to open the file!" << endl;
    }
    fileWithScore.close();
}
//Helper function to create a file that will collect the usernames of the players
void createFileWithUsernames(const char fileWithUsernames[], const char username[][100])
{
    ofstream leaderboard;
    leaderboard.open(fileWithUsernames, ios::app);
    if (leaderboard.is_open())
    {
        leaderboard << username[0] << endl;
    }
    else
    {
        cout << "ERROR! Failed to open the file!" << endl;
    }
    leaderboard.close();
}
//Helper function to swap numbers
void swapNumbers(long& number1, long& number2)
{
    long temp = number1;
    number1 = number2;
    number2 = temp;
}
//Helper function to sorts arrays in descending order depending on the score
void bubbleSort(long readScore[], char readUsernames[][100], const int SIZE)
{
    for (int i = 0; i < SIZE - 1; ++i)
    {
        for (int j = 0; j < SIZE - i - 1; ++j)
        {
            if (readScore[j] < readScore[j + 1])
            {
                swapCharArrays(readUsernames[j], readUsernames[j + 1]);
                swapNumbers(readScore[j], readScore[j + 1]);
            }
        }
    }
}
//Helper function to sort the files with usernames and score
void sortFile(long scoreList[], const char scoreFile[], const char fileWithUsernames[], const char filename[], char readUsernames[][100], long readScore[])
{
    const int SIZE = 50;
    ifstream file1;
    file1.open(scoreFile);
    if (file1.is_open())
    {
        for (int i = 0; i < SIZE; ++i)
        {
            file1 >> readScore[i];
        }
    }
    else
    {
        cout << "ERROR! Failed to open the file!" << endl;
    }
    ifstream file2;
    file2.open(fileWithUsernames);
    if (file2.is_open())
    {
        for (int i = 0; i < SIZE; ++i)
        {
            file2 >> readUsernames[i];
        }
    }
    else
    {
        cout << "ERROR! Failed to open the file!" << endl;
    }
    
    bubbleSort(readScore, readUsernames, SIZE);
    file1.close();
    file2.close();
}
//Helper function to read from the file, which contains the usernames and score of the players
void readFromLeaderboard(long scoreList[], const char scoreFile[], const char fileWithUsernames[], const char filename[], char readUsernames[][100], long readScore[])
{
    const int SIZE = 100;
    const int maxRows = 5;
    sortFile(scoreList, scoreFile, fileWithUsernames, filename, readUsernames, readScore);
   
    for (int i = 0; i < SIZE; ++i)
    {
        while (i < maxRows)
        {
            cout << readUsernames[i] << " " << readScore[i] << endl;
            ++i;
        }
    }
    ofstream leaderboard;
    leaderboard.open(filename, ios::in);

    for (int j = 0; j < SIZE; ++j)
    {
        leaderboard << readUsernames[j] << " " << readScore[j] << endl;
    }
    leaderboard.close();
}
//Helper function to find the number of the digits of a given number
//used in the function "createBoard"
int numberOfDigits(int number)
{
    int count = 0;
    if (number == 0)
    {
        return 1;
    }
    while (number != 0)
    {
        number = number / 10;
        ++count;
    }
    return count;
}
//Helper function to generate random position from the board
//where new random element will be included
int randomIndexGenerate(int dimension)
{
    int randomIndex = rand() % dimension;
    return randomIndex;
}
//Helper function to generate new random number (2 or 4) 
int newRandomElement()
{
    int randomElement = rand() % 10;
    int smallerRandomNumber = 2;
    int biggerRandomNumber = 4;
    if (randomElement == 0)
    {
        randomElement = biggerRandomNumber;
    }
    else
    {
        randomElement = smallerRandomNumber;
    }
    return randomElement;
}
//Helper function to check whether the game is won
bool Win(int board[][10], int dimension, const int MAX)
{
    for (int i = 0; i < dimension; ++i)
    {
        for (int j = 0; j < dimension; ++j)
        {
            if (board[i][j] == MAX)
            {
                return true;
            }
        }
    }
    return false;
}
//Helper function to check whether the game is over
int gameOver(int board[][10], int dimension)
{
    int isGameOver = 1;
    for (int i = 0; i < dimension; ++i)
    {
        for (int j = 0; j < dimension - 1; ++j)
        {
            if (board[i][j] == 0 || board[i][j + 1] == 0 || board[i][j] == board[i][j + 1])
            {
                isGameOver = 0;
                break;
            }
        }
    }
    for (int j = 0; j < dimension; ++j)
    {
        for (int i = 0; i < dimension - 1; ++i)
        {
            if (board[i][j] == 0 || board[i + 1][j] == 0 || board[i][j] == board[i + 1][j])
            {
                isGameOver = 0;
                break;
            }
        }
    }
    return isGameOver;
}
//Helper function to add the generated new random number
//which will appear in a random position after each turn during the game 
void addElement(int board[][10], int dimension)
{
    int indexI3;
    int indexJ3;
    int counter = 0;
    while (1)
    {
        if (counter == 1)
        {
            break;
        }
        indexI3 = randomIndexGenerate(dimension);
        indexJ3 = randomIndexGenerate(dimension);
        if (board[indexI3][indexJ3] == 0)
        {
            board[indexI3][indexJ3] = newRandomElement();
            counter = 1;
        }
    }
}
//Helper function to create the UI for the game 
void createBoard(int board[][10], int dimension, long long step)
{
    int indexI1, indexJ1, indexI2, indexJ2;
    system("cls");
    while (1)
    {
        indexI1 = randomIndexGenerate(dimension);
        indexJ1 = randomIndexGenerate(dimension);
        indexI2 = randomIndexGenerate(dimension);
        indexJ2 = randomIndexGenerate(dimension);

        if (indexI1 == indexI2 && indexJ1 == indexJ2)
        {
            continue;
        }
        else
        {
            break;
        }
    }
    system("cls");
    if (step == 0)
    {
        cout << "Commands: w(up) ; s(down) ; a(left) ; d(right) ; q(quit)" << endl;
        for (int i = 0; i < dimension; i++)
        {
            cout << "|";
            for (int i = 1; i <= dimension; ++i)
            {
                if (i < dimension)
                {
                    cout << "------";
                }
                else if (i == dimension)
                {
                    cout << "-----";
                }
            }
            cout << "|" << endl;
            for (int j = 0; j < dimension; j++)
            {
                cout << "|";
                if (i == indexI1 && j == indexJ1)
                {
                    board[i][j] = 2;
                    cout << "  " << 2 << "  ";
                }
                else if (i == indexI2 && j == indexJ2)
                {
                    int temp = newRandomElement();
                    board[i][j] = temp;
                    cout << "  " << temp << "  ";
                }
                else
                {
                    cout << "     ";
                }
            }
            cout << "|" << endl;
        }
        cout << "|";
        for (int i = 1; i <= dimension; ++i)
        {
            if (i < dimension)
            {
                cout << "------";
            }
            else if (i == dimension)
            {
                cout << "-----";
            }
        }
        cout << "|" << endl;
    }
    else
    {
        cout << "Commands: w(up) ; s(down) ; a(left) ; d(right) ; q(quit)" << endl;
        for (int i = 0; i < dimension; i++)
        {
            cout << "|";
            for (int i = 1; i <= dimension; ++i)
            {
                if (i < dimension)
                {
                    cout << "------";
                }
                else if (i == dimension)
                {
                    cout << "-----";
                }
            }
            cout << "|" << endl;
            for (int j = 0; j < dimension; j++)
            {
                cout << "|";
                if (board[i][j] != 0)
                {
                    if (numberOfDigits(board[i][j]) == 4)
                    {
                        cout << " " << board[i][j];
                    }
                    if (numberOfDigits(board[i][j]) == 3)
                    {
                        cout << " " << board[i][j] << " ";
                    }
                    if (numberOfDigits(board[i][j]) == 2)
                    {
                        cout << "  " << board[i][j] << " ";
                    }
                    if (numberOfDigits(board[i][j]) == 1)
                    {
                        cout << "  " << board[i][j] << "  ";
                    }
                }
                else
                {
                    cout << "     ";
                }
            }
            cout << "|" << endl;
        }
        cout << "|";
        for (int i = 1; i <= dimension; ++i)
        {
            if (i < dimension)
            {
                cout << "------";
            }
            else if (i == dimension)
            {
                cout << "-----";
            }
        }
        cout << "|" << endl;
    }
}
//Helper functions for the possible moves in the game
void moveUp(int board[][10], int dimension, long& step, long& score)
{
    int counter = 0;
    for (int i = 0; i < dimension; ++i)
    {
        int num = 0;
        int previous = 0;
        for (int j = 0; j < dimension; ++j)
        {
            if (num == board[j][i] && num != 0)
            {
                board[previous][i] = 2 * num;
                board[j][i] = 0;
                score += 2 * num;
                num = 0;
                ++counter;
                continue;
            }
            if (board[j][i] != 0)
            {
                num = board[j][i];
                previous = j;
            }
        }
    }
    for (int i = 0; i < dimension; ++i)
    {
        for (int j = 0; j < dimension; ++j)
        {
            for (int k = 0; k < dimension - 1; ++k)
            {
                if (board[k][i] == 0 && board[k + 1][i] != 0)
                {
                    board[k][i] = board[k][i] ^ board[k + 1][i];
                    board[k + 1][i] = board[k][i] ^ board[k + 1][i];
                    board[k][i] = board[k][i] ^ board[k + 1][i];
                    ++counter;
                }
            }
        }
    }
    if (counter != 0)
    {
        addElement(board, dimension);
        ++step;
    }
    createBoard(board, dimension, step);
}
void moveDown(int board[][10], int dimension, long& step, long& score)
{
    int counter = 0;
    for (int i = 0; i < dimension; ++i)
    {
        int num = 0;
        int previous = 0;
        for (int j = dimension - 1; j >= 0; --j)
        {
            if (num == board[j][i] && num != 0)
            {
                board[previous][i] = 2 * num;
                board[j][i] = 0;
                score += 2 * num;
                num = 0;
                ++counter;
                continue;
            }
            if (board[j][i] != 0)
            {
                num = board[j][i];
                previous = j;
            }
        }
    }
    for (int i = 0; i < dimension; ++i)
    {
        for (int j = 0; j < dimension; ++j)
        {
            for (int k = dimension - 1; k > 0; --k)
            {
                if (board[k][i] == 0 && board[k - 1][i] != 0)
                {
                    board[k][i] = board[k][i] ^ board[k - 1][i];
                    board[k - 1][i] = board[k][i] ^ board[k - 1][i];
                    board[k][i] = board[k][i] ^ board[k - 1][i];
                    ++counter;
                }
            }
        }
    }
    if (counter != 0)
    {
        addElement(board, dimension);
        ++step;
    }
    createBoard(board, dimension, step);
}
void moveRight(int board[][10], int dimension, long& step, long& score)
{
    int counter = 0;
    for (int i = 0; i < dimension; ++i)
    {
        int num = 0;
        int previous = 0;
        for (int j = dimension - 1; j >= 0; --j)
        {
            if (num == board[i][j] && num != 0)
            {
                board[i][previous] = 2 * num;
                board[i][j] = 0;
                score += 2 * num;
                num = 0;
                ++counter;
                continue;
            }
            if (board[i][j] != 0)
            {
                num = board[i][j];
                previous = j;
            }
        }
    }
    for (int i = 0; i < dimension; ++i)
    {
        for (int j = 0; j < dimension; ++j)
        {
            for (int k = dimension - 1; k > 0; --k)
            {
                if (board[i][k] == 0 && board[i][k - 1] != 0)
                {
                    board[i][k] = board[i][k] ^ board[i][k - 1];
                    board[i][k - 1] = board[i][k] ^ board[i][k - 1];
                    board[i][k] = board[i][k] ^ board[i][k - 1];
                    ++counter;
                }
            }
        }
    }
    if (counter != 0)
    {
        addElement(board, dimension);
        ++step;
    }
    createBoard(board, dimension, step);
}
void moveLeft(int board[][10], int dimension, long& step, long& score)
{
    int counter = 0;
    for (int i = 0; i < dimension; ++i)
    {
        int num = 0;
        int previous = 0;
        for (int j = 0; j < dimension; ++j)
        {
            if (num == board[i][j] && num != 0)
            {
                board[i][previous] = 2 * num;
                board[i][j] = 0;
                score += 2 * num;
                num = 0;
                ++counter;
                continue;
            }
            if (board[i][j] != 0)
            {
                num = board[i][j];
                previous = j;
            }
        }
    }
    for (int i = 0; i < dimension; ++i)
    {
        for (int j = 0; j < dimension; ++j)
        {
            for (int k = 0; k < dimension - 1; ++k)
            {
                if (board[i][k] == 0 && board[i][k + 1] != 0)
                {
                    board[i][k] = board[i][k] ^ board[i][k + 1];
                    board[i][k + 1] = board[i][k] ^ board[i][k + 1];
                    board[i][k] = board[i][k] ^ board[i][k + 1];
                    ++counter;
                }
            }
        }
    }
    if (counter != 0)
    {
        addElement(board, dimension);
        ++step;
    }
    createBoard(board, dimension, step);
}

int main()
{
MENU:
    cout << "     MENU    " << endl;
    cout << "1. Start game" << endl;
    cout << "2. Leaderboard" << endl;
    cout << "3. Quit" << endl << endl;

    cout << "Enter your choice: ";
    int myChoice;
    cin >> myChoice;
    cin.get();

    if (myChoice == 1)
    {
        system("cls");
        cout << "!Your username should not exceed 100 symbols and should not contains spaces!" << endl;
        cout << "Enter your username: " << endl;
        int counter = 0;
        cin.getline(username[counter], SIZE);
        ++counter;

        int dimension;
        cout << "Enter dimension: " << endl;
        cin >> dimension;

    STARTGAME:
        if (dimension >= 4 && dimension <= 10)
        {
            srand((unsigned)time(NULL));
            char direction;
            const int MAXSCORE = 2048;
            long step = 0;
            long score = 0;
            const int MAXDIMENSION = 10;
            int board[MAXDIMENSION][MAXDIMENSION] = {};
            createBoard(board, dimension, step);
            while (1)
            {
                if (Win(board, dimension, MAXSCORE) == true)
                {
                    if (dimension == 4)
                    {
                        createFileWithScore(score1, scoreList1, score);
                        createFileWithUsernames(usernameList1, username);
                        sortFile(score1, scoreList1, usernameList1, filename1, readUsernames1, readScore1);
                    }
                    else if (dimension == 5)
                    {
                        createFileWithScore(score2, scoreList2, score);
                        createFileWithUsernames(usernameList2, username);
                        sortFile(score2, scoreList2, usernameList2, filename2, readUsernames2, readScore2);
                    }
                    else if (dimension == 6)
                    {
                        createFileWithScore(score3, scoreList3, score);
                        createFileWithUsernames(usernameList3, username);
                        sortFile(score3, scoreList3, usernameList3, filename3, readUsernames3, readScore3);
                    }
                    else if (dimension == 7)
                    {
                        createFileWithScore(score4, scoreList4, score);
                        createFileWithUsernames(usernameList4, username);
                        sortFile(score4, scoreList4, usernameList4, filename4, readUsernames4, readScore4);
                    }
                    else if (dimension == 8)
                    {
                        createFileWithScore(score5, scoreList5, score);
                        createFileWithUsernames(usernameList5, username);
                        sortFile(score5, scoreList5, usernameList5, filename5, readUsernames5, readScore5);
                    }
                    else if (dimension == 9)
                    {
                        createFileWithScore(score6, scoreList6, score);
                        createFileWithUsernames(usernameList6, username);
                        sortFile(score6, scoreList6, usernameList6, filename6, readUsernames6, readScore6);
                    }
                    else if (dimension == 10)
                    {
                        createFileWithScore(score7, scoreList7, score);
                        createFileWithUsernames(usernameList7, username);
                        sortFile(score7, scoreList7, usernameList7, filename7, readUsernames7, readScore7);
                    }
                    int quitOrContinue1;
                    cout << "YOU WIN!" << endl;
                    cout << "Your final score is: " << score << endl;
                    cout << "Enter 'm' to go back to the MENU or anything else to quit: ";
                    cin >> quitOrContinue1;
                    if (quitOrContinue1 == 'm')
                    {
                        system("cls");
                        goto MENU;
                    }
                    else
                    {
                        system("cls");
                        return 0;
                    }
                }
                if (gameOver(board, dimension))
                {
                    if (dimension == 4)
                    {
                        createFileWithScore(score1, scoreList1, score);
                        createFileWithUsernames(usernameList1, username);
                        sortFile(score1, scoreList1, usernameList1, filename1, readUsernames1, readScore1);
                    }
                    else if (dimension == 5)
                    {
                        createFileWithScore(score2, scoreList2, score);
                        createFileWithUsernames(usernameList2, username);
                        sortFile(score2, scoreList2, usernameList2, filename2, readUsernames2, readScore2);
                    }
                    else if (dimension == 6)
                    {
                        createFileWithScore(score3, scoreList3, score);
                        createFileWithUsernames(usernameList3, username);
                        sortFile(score3, scoreList3, usernameList3, filename3, readUsernames3, readScore3);
                    }
                    else if (dimension == 7)
                    {
                        createFileWithScore(score4, scoreList4, score);
                        createFileWithUsernames(usernameList4, username);
                        sortFile(score4, scoreList4, usernameList4, filename4, readUsernames4, readScore4);
                    }
                    else if (dimension == 8)
                    {
                        createFileWithScore(score5, scoreList5, score);
                        createFileWithUsernames(usernameList5, username);
                        sortFile(score5, scoreList5, usernameList5, filename5, readUsernames5, readScore5);
                    }
                    else if (dimension == 9)
                    {
                        createFileWithScore(score6, scoreList6, score);
                        createFileWithUsernames(usernameList6, username);
                        sortFile(score6, scoreList6, usernameList6, filename6, readUsernames6, readScore6);
                    }
                    else if (dimension == 10)
                    {
                        createFileWithScore(score7, scoreList7, score);
                        createFileWithUsernames(usernameList7, username);
                        sortFile(score7, scoreList7, usernameList7, filename7, readUsernames7, readScore7);
                    }
                    char quitOrContinue2;
                    cout << "GAME OVER!" << endl;
                    cout << "Your final score is: " << score << endl;
                    cout << "Enter 'm' to go back to the MENU or anything else to quit: ";
                    cin >> quitOrContinue2;
                    if (quitOrContinue2 == 'm')
                    {
                        system("cls");
                        goto MENU;
                    }
                    else
                    {
                        system("cls");
                        return 0;
                    }
                }
                cout << "Enter direction: ";
                cin >> direction;
                if (direction == 'w')
                {
                    moveUp(board, dimension, step, score);
                }
                else if (direction == 's')
                {
                    moveDown(board, dimension, step, score);
                }
                else if (direction == 'a')
                {
                    moveLeft(board, dimension, step, score);
                }
                else if (direction == 'd')
                {
                    moveRight(board, dimension, step, score);
                }
                else if (direction == 'q')
                {
                    if (dimension == 4)
                    {
                        createFileWithScore(score1, scoreList1, score);
                        createFileWithUsernames(usernameList1, username);
                        sortFile(score1, scoreList1, usernameList1, filename1, readUsernames1, readScore1);
                    }
                    else if (dimension == 5)
                    {
                        createFileWithScore(score2, scoreList2, score);
                        createFileWithUsernames(usernameList2, username);
                        sortFile(score2, scoreList2, usernameList2, filename2, readUsernames2, readScore2);
                    }
                    else if (dimension == 6)
                    {
                        createFileWithScore(score3, scoreList3, score);
                        createFileWithUsernames(usernameList3, username);
                        sortFile(score3, scoreList3, usernameList3, filename3, readUsernames3, readScore3);
                    }
                    else if (dimension == 7)
                    {
                        createFileWithScore(score4, scoreList4, score);
                        createFileWithUsernames(usernameList4, username);
                        sortFile(score4, scoreList4, usernameList4, filename4, readUsernames4, readScore4);
                    }
                    else if (dimension == 8)
                    {
                        createFileWithScore(score5, scoreList5, score);
                        createFileWithUsernames(usernameList5, username);
                        sortFile(score5, scoreList5, usernameList5, filename5, readUsernames5, readScore5);
                    }
                    else if (dimension == 9)
                    {
                        createFileWithScore(score6, scoreList6, score);
                        createFileWithUsernames(usernameList6, username);
                        sortFile(score6, scoreList6, usernameList6, filename6, readUsernames6, readScore6);
                    }
                    else if (dimension == 10)
                    {
                        createFileWithScore(score7, scoreList7, score);
                        createFileWithUsernames(usernameList7, username);
                        sortFile(score7, scoreList7, usernameList7, filename7, readUsernames7, readScore7);
                    }
                    return 0;
                }
                cout << "SCORE: " << score << endl;
            }
        }
        else
        {
        WRONGDIMENSION:
            cout << "The dimension you entered is invalid!" << endl << "Please enter dimension between 4 and 10 inclusive!" << endl;
            cout << "If you want to quit enter 0.";
            cin >> dimension;

            if (dimension >= 4 && dimension <= 10)
            {
                goto STARTGAME;
            }
            else if (dimension == 0)
            {
                return 0;
            }
            else
            {
                goto WRONGDIMENSION;
            }
        }
    }
    else if (myChoice == 2)
    {
    LEADERBOARD:
        system("cls");
        cout << "          LEADERBOARD          " << endl;
        cout << "1.Leaderboard for 4x4 dimension" << endl;
        cout << "2.Leaderboard for 5x5 dimension" << endl;
        cout << "3.Leaderboard for 6x6 dimension" << endl;
        cout << "4.Leaderboard for 7x7 dimension" << endl;
        cout << "5.Leaderboard for 8x8 dimension" << endl;
        cout << "6.Leaderboard for 9x9 dimension" << endl;
        cout << "7.Leaderboard for 10x10 dimension" << endl;
        cout << endl;

        cout << "Enter the number of the leaderboard you want to check: ";
        int number;
        cin >> number;

        if (number >= 1 && number <= 7)
        {
            system("cls");
            if (number == 1)
            {
                readFromLeaderboard(score1, scoreList1, usernameList1, filename1, readUsernames1, readScore1);
            }
            else if (number == 2)
            {
                readFromLeaderboard(score2, scoreList2, usernameList2, filename2, readUsernames2, readScore2);
            }
            else if (number == 3)
            {
                readFromLeaderboard(score3, scoreList3, usernameList3, filename3, readUsernames3, readScore3);
            }
            else if (number == 4)
            {
                readFromLeaderboard(score4, scoreList4, usernameList4, filename4, readUsernames4, readScore4);
            }
            else if (number == 5)
            {
                readFromLeaderboard(score5, scoreList5, usernameList5, filename5, readUsernames5, readScore5);
            }
            else if (number == 6)
            {
                readFromLeaderboard(score6, scoreList6, usernameList6, filename6, readUsernames6, readScore6);
            }
            else if (number == 7)
            {
                readFromLeaderboard(score7, scoreList7, usernameList7, filename7, readUsernames7, readScore7);
            }
        }
        else
        {
        WRONGNUMBER:
            system("cls");
            cout << "The number is invalid!" << endl << "Please enter a number between 1 and 7." << endl;
            cout << "If you want to quit press 0. ";
            cin >> number;
            if (number >= 1 && number <= 7)
            {
                goto LEADERBOARD;
            }
            else if (number == 0)
            {
                return 0;
            }
            else
            {
                goto WRONGNUMBER;
            }
        }

    }
    else if (myChoice == 3)
    {
        system("cls");
        return 0;
    }
    else
    {
    WRONGCHOICE:
        system("cls");
        cout << "Wrong number! Please enter number between 1 and 3. " << endl;
        cout << "If you want to quit enter 0. ";
        cin >> myChoice;
        if (myChoice >= 1 && myChoice <= 3)
        {
            system("cls");
            goto MENU;
        }
        else if (myChoice == 0)
        {
            return 0;
        }
        else
        {
            goto WRONGCHOICE;
        }
        return 0;
    }

    return 0;
}

