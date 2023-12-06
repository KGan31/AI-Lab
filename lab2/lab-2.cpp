#include <bits/stdc++.h>
using namespace std;
// 1 - Fill A
// 2 - Fill B
// 3 - Transfer A->B
// 4 - Transfer B->A
// 5 - Empty A
// 6 - Empty B

void fillA(int &cur_a, int &cur_b, int cap_a){
    cur_a = cap_a;
    return;
}

void fillB(int &cur_a, int &cur_b, int cap_b){
    cur_b = cap_b;
    return;
}

void transferAtoB(int &cur_a, int &cur_b, int cap_b){
    int cur_b3 = min(cap_b, cur_b + cur_a);
    int cur_a3 = cur_a+cur_b-cur_b3;
    cur_a = cur_a3;
    cur_b = cur_b3;
    return;
}

void transferBtoA(int &cur_a, int &cur_b, int cap_a){
    int cur_a4 = min(cap_a, cur_b + cur_a);
    int cur_b4 = cur_a+cur_b-cur_a4;
    cur_a = cur_a4;
    cur_b = cur_b4;
    return;
}

void emptyA(int &cur_a, int &cur_b){
    cur_a = 0;
    return;
}

void emptyB(int &cur_a, int &cur_b){
    cur_b = 0;
    return;
}

void dfs(int &cap_a, int &cap_b, int cur_a, int cur_b, int &target, set<pair<int, int>>&vis, vector<vector<int>>&dp, int &mn, int d, vector<vector<int>>path, vector<vector<int>>&f_path){
    if(cur_a==target || cur_b==target){
        if(mn>d){
            mn = d;
            f_path.clear();
            f_path = path;
            // cout<<path.size()<<" "<<f_path.size()<<endl;
        }
        // dp[cur_a][cur_b] = mn;
        return;
    }
    if(vis.find({cur_a, cur_b})!=vis.end()) return;

    vis.insert({cur_a, cur_b});

    // Fill A
    int cur_a1 = cur_a;
    int cur_b1 = cur_b;
    fillA(cur_a1, cur_b1, cap_a);
    path.push_back({1, cur_a1, cur_b1});
    dfs(cap_a, cap_b, cur_a1, cur_b1, target, vis, dp, mn, d+1, path, f_path);
    path.pop_back();

    // Fill B
    int cur_a2 = cur_a;
    int cur_b2 = cur_b;
    fillB(cur_a2, cur_b2, cap_b);
    path.push_back({2, cur_a2, cur_b2});
    dfs(cap_a, cap_b, cur_a2, cur_b2, target, vis, dp, mn, d+1, path, f_path);
    path.pop_back();

    // Transfer A->B
    int cur_b3 = cur_b;
    int cur_a3 = cur_a;
    transferAtoB(cur_a3, cur_b3, cap_b);
    path.push_back({3, cur_a3, cur_b3});
    dfs(cap_a, cap_b, cur_a3, cur_b3, target, vis, dp, mn, d+1, path, f_path);
    path.pop_back();

    // Transfer B->A
    int cur_a4 = cur_a;
    int cur_b4 = cur_b;
    transferBtoA(cur_a4, cur_b4, cap_a);
    path.push_back({4, cur_a4, cur_b4});
    dfs(cap_a, cap_b, cur_a4, cur_b4, target, vis, dp, mn, d+1, path, f_path);
    path.pop_back();

    // Empty A
    int cur_a5 = cur_a;
    int cur_b5 = cur_b;
    emptyA(cur_a5, cur_b5);
    path.push_back({5, cur_a5, cur_b5});
    dfs(cap_a, cap_b, cur_a5, cur_b5, target, vis, dp, mn, d+1, path, f_path);
    path.pop_back();

    // Empty B
    int cur_a6 = cur_a;
    int cur_b6 = cur_b;
    emptyA(cur_a6, cur_b6);
    path.push_back({6, cur_a6, cur_b6});
    dfs(cap_a, cap_b, cur_a6, cur_b6, target, vis, dp, mn, d+1, path, f_path);
    path.pop_back();

    // dp[cur_a][cur_b] = mn;
    return ;
}

