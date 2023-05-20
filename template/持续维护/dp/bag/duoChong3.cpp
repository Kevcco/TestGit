
//单调队列优化  O(n * m)

#include <bits/stdc++.h>

using namespace std;

const int N=2e4+10;

int f[2][N],q[N],n,m;

int main()
{
    cin >> n >> m;
    for(int i=1;i<=n;i++)
    {
        int cur=i&1,pre=cur^1;
        int v,w,s;
        scanf("%d%d%d",&v,&w,&s);
        for(int j=0;j<v;j++)
        {
            int ff=0,rr=-1;
            for(int k=0;j+k*v<=m;k++)
            {
                if(ff<=rr&&k-q[ff]>s) ff++;
                while(ff<=rr&&f[pre][q[rr]*v+j]-q[rr]*w<=f[pre][k*v+j]-k*w) rr--;
                q[++rr]=k;
                f[cur][k*v+j]=f[pre][q[ff]*v+j]+(k-q[ff])*w;
            }
        }
    }
    
    printf("%d",f[n&1][m]);
    return 0;
}