#include <iostream>
#include <random>
#include <ctime>
#include <string>
#include <iomanip>


int playerTurn(char, char, char, char, char, char, char, char, char);
int aiTurn(std::default_random_engine&, char, char, char, char, char, char, char, char, char);
int convertEntry(std::string);
void playMove(int, char&, char&, char&, char&, char&, char&, char&, char&, char&, char);
void printBoard(char, char, char, char, char, char, char, char, char);
bool isPCFirst(std::default_random_engine&);
bool isValidMove(int, char, char, char, char, char, char, char, char, char);
bool boardFull(char, char, char, char, char, char, char, char, char);
bool playAgain();
bool playTurn(std::default_random_engine&, char&, char&, char&, char&, char&, char&, char&, char&, char&, char, bool);
bool gameOver(char, char, char, char, char, char, char, char, char, char, bool);

const int NB_TILES = 9;
const char SYMBOLP1 = 'X';
const char SYMBOLP2 = 'O';

int main()
{
    bool play = true;
  
    std::default_random_engine engine(static_cast<unsigned int>(time(0)));

    while (play)
    {
        char tile1 = '1';
        char tile2 = '2';
        char tile3 = '3';
        char tile4 = '4';
        char tile5 = '5';
        char tile6 = '6';
        char tile7 = '7';
        char tile8 = '8';
        char tile9 = '9';
        char symbol = SYMBOLP1;

        bool isGameOver = false;
        bool isPlayerTurn = isPCFirst(engine);

        printBoard(tile1, tile2, tile3, tile4, tile5, tile6, tile7, tile8, tile9);

        while(!isGameOver)
        {
            isGameOver = playTurn(engine, tile1, tile2, tile3, tile4, tile5, tile6, tile7, tile8, tile9, symbol, isPlayerTurn);
            symbol = (symbol == SYMBOLP1) ? SYMBOLP2 : SYMBOLP1;
            isPlayerTurn = !isPlayerTurn;
        }
        play = playAgain();
    }
    return 0;
}

int playerTurn(char tile1, char tile2, char tile3, char tile4, char tile5,
               char tile6, char tile7, char tile8, char tile9)
{
    int placement = 0;
    std::string entry = "";
    while (true)
    {
        std::cout << "Veuillez entrer votre placement (1-9): ";
        std::cin >> entry;
        placement = convertEntry(entry);
        if (placement < 1 || placement > 9 || entry.length() > 1)
        {
            std::cout << "Entree invalide" << std::endl;
        }
        else if (!isValidMove(placement, tile1, tile2, tile3, tile4, tile5, tile6, tile7, tile8, tile9))
        {
            std::cout << "Case deja prise!" << std::endl;
        }
        else
        {
            std::cout << "Vous avez joue dans l'emplacement " << placement << std::endl;
            return placement;
        }
    }
}

int aiTurn(std::default_random_engine& engine, char tile1, char tile2, char tile3,
           char tile4, char tile5, char tile6, char tile7, char tile8, char tile9)

{
    int placement = 0;
    std::uniform_int_distribution<unsigned int> randomInt(1, NB_TILES);
    while (true)
    {
        for (int i = 0; i <= 5; i++)
        {
            placement = static_cast<char>(randomInt(engine));
            if (isValidMove(placement, tile1, tile2, tile3, tile4, tile5, tile6, tile7, tile8, tile9))
            {
                std::cout << "L'ordinateur a joue dans l'emplacement " << placement << std::endl;
                return placement;
            }
        }
        for (int i = 0; i <= NB_TILES; i++)
        {
            if (isValidMove(i, tile1, tile2, tile3, tile4, tile5, tile6, tile7, tile8, tile9))
            {
                std::cout << "L'ordinateur a joue dans l'emplacement " << i << std::endl;
                return i;
            }
        }
    }
}

void playMove(int placement, char& tile1, char& tile2, char& tile3, char& tile4, char& tile5,
              char& tile6, char& tile7, char& tile8, char& tile9, char symbol)
{
    switch (placement)
    {
    case 1: tile1 = symbol; break;
    case 2: tile2 = symbol; break;
    case 3: tile3 = symbol; break;
    case 4: tile4 = symbol; break;
    case 5: tile5 = symbol; break;
    case 6: tile6 = symbol; break;
    case 7: tile7 = symbol; break;
    case 8: tile8 = symbol; break;
    case 9: tile9 = symbol; break;
    default:
        std::cout << "Should never reach here" << std::endl;
    }
}

void printBoard(char tile1, char tile2, char tile3, char tile4, char tile5,
                char tile6, char tile7, char tile8, char tile9)
{
    std::cout << std::endl;
    std::cout << " " << tile1 << " | " << tile2 << " | " << tile3 << std::endl;
    std::cout << "---" << '+' << "---" << '+' << "---" << std::endl;
    std::cout << " " << tile4 << " | " << tile5 << " | " << tile6 << std::endl;
    std::cout << "---" << "+" << "---" << "+" << "---" << std::endl;
    std::cout << " " << tile7 << " | " << tile8 << " | " << tile9 << std::endl;
    std::cout << std::endl;
}

