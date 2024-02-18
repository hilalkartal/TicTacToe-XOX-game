#include <iostream>
#include <string>
#include <sstream>

using namespace std;

class Game{
    private: 
        char board[3][3];
        char current_player;
        bool game_over;
    public:
        Game();     //constructer, need to initialize the board
        bool get_game_over();
        char get_current_player();
        void draw_board();
        bool make_move(string);
        bool check_tie();
        bool check_win();
};

Game::Game(){
    //initialize the board
    for(int i = 0 ; i< 3 ; i++){
        for(int j = 0 ; j< 3 ; j++){
            board[i][j] = ' ';
        }
    }

    //X starts the game
    current_player = 'X';
    game_over = false;
}

void Game::draw_board(){
    for(int i = 0 ; i< 3 ; i++){
        for(int j = 0 ; j< 3 ; j++){
            cout << board[i][j];
            if(j < 2){
                cout << " | ";
            }
        }
        cout << endl;
        if(i<2){
            cout << "---------" << endl;
        }
    }
    cout << endl;
}

bool Game::make_move(string move){
    //split the users move into row and column
    string roworcol;
    int row, col;
    
    istringstream to_split(move);
    getline(to_split, roworcol, 'x');
    row = stoi(roworcol);
    getline(to_split, roworcol);
    col = stoi(roworcol);

    //if non-existing box is chosen
    if(row < 1 || row > 3 ){
        cout <<"please choose a valid row."<< endl << endl;
        return false;
    }else if(col > 3 || col < 1){
        cout <<"please choose a valid column."<< endl << endl;
        return false;
    }

    //check if box is already marked
    if(board[row-1][col-1] == 'X' || board[row-1][col-1] == 'O'){
        cout << "please choose an unmarked box." << endl;
        return false;
    }

    // mark the box as the current player (X or O)
    board[row-1][col-1] = current_player;
    draw_board();

    //check for win or tie
    if(check_win() || check_tie()){
        game_over = true;
    }
    else{
        //player change
        if(current_player == 'X'){
            current_player = 'O';
        }else{
            current_player = 'X';
        }
    }
    return true;
}

bool Game::check_win(){
    // yatay check
    for(int i = 0 ; i<3 ; i++){
        if(board[i][0] == 'X' && board[i][1] == 'X' && board[i][2] == 'X'){
            cout << "X won!" << endl;
            return true;
        }else if(board[i][0] == 'O' && board[i][1] == 'O' && board[i][2] == 'O'){
            cout << "O won!" << endl;
            return true;
        } 
    }
    //dikey check 
    for(int j = 0 ; j<3 ; j++){
        if(board[0][j] == 'X' && board[1][j] == 'X' && board[2][j] == 'X'){
            cout << "X won!" << endl;
            return true;
        }else if(board[0][j] == 'O' && board[1][j] == 'O' && board[2][j] == 'O'){
            cout << "O won!" << endl;
            return true;
        } 
    }
    //çapraz check
    for(int k = 0; k<3 ; k++){
        if(board[k+2][k] == 'X' && board[k+1][k+1] == 'X' && board[k][k+2] == 'X'){
            cout << "X won!" << endl;
            return true;
        }else if(board[k][k] == 'X' && board[k+1][k+1] == 'X' && board[k+2][k+2] == 'X'){
            cout << "X won!" << endl;
            return true;
        }else if(board[k][k] == 'O' && board[k+1][k+1] == 'O' && board[k+2][k+2] == 'O'){
            cout << "O won!" << endl;
            return true;
        }else if(board[k+2][k] == 'O' && board[k+1][k+1] == 'O' && board[k][k+2] == 'O'){
            cout << "O won!" << endl;
            return true;
        }
    }
    return false;
}

bool Game::check_tie(){
    for(int i = 0 ; i<3 ; i++){
        for(int j = 0; j<3 ; j++){
            if(board[i][j] == ' '){
                return false;    
            }
        }   
    }
    cout<< "Game is a Tie!" << endl;
    return true;
}

bool Game::get_game_over(){
    return game_over;
}

char Game::get_current_player(){
    return current_player;
}

int main(){
    Game start;
    start.draw_board();
    cout << "Welcome to the TicTacToe(XOX) Game!" <<endl;
    cout << "Purpose of this game is to make a 3 character line (horizontol, vertical or cross) with your character (X or O)." << endl;
    cout << "X will start the game." << endl <<endl;

    int row, col;
    string move;
    while(start.get_game_over() == false){
        cout<< "Player " << start.get_current_player() << " make your move(rowxcolumn): " << endl;
        cin >> move;
        cout << endl;
        start.make_move(move);
    }
    
    return 0;
}