void solve(int cap_a, int cap_b, int cur_a, int cur_b, int target){
    set<pair<int, int>>vis;
    int d = 0;
    int mn = INT_MAX;
    vector<vector<int>>dp(cap_a, vector<int>(cap_b, -1));
    vector<vector<int>>path, f_path;
    dfs(cap_a, cap_b, cur_a, cur_b, target, vis, dp, mn, d, path, f_path);
    if(mn==INT_MAX){
        cout<<"NOT POSSIBLE"<<endl;
        return;
    }
    cout<<"Minimum operations required are: "<<mn<<endl;
    for(int i = 0; i<f_path.size(); i++){
        cout<<"Operation: "<<f_path[i][0]<<" Current value A: "<<f_path[i][1]<<" Current value B: "<<f_path[i][2]<<endl; 
    }
    return;
}

void slv(int cap_a, int cap_b, int cur_a, int cur_b, int target){
    if(cap_a<cap_b){
        return solve(cap_b, cap_a, cur_a, cur_b, target);
    }
    queue<pair<vector<int>, vector<pair<int, pair<int, int>>>>>q;
    set<pair<int, int>>s;
    q.push({{cur_a, cur_b}, {}});
    s.insert({0, 0});
    bool fl = false;
    while(!q.empty()){
        cur_a = q.front().first[0];
        cur_b = q.front().first[1];
        // int op = q.front().first[2];
        vector<pair<int, pair<int, int>>>path = q.front().second;
        q.pop();
        if(cur_a==target || cur_b==target){
            for(int i = 0; i<path.size(); i++){
                cout<<"Operation: "<<path[i].first<<" Capacity A: "<<path[i].second.first<<" Capacity B: "<<path[i].second.second<<endl;
            }
            fl = true;
            break;
        }

        //Fill A
        if(s.find({cap_a, cur_b})==s.end()){
            vector<pair<int, pair<int, int>>>path1 = path;
            path1.push_back({1, {cap_a, cur_b}});
            q.push({{cap_a, cur_b}, path1});
            s.insert({cap_a, cur_b});
        }
        

        // Fill B
        if(s.find({cur_a, cap_b})==s.end()){
            vector<pair<int, pair<int, int>>>path2 = path;
            path2.push_back({2, {cur_a, cap_b}});
            q.push({{cur_a, cap_b}, path2});
            s.insert({cur_a, cap_b});
        }
        

        // Transfer A->B
        int cur_b3 = min(cap_b, cur_b + cur_a);
        int cur_a3 = cur_a+cur_b-cur_b3;
        if(s.find({cur_a3, cur_b3})==s.end()){
            vector<pair<int, pair<int, int>>>path3 = path;
            path3.push_back({3, {cur_a3, cur_b3}});
            q.push({{cur_a3, cur_b3}, path3});
        }
        

        // Transfer B->A
        int cur_a4 = min(cap_a, cur_b + cur_a);
        int cur_b4 = cur_a+cur_b-cur_a4;
        if(s.find({cur_a4, cur_b4})==s.end()){
            vector<pair<int, pair<int, int>>>path4 = path;
            path4.push_back({4, {cur_a4, cur_b4}});
            q.push({{cur_a4, cur_b4}, path4});
        }
        

        // Empty A
        if(s.find({0, cur_b})==s.end()){
            vector<pair<int, pair<int, int>>>path5 = path;
            path5.push_back({5, {0, cur_b}});
            q.push({{0, cur_b}, path5});
        }

        // Empty B
        if(s.find({cur_a, 0})==s.end()){
            vector<pair<int, pair<int, int>>>path6 = path;
            path6.push_back({6, {cur_a, 0}});
            q.push({{cur_a, 0}, path6});
        }
    }
    if(!fl){
        cout<<"It is not possible";
    }
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
    int cur_a = 0, cur_b = 0;
    solve(cap_a, cap_b, cur_a, cur_b, target);

    return 0;
}