bool isPCFirst(std::default_random_engine& engine)
{
    std::uniform_int_distribution<unsigned int> randomInt(0, 1);
    bool isPlayerFirst = randomInt(engine);
    if (isPlayerFirst)
    {
        std::cout << "Vous jouez en premier" << std::endl;
    }
    else
    {
        std::cout << "L'ordinateur joue en premier" << std::endl;
    }
    return isPlayerFirst;
}

bool boardFull(char tile1, char tile2, char tile3, char tile4, char tile5,
               char tile6, char tile7, char tile8, char tile9)
{

    if (tile1 != '1' && tile2 != '2' && tile3 != '3' &&
        tile4 != '4' && tile5 != '5' && tile6 != '6' &&
        tile7 != '7' && tile8 != '8' && tile9 != '9')
    {
        std::cout << "Partie nulle!" << std::endl;
        return true;
    }
    else
    {
        return false;
    }
}

int convertEntry(std::string entry)
{
    char selection = entry.at(0);
    switch (selection)
    {
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
            return selection - '0';
        default:
            return 0;
    }
}

bool isValidMove(int placement, char tile1, char tile2, char tile3, char tile4,
                 char tile5, char tile6, char tile7, char tile8, char tile9)
{
    switch (placement)
    {
        case 1: return (tile1 == '1');
        case 2: return (tile2 == '2');
        case 3: return (tile3 == '3');
        case 4: return (tile4 == '4');
        case 5: return (tile5 == '5');
        case 6: return (tile6 == '6');
        case 7: return (tile7 == '7');
        case 8: return (tile8 == '8');
        case 9: return (tile9 == '9');
        default: return false;
    }
}

bool gameOver(char tile1, char tile2, char tile3, char tile4, char tile5, char tile6,
              char tile7, char tile8, char tile9, char symbol, bool isPlayerTurn)
{

    if ((tile1 == tile2 && tile2 == tile3 && tile1 == symbol) ||
        (tile4 == tile5 && tile5 == tile6 && tile4 == symbol) ||
        (tile7 == tile8 && tile8 == tile9 && tile7 == symbol) ||
        (tile1 == tile4 && tile4 == tile7 && tile1 == symbol) ||
        (tile2 == tile5 && tile5 == tile8 && tile2 == symbol) ||
        (tile3 == tile6 && tile6 == tile9 && tile3 == symbol) ||
        (tile1 == tile5 && tile5 == tile9 && tile1 == symbol) ||
        (tile3 == tile5 && tile5 == tile7 && tile3 == symbol))
    {
        if (isPlayerTurn)
        {
            std::cout << "Vous avez gagne avec les " << symbol << "!" << std::endl;
            return true;
        }
        else
        {
            std::cout << "l'ordinateur a gagne avec les " << symbol << "!" << std::endl;
            return true;
        }
    }
    else
    {
        return false;
    }
}

bool playAgain()
{
    std::string entry = "";
    char playAgain = ' ';

    while (1)
    {
        std::cout << "Voulez-vous rejoue? (O/N) : ";
        std::cin >> entry;
        playAgain = entry.at(0);
        if ((playAgain == 'O' || playAgain == 'o') && entry.length() == 1)
        {
            return true;
        }
        else if ((playAgain == 'N' || playAgain == 'n') && entry.length() == 1)
        {
            return false;
        }
        else
        {
            std::cout << "Entree invalide" << std::endl;
        }
    }
}

bool playTurn(std::default_random_engine& engine, char& tile1, char& tile2, char& tile3, char& tile4, char& tile5,
    char& tile6, char& tile7, char& tile8, char& tile9, char symbol, bool isPlayerTurn)
{
    int placement = 0;

    if (isPlayerTurn)
    {
        placement = playerTurn(tile1, tile2, tile3, tile4, tile5, tile6, tile7, tile8, tile9);
    }
    else
    {
        placement = aiTurn(engine, tile1, tile2, tile3, tile4, tile5, tile6, tile7, tile8, tile9);
    }
    playMove(placement, tile1, tile2, tile3, tile4, tile5, tile6, tile7, tile8, tile9, symbol);
    printBoard(tile1, tile2, tile3, tile4, tile5, tile6, tile7, tile8, tile9);
    if (gameOver(tile1, tile2, tile3, tile4, tile5, tile6, tile7, tile8, tile9, symbol, isPlayerTurn))
    {
        return true;
    }
    else if (boardFull(tile1, tile2, tile3, tile4, tile5, tile6, tile7, tile8, tile9))
    {
        return true;
    }
    else
    {
        return false;
    }
}
