#include <bits/stdc++.h>
using namespace std;
 
typedef unsigned long long ll;
#define pb push_back



bool check(int x, int y, int n, int m){
    if(x>n-1 || y>m-1 || x<0 || y<0){
        return false;
    }
    return true;
}

void dfs_search(vector<vector<int>>&g, int x, int y, int &cnt, int &dirt, vector<vector<bool>>&vis){
    if(vis[x][y]) return;
    if(g[x][y]==1){
        dirt++;
        g[x][y] = 0;
    }
    
    vis[x][y] = true;
    for(int i:{-1, 1}){ 
        int j = 0;
        if(check(x+i, y+j, g.size(), g[0].size()) && !vis[x+i][y+j]){
            dfs_search(g, x+i, y+j, cnt, dirt, vis);
            cnt++;
        }
    }

    for(int j:{-1, 1}){
        int i = 0;
        if(check(x+i, y+j, g.size(), g[0].size()) && !vis[x+i][y+j]){
            cnt++;
            dfs_search(g, x+i, y+j, cnt, dirt, vis);
            cnt++;
        }
    }
    
    // vis[x][y] = false;
    return;
}

void dfs(vector<vector<int>>g){
    cout<<"For DFS: "<<endl;
    int cnt = 0;
    int dirt_found = 0;
    vector<vector<bool>>vis(g.size(), vector<bool>(g[0].size(), false));
    dfs_search(g, 0, 0, cnt, dirt_found, vis);
    cout<<"Number of tile visited: "<<cnt<<endl;
    cout<<"Dirt found: "<<dirt_found<<endl;
} 

void bfs(vector<vector<int>>g){
    cout<<"For BFS: "<<endl;
    int cnt = 0;
    int dirt = 0;
    vector<vector<bool>>vis(g.size(), vector<bool>(g[0].size(), false));
    queue<pair<int, int>>q;
    q.push({0, 0});
    while(!q.empty()){
        int x = q.front().first;
        int y = q.front().second;
        q.pop();
        if(vis[x][y]) continue;
        vis[x][y] = true;
        if(g[x][y]==1){
            g[x][y] = 0;
            dirt++;
        }
        for(int i:{-1, 1}){ 
            int j = 0;
            if(check(x+i, y+j, g.size(), g[0].size()) && !vis[x+i][y+j]){
                q.push({x+i, y+j});
                cnt++;
            }
        }
        
        for(int j:{-1, 1}){
            int i = 0;
            if(check(x+i, y+j, g.size(), g[0].size()) && !vis[x+i][y+j]){
                q.push({x+i, y+j});
                cnt++;
            }
        }
    }
    cout<<"Number of tile visited: "<<cnt<<endl;
    cout<<"Dirt found: "<<dirt<<endl;
}

void gen_env(vector<vector<int>>&g){
    for(int i = 0; i<g.size(); i++){
        for(int j = 0; j<g[0].size(); j++){
            if(rand()%4==0){
                g[i][j] = 1;
            }
        }
    }
}

void display(vector<vector<int>>g){
    for(auto i:g){
        for(auto j:i){
            cout<<j<<" ";
        }
        cout<<endl;
    }
    return;
}

signed main(){
    int x, y;
    cout<<"Enter number of x, y: ";
    cin>>x>>y;
    vector<vector<int>> g(x, vector<int>(y, 0));
    srand((unsigned) time(NULL));
    gen_env(g);
    display(g);
    dfs(g);
    bfs(g);
    
    return 0;
}