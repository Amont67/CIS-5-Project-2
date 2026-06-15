/*
    Author: Andrew Montes
    Date: June 5th, 2026
    Purpose: Connect 4 project 2 version 2.1
*/

//System Libraries 
#include <iostream> //Input/output Library 
#include <cstdlib>  //Random Number Library
#include <ctime>   //time library 
#include <fstream> //file input and output library 
#include <string>  //string library
#include <cmath>   //math library 
#include <iomanip> //format library 
#include <vector>  //vector library 
using namespace std; 

//User Libraries 

//Global Constants - Scientific/Physics/Chemistry/Conversions/Higher Dimensions 

//Functions Prototypes
void prntBrd ( int [][7], int , int );           //printing the board 
void initBrd ( int [][7], int , int );           //initializing board
void drpPiec ( int [][7], int , int );           //each piece that is being dropped
int compTrn ();                                  //Computer's turn
bool chkWin ( int [][7], int );                  //Checking for win condition  
void bblSort ( int [], string [], int );         // bubble sort scores
void selSort ( int [], string [], int );         // selection sort scores 
int lnrSrch ( string [], int, string );          //linear search for player 
void shwScrs ( int [], string [], int, string ); //show final scores
void swap1 ( int &, int & );                     //swap integers
void swap2 ( string &, string & );               //swap strings - overloaded
void prntHst ( vector<string> );                 //print game history - passes vector

