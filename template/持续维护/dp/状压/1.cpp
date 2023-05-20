#include <bits/stdc++.h>

using namespace std;

const int N=110,M=1<<10;

int n,m,g[N],f[N][70][70];
int cnt[M];
vector<int> st;

bool check(int i)
{
    for(int j=0;j<m;j++)
        if((i>>j&1)+((i>>j+1)&1)+((i>>j+2)&1)>1) return false;
    return true;
}

int main()
{
    cin >> n >> m;
    
    for(int i=1;i<=n;i++)
    {
        string s;
        cin >> s;
        for(int j=0;j<m;j++)
            if(s[j]=='H') g[i]+=1<<j;
    }
    g[0]=g[n+1]=g[n+2]=(1<<m)-1;
    
    for(int i=0;i<1<<m;i++)
        if(check(i)) st.push_back(i);
        
    for(int i=0;i<1<<m;i++)
        for(int j=0;j<m;j++)
            if(i>>j&1) cnt[i]++;
    
    memset(f,0xc0,sizeof f);
    f[0][0][0]=0;
    
    for(int i=1;i<=n+2;i++)
    {
        for(int j=0;j<st.size();j++)
        {
            for(int k=0;k<st.size();k++)
            {
                if((st[j]&g[i-1])||(st[k]&g[i])||(st[j]&st[k])) continue;
                for(int l=0;l<st.size();l++)
                    if(!(st[l]&st[k]))
                        f[i][j][k]=max(f[i-1][l][j]+cnt[st[k]],f[i][j][k]);
            }
        }
    }
    
    printf("%d\n",f[n+2][0][0]);
}