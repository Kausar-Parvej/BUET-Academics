#include <bits/stdc++.h>
#include <conio.h>
#include "mancala_board.cpp"

using namespace std;
int tie_games = 0, p1_wins = 0, p2_wins = 0;

class Game{
private:
    int explored_nodes;
    int pruned_nodes;
    int max_depth = 6;
    int heuristic_id1 = 1;
    int heuristic_id2 = 1;
    int best_move;

public:
    Board currtent_board;
    bool multipleGames;
    bool allHeuristics;

    Game(){
        heuristic_id1 = 1;
        heuristic_id2 = 1;
        pruned_nodes = 0;
        best_move = 0;
        explored_nodes = 0;
        max_depth = 7;
        multipleGames = false;

        this->currtent_board.p1_turn = true;
    }
    void set_heuristic(int h1, int h2){
        heuristic_id1 = h1;
        heuristic_id2 = h2;
    }

    double minimax(Board board, int depth, double alpha, double beta);
    void print_stats();
    void play_game(int mode);

    bool player_turn();
    bool ai_turn();
    void ai_vs_ai();
    void player_vs_ai();
    void ai_vs_ai_multiple();
    void all_ai();

};


double Game :: minimax(Board board, int depth, double alpha, double beta){
    explored_nodes++;
    if(board.is_gameOver()){
        return board.evaluate(-1);
    }
    if(board.pits[6] > 24 || board.pits[13] > 24){
        return board.evaluate(-2);
    }
    if(depth >= max_depth){
       if(board.p1_turn) return board.evaluate(heuristic_id1);
       else return board.evaluate(heuristic_id2);
    }

    vector<int> moves = board.get_nextMoves();
    if(depth == 0) best_move = moves[0];

    double best, val;
    int count = 0;
    if(board.p1_turn){
        best = -INF;
        for(int move : moves){
            count++;
            Board next_board = board;
            bool again = next_board.make_move(move);
            if(!again) next_board.p1_turn = !next_board.p1_turn;
            val = minimax(next_board, depth+1, alpha, beta);
           
            if(val > best){
                best = val;
                if(depth == 0) best_move = move;
            }
            alpha = max(alpha, best);
            if(beta <= alpha){
                pruned_nodes += (moves.size() - count)*(max_depth - depth);
                break;
            }
        }
        return best;
    }
    else{
        best = INF;
        for(int move : moves){
            count++;
            Board next_board = board;
            bool again = next_board.make_move(move);
            if(!again) next_board.p1_turn = !next_board.p1_turn;
            val = minimax(next_board, depth+1, alpha, beta);
            if(val < best){
                best = val;
                if(depth == 0) best_move = move;
            }
            beta = min(beta, best);
            if(beta <= alpha){
                pruned_nodes += (moves.size() - count)*(max_depth - depth);
                break;
            }
        }
        return best;
    }
    
}

void Game :: print_stats(){
    pair<int, int> scores = currtent_board.get_finalScore();
    
    if(multipleGames && !allHeuristics){
        if(scores.first == scores.second){
            tie_games++;
            cout << "It's a tie!\n";
        }
        else if(scores.first > scores.second){
            p1_wins++;
            cout << "Player 1 (H"<<heuristic_id1 <<") wins!\n";
        }
        else{
            p2_wins++;
            cout << "Player 2 (H"<<heuristic_id2 <<") wins!\n";
        }
        return;
    }
    if(allHeuristics){
        if(scores.first == scores.second) tie_games++;
        else if(scores.first > scores.second) p1_wins++;
        else p2_wins++;
        return;
    }


    cout << "Game over!\n";
    cout << "Explored nodes: " << explored_nodes << ". Pruned nodes: " << pruned_nodes<< endl;

    cout<< "\n";
    if(scores.first == scores.second) cout << "It's a tie!\n";
    else if(scores.first > scores.second) cout << "Player 1 wins!\n";
    else cout << "Player 2 wins!\n";
    cout << "Player 1 score: " << scores.first << ". Player 2 score: " << scores.second << "\n\n";
}

bool Game :: player_turn(){
    cout << "Your turn! Choose a pit (1-6): ";
    int pit;
    while(cin >> pit){
        if(pit < 1 || pit > 6 || currtent_board.pits[pit-1] == 0){
            cout << "Invalid move! Choose a pit (1-6): ";
        }
        else break;
    }
    return currtent_board.make_move(pit-1);
}

