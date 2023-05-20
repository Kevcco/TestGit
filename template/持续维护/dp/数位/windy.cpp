// Windy 数：不含前导零且相邻两个数字之差至少为2的正整数被称为 Windy 数。
#include <bits/stdc++.h>

using namespace std;

int f[11][10],a,b;

int dp(int n)
{
    if(!n) return 0;
    
    int res=0,last=-2;
    vector<int> a;
    while(n) a.push_back(n%10), n/=10;
    
    for(int i=a.size()-1;i>=0;i--)
    {
        int t=a[i];
        for(int j=0;j<t;j++)
            if(abs(j-last)>=2) res+=f[i][j];
        if(abs(t-last)>=2) last=t;
        else break;
        
        if(!i) res++;
    }
    
    for(int i=0;i<a.size()-2;i++)
        for(int j=1;j<10;j++)
            res+=f[i][j];
            
    res+=f[a.size()-2][1];
    
    return res;
}

int main()
{
    cin >> a >> b;
    for(int i=0;i<10;i++) f[0][i]=1;
    for(int i=1;i<11;i++)
        for(int j=0;j<10;j++)
            for(int k=0;k<10;k++)
                if(abs(j-k)>=2) 
                    f[i][j]+=f[i-1][k];
                    
    printf("%d\n",dp(b)-dp(a-1));
    
    return 0;
}