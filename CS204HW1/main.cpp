// Ismayil Taghi-Zada 00033582

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>


// these are definitions, to not have magic values.
#define INV_FILE (-6)
#define EMPTY (-5)
#define NO_MATCH (-4)
#define OUT_OF_BOUNDS (-3)
#define INV_INPUT (-2)
#define INV_COORDS (-1)
#define SUCCESS 0

//shortening the type
#define MATRIX std::vector<std::vector<char>>

// to not swap in matches_check()
#define NSWAP false


// just iterates through matrix and displays chars in matrix style
void show_matrix(const MATRIX& matrix) {
    for (auto & char_vec : matrix) {
        for (const char ch : char_vec) {
            std::cout << ch;
        }
        std::cout << std::endl;
    }
}

int matches_check(int row, int col, char direction, const MATRIX& matrix, bool move = true) {
    char temp;
    MATRIX temp_matrix(matrix);

    if (move) {
        if (direction == 'r') {
            temp = matrix[row][col];
            temp_matrix[row][col] = temp_matrix[row][col+1];
            temp_matrix[row][col+1] = temp;
        }
        else if (direction == 'l') {
            temp = matrix[row][col];
            temp_matrix[row][col] = temp_matrix[row][col-1];
            temp_matrix[row][col-1] = temp;
        }
        else if (direction == 'u') {
            temp = matrix[row][col];
            temp_matrix[row][col] = temp_matrix[row-1][col];
            temp_matrix[row-1][col] = temp;
        }
        else if (direction == 'd') {
            temp = matrix[row][col];
            temp_matrix[row][col] = temp_matrix[row+1][col];
            temp_matrix[row+1][col] = temp;
        }
    }

    // horizontal check
    for (const auto & i : temp_matrix) {
        for (int j = 0; j <= i.size() - 3; j++) {
            if (i[j] != '-' && i[j] == i[j + 1] && i[j + 1] == i[j + 2]) {
                return SUCCESS;
            }
        }
    }

    // vertical check
    for (int j = 0; j < temp_matrix[0].size(); j++) {
        for (int i = 0; i <= temp_matrix.size() - 3; i++) {
            if (temp_matrix[i][j] != '-' && temp_matrix[i][j] == temp_matrix[i + 1][j] && temp_matrix[i][j] == temp_matrix[i + 2][j]) {
                return SUCCESS;
            }
        }
    }
    return NO_MATCH;
}

// check oob and matches, and perform swap in matrix
int swap(int row, int col, char direction, MATRIX& matrix) {
    char temp;
    if (direction == 'r') {
        if (col+1 >= matrix[row].size()) {
            return OUT_OF_BOUNDS;
        }
        if (matrix[row][col+1] == '-' || matrix[row][col] == '-') {
            return EMPTY;
        }
        if (matches_check(row, col, direction, matrix) == NO_MATCH) {
            return NO_MATCH;
        }
        temp = matrix[row][col];
        matrix[row][col] = matrix[row][col+1];
        matrix[row][col+1] = temp;
        return SUCCESS;
    }
    if (direction == 'l') {
        if (col-1 < 0) {
            return OUT_OF_BOUNDS;
        }
        if (matrix[row][col-1] == '-' || matrix[row][col] == '-') {
            return EMPTY;
        }
        if (matches_check(row, col, direction, matrix) == NO_MATCH) {
            return NO_MATCH;
        }
        temp = matrix[row][col];
        matrix[row][col] = matrix[row][col-1];
        matrix[row][col-1] = temp;
        return SUCCESS;
    }
    if (direction == 'u') {
        if (row-1 < 0) {
            return OUT_OF_BOUNDS;
        }
        if (matrix[row-1][col] == '-' || matrix[row][col] == '-') {
            return EMPTY;
        }
        if (matches_check(row, col, direction, matrix) == NO_MATCH) {
            return NO_MATCH;
        }
        temp = matrix[row][col];
        matrix[row][col] = matrix[row-1][col];
        matrix[row-1][col] = temp;
        return SUCCESS;
    }
    if (direction == 'd') {
        if (row+1 >= matrix.size()) {
            return OUT_OF_BOUNDS;
        }
        if (matrix[row+1][col] == '-' || matrix[row][col] == '-') {
            return EMPTY;
        }
        if (matches_check(row, col, direction, matrix) == NO_MATCH) {
            return NO_MATCH;
        }
        temp = matrix[row][col];
        matrix[row][col] = matrix[row+1][col];
        matrix[row+1][col] = temp;
        return SUCCESS;
    }
    return INV_INPUT; // return in case direction is wrong
}