bool Game :: ai_turn(){
    if(!multipleGames) cout << "AI's turn!\n";
    best_move = -1;
    minimax(currtent_board, 0, -INF, INF);
    if(best_move == -1){
        best_move = currtent_board.get_nextMoves()[0];
    }
    //cout << "Explored nodes: " << explored_nodes << " Pruned nodes: " << pruned_nodes<< endl;
    if(!multipleGames) cout << "AI chose pit " << best_move+1 << endl;
    return currtent_board.make_move(best_move);
}

void Game :: play_game(int mode){
    currtent_board.reset_board();
    if(!multipleGames) currtent_board.print_board();
    while(!currtent_board.is_gameOver()){
        bool again = false;
        if( mode == 1){
            if(currtent_board.p1_turn){
                again = player_turn();
            }
            else{
                again = ai_turn();
                getch();
            }
        }
        else{
            if(currtent_board.p1_turn){
                again = ai_turn();
            }
            else{
                again = ai_turn();
            }
        }
        if(!multipleGames) currtent_board.print_board();
        if(currtent_board.is_gameOver()) break;
        if(!again) currtent_board.p1_turn = !currtent_board.p1_turn;
        else if(!multipleGames) cout << "Another turn for player " << (currtent_board.p1_turn ? 1 : 2) << endl;
    }
    print_stats();
}

void Game :: player_vs_ai(){
    cout << "\n\t--->Player vs AI-<---\n";
    cout<< "Chosse a heuristic function for the AI (1-5):";
    int h1;
    cin >> h1;
    if(h1 < 1 || h1 > 5){
        cout << "Invalid choice\n";
        return;
    }
    set_heuristic(1, h1);
    cout << "Player 1 starts\n";
    play_game(1);
}

void Game :: ai_vs_ai(){
    cout << "\n\t--->AI vs AI-<---\n";
    cout<< "Chosse a heuristic function for the Player1 and Player2 (1-5):";
    int h1, h2;
    cin >> h1 >> h2;
    if(h1 < 1 || h1 > 5 || h2 < 1 || h2 > 5){
        cout << "Invalid choice\n";
        return;
    }
    set_heuristic(h1, h2);
    cout << "Player 1 starts\n";
    play_game(2);
}

void Game :: ai_vs_ai_multiple(){
    cout << "\n\t--->AI vs AI (multiple)<---\n";
    cout<< "Chosse a heuristic function for the Player1 and Player2 (1-5):";
    int h1, h2;
    cin >> h1 >> h2;
    if(h1 < 1 || h1 > 5 || h2 < 1 || h2 > 5){
        cout << "Invalid choice\n";
        return;
    }
    set_heuristic(h1, h2);
    multipleGames = true;
    cout << "How many games do you want the AI to play?\n";
    int gameCount;
    cin >> gameCount;
    for(int i = 0; i < gameCount; i++){
        cout << "Game " << i+1 << " : ";
        play_game(2);
    }
    cout << "Player 1 wins: " << p1_wins << ". Player 2 wins: " << p2_wins << ". Tie games: " << tie_games << endl;
}

void Game :: all_ai(){
    cout << "\n\t--->ALL AI<---\n";
    cout << "How many games do you want the AIs to play to play each other?\n";
    int gameCount;
    cin >> gameCount;
    allHeuristics = true;
    multipleGames = true;
    for(int i=1; i<=5; i++){
        for(int j=i+1; j<=5; j++){
            set_heuristic(i, j);
            cout <<"\n------------------------------------------------------------\n";
            cout << "Heuristic " << i << " vs Heuristic " << j << endl;
            for(int k = 0; k < gameCount; k++){
                play_game(2);
            }
            cout << "Heuristic " << i << " wins: " << p1_wins << ". Heuristic " << j << " wins: " << p2_wins << ". Tie games: " << tie_games << endl;
            p1_wins = p2_wins = tie_games = 0;
            //cout << "----------------------------------------------------------\n";
        }
    }
}



int main(){
    cout << "\t----->Mancala Game<-------\n";
    cout << "Choose a game mode:\n";
    cout << "1. Player vs AI\n";
    cout << "2. AI vs AI (single game)\n";
    cout << "3. AI vs AI (multiple game)\n";
    cout << "4. Better Heuristic\n";

    Game game;

    int choice;
    cin >> choice;
    if(choice == 1) game.player_vs_ai();
    else if(choice == 2) game.ai_vs_ai();
    else if(choice == 3) game.ai_vs_ai_multiple();
    else if(choice == 4) game.all_ai();
    else{
        cout << "Invalid choice\n";
    }
    return 0;
}


