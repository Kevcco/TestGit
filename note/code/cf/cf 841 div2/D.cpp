/*
    二分+前缀和
*/


#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int,int> pii;

const int mod=1e9+7,N=2e5+10;

int n,m,k;

void solve()
{
    cin >> n >> m;
    vector<vector<int>> a(n+1,vector<int>(m+1));
    
    int l=1,r=0;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            cin >> a[i][j],r=max(a[i][j],r);

    r=min(n,r);
    while(l<r)
    {
        int mid=l+r+1>>1;
        vector<vector<int>> p(n+1,vector<int>(m+1));
        for(int i=1;i<=n;i++)
            for(int j=1;j<=m;j++)
            {
                if(a[i][j]<mid) p[i][j]=-1;
                p[i][j]+=p[i-1][j]+p[i][j-1]-p[i-1][j-1];
            }
        bool flag=false;
        for(int i=mid;i<=n;i++)
            for(int j=mid;j<=m;j++)
            {
                int x=p[i][j]-p[i-mid][j]-p[i][j-mid]+p[i-mid][j-mid];
                if(!x)
                {
                    flag=true;
                    break;
                }
            }
        
        if(flag) l=mid;
        else r=mid-1;
    }
    printf("%d\n",l);
    return;
}

int main()
{
    int t;
    cin >> t;
    while(t--) solve();

    return 0;
}
