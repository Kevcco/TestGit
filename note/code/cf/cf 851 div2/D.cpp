/*

*/

#include <bits/stdc++.h>

#define YES puts("YES")
#define Yes puts("Yes")
#define NO puts("NO")
#define No puts("No")

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int> pii;

const int mod=1e9+7,N=3010;

int n,m,k;
int a[N],p[N];

void solve()
{
    cin >> n;
    for(int i=1;i<=n;i++) scanf("%d",a+i);
    a[n+1]=2e9,a[0]=-1e9;
    p[0]=1;
    for(int i=1;i<=n;i++) p[i]=p[i-1]*2%mod;

    ll res=0;
    for(int i=1;i<=n;i++)
    {
        int l=i,r=i;
        for(int j=i+1;j<=n;j++)
        {
            while(a[r]-a[j]<a[j]-a[i]) r++;
            while(a[i]-a[l]<=a[j]-a[i]) l--;
            res=(res+(ll)p[l]*p[n-r+1]%mod)%mod;
        }
    }
    printf("%lld\n",res);
    
}

int main()
{
    solve();
    return 0;
}