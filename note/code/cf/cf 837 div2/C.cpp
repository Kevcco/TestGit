/*
判断n个数是否两两互质
n:1e5
an:1e9
time:3s
两个数不互质，即有公约数，因此可以对每个数求约数 hashmap判重 O(n*sqrt(max an)) 3e9 超时
考虑x|a,x|b,则必定存在素数p使得p|a,p|b，因此可以对每一个ai分解质因数，开hashmap,若有相同质因数，则返回NO
分解质因数：先预处理出2-sqrt(1e9)中的所有素数，大概有 3e4/ln3e4 = 3e3个,再用筛好的素数来分解质因数
           比直接分解快10倍           O(n*sqrt(x) / ln sqrt(x))  =  3e8    3s
*/

#include <iostream>
#include <algorithm>
#include <map>

using namespace std;

const int M=1e5;

int cnt,p[M],a[M];
bool st[M];

map<int,int> h;

void check()
{
    int n;
    cin >> n;
    for(int i=0;i<n;i++) cin >> a[i];
    for(int j=0;j<n;j++)
    {
        int x=a[j];
        for(int i=0;p[i]<=x/p[i];i++)
        {
            if(x%p[i]==0)
            {
                h[p[i]]++;
                if(h[p[i]]>1)
                {
                    puts("YES");
                    return;
                }
                while(x%p[i]==0) x/=p[i];
            }
        }
        if(x>1)
        {
            h[x]++;
            if(h[x]>1)
            {
                puts("YES");
                return;
            }
        }
    }
    puts("NO");
    return;
}

int main()
{
    for(int i=2;i<=34000;i++)
    {
        if(!st[i]) p[cnt++]=i;
        for(int j=0;p[j]<=34000/i;j++)
        {
            st[p[j]*i]=true;
            if(i%p[j]==0) break;
        }
    }

    int t;
    cin >> t;
    while(t--)
    {
        h.clear();
        check();
    }
    system("pause");
    return 0;
}