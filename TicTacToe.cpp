#include <array>
#include <iostream>

int main(int argc, char* argv[])
{
    std::array board =
        {
            '0', '1', '2',
            '3', '4', '5',
            '6', '7', '8'
        };


    std::cout
        << board[0] << " | " << board[1] << " | " << board[2] << '\n'
        << "---------\n"
        << board[3] << " | " << board[4] << " | " << board[5] << '\n'
        << "---------\n"
        << board[6] << " | " << board[7] << " | " << board[8] << '\n';

    int position;

    std::cout << "Choose a position: ";
    std::cin >> position;

    board[position] = 'X';

    return 0;
}
