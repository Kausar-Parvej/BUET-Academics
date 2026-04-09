#include <bits/stdc++.h>
using namespace std;


class node {
public:
    vector<vector<int>> state;
    int dimension;
    node* parent;


    node(vector<vector<int>> state, int dimension, node* parent = nullptr) {
        this->state = state;
        this->dimension = dimension;
        this->parent = parent;
    }

    bool isSolvable();
    int getInversionCount();
    int getHammingDistance();
    int getManhattanDistance();
    pair<int, int> getBlankPosition();
    vector<node*> getChildren();
    bool isGoalState();
    bool isSameState(vector<vector<int>> other);


};

bool node :: isSolvable(){
    if(dimension%2 != 0)
        return getInversionCount()%2 == 0;

    else{
        int blankRow = dimension - getBlankPosition().first - 1;  //from the bottom where bottom = 0;
        return (blankRow + getInversionCount())%2 == 0;

    }
}

int node :: getInversionCount(){
    vector<int> linearArray;
    for(int i = 0; i < dimension; i++){
        for(int j = 0; j < dimension; j++){
            if(state[i][j] != 0)
                linearArray.push_back(state[i][j]);
        }
    }

    int inversionCount = 0;
    for(int i = 0; i < linearArray.size(); i++){
        for(int j = i+1; j < linearArray.size(); j++){
            if(linearArray[i] > linearArray[j])
                inversionCount++;
        }
    }
    return inversionCount;
}

pair<int, int> node :: getBlankPosition(){
    for(int i = 0; i < dimension; i++){
        for(int j = 0; j < dimension; j++){
            if(state[i][j] == 0)
                return {i, j};
        }
    }
    return {-1, -1};
}

bool node :: isSameState(vector<vector<int>> other){
    for(int i = 0; i < dimension; i++){
        for(int j = 0; j < dimension; j++){
            if(state[i][j] != other[i][j])
                return false;
        }
    }
    return true;
}

vector<node*> node :: getChildren(){
    vector<node*> children;
    pair<int, int> blankPosition = getBlankPosition();
    int x = blankPosition.first;
    int y = blankPosition.second;

    if(x > 0){
        vector<vector<int>> newState = state;
        swap(newState[x][y], newState[x-1][y]);
        if(parent == nullptr || !parent->isSameState(newState))
            children.push_back(new node(newState, dimension, this));
    }

    if(x < dimension-1){
        vector<vector<int>> newState = state;
        swap(newState[x][y], newState[x+1][y]);
        if(parent == nullptr || !parent->isSameState(newState))
            children.push_back(new node(newState, dimension, this));
    }

    if(y > 0){
        vector<vector<int>> newState = state;
        swap(newState[x][y], newState[x][y-1]);
        if(parent == nullptr || !parent->isSameState(newState))
            children.push_back(new node(newState, dimension, this));
    }

    if(y < dimension-1){
        vector<vector<int>> newState = state;
        swap(newState[x][y], newState[x][y+1]);
        if(parent == nullptr || !parent->isSameState(newState))
            children.push_back(new node(newState, dimension, this));
    }

    return children;
}


bool node :: isGoalState(){
    int count = 1;
    for(int i = 0; i < dimension; i++){
        for(int j = 0; j < dimension; j++){
            if(state[i][j] != count)
                return false;
            count++;
            if(count == dimension*dimension) return true;
        }
    }
    return true;
}

int node :: getHammingDistance(){
    int distance = 0;
    int count = 0;
    for(int i = 0; i < dimension; i++){
        for(int j = 0; j < dimension; j++){
            count++;
            if(state[i][j] == 0) continue;
            if(state[i][j] != count)
                distance++;
        }
    }
    return distance;
}

int node :: getManhattanDistance(){
    int distance = 0;
    for(int i = 0; i < dimension; i++){
        for(int j = 0; j < dimension; j++){
            if(state[i][j] == 0) continue;
            int x = (state[i][j]-1)/dimension;    // expected row
            int y = (state[i][j]-1)%dimension;    // expected column
            distance += abs(x-i) + abs(y-j);
        }
    }
    return distance;
}

// int moves(node* current, bool printSteps){
//     int count = 0;
//     while(current->parent != nullptr){
//         if(printSteps){
//             for(int i = 0; i < current->dimension; i++){
//                 for(int j = 0; j < current->dimension; j++){
//                     if(current->state[i][j] == 0) cout<<"* ";
//                     else cout << current->state[i][j] << " ";
//                 }
//                 cout << "\n";
//             }
//             cout << "\n";
//             cout << " |\n";
//             cout << " V\n";
//         }
//         current = current->parent;
//         count++;
//     }
//     return count;
// }

int moves(node* current, bool printSteps){
    int count = 0;
    stack<node*> st;
    while(current->parent != nullptr){
        st.push(current);
        current = current->parent;
        count++;
    }
    st.push(current);
    if(printSteps){
        while(!st.empty()){
            current = st.top();
            st.pop();
            for(int i = 0; i < current->dimension; i++){
                for(int j = 0; j < current->dimension; j++){
                    if(current->state[i][j] == 0) cout<<"* ";
                    else cout << current->state[i][j] << " ";
                }
                cout << "\n";
            }
            cout << "\n";
            cout << " |\n";
            cout << " V\n";
        }
    }
    return count;
}


void solve_nPuzzle(node *satrt, string heuristic, bool printSteps){
    if(!satrt->isSolvable()){
        cout << "Puzzle is not solvable!" << "\n";
        return;
    }

    int distance = 0;
    int totalCost = 0;
    int expandedNodes = 0;
    int exploredNodes = 0;

    priority_queue<pair<int, node*>, vector<pair<int, node*>>, greater<pair<int, node*>>> pq;
    if(heuristic == "hamming") distance = satrt->getHammingDistance();
    else distance = satrt->getManhattanDistance();
    pq.push({distance, satrt});

    map<vector<vector<int>>, int> visited;
    visited[satrt->state] = 0;

    while(!pq.empty()){
        node* current = pq.top().second;
        pq.pop();
        expandedNodes++;

        if(current->isGoalState()){
            totalCost = moves(current, printSteps);
            cout << "total Cost/Moves: " << totalCost << "\n";
            cout << "Nodes Explored: " << exploredNodes << "\n";
            cout << "Nodes Expanded: " << expandedNodes << "\n";
            return;
        }
        if(exploredNodes > 1000000){
            cout << "Nodes Explored: " << exploredNodes << "\n";
            cout << "Nodes Expanded: " << expandedNodes << "\n";
            cout << "Solution not found! Too many steps" << "\n";
            return;
        }

        vector<node*> children = current->getChildren();
        for(node* child : children){
            if(visited.find(child->state) == visited.end()){
                visited[child->state] = visited[current->state] + 1;
                if(heuristic == "hamming") distance = child->getHammingDistance();
                else distance = child->getManhattanDistance();
                pq.push({distance + visited[child->state], child});
                exploredNodes++;
            }
        }
    }
}

int main(){
    int k;
    cin>>k;
    vector<vector<int>> state(k, vector<int>(k));

    string str;
    for(int i = 0; i < k; i++){
        for(int j = 0; j < k; j++){
            cin>>str;
            if(str == "*") str = "0";
            state[i][j] = stoi(str);
        }
    }

    node* initialBoard = new node(state, k);
    if(!initialBoard->isSolvable()){
        cout << "Puzzle is not solvable!" << "\n";
        return 0;
    }
    cout << "Puzzle is solvable!\nType \"yes\" to print the steps, \"no\" otherwise: \n";
    bool printSteps;
    cin >> str;
    if(str == "yes") printSteps = true;
    else printSteps = false;


    cout << "\nFor Hamming Heuristic: \n";
    solve_nPuzzle(initialBoard, "hamming", printSteps);

    cout << "\nFor Manhattan Heuristic: \n";
    solve_nPuzzle(initialBoard, "manhattan", printSteps);

    return 0;
}
