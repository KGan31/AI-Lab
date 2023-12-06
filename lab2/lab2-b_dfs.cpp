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

bool goalTest(state cur, vector<vector<int>> &target){
    for(int i = 0; i<cur.mat.size(); i++){
        for(int j = 0; j<cur.mat[0].size(); j++){
            if(cur.mat[i][j]!=target[i][j]){
                return false;
            }
        }
    }
    return true;
}

void print_res(vector<vector<vector<int>>>&path){
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
}

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

void movegen_dfs(state prev, stack<state>&s,  set<vector<vector<int>>>&vis){
    int x = prev.x;
    int y = prev.y;
    if(y!=0){
        state k = move_right(prev, x, y);
        if(vis.find(k.mat)==vis.end()){
            vis.insert(k.mat);
            s.push(k);
        }    
    }
    if(x!=0){
        state k = move_down(prev, x, y);
        if(vis.find(k.mat)==vis.end()){
            vis.insert(k.mat);
            s.push(k);
        } 
    }
    if(y!=prev.mat[0].size()-1){
        state k = move_left(prev, x, y);
        if(vis.find(k.mat)==vis.end()){
            vis.insert(k.mat);
            s.push(k);
        } 
    }
    if(x!=prev.mat.size()-1){
        state k = move_up(prev, x, y);
        if(vis.find(k.mat)==vis.end()){
            vis.insert(k.mat);
            s.push(k);
        } 
    }
    return;

}

void dfs_search(state ini, vector<vector<int>> target){
    stack<state>s;
    s.push(ini);
    int sz = INT_MAX;
    state fin(ini);
    int m_s = 0;
    set<vector<vector<int>>>vis;
    int cnt = 0;
    while(!s.empty()){
        state cur = s.top();
        s.pop();
        if(goalTest(cur, target)){
            print_res(cur.path);
            cout<<"Max stack size: "<<m_s<<endl;
            cout<<"Steps to reach target "<<cur.path.size()<<endl;
            cout<<"Number of states explored: "<<cnt<<endl;
            return;
        }
        // if(sz<cur.path.size()) continue;
        movegen_dfs(cur, s, vis);
        cnt++;
        m_s = max(m_s, int(s.size()));
    }
    if(sz!=INT_MAX){
        print_res(fin.path);
        cout<<"Max stack size: "<<m_s<<endl;
        cout<<"Steps to reach target "<<fin.path.size()<<endl;
    }
    else{
        cout<<"Not Possible"<<endl;
    }
    return;
}

int main(){
    int n, m;
    freopen("input.txt", "r", stdin);
    // cout<<"Enter length and breadth for matrix: ";
    cin>>n>>m;
    vector<vector<int>>arr(n, vector<int>(m));
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
    cout<<"\n";
    dfs_search(ini, target);
    return 0;
}