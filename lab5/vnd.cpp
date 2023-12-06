#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

class state{
    public:
        vector<vector<int>>expr;
        vector<int>val;
        int var, cl;
        int lvl=0, cost=0;
        state(int a, int b, vector<vector<int>>&arr, vector<int>&cur, int l, int c){
            expr = arr;
            cost = c;
            lvl = l;
            var = a;
            cl = b;
            val = cur;
        }
};

set<vector<int>>vis;

int huer(state &s){
    int cost = 0;
    for(int i = 0; i<s.cl; i++){
        int cur = 0;
        for(int j = 0; j<s.var; j++){
            if(s.val[j] * s.expr[i][j]==1){
                cur++;
            }
        }
        if(cur!=3){
            cost++;
        }
    }
    return cost;
}

class cmp_h {
public:
    bool operator()(state &s1, state &s2)
    {
        return s1.cost<=s2.cost;
    }
};
state generate_expr(int var, int cl){
    vector<vector<int>>expr(cl, vector<int>(var, 0));
    for(int i = 0; i<cl; i++){
        int cnt = 0;
        int j = 0;
        while(cnt<3){
            if(expr[i][j]==0){
                expr[i][j] = rand()%3 - 1;
                if(expr[i][j]!=0){
                    cnt++;
                }
            }
            j++;
            j=j%var;
        }  
    }
    vector<int>cur(var, 1);
    state ini1(var, cl, expr, cur, 0, 0);
    state ini(var, cl, expr, cur, 0, huer(ini1));
    return ini;
}
void print_expr(state &s){
    vector<vector<int>>expr = s.expr;
    int cl = s.cl;
    int var = s.var;
    for(int i = 0; i<cl; i++){
        cout<<"(";
        int cnt = 0;
        for(int j = 0; j<var; j++){
            if(expr[i][j]==1){
                cout<<char('a'+j)<<" ";
                cnt++;
            }
            else if(expr[i][j]==-1){
                cout<<"~"<<char('a'+j)<<" ";
                cnt++;
            }
            else{
                continue;
            }
            if(cnt<3){
                cout<<"v"<<" ";
            }
        }
        cout<<")";
        if(i!=cl-1){
            cout<<"ʌ";
        }
    }
    cout<<endl;
}

void movegen_bfs1(state prev, priority_queue<state, vector<state>, cmp_h>&s, set<vector<int>>&vis){
    priority_queue<state, vector<state>, cmp_h>new_pq;
    for(int i = 0; i<prev.var; i++){
        vector<int>cur = prev.val;
        if(cur[i]==1){
            cur[i] = -1;
        }
        else{
            cur[i] = 1;
        }
        if(vis.find(cur)==vis.end()){
            state k(prev.var, prev.cl, prev.expr, cur, prev.lvl+1, 0);
            state k1(prev.var, prev.cl, prev.expr, cur, prev.lvl+1, huer(k));
            new_pq.push(k1);
            vis.insert(cur);
        }
    }
    s = new_pq;
    return;
}

void movegen_bfs2(state prev, priority_queue<state, vector<state>, cmp_h>&s, set<vector<int>>&vis){
    priority_queue<state, vector<state>, cmp_h>new_pq;
    for(int i = 0; i<prev.var; i++){
        for(int j = i+1; j<prev.var; j++){
            vector<int>cur = prev.val;
            if(cur[i]==1){
                cur[i] = -1;
            }
            else{
                cur[i] = 1;
            }
            if(cur[j]==1){
                cur[j] = -1;
            }
            else{
                cur[j] = 1;
            }
            if(vis.find(cur)==vis.end()){
                state k(prev.var, prev.cl, prev.expr, cur, prev.lvl+1, 0);
                state k1(prev.var, prev.cl, prev.expr, cur, prev.lvl+1, huer(k));
                new_pq.push(k1);
                vis.insert(cur);
            }
        }
    }
    s = new_pq;
    return;
}

