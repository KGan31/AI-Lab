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
        vector<vector<int>>path;

        state(int x, int y, vector<vector<int>>&p, int op){
            a = x;
            b = y;
            path = p;
            path.push_back({x, y, op});
        }
};

state fillA(state prev, int cap_a){
    state cur(cap_a, prev.b, prev.path, 1);
    return cur;
}

state fillB(state prev, int cap_b){
    state cur(prev.a, cap_b, prev.path, 2);
    return cur;
}

state emptyA(state prev){
    state cur(0, prev.b, prev.path, 3);
    return cur;
}

state emptyB(state prev){
    state cur(prev.a, 0, prev.path, 4);
    return cur;
}

state transferAtoB(state prev, int cap_b){
    int cur_b = min(cap_b, prev.b + prev.a);
    int cur_a = prev.a+prev.b-cur_b;
    state cur(cur_a, cur_b, prev.path, 5);
    return cur;
}

state transferBtoA(state prev, int cap_a){
    int cur_a = min(cap_a, prev.b + prev.a);
    int cur_b = prev.a+prev.b-cur_a;
    state cur(cur_a, cur_b, prev.path, 6);
    return cur;
}

bool goalTest(state prev, int target){
    if(prev.a==target || prev.b == target){
        return true;
    }
    return false;
}

void movegen_bfs(state cur, queue<state>&q, int cap_a, int cap_b){
    q.push(fillA(cur, cap_a));
    q.push(fillB(cur, cap_b));
    q.push(transferAtoB(cur, cap_b));
    q.push(transferBtoA(cur, cap_a));
    q.push(emptyA(cur));
    q.push(emptyB(cur));
    return;
}

void print_res(vector<vector<int>>path, vector<vector<int>>&vis){
    cout<<"Number of operations: "<<path.size()-1<<endl;
    for(int i = 1; i<path.size(); i++){
        cout<<"Operation: "<<path[i][2]<<" Current value A: "<<path[i][0]<<" Current value B: "<<path[i][1]<<endl;
    }
    int cnt = 0;
    for(int i = 0; i<vis.size(); i++){
        for(int j = 0; j<vis.size(); j++){
            if(vis[i][j]!=-1){
                cnt++;
            }
        }
    }
    cout<<"Total states explored: "<<cnt<<endl;
    return;
}

void bfs_search(state ini, int cap_a, int cap_b, int target){
    queue<state>q;
    q.push(ini);
    vector<vector<int>>vis(cap_a+1, vector<int>(cap_b+1, -1));
    int m_q = -1;
    while(!q.empty()){
        state cur = q.front();
        q.pop();
        if(goalTest(cur, target)){
            print_res(cur.path, vis);
            cout<<"Max queue size: "<<m_q<<endl;
            return;
        }
        if(vis[cur.a][cur.b]!=-1) continue;
        vis[cur.a][cur.b]=1;
        movegen_bfs(cur, q, cap_a, cap_b);
        m_q = max(m_q, int(q.size()));
    }
    cout<<"Not Possible"<<endl;
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
    state ini(cur_a, cur_b, p, -1);
    bfs_search(ini, cap_a, cap_b, target);
    return 0;
}
