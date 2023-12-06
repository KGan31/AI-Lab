#include <bits/stdc++.h>
using namespace std;

class state{
    public:
        vector<vector<int>>mat;
        int x, y;
        vector<vector<vector<int>>>path;
        int lvl=0, cost=0;
        state(int a, int b, vector<vector<int>>&arr, vector<vector<vector<int>>>&p, int c, int l){
            x = a;
            y = b;
            mat = arr;
            path = p;
            path.push_back(arr);
            cost = c;
            lvl = l;
        }
};

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

int huer2(state s, vector<vector<int>>&target){
    int cnt = 0;
    unordered_map<int, pair<int, int>>mp;
    for(int i = 0; i<s.mat.size(); i++){
        for(int j = 0; j<s.mat[i].size(); j++){
            mp[target[i][j]] = {i, j};
        }
    }
    for(int i = 0; i<s.mat.size(); i++){
        for(int j = 0; j<s.mat[i].size(); j++){
            cnt += abs(mp[s.mat[i][j]].first-i) + abs(mp[s.mat[i][j]].second-j);
        }
    }
    return cnt;
}

state move_left_h2(state prev, int x, int y, vector<vector<int>>&target){
    swap(prev.mat[x][y], prev.mat[x][y+1]);
    state cur(x, y+1, prev.mat, prev.path, huer2(prev, target), prev.lvl+1);
    return cur;
}

state move_right_h2(state prev, int x, int y, vector<vector<int>>&target){
    swap(prev.mat[x][y], prev.mat[x][y-1]);
    state cur(x, y-1, prev.mat, prev.path, huer2(prev, target), prev.lvl+1);
    return cur;
}

state move_up_h2(state prev, int x, int y, vector<vector<int>>&target){
    swap(prev.mat[x][y], prev.mat[x+1][y]);
    state cur(x+1, y, prev.mat, prev.path , huer2(prev, target), prev.lvl+1);
    return cur;
}

state move_down_h2(state prev, int x, int y, vector<vector<int>>&target){
    swap(prev.mat[x][y], prev.mat[x-1][y]);
    state cur(x-1, y, prev.mat, prev.path, huer2(prev, target), prev.lvl+1);
    return cur;
}

class cmp_h {
public:
    bool operator()(state &s1, state &s2)
    {
        return s1.cost>=s2.cost;
    }
};

bool goalTest(state cur, priority_queue<state, vector<state>, cmp_h>&s){
    cout<<cur.cost<<" "<<s.top().cost<<endl;
    if(cur.cost<=s.top().cost){
        return true;
    }
    return false;
}

void movegen_dfs_h2(state prev, priority_queue<state, vector<state>, cmp_h>&s, vector<vector<int>>&target, set<vector<vector<int>>>&vis){
    int x = prev.x;
    int y = prev.y;
    priority_queue<state, vector<state>, cmp_h>new_pq;
    if(y!=0){
        state k = move_right_h2(prev, x, y, target);
        if(vis.find(k.mat)==vis.end()){
            vis.insert(k.mat);
            new_pq.push(k);
        }    
    }
    if(x!=0){
        state k = move_down_h2(prev, x, y, target);
        if(vis.find(k.mat)==vis.end()){
            vis.insert(k.mat);
            new_pq.push(k);
        } 
    }
    if(y!=prev.mat[0].size()-1){
        state k = move_left_h2(prev, x, y, target);
        if(vis.find(k.mat)==vis.end()){
            vis.insert(k.mat);
            new_pq.push(k);
        } 
    }
    if(x!=prev.mat.size()-1){
        state k = move_up_h2(prev, x, y, target);
        if(vis.find(k.mat)==vis.end()){
            vis.insert(k.mat);
            new_pq.push(k);
        } 
    }
    s = new_pq;
    return;
}

int cnt2 = 0;
void bfs_search_manhattandis(state ini, vector<vector<int>> target){
    priority_queue<state, vector<state>, cmp_h>pq;
    pq.push(ini);
    int sz = INT_MAX;
    int m_s = 0;
    set<vector<vector<int>>>vis;
    while(!pq.empty()){
        state cur = pq.top();
        pq.pop();
        cnt2++;
        movegen_dfs_h2(cur, pq, target, vis);
        if(goalTest(cur, pq)){
            print_res(cur.path);
            cout<<"Max queue size: "<<m_s<<endl;
            cout<<"Steps to reach target "<<cur.path.size()<<endl;
            cout<<"Total states explored: "<<cnt2<<endl;
            return;
        }
        m_s = max(m_s, int(pq.size()));
    }
    cout<<"Not Possible"<<endl;
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
    
    vector<vector<vector<int>>>p;
    set<vector<vector<int>>>s;
    vector<vector<int>>target(n, vector<int>(m));
    int c = 0;
    // cout<<"Enter end position: \n";
    for(int i = 0; i<n; i++){
        for(int j = 0; j<m; j++){
            cin>>target[i][j];
            if(target[i][j]!=arr[i][j]){
                c++;
            }
        }
    }
    cout<<"\n";
    state ini1(srcx, srcy, arr, p, c, 0);
    int cos = huer2(ini1, target);
    state ini(srcx, srcy, arr, p, cos, 0);
    cout<<"Hill Climb using Manhattan Distance hueristic: \n";
    bfs_search_manhattandis(ini, target);
    return 0;
}