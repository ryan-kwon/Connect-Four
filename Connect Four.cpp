#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string>
#include <cstring>
#include <cmath>

using namespace std;

bool num_present(string& sentence) {
    for (int i = 0; i < sentence.length(); i++) {
        int value = unsigned(sentence[i]);
        if (value >= 48 && value <= 57) {
            return true;
            break;
        }
    }
    return false;
}
string to_lower(string& sentence) {
    for (int i = 0; i < sentence.length(); i++) {
        if (sentence[i] >= 'A' && sentence[i] <= 'Z') {
            sentence[i] += 32;
        }
    }
    return sentence;
}
bool is_int(string& input) {
    for (int i = 0; i < input.length(); i++) {
        int value = unsigned(input[i]);
        if (value < 48 || value > 57) {
            return false;
        }
    }
    return true;
}
int get_int(string& input) {
    int x = 0;
    for (int i = 0; i < input.length(); i++) {
        int number = unsigned(input[i]);
        if (number >= 48 && number <= 57) {
            number -= 48; //to get the actual number
            x *= 10; //if it is a multidigit number, add on like append
            x += number;
        }
    }
    return x;
}
int NumCheck(string& input) {
    while (is_int(input) == false) {
        cout << "Invalid input\nTry again: ";
        input.clear();
        getline(cin, input);
    }
    while (get_int(input) > 20) {
        cout << "Invalid input\nTry again: ";
        input.clear();
        getline(cin, input);
    }

    return get_int(input);
}

void Build(char** array, int* x, int* y) {
    for (int i = 0; i < *x; i++) {
        array[i][0] = ' ';
        for (int j = 1; j < *y; j++) {
            array[i][j] = ' ';
        }
    }
}
void Print(char** array, int* x, int* y) {
    if (*y > 9) {//print numbers at the top
        for (int i = 0; i < 9; ++i) {
            cout << "  " << i + 1;
        }
        for (int i = 0; i < *y - 9; ++i) {
            cout << " " << i + 10;
        }
    }
    else {
        for (int i = 0; i < *y; ++i) {
            cout << "  " << i + 1;
        }
    }

    cout << endl;

    for (int i = 0; i < *x; i++) {
        for (int j = 0; j < *y; j++) {
            if (i % 2 == 0 && j % 2 == 0) {
                cout << "|\033[30;104m" << array[i][j] << " \033[0m";
            }
            else if (i % 2 == 1 && j % 2 == 1) {
                cout << "|\033[30;104m" << array[i][j] << " \033[0m";
            }
            else {
                cout << "|\033[43;30m" << array[i][j] << " \033[0m";
            }
            cout << "\033[0m";
        }

        cout << endl;
    }
}

char Switch(char* player) {
    if (*player == 'X') {
        *player = 'O';
    }
    else {
        *player = 'X';
    }
    return *player;
}

void CheckMove(char* player, char** array, int* x, int* y) {
    string place;
    int drop = 0;

    cout << "Player " << *player << " choose a place to drop: ";
    getline(cin, place);
    drop = NumCheck(place);
    place.clear();
    while (drop <= 0 || drop > *y) {
        cout << "False input\nTry again: ";
        getline(cin, place);
        drop = NumCheck(place);
        place.clear();
    }

    int num = 0;
    while (array[(*x - 1) - num][drop - 1] != ' ') {
        num++;
        if (num > (*x - 1)) {//check if that column filled
            cout << "Try again: ";
            getline(cin, place);
            drop = NumCheck(place);
            place.clear();
            num = 0;
        }
    }

    array[(*x - 1) - num][drop - 1] = *player;
}

