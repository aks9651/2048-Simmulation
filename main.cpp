#include <iostream>
#include<iomanip>
#include<ctime>
#include<cstdlib>

using namespace std;
int board[4][4];
int dirLine[]={1,0,-1,0};
int dirColm[]={0,1,0,-1};

pair<int,int> GenerateUnoccupiedPosition()
{
    int occupied =1,line,colm;
    while(occupied)
    {
        line = rand() % 4;
        colm = rand() % 4;
        if(board[line][colm]==0)
            occupied =0;
    }
    return make_pair(line, colm);
}

void Addpiece()
{
    pair<int, int> pos = GenerateUnoccupiedPosition();
    board[pos.first][pos.second]= 2;
}
void newGame()
{
    for(int i =0; i<4; i++)

        for(int j =0; j<4; j++)

            board[i][j]=0;
        pair<int, int> pos = GenerateUnoccupiedPosition();
        board[pos.first][pos.second] = 2;


}

void printUI()
{
    system("cls");
    for(int i =0; i<4; i++)
    {
        for(int j =0; j<4; j++)
        {
            if(board[i][j]==0)
                cout<< setw(4) << "_";
            else
                cout<< setw(4) <<board[i][j];
        }
        cout<< endl;
    }
    cout<< "n.newgame w:up s:down a:left d:right"<< endl;
    cout<< "q. quit";
    cout<< endl;
}
bool CanDoMove(int line, int colm, int nextLine , int nextColm)
{
    if(nextLine<0 || nextColm<0 || nextLine>=4 || nextColm>=4 || board[line][colm] != board[nextLine][nextColm]
       && board[nextLine][nextColm] != 0)
        return false;
    return true;
}
void applyMove(int direction)
{
    int startLine=0,startColm=0;
    int lineStep =1, colmStep=1;

    if(direction == 0) {
        startLine =3;
        lineStep = -1;
    }
    if( direction == 1) {
        startColm =3;
        colmStep = -1;
    }
    int movePossible,canAddPiece=0;
    do {
        movePossible=0;
        for(int i =startLine; i>=0 && i<4; i += lineStep)
        {
            for(int j = startColm; j>=0 && j< 4; j += colmStep)
            {
                int nextI = i + dirLine[direction];
                int nextJ = j + dirColm[direction];
                if(board[i][j] && CanDoMove(i, j, nextI, nextJ)) {
                        board[nextI][nextJ] +=board[i][j];
                board[i][j]=0;
                movePossible = canAddPiece =1;

                }
            }
        }
        //printUI(); optional to see the real movment of block moving.
    } while(movePossible);
    if(canAddPiece) {
        Addpiece();
    }

}

int main()
{
    srand(time(0));
    char commandToDir[128];
    commandToDir['s']=0;
    commandToDir['d']=1;
    commandToDir['w']=2;
    commandToDir['a']=3;
    newGame();
    while(true)
    {
        printUI();
        char command;
        cin>> command;
        if(command== 'n')
        {
            newGame();
        } else if(command == 'q') {
        break;
        }
        else {
            int currentDirection = commandToDir[command];
            applyMove(currentDirection);
        }
    }



    return 0;
}