//Execution Begins Here
int main(int argv,char **argc) {
    //Set the Random Number Seed
    srand(static_cast<unsigned int>(time(0)));

    //Declare vartiables 
    const int ROWS = 6; //Max rows on the board 
    const int COLS = 7; //Max columns on the board
    const int PLYRS = 2; //Max amount of players 
    int board [6][7];

    int colChce; //Players choice on what column they are inputting 
    
    int p2Col; // player 2 column 

    string plyrNm; //Player's name inputng 
    string plyrNms[2]; //Player's name input 
    fstream in,
            out; //input and output files for player name

    bool isClVal; //Column input valid?

    float fillPct, //percentage of the board that has been filled
          spcLft; // spaces left on the board 

    int rounds; //Number of rounds that have been completed
    int scores[2],
        p1Wins,
        p2Wins; //win counters 

    vector <string> gameHst; //Game hsitory 

    //Intialize Variables 
    colChce = 0; //no column chosen yet 

    in.open ("in.dat", ios :: in);
    out.open ("out.dat", ios :: out);
    in >> plyrNm;

    isClVal = false;

    fillPct = 0.0f; //board starts off empty  
    spcLft = 0.0f; //^^

    rounds = 0; //starts off at 0

    plyrNms[0] = plyrNm;
    plyrNms[1] = "Computer";
    scores[0] = 0;
    scores[1] = 0;
    p1Wins = 0;
    p2Wins = 0;



    //Welcome message
    cout << "Welcome to Connect 4 " << plyrNm << "!" << endl;
    cout << "The goal is to be the first to connect four of your own discs in a row—horizontally, vertically, or diagonally!" << endl;

    //Outputting game board 
    initBrd ( board, ROWS, COLS );
    prntBrd ( board, ROWS, COLS );


    //Game loop keeps until board is full 
    while (fillPct < 1.0f && colChce != 99){
        rounds++;
        cout << "ROUNDS - " << rounds << endl << endl;

        //Matching Player 1's input to inputted column
        do {
            cout << "Player 1 choose a column [1-7]." << endl;
            cout << "Input '99' to quit." << endl;
            cin >> colChce;
            if (colChce == 99){
                cout << "Thanks for playing " << plyrNm << endl;
            } else if (colChce < 1 || colChce > 7){
                cout << "Invalid input please choose between 1 and 7." << endl;
                isClVal = false;
            } else {
                isClVal = true;
            }
        } while ((colChce < 1 || colChce > 7) && colChce != 99); //checking if user inputs anything less then 1 or greater than 7 - keeps looping

        if (colChce != 99){ // only run if player didnt quit/99    
            drpPiec ( board, colChce - 1, 1 );
            if ( chkWin ( board, 1 ) ) {
                prntBrd ( board, ROWS, COLS );
                scores [0]++;
                p1Wins++;
                gameHst.push_back ( plyrNm + " won round " + to_string ( rounds ) );
                cout << plyrNm << " wins round " << rounds << "! Score: " << scores [0] << "-" << scores[1]<< endl;
                out << plyrNm << " wins round " << rounds << "!" << endl;
                if ( p1Wins == 3 ) {
                    shwScrs ( scores, plyrNms, PLYRS, plyrNm );
                    prntHst ( gameHst );
                    cout << plyrNm << " wins the match!" << endl;
                    out << plyrNm << " wins the match!" << endl;
                    exit (0);
                }
                initBrd ( board, ROWS, COLS );
            }

            //Player 2 / computers random input
            p2Col = compTrn();
            drpPiec ( board, p2Col - 1, 2 );
            if ( chkWin ( board, 2 ) ) {
                prntBrd ( board, ROWS, COLS );
                scores [1]++;
                p2Wins++;
                gameHst.push_back ( " Computer won round " + to_string ( rounds ) );
                cout << "Computer wins round " << rounds << "! Score: " << scores [0] << "-" << scores[1]<< endl;
                out << "Computer wins round " << rounds << "!" << endl;
                if ( p2Wins == 3 ) {
                    shwScrs ( scores, plyrNms, PLYRS, plyrNm );
                    prntHst ( gameHst );
                    cout << "Computer wins the match!" << endl;
                    out << "Computer wins the match!" << endl;
                    exit (0);
                }
                initBrd ( board, ROWS, COLS );
            }

            //Print updated board
            prntBrd ( board, ROWS, COLS );

            //Mapping Input to Output
            out << plyrNm << " placed X at column " << colChce << endl;
            cout << plyrNm << " placed X at column " << colChce << endl;

            out << "Computer placed O at column " << p2Col << endl;
            cout << "Computer placed O at column " << p2Col << endl << endl;

            //Board percentage
            int total = 0;
            for ( int indx = 0; indx < ROWS; indx++ )
                for ( int jndx = 0; jndx < COLS; jndx++ )
                    if ( board [indx][jndx] != 0 ) total++;
            fillPct = total / 42.0f;
                cout << fixed << setprecision(2) << "Board filled: " << fillPct * 100 << "%" << endl;
                out << fixed << setprecision(2) << "Board filled: " << fillPct * 100 << "%" << endl << endl;

            //Calculating remaining board spaces
            spcLft = round(42 - (fillPct * 42));
                cout << "Spaces left: " << spcLft << endl;
                out << "Spaces left: " << spcLft << endl;

            //warning to player that board is almost full or theres plenty of time 
            cout << (spcLft <= 10 ? "Board is almost full!"
                                  : "Plenty of spaces left!") << endl;
            out << (spcLft <= 10 ? "Board is almost full!"
                                 : "Plenty of spaces left!") << endl;
        }
    }

    //Sorting and final scores 
    bblSort ( scores, plyrNms, PLYRS );
    cout << "\n-- Final Scores --" << endl;
    for ( int indx = 0; indx < PLYRS; indx++ )
        cout << plyrNms [indx] << "." << scores[indx] << endl;

    //searching for player - linear search 
    int pos = lnrSrch ( plyrNms, PLYRS, plyrNm );
    if ( pos != -1 )
        cout << plyrNm << " finished in position " << pos + 1 << endl;

    //Closing files
    in.close();
    out.close();

    //Exit Stage Right
    return 0;
}

void drpPiec ( int board [][7], int col, int piec ) {
    for ( int indx = 5; indx >= 0; indx-- ) {
        if ( board [indx][col] == 0 ) {
            board [indx][col] = piec;
            return;
        }
    }
}

void initBrd ( int board [][7], int rows, int cols) {
    for ( int indx = 0; indx < rows; indx++ )
        for ( int jndx = 0; jndx < cols; jndx++ )
            board [indx][jndx] = 0;
}

void prntBrd ( int board[][7], int rows , int cols ) {  
    cout << "   1 2 3 4 5 6 7 " << endl;  //Labels for columns [1-7]
    cout << "  ---------------" << endl;  //Top boarder 
    for ( int indx = 0; indx < rows; indx++ ) {
        cout << ( char )( 'A' + indx ) << " ";   //Labels for rows [A-F]
        for ( int jndx = 0; jndx < cols; jndx++ ) { 
            if ( board [indx][jndx] == 0 )      cout << "|-";
            else if ( board [indx][jndx] == 1 ) cout << "|X";
            else                                cout << "|O";
        }
        cout << "|" << endl;
    }
    cout << "  ---------------" << endl;  //Bottom boarder
}

