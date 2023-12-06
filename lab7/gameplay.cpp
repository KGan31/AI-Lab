#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
// cur = 1 - Player
// cur = 2 - Comp
class game{
    public: 
    vector<vector<int>>arr;
    int cur = 0;
    game(){}
    game(vector<vector<int>>&a, int c){
        arr = a;
        cur = c;
    }
    game(game &d){
        arr = d.arr;
        cur = d.cur;
    }
};

void display(game g){
    cout<<"Game: "<<endl;
    for(int i = 0; i<3; i++){
        for(int j = 0; j<3; j++){
            cout<<g.arr[i][j]<<" ";
        }
        cout<<endl;
    }
    return;
}

int eval(game g){
    int sc = 0;
    int em = 0;
    for(int i = 0; i<3; i++){
        int comp = 0, pl = 0;
        for(int j = 0; j<3; j++){
            if(g.arr[i][j]==2){
                comp++;
            }
            else if(g.arr[i][j]==1){
                pl++;
            }
            else{
                em++;
            }
        }
        if(comp==3){
            return 1;
        }
        if(pl==3){
            return -1;
        }
    }
    for(int i = 0; i<3; i++){
        int comp = 0, pl = 0;
        for(int j = 0; j<3; j++){
            if(g.arr[j][i]==2){
                comp++;
            }
            else if(g.arr[j][i]==1){
                pl++;
            }
            else{
                em++;
            }
        }
        if(comp==3){
            return 1;
        }
        if(pl==3){
            return -1;
        }
    }
    int comp = 0, pl = 0;
    if(g.arr[0][0]==1 && g.arr[1][1]==1 && g.arr[2][2]==1){
        pl = 3;
    }
    if(g.arr[0][0]==2 && g.arr[1][1]==2 && g.arr[2][2]==2){
        comp = 3;
    }
    if(g.arr[2][0]==1 && g.arr[1][1]==1 && g.arr[0][2]==1){
        pl = 3;
    }
    if(g.arr[2][0]==2 && g.arr[1][1]==2 && g.arr[0][2]==2){
        comp = 3;
    }
    if(comp==3){
        return 1;
    }
    if(pl==3){
        return -1;
    }
    return 0;
}
bool poss(game g){
    int em = 0;
    for(int i = 0; i<3; i++){
        int comp = 0, pl = 0;
        for(int j = 0; j<3; j++){
            if(g.arr[i][j]==2){
                comp++;
            }
            else if(g.arr[i][j]==1){
                pl++;
            }
            else{
                em++;
            }
        }
    }
    int ev = eval(g);
    if(ev!=0) return false;
    return em>0;
}
int minmax(game g){
    int ev = eval(g);
    if(!poss(g)){
        return ev;
    }
    int sc = 0;
    int cur = g.cur;
    if(cur==2){
        sc = -10;
        for(int i = 0; i<3; i++){
            for(int j = 0; j<3; j++){
                if(g.arr[i][j]==0){
                    vector<vector<int>>a = g.arr;
                    a[i][j] = cur;
                    game k(a, 1);
                    int temp = minmax(k);  //Recursive call
                    if(temp>sc){
                        sc = temp;
                    }
                }
            }
        }
    }
    if(cur==1){
        sc = 10;
        for(int i = 0; i<3; i++){
            for(int j = 0; j<3; j++){
                if(g.arr[i][j]==0){
                    vector<vector<int>>a = g.arr;
                    a[i][j] = cur;
                    game k(a, 2);
                    int temp;
                    temp = minmax(k);  //Recursive call
                    if(temp<sc){
                        sc = temp;
                    }
                }
            }
        }
    }
    return sc;
}

game best_move(game g){
    game fin(g);
    int cur = g.cur;
    int sc = 0;
    if(cur==2){
        sc = -10;
        for(int i = 0; i<3; i++){
            for(int j = 0; j<3; j++){
                if(g.arr[i][j]==0){
                    vector<vector<int>>a = g.arr;
                    a[i][j] = cur;
                    game k(a, 1);
                    
                    int temp = minmax(k);  //Recursive call
                    if(temp>sc){
                        fin = k;
                        sc = temp;
                    }
                }
            }
        }
    }
    return fin;
}

void play(){
    vector<vector<int>>g(3, vector<int>(3, 0));
    cout<<"Enter a coordinates of move: ";
    int x, y;
    cin>>x>>y;
    g[x-1][y-1] = 1;
    game start(g, 2);
    int ev = eval(start);
    game cur = start;
    // display(cur);
    while(poss(cur)){
        cur = best_move(cur);
        display(cur);
        ev = eval(cur);
        if(!poss(cur)) break;
        cout<<"Enter a coordinates of move: ";
        cin>>x>>y;
        cur.arr[x-1][y-1] = 1;
        cur.cur = 2;
        ev = eval(cur);
    }
    if(ev==-1) cout<<"Player "<<1<<" Wins!!!"<<endl;
    else if(ev==1) cout<<"Player "<<2<<" Wins!!!"<<endl;
    else cout<<"Tie"<<endl;
    return;
}

int main(){
    play();
    return 0;
}