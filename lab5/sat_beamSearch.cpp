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

int huer(state &s){
    int cost = 0;
    for(int i = 0; i<s.cl; i++){
        int cur = 0;
        for(int j = 0; j<s.var; j++){
            if(s.val[j] * s.expr[i][j]==1){
                cost++;
                break;
            }
        }
        // if(cur>0){
        //     cost++;
        // }
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

void movegen_bfs(state prev, priority_queue<state, vector<state>, cmp_h>&s, set<vector<int>>&vis){
    
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
            s.push(k1);
            vis.insert(cur);
        }
    }
    return;
}
bool goalTest(state &cur, priority_queue<state, vector<state>, cmp_h>&pq){
    if(pq.top().cost<cur.cost){
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
void beam_search(state ini){
    priority_queue<state, vector<state>, cmp_h>pq;
    pq.push(ini);
    int sz = INT_MAX;
    int m_s = 0;
    int cnt2 = 0;
    set<vector<int>>vis;
    int beam = 3;
    vis.insert(ini.val);
    while(!pq.empty()){
        queue<state>q;
        for(int i = 0; i<beam && !pq.empty(); i++){
            q.push(pq.top());
            pq.pop();
        }
        int fl = 0;
        state fin(ini);
        while(!pq.empty()){
            pq.pop();
        }
        while(!q.empty()){
            state cur = q.front();
            q.pop();
            cnt2++;
            movegen_bfs(cur, pq, vis);
            if(goalTest(cur, pq)){
                fl++;
                fin = cur;
            }
            m_s = max(m_s, int(pq.size()));
        }
        if(fl==beam || pq.top().cost==pq.top().cl){
            state r = pq.top();
            print_res(r);
            cout<<"Max queue size: "<<m_s<<endl;
            cout<<"Total states explored: "<<cnt2<<endl;
            return;
        }
    }
    cout<<cnt2<<endl;
    cout<<"Not Possible"<<endl;
    return;
}


int main(){
    // ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    freopen("input_beam.txt", "r", stdin);
    freopen("output_beam.txt", "w", stdout);
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
    beam_search(ini);
    return 0;
}