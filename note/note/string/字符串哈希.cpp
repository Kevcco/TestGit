/*
base 要大于字符串元素种类 
字符串元素不要映射成0

*/
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int mod=1e9+7,N=2e5+10,base=131;
const int mod2=998244353,base2=13331;

int n,m,k;
int ha[N],b[N];
char s[N];

int hash_value(int l,int r)
{
    return (ha[r]-(ll)ha[l-1]*b[r-l+1]%mod+mod)%mod;
}

void solve()
{
    scanf("%d%s",&n,s+1);
    b[0]=1;
    for(int i=1;i<=n;i++)
    {
        b[i]=(ll)b[i-1]*base%mod;
        ha[i]=((ll)ha[i-1]*base+s[i])%mod;
    }
}

int main()
{
    solve();
    return 0;
}