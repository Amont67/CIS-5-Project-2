/*
    Author: Andrew Montes
    Date: June 3rd, 2026
    Purpose: Connect 4 project 2 version 2.0 
*/

//System Libraries 
#include <iostream> //Input/output Library 
#include <cstdlib>  //Random Number Library
#include <ctime>   //time library 
#include <fstream> //file input and output library 
#include <string>  //string library
#include <cmath>   //math library 
#include <iomanip> //format library 
using namespace std; 

//User Libraries 

//Global Constants - Scientific/Physics/Chemistry/Conversions/Higher Dimensions 

//Functions Prototypes
void prntBrd ( int [][7], int , int ); //printing the board 
void initBrd ( int [][7], int , int ); //initializing board
void drpPiec ( int [][7], int , int ); //each piece that is being dropped
int compTrn ();                        //Computer's turn
bool chkWin ( int [][7], int );        //Checking for win condition  

//Execution Begins Here
int main(int argv,char **argc) {
    //Set the Random Number Seed
    srand(static_cast<unsigned int>(time(0)));

    //Declare vartiables 
    const int ROWS = 6; //Max rows on the board 
    const int COLS = 7; //Max columns on the board
    int board [6][7];

    int colChce; //Players choice on what column they are inputting 
    
    int p2Col; // player 2 column 

    string plyrNm; //Player's name input
    fstream in,
            out; //input and output files for player name

    bool isClVal; //Column input valid?

    float fillPct, //percentage of the board that has been filled
          spcLft; // spaces left on the board 

    int rounds; //Number of rounds that have been completed

    //Intialize Variables 
    colChce = 0; //no column chosen yet 

    in.open ("in.dat", ios :: in);
    out.open ("out.dat", ios :: out);
    in >> plyrNm;

    isClVal = false;

    fillPct = 0.0f; //board starts off empty  
    spcLft = 0.0f; //^^

    rounds = 0; //starts off at 0


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
                cout << plyrNm << " wins!" << endl;
                out << plyrNm << " wins!" << endl;
                exit (0);
            }

            //Player 2 / computers random input
            p2Col = compTrn();
            drpPiec ( board, p2Col - 1, 2 );
            if ( chkWin ( board, 2 ) ) {
                prntBrd ( board, ROWS, COLS );
                cout << "Computer wins!" << endl;
                out << "Computer wins!" << endl;
                exit (0);
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
    //Display the Results

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
