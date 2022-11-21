class DisjointSet {
    vector<int> rank, parent, size; 
public: 
    DisjointSet(int n) {
        rank.resize(n+1, 0); 
        parent.resize(n+1);
        size.resize(n+1); 
        for(int i = 0;i<=n;i++) {
            parent[i] = i; 
            size[i] = 1; 
        }
    }

    int findUPar(int node) {
        if(node == parent[node])
            return node; 
        return parent[node] = findUPar(parent[node]); 
    }

    void unionByRank(int u, int v) {
        int ulp_u = findUPar(u); 
        int ulp_v = findUPar(v); 
        if(ulp_u == ulp_v) return; 
        if(rank[ulp_u] < rank[ulp_v]) {
            parent[ulp_u] = ulp_v; 
        }
        else if(rank[ulp_v] < rank[ulp_u]) {
            parent[ulp_v] = ulp_u; 
        }
        else {
            parent[ulp_v] = ulp_u; 
            rank[ulp_u]++; 
        }
    }

    void unionBySize(int u, int v) {
        int ulp_u = findUPar(u); 
        int ulp_v = findUPar(v); 
        if(ulp_u == ulp_v) return; 
        if(size[ulp_u] < size[ulp_v]) {
            parent[ulp_u] = ulp_v; 
            size[ulp_v] += size[ulp_u]; 
        }
        else {
            parent[ulp_v] = ulp_u;
            size[ulp_u] += size[ulp_v]; 
        }
    }
}; 
class Solution {
public:
    vector<vector<string>> accountsMerge(vector<vector<string>>& accounts)
    {
        int n=accounts.size();
        DisjointSet ds(n);
        unordered_map<string,int>mp;
        // step 1
        for(int i=0;i<n;i++)
        {
         for(int j=1;j<accounts[i].size();j++)
         {
             string s=accounts[i][j];
             if(mp.find(s)!=mp.end())
             {
                 ds.unionByRank(i,mp[s]);
             }
             else
             {
                 mp[s]=i;
             }
         }
        }
        // step 2
        vector<string>merge[n];
        for(auto it:mp)
        {
            string node=it.first;
            int kk=ds.findUPar(it.second);
            merge[kk].push_back(node);
        }
        // step 3
        vector<vector<string>>ans;
        for(int i=0;i<n;i++)
        {
            if(merge[i].size()==0)
            {
                continue;
            }
            sort(merge[i].begin(),merge[i].end());
            vector<string>temp;
            temp.push_back(accounts[i][0]);
            for(auto it:merge[i])
            {
              temp.push_back(it);
            }
            ans.push_back(temp);
        }
        return ans;
    }
};