bool Vertical(char* player, char** array, int* x, int* y) {
    for (int i = 0; i < *x - 3; i++) {
        for (int j = 0; j < *y; j++) {
            if (array[i][j] == *player && array[i + 1][j] == *player &&
                array[i + 2][j] == *player && array[i + 3][j] == *player) {
                return true;
            }
        }
    }
    return false;
}
bool Horizontal(char* player, char** array, int* x, int* y) {
    for (int j = 0; j < *y - 3; j++) {
        for (int i = 0; i < *x; i++) {
            if (array[i][j] == *player && array[i][j + 1] == *player &&
                array[i][j + 2] == *player && array[i][j + 3] == *player) {
                return true;
            }
        }
    }
    return false;
}
//TopRight to BottomLeft
bool FirstDiagonal(char* player, char** array, int* x, int* y) {
    for (int i = 3; i < *x; i++) {
        for (int j = 0; j < *y - 3; j++) {
            if (array[i][j] == *player && array[i - 1][j + 1] == *player &&
                array[i - 2][j + 2] == *player && array[i - 3][j + 3] == *player) {
                return true;
            }
        }
    }
    return false;
}
//TopLeft to BottomRight
bool SecDiagonal(char* player, char** array, int* x, int* y) {
    for (int i = 3; i < *x; i++) {
        for (int j = 3; j < *y; j++) {
            if (array[i][j] == *player && array[i - 1][j - 1] == *player &&
                array[i - 2][j - 2] == *player && array[i - 3][j - 3] == *player) {
                return true;
            }
        }
    }
    return false;
}
int Full(char* player, char** array, int* x, int* y) {
    int tie = 0;
    for (int i = 0; i < *x; i++) {
        for (int j = 0; j < *y; j++) {
            if (array[i][j] != ' ') {
                tie++;
            }
        }
    }
    return tie; //if tie == rows * columns
}
bool WinCheckMain(char* player, char** array, int* x, int* y) {
    if (Vertical(player, array, x, y) == true) {
        return true;
    }
    else if (Horizontal(player, array, x, y) == true) {
        return true;
    }
    else if (FirstDiagonal(player, array, x, y) == true) {
        return true;
    }
    else if (SecDiagonal(player, array, x, y) == true) {
        return true;
    }
    else {
        return false;
    }
}

void BuildArray(int* x, int* y, int* rows, int* columns) {
    char player = 'X';
    bool win = false;
    int tie = 0;

    char** array = new char* [*x];
    for (int i = 0; i < *x; ++i) {
        array[i] = new char[*y];
    }

    Build(array, rows, columns);
    cout << "New Board\n";
    Print(array, rows, columns);
    cout << endl;

    while (win == false) {
        CheckMove(&player, array, x, y);
        Print(array, rows, columns);
        win = WinCheckMain(&player, array, x, y);
        tie = Full(&player, array, x, y);
        if (win == true) {
            break;
        }
        if (tie == *x * *y) {
            break;
        }
        Switch(&player);
    }
    if (win == true) {
        cout << player << " won!" << endl;
    }
    if (tie == *x * *y) {
        cout << "Tie!" << endl;
    }

    for (int i = 0; i < *x; i++) {
        delete[] array[i];
    }
    delete[] array;
    array = NULL;
}

void NewInput(int* x, int* y, int* rows, int* columns) {
    string input;

    input.clear();
    cout << "Enter number of rows: ";
    getline(cin, input);
    *x = NumCheck(input);
    while (*x < 4) {
        input.clear();
        cout << "False input\nTry again: ";
        getline(cin, input);
        *x = NumCheck(input);
    }
    cout << "Enter number of columns: ";
    getline(cin, input);
    *y = NumCheck(input);
    while (*y < 4) {
        input.clear();
        cout << "False input\nTry again: ";
        getline(cin, input);
        *y = NumCheck(input);
    }

    *rows = *x;
    *columns = *y;

    BuildArray(x, y, rows, columns);
}

int main() {
    int x = 0, y = 0, rows = 0, columns = 0;
    string an = "";

    NewInput(&x, &y, &rows, &columns);

    while (an != "n") {
        cout << "Run again? (y/n): ";
        getline(cin, an);
        an = to_lower(an);
        while (num_present(an) == true || an.length() > 1) {
            an.clear();
            cout << "False input\nRun again? (y/n): ";
            getline(cin, an);
        }
        if (an == "y") {
            NewInput(&x, &y, &rows, &columns);
        }
    }

    cout << "\nThank you" << endl;
    return 0;
}