int clear(MATRIX& matrix) {
    // horizontal clear
    for (auto & i : matrix) {
        for (int j = 0; j <= i.size()-3; j++) {
            if (i[j] != '-' && i[j] == i[j+1] && i[j] == i[j+2]) {
                int k = j;
                const char temp = i[j];
                while (k < i.size() && i[k] == temp) {
                    i[k] = '-';
                    k++;
                }
            }
        }
    }

    // vertical clear
    for (int i = 0; i < matrix[0].size(); i++) {
        for (int j = 0; j <= matrix.size()-3; j++) {
            if (matrix[j][i] != '-' && matrix[j][i] == matrix[j+1][i] && matrix[j][i] == matrix[j+2][i]) {
                int k = j;
                const char temp = matrix[j][i];
                while (k < matrix.size() && matrix[k][i] == temp) {
                    matrix[k][i] = '-';
                    k++;
                }
            }
        }
    }
    return SUCCESS;
}
int gravity(MATRIX& matrix) {
    // for (int i = 0; i < matrix.size()-1; i++) {
    //     for (int j = 0; j < matrix[i].size(); j++) {
    //         if (matrix[i+1][j] == '-') {
    //             temp = matrix[i][j];
    //             matrix[i][j] = matrix[i+1][j];
    //             matrix[i+1][j] = temp;
    //         }
    //     }
    // }
    for (int i = matrix.size()-1; i >= 0; i--) {
        for (int j = 0; j < matrix[0].size(); j++) {
            if (matrix[i][j] == '-') {
                for (int k = 0; k < i; k++) {
                    if (matrix[k][j] != '-') {
                        char temp = matrix[k][j];
                        matrix[k][j] = matrix[i][j];
                        matrix[i][j] = temp;
                    }
                }
            }
        }
    }
    return SUCCESS;
}


int main() {
    MATRIX matrix;
    std::string filename;
    std::ifstream file;
    bool open = false;
    std::string message = "Please enter the file name:";
    // dimensions and symbols checks and parsing
    while (!open) {
        std::cout << message << std::endl;
        std::getline(std::cin, filename);
        if (file.open(filename); file.is_open()) {
            std::string line;
            std::vector<char> buffer;
            while (file && file.good()) {
                std::getline(file, line);
                for (auto ch : line) {
                    if (ch != 'X' && ch != 'O' && ch != 'S') { // symbols check
                        std::cout << "The matrix either has invalid dimensions or contains invalid characters." << std::endl << "Exiting the game. Bye bye." << std::endl;
                        return INV_FILE;
                    }
                    buffer.push_back(ch);
                }
                matrix.push_back(buffer); // matrix parsing
                buffer.clear();
            }
            for (int i = 0; i < matrix.size(); i++) { // dims check
                for (int j = 0; j < matrix.size(); j++) {
                    if (matrix[i].size() != matrix[j].size()) {
                        std::cout << "The matrix either has invalid dimensions or contains invalid characters." << std::endl << "Exiting the game. Bye bye." << std::endl;
                        return INV_FILE;
                    }
                }
            }
            std::cout << "The content of the matrix is:" << std::endl;
            show_matrix(matrix);
            std::cout << std::endl;
            open = true;
        }
        else {
            std::cout << "The file couldn't be opened." << std::endl;
            message = "Please enter a valid file name:";
        }
    }
    file.close();
    // end checks

    std::string move_string;
    std::cout << "Enter row, col, and direction (r/l/u/d). Type '0 0 q' to exit." << std::endl;
    while (true) {
        int row = - 1, col = -1;
        char direction = '.'; // if input doesn't contain all the chars, it will automatically fail.

        std::cout << "Move:" << std::endl;
        std::getline(std::cin, move_string);

        if (move_string == "0 0 q") {
            std::cout << "Exiting the game. Bye bye." << std::endl;
            return -1;
        }

        std::istringstream stream(move_string);
        stream >> row;
        stream >> col;
        stream >> direction;

        if (row < 0 || col < 0) {
            std::cout << "Invalid input. Try again." << std::endl;
        }
        else if (row >= matrix.size() || col >= matrix[row].size()) {
            std::cout << "Invalid coordinates!" << std::endl;
        }
        else {
            int RESULT = swap(row, col, direction, matrix);
            if (RESULT == OUT_OF_BOUNDS) {
                std::cout << "Move out of bounds!" << std::endl;
            }
            else if (RESULT == INV_INPUT) {
                std::cout << "Invalid input. Try again." << std::endl;
            }
            else if (RESULT == NO_MATCH) {
                std::cout << "Invalid move: No match found!" << std::endl;
            }
            else if (RESULT == EMPTY) {
                std::cout << "Cannot swap with an empty cell!" << std::endl;
            }
            else if (RESULT == SUCCESS) {
                std::cout << "After swap:" << std::endl;
                show_matrix(matrix);
                std::cout << std::endl << "Move successful. Clearing matches..." << std::endl;
                while (matches_check(row, col, direction, matrix, NSWAP) == SUCCESS) {
                    std::cout << "After clearing matches:" << std::endl;
                    clear(matrix);
                    show_matrix(matrix);
                    std::cout << std::endl;
                    std::cout << "After applying gravity:" << std::endl;
                    gravity(matrix);
                    show_matrix(matrix);
                    std::cout << std::endl;
                }
            }
        }
    }
}