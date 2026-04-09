#include <bits/stdc++.h>
using namespace std;

const double INF = 1e9;

class Board{
public:
    bool p1_turn;
    int captured_stones, earned_moves;

    vector<int> pits;       // 0-5: player 1, 6: player 1's mancala, 
                            //7-12: player 2, 13: player 2's mancala


    Board(){
        captured_stones = 0;
        earned_moves = 0;
        p1_turn = true;

        pits = vector<int>(14, 4);
        pits[6] = pits[13] = 0;
    }

    double evaluate(int heuristic_id);
    vector<int> get_nextMoves();
    pair<int, int> get_finalScore();
    bool is_gameOver();
    bool make_move(int pit);
    void print_board();
    void reset_board();

};

void Board :: reset_board(){
    captured_stones = 0;
    earned_moves = 0;
    p1_turn = true;

    pits = vector<int>(14, 4);
    pits[6] = pits[13] = 0;
}

bool Board :: is_gameOver(){
    bool p1_empty = true, p2_empty = true;
    for(int i = 0; i < 6; i++){
        if(pits[i] > 0) p1_empty = false;
        if(pits[7+i] > 0) p2_empty = false;
    }
    return p1_empty || p2_empty;
}

pair<int, int> Board :: get_finalScore(){
    int p1_score = pits[6];
    int p2_score = pits[13];

    for(int i = 0; i < 6; i++){
        p1_score += pits[i];
        p2_score += pits[7+i];
    }

    return {p1_score, p2_score};
}

vector<int> Board :: get_nextMoves(){
    vector<int> moves;
    if(p1_turn){
        for(int i = 0; i < 6; i++){
            if(pits[i] > 0) moves.push_back(i);
        }
    }
    else{
        for(int i = 7; i < 13; i++){
            if(pits[i] > 0) moves.push_back(i);
        }
    }
    random_shuffle(moves.begin(), moves.end());
    return moves;
}


bool Board :: make_move(int pit){

    if(pit < 0 || pit == 6 || pit >= 14){
        cout << "Invalid move\n";
        return true;
    }
    if((p1_turn && pit >= 7) || (!p1_turn && pit < 7)){
        cout << "Invalid move\n";
        return true;
    }
    if(pits[pit] == 0){
        cout << "Empty pit\n";
        return true;
    }

    int stones = pits[pit];
    pits[pit] = 0;

    int i = pit;

    //move stones
    while(stones > 0){
        i = (i+1)%14;
        if((p1_turn && i == 13) || (!p1_turn && i == 6)) continue;
        pits[i]++;
        stones--;
    }

    //last stone in player's mancala
    if((p1_turn && i == 6) || (!p1_turn && i == 13)){
        earned_moves += (p1_turn ? 1:-1);
        return true;
    }

    //capture stones
    if(p1_turn){
        if(i < 6 && pits[i] == 1 && pits[12-i] > 0){
            pits[6] += pits[12-i] + 1;
            captured_stones += pits[12-i] + 1;
            pits[12-i] = pits[i] = 0;
        }
    }
    else{
        if(i >= 7 && pits[i] == 1 && pits[12-i] > 0){
            pits[13] += pits[12-i] + 1;
            captured_stones -= (pits[12-i] + 1);
            pits[12-i] = pits[i] = 0;
        }
    }

    return false;
}

double Board :: evaluate(int heuristic_id){
    int p1_sideStones = accumulate(pits.begin(), pits.begin()+5, 0);
    int p2_sideStones = accumulate(pits.begin()+7, pits.begin()+12, 0);
    int p1_mancala = pits[6];
    int p2_mancala = pits[13];

    if(heuristic_id == -1){ //game over heuristic
        int p1_score = this->get_finalScore().first;
        int p2_score = this->get_finalScore().second;

        if(p1_score == p2_score) return 0;
        else return INF*(p1_score - p2_score)/(p1_score + p2_score);
    }
    if(heuristic_id == -2){ // one player has more than 24 stones heuristic
        return INF*(p1_mancala - p2_mancala)/(p1_mancala + p2_mancala);
    }

    double score = 0;
    if(heuristic_id == 1){
        return 0.20*(p1_mancala - p2_mancala) + 0.80*captured_stones;
    }
    else if(heuristic_id == 2){
        score = 0.30*(p1_mancala - p2_mancala) + 0.70*captured_stones;
    }
    else if(heuristic_id == 3){
        score = 0.40*(p1_mancala - p2_mancala) + 0.20*(p1_sideStones - p2_sideStones) + 0.40*captured_stones;
    }
    else if(heuristic_id == 4){
        score = 0.40*(p1_mancala - p2_mancala) + 0.25*(p1_sideStones - p2_sideStones) + 0.25*earned_moves + 0.10*captured_stones;
    }
    else{
        // customize heuristic here
        double w_mancala = 0.40;
        double w_sideStones = 0.30;
        double w_earnedMoves = 0.15;
        double w_capturedStones = 0.25;

        score += w_mancala*(p1_mancala - p2_mancala) + w_sideStones*(p1_sideStones - p2_sideStones);
        score += w_earnedMoves*earned_moves + w_capturedStones*captured_stones;
    }
    return score;
}

void Board :: print_board(){
    cout <<"----------------------------------------------\n";
    cout << "\t\tPlayer 2\n\t";
    for(int i = 12; i >= 7; i--){
        cout <<"| "<< pits[i] << " ";
    }
    cout << "|\n";
    cout <<"  \""<< pits[13] << "\"\t\t\t\t   \"" << pits[6] << "\"\n\t";
    for(int i = 0; i < 6; i++){
        cout <<"| "<< pits[i] << " ";
    }
    cout << "|\n\t\tPlayer 1\n";
    cout <<"----------------------------------------------\n";
}
