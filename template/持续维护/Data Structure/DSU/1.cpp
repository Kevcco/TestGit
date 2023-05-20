
#include <bits/stdc++.h>

using namespace std;

const int N=50010;

int p[N],d[N];

int find(int k)
{
    if(p[k]!=k)
    {
        int u=p[k];
        p[k]=find(p[k]);
        d[k]+=d[u];
    }
    return p[k];
}

int main()
{
    int n,k;
    cin >> n >> k;
    for(int i=1;i<=n;i++) p[i]=i;
    int res=0;
    
    while(k--)
    {
        int D,x,y;
        cin >> D >> x >> y;

        if(x>n||y>n) res++;
        else if(D==2)
        {
            if(x==y) res++;
            else
            {
                int a=find(x),b=find(y);
                if(a==b)
                {
                    if((d[x]-d[y]-1)%3) res++;
                }
                else p[a]=b,d[a]=d[y]-d[x]+1;
            }
        }
        else
        {
            int a=find(x),b=find(y);
            if(a==b)
            {
                if((d[x]-d[y])%3)res++;
            }
            else p[a]=b,d[a]=d[y]-d[x];
        }
    }

    cout << res;
    return 0;
}