void movegen_bfs3(state prev, priority_queue<state, vector<state>, cmp_h>&s, set<vector<int>>&vis){
    priority_queue<state, vector<state>, cmp_h>new_pq;
    for(int i = 0; i<prev.var; i++){
        for(int j = i+1; j<prev.var; j++){
            for(int k = j+1; k<prev.var; k++){
                vector<int>cur = prev.val;
                if(cur[i]==1){
                    cur[i] = -1;
                }
                else{
                    cur[i] = 1;
                }
                if(cur[j]==1){
                    cur[j] = -1;
                }
                else{
                    cur[j] = 1;
                }
                if(cur[k]==1){
                    cur[k] = -1;
                }
                else{
                    cur[k] = 1;
                }
                if(vis.find(cur)==vis.end()){
                    state k(prev.var, prev.cl, prev.expr, cur, prev.lvl+1, 0);
                    state k1(prev.var, prev.cl, prev.expr, cur, prev.lvl+1, huer(k));
                    new_pq.push(k1);
                    vis.insert(cur);
                }
            }
        }
    }
    s = new_pq;
    return;
}

bool goalTest(state &cur, priority_queue<state, vector<state>, cmp_h>&pq){
    if(pq.top().cost<cur.cost || cur.cost==cur.cl){
        return true;
    }
    return false;
}

void print_res(state &s){
    cout<<"The value of variables yeilding the best result are: ";
    for(int i = 0; i<s.var; i++){
        cout<<char('a'+i)<<": "<<s.val[i]<<" ";
    }
    cout<<"\nClauses satisfied: "<<s.cost<<endl;
    return;
}
state hill_climb1(state ini){
    priority_queue<state, vector<state>, cmp_h>pq;
    pq.push(ini);
    int sz = INT_MAX;
    int m_s = 0;
    int cnt2 = 0;
    // set<vector<int>>vis;
    while(!pq.empty()){
        state cur = pq.top();
        pq.pop();
        cnt2++;
        movegen_bfs1(cur, pq, vis);
        if(goalTest(cur, pq)){
            print_res(cur);
            cout<<"Max queue size: "<<m_s<<endl;
            cout<<"Total states explored: "<<cnt2<<endl;
            return cur;
        }
        m_s = max(m_s, int(pq.size()));
    }
    cout<<cnt2<<endl;
    cout<<"Not Possible"<<endl;
    return ini;
}

state hill_climb2(state ini){
    priority_queue<state, vector<state>, cmp_h>pq;
    pq.push(ini);
    int sz = INT_MAX;
    int m_s = 0;
    int cnt2 = 0;
    
    while(!pq.empty()){
        state cur = pq.top();
        pq.pop();
        cnt2++;
        movegen_bfs2(cur, pq, vis);
        if(goalTest(cur, pq)){
            print_res(cur);
            cout<<"Max queue size: "<<m_s<<endl;
            cout<<"Total states explored: "<<cnt2<<endl;
            return cur;
        }
        m_s = max(m_s, int(pq.size()));
    }
    cout<<cnt2<<endl;
    cout<<"Not Possible"<<endl;
    return ini;
}

state hill_climb3(state ini){
    priority_queue<state, vector<state>, cmp_h>pq;
    pq.push(ini);
    int sz = INT_MAX;
    int m_s = 0;
    int cnt2 = 0;
    // set<vector<int>>vis;
    while(!pq.empty()){
        state cur = pq.top();
        pq.pop();
        cnt2++;
        movegen_bfs3(cur, pq, vis);
        if(goalTest(cur, pq)){
            print_res(cur);
            cout<<"Max queue size: "<<m_s<<endl;
            cout<<"Total states explored: "<<cnt2<<endl;
            return cur;
        }
        m_s = max(m_s, int(pq.size()));
    }
    cout<<cnt2<<endl;
    cout<<"Not Possible"<<endl;
    return ini;
}


void vnd(state ini){
    cout<<"For Neighbourhood 1: "<<endl;
    state hc1 = hill_climb1(ini);
    cout<<endl;
    cout<<"For Neighbourhood 2: "<<endl;
    state hc2 = hill_climb2(hc1);
    cout<<endl;
    cout<<"For Neighbourhood 3: "<<endl;
    // print_res(hc2);
    state hc3 = hill_climb3(hc2);
}


int main(){
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    freopen("input_vnd.txt", "r", stdin);
    freopen("output_vnd.txt", "w", stdout);
    srand((unsigned) time(NULL));
    int cl, var;
    // cout<<"Enter number of variables: ";
    cin>>var;
    // cout<<"Enter number of clauses: ";
    cin>>cl;
    state ini = generate_expr(var, cl);
    cout<<"The expression generated is: ";
    print_expr(ini);
    // cout<<ini.cost<<endl;
    vnd(ini);
    return 0;
}