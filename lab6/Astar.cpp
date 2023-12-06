#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
class Node{
    public: int src, val;
            vector<int>path;
            Node(int sr, int cost, vector<int> p){
                src = sr;
                val = cost;
                path = p;
            }
};

class cmp_h {
public:
    bool operator()(Node &s1, Node &s2)
    {
        return s1.val>s2.val;
    }
};

void print_res(Node res){
    cout<<"Minimum Cost: "<<res.val<<endl;
    cout<<"Path Followed: ";
    for(int i = 0; i<res.path.size(); i++){
        cout<<res.path[i];
        if(i!=res.path.size()-1) cout<<"->";
    }
    cout<<endl;
    return;
}

void print_p(Node res){
    cout<<"Path Followed: ";
    for(int i = 0; i<res.path.size(); i++){
        cout<<res.path[i];
        if(i!=res.path.size()-1) cout<<"->";
    }
    cout<<endl;
    return;
}

int main(){
    int nodes, edges;
    freopen("input.txt", "r", stdin);
    // cout<<"Enter number of Nodes: ";
    cin>>nodes;
    // cout<<"Enter number of Edges: ";
    cin>>edges;
    // cout<<"Enter source, destination, weight for all edges: ";
    vector<vector<vector<int>>>g(nodes+1);
    for(int i = 0; i<edges; i++){
        int src, dst, wt;
        cin>>src>>dst>>wt;
        g[src].push_back({dst, wt});
    }
    // cout<<"Enter distance of all nodes from goal node: ";
    vector<int>huer(nodes+1, 0);
    for(int i = 1; i<nodes+1; i++){
        cin>>huer[i];
    }
    priority_queue<Node, vector<Node>, cmp_h>pq;
    Node st(1, huer[1], {1});
    // vector<int>path(nodes+1, -1);
    pq.push(st);
    while(!pq.empty()){
        int src = pq.top().src;
        int dis = pq.top().val - huer[src];
        vector<int>path = pq.top().path;
        print_p(pq.top());
        if(src==nodes){
            print_res(pq.top());
            break;
        }
        pq.pop();
        for(auto i:g[src]){
            vector<int>cur = path;
            cur.push_back(i[0]);
            Node child(i[0], huer[i[0]]+dis+i[1], cur);
            pq.push(child);
        }
    }
    return 0;
}