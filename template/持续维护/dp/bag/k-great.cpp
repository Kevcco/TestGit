/*
求前k优解  O(n * m * k)
转移变成两个长为k的降序数组合并
*/
#include <bits/stdc++.h>

using namespace std;

const int N=5010,K=60;

int n,m,k,v[N],w[N];
int f[N][K],temp[K];

int main()
{
    cin >> k >> m >> n;
    for(int i=1;i<=n;i++) cin >> v[i] >> w[i];
    memset(f,-0x3f,sizeof f);
    f[0][0]=0;
    for(int i=1;i<=n;i++)
    {
        for(int j=m;j>=v[i];j--)
        {
            int t=0,a=0,b=0;
            while(t<k)
            {
                if(f[j][a]>f[j-v[i]][b]+w[i]) temp[t++]=f[j][a++];
                else temp[t++]=f[j-v[i]][b++]+w[i];
            }
            memcpy(f[j],temp,sizeof temp);
        }
    }
        
    int res=0;
    for(int i=0;i<k;i++)
        if(f[m][i]) res+=f[m][i];
    printf("%d\n",res);
    return 0;
}