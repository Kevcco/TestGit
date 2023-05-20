// O(n * logn)
#include <iostream>
#include <algorithm>

using namespace std;

const int N=1e5+10;

int n,g[N];

int main()
{
    cin >> n;
    int len=0;
    for(int i=1;i<=n;i++)
    {
        int x;
        scanf("%d",&x);
        int l=0,r=len;
        while(l<r)
        {
            int mid=l+r+1>>1;
            if(g[mid]<x) l=mid;
            else r=mid-1;
        }
        g[r+1]=x;
        len=max(len,r+1);
    }
    printf("%d\n",len);
}