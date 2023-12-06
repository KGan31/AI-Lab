#include <bits/stdc++.h>
using namespace std;

// 1 - Fill A
// 2 - Fill B
// 3 - Empty A
// 4 - Empty B
// 5 - Transfer A->B
// 6 - Transfer B->A

class state {
    public:
        int a;
        int b;
        vector<vector<bool>>vis;
        vector<vector<int>>path;

        state(int x, int y, vector<vector<int>>&p, int op, vector<vector<bool>>&v){
            a = x;
            b = y;
            path = p;
            path.push_back({x, y, op});
            vis = v;
            vis[x][y]=true;
        }
};

state fillA(state prev, int cap_a){
    state cur(cap_a, prev.b, prev.path, 1, prev.vis);
    return cur;
}

state fillB(state prev, int cap_b){
    state cur(prev.a, cap_b, prev.path, 2, prev.vis);
    return cur;
}

state emptyA(state prev){
    state cur(0, prev.b, prev.path, 3, prev.vis);
    return cur;
}

state emptyB(state prev){
    state cur(prev.a, 0, prev.path, 4, prev.vis);
    return cur;
}

state transferAtoB(state prev, int cap_b){
    int cur_b = min(cap_b, prev.b + prev.a);
    int cur_a = prev.a+prev.b-cur_b;
    state cur(cur_a, cur_b, prev.path, 5, prev.vis);
    return cur;
}

state transferBtoA(state prev, int cap_a){
    int cur_a = min(cap_a, prev.b + prev.a);
    int cur_b = prev.a+prev.b-cur_a;
    state cur(cur_a, cur_b, prev.path, 6, prev.vis);
    return cur;
}

bool goalTest(state prev, int target){
    if(prev.a==target || prev.b == target){
        return true;
    }
    return false;
}

void movegen_dfs(state cur, stack<state>&s, int cap_a, int cap_b){
    state k = fillA(cur, cap_a);
    if(!cur.vis[k.a][k.b]){
        s.push(k);
    }
    k = fillB(cur, cap_b);
    if(!cur.vis[k.a][k.b]){
        s.push(k);
    }
    k = transferAtoB(cur, cap_b);
    if(!cur.vis[k.a][k.b]){
        s.push(k);
    }
    k = transferBtoA(cur, cap_a);
    if(!cur.vis[k.a][k.b]){
        s.push(k);
    }
    k = emptyA(cur);
    if(!cur.vis[k.a][k.b]){
        s.push(k);
    }
    k = emptyB(cur);
    if(!cur.vis[k.a][k.b]){
        s.push(k);
    }
    return;
}
void print_res(vector<vector<int>>path, vector<vector<bool>>&vis){
    cout<<"Number of operations: "<<path.size()-1<<endl;
    for(int i = 1; i<path.size(); i++){
        cout<<"Operation: "<<path[i][2]<<" Current value A: "<<path[i][0]<<" Current value B: "<<path[i][1]<<endl;
    }
    int cnt = 0;
    for(int i = 0; i<vis.size(); i++){
        for(int j = 0; j<vis.size(); j++){
            if(!vis[i][j]){
                cnt++;
            }
        }
    }
    cout<<"Total states explored: "<<cnt<<endl;
    return;
}

void dfs_search(state ini, int cap_a, int cap_b, int target){
    stack<state>s;
    s.push(ini);
    vector<vector<bool>>v(cap_a+1, vector<bool>(cap_b+1, false));
    vector<vector<int>>p;
    state fin(ini.a, ini.b, p, -1, v);
    int m_s = -1;
    while(!s.empty()){
        state cur = s.top();
        s.pop();
        if(goalTest(cur, target) && (cur.path.size()<fin.path.size() || fin.a==ini.a)){
            fin = cur;
            continue;
        }
        movegen_dfs(cur, s, cap_a, cap_b);
        m_s = max(m_s, (int)s.size());
    }
    if(fin.a!=ini.a) print_res(fin.path, fin.vis);
    else cout<<"Not Possible"<<endl;
    cout<<"Max stack size: "<<m_s<<endl;
    return;
}

int main(){
    int cap_a, cap_b, target;
    cout<<"Enter capacity of jug A: ";
    cin>>cap_a;
    cout<<"Enter capacity of jug B: ";
    cin>>cap_b;
    cout<<"Enter target value: ";
    cin>>target;
    cout<<endl;
    int cur_a = 0, cur_b = 0;
    vector<vector<int>>p;
    vector<vector<bool>>vis(cap_a+1, vector<bool>(cap_b+1, false));
    vis[cur_a][cur_b] = true;
    state ini(cur_a, cur_b, p, -1, vis);
    dfs_search(ini, cap_a, cap_b, target);
    return 0;
}