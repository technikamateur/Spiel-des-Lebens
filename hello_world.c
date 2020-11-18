#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// game size ist 16
// is there a way to create gameBoard with gameSize ?
const int gameSize = 16;
int gameBoard[16][16];

void field_initializer()
{
    // fills fields with random numbers 0 = dead, 1 = alive
    srand(time(0));
    for (int i = 0; i < gameSize; i++)
    {
        for (int j = 0; j < gameSize; j++)
        {
            gameBoard[i][j] = rand() % 2;
        }
    }
    return;
}

int calculate_next_gen_cell(int neighbours)
{
    // cell will be dead
    if (neighbours < 2 || neighbours > 3)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

void calculate_next_gen()
{
    int nextGen[gameSize][gameSize];

    // i = row, j = column
    for (int i = 0; i < gameSize; i++)
    {
        for (int j = 0; j < gameSize; j++)
        {
            // coi = Cell of Interest
            int coi = gameBoard[i][j];
            // create an array which contains all neighbours
            int neighbourCounter = 0;

            // coi is left, top edge
            if (!i && !j)
            {
                if (gameBoard[0][1])
                {
                    neighbourCounter++;
                }
                else if (gameBoard[1][1])
                {
                    neighbourCounter++;
                }
                else if (gameBoard[1][0])
                {
                    neighbourCounter++;
                }
                nextGen[i][j] = calculate_next_gen_cell(neighbourCounter);
            }
        }
    }
    return;
}

int main()
{
    field_initializer();
    // print 2D array
    for (int i = 0; i < gameSize; i++)
    {
        for (int j = 0; j < gameSize; j++)
        {
            printf("%d ", gameBoard[i][j]);
        }
        printf("\n");
    }
    return 0;
}