int compTrn () {
    static int cnt = 0; //counts how many times computer has played 
    cnt++;
    return ( rand () % 7 ) + 1;
}

bool chkWin ( int board [][7], int piec ) {
    //Checking for horiztonal win 
    for ( int indx = 0; indx < 6; indx++ ) {
        for ( int jndx = 0; jndx < 4; jndx++ ) {
            if ( board [indx][jndx] == piec &&
                 board [indx][jndx + 1] == piec &&
                 board [indx][jndx + 2] == piec &&
                 board [indx][jndx + 3] == piec )
                 return true;
        }
    }
    //Checking for verticl win 
    for ( int indx = 0; indx < 3; indx++ ) {
        for ( int jndx = 0; jndx < 7; jndx++ ) {
            if ( board [indx][jndx] == piec &&
                 board [indx + 1][jndx] == piec &&
                 board [indx + 2][jndx] == piec &&
                 board [indx + 3][jndx] == piec )
                 return true;
        }
    }
    //Checking for diagonal win - down and right 
    for ( int indx = 0; indx < 3; indx++ ) {
        for ( int jndx = 0; jndx < 4; jndx++ ) {
            if ( board [indx][jndx] == piec &&
                 board [indx + 1][jndx + 1] == piec &&
                 board [indx + 2][jndx + 2] == piec &&
                 board [indx + 3][jndx + 3] == piec )
                 return true;
        }
    }
    //Checking for diagonal win - down and left 
    for ( int indx = 0; indx < 3; indx++ ) {
        for ( int jndx = 3; jndx < 7; jndx++ ) {
            if ( board [indx][jndx] == piec &&
                 board [indx + 1][jndx - 1] == piec &&
                 board [indx + 2][jndx - 2] == piec &&
                 board [indx + 3][jndx - 3] == piec )
                 return true;
        }
    }
    return false;
}

//Bubble sory - sorting scores high to low
void bblSort ( int scores[], string names [], int size ) {
    for ( int indx = 0; indx < size - 1; indx++ ) {
        for ( int jndx = 0; jndx < size - indx - 1; jndx++ ) {
            if ( scores [jndx] < scores [jndx + 1] ) {
                //swap 
                swap1 ( scores [jndx], scores [jndx + 1] );
                swap2 ( names [jndx], names [jndx + 1] );
            }
        }
    }
}

//Selection sort - sorting names low to high 
void selSort ( int scores [], string names [], int size ) {
    for ( int indx = 0; indx < size - 1; indx++ ) {
        int minIndx = indx;
        for ( int jndx = indx + 1; jndx < size; jndx++ ) {
            if ( scores [jndx] < scores [minIndx] )
                minIndx = jndx;
        }
        //swap 
        swap1 ( scores [indx], scores [minIndx] );
        swap2 ( names [indx], names [minIndx] );
    }
}

//Linear search for player by name 
int lnrSrch ( string names [], int size, string target ) {
    for ( int indx = 0; indx < size; indx++ ) {
        if ( names [indx] == target )
            return indx;
    }
    return -1; //if not found 
}

//Show Final Scores after game ends
void shwScrs ( int scores[], string names[], int size, string player ) {
    //Sort scores high to low
    bblSort ( scores, names, size );
    //Display leaderboard
    cout << "\n-- Final Scores --" << endl;
    for ( int indx = 0; indx < size; indx++ )
        cout << names[indx] << ": " << scores[indx] << endl;
    //Search for player 
    int pos = lnrSrch ( names, size, player );
    if ( pos != -1 )
        cout << player << " finished in position " << pos + 1 << endl;
}

void swap1 ( int &a, int &b ) {
    int temp = a;
    a = b;
    b = temp;
}
void swap2 ( string &a, string &b ) {
    string temp = a;
    a = b;
    b = temp;
}

//Print game history 
void prntHst ( vector<string> hist ) {
    cout << "\n-- Game History --" << endl;
    for ( int indx = 0; indx < hist.size(); indx++ )
        cout << indx + 1 << ". " << hist[indx] << endl;
}
