for(int i:{0}){
        for(int j:{-1, 1}){
            if(check(x+i, y+j, g.size(), g[0].size()) && !vis[x+i][y+j]){
                dfs_search(g, x+i, y+j, cnt, dirt, vis);
                cnt++;
            }
        }
    }