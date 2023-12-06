#include <bits/stdc++.h>
using namespace std;

class state{
    public:
        vector<vector<int>>mat;
        int x, y;
        vector<vector<vector<int>>>path;
        state(int a, int b, vector<vector<int>>&arr, vector<vector<vector<int>>>&p){
            x = a;
            y = b;
            mat = arr;
            path = p;
            path.push_back(mat);
        }
};

state move_left(state prev, int x, int y){
    swap(prev.mat[x][y], prev.mat[x][y+1]);
    state cur(x, y+1, prev.mat, prev.path);
    return cur;
}

state move_right(state prev, int x, int y){
    swap(prev.mat[x][y], prev.mat[x][y-1]);
    state cur(x, y-1, prev.mat, prev.path);
    return cur;
}

state move_up(state prev, int x, int y){
    swap(prev.mat[x][y], prev.mat[x+1][y]);
    state cur(x+1, y, prev.mat, prev.path);
    return cur;
}

state move_down(state prev, int x, int y){
    swap(prev.mat[x][y], prev.mat[x-1][y]);
    state cur(x-1, y, prev.mat, prev.path);
    return cur;
}

void movegen_bfs(state prev, queue<state>&q){
    int x = prev.x;
    int y = prev.y;
    if(y!=0){
        q.push(move_right(prev, x, y));
    }
    if(x!=0){
        q.push(move_down(prev, x, y));
    }
    if(y!=prev.mat[0].size()-1){
        q.push(move_left(prev, x, y));
    }
    if(x!=prev.mat.size()-1){
        q.push(move_up(prev, x, y));
    }
    return;
}

bool goalTest(state cur, vector<vector<int>> target){
    for(int i = 0; i<cur.mat.size(); i++){
        for(int j = 0; j<cur.mat[0].size(); j++){
            if(cur.mat[i][j]!=target[i][j]){
                return false;
            }
        }
    }
    return true;
}

void print_res(vector<vector<vector<int>>>path){
    cout<<"Answer procedure: \n";
    for(int i = 0; i<path.size(); i++){
        for(int j = 0; j<path[i].size(); j++){
            for(int k = 0; k<path[i][0].size(); k++){
                cout<<path[i][j][k]<<" ";
            }
            cout<<endl;
        }
        cout<<endl;
    }
    cout<<"Total steps to reach: "<<path.size()<<endl;
}

void bfs_search(state ini, vector<vector<int>> target){
    queue<state>q;
    q.push(ini);
    set<vector<vector<int>>>vis;
    int m_q = -1;
    while(!q.empty()){
        state cur = q.front();
        q.pop();
        if(goalTest(cur, target)){
            print_res(cur.path);
            cout<<"Total states explored: "<<vis.size()<<endl;
            cout<<"Max queue size: "<<m_q<<endl;
            return;
        }
        if(vis.find(cur.mat)!=vis.end()) continue;
        vis.insert(cur.mat);
        movegen_bfs(cur, q);
        m_q = max(m_q, int(q.size()));
    }
    cout<<"Not Possible"<<endl;
    return;
}

int main(){
    int n, m;
    freopen("input.txt", "r", stdin);
    // cout<<"Enter length and breadth for matrix: ";
    cin>>n>>m;
    vector<vector<int>>arr(n, vector<int>(m, 0));
    // cout<<"Enter start position: \n";
    
    int srcx, srcy;
    for(int i = 0; i<n; i++){
        for(int j = 0; j<m; j++){
            cin>>arr[i][j];
            if(arr[i][j]==-1){
                srcx = i;
                srcy = j;
            }
        }
    }
    vector<vector<int>>target(n, vector<int>(m));
    vector<vector<vector<int>>>p;
    state ini(srcx, srcy, arr, p);
    // cout<<"Enter end position: \n";
    for(int i = 0; i<n; i++){
        for(int j = 0; j<m; j++){
            cin>>target[i][j];
        }
    }
    // cout<<"\n";
    bfs_search(ini, target);
    return 0;
}