
#include <iostream>

using namespace std;

const int N=1e6+10;

int a[N],q[N];
int n,k;

int main()
{
    scanf("%d%d",&n,&k);
    for(int i=0;i<n;i++) scanf("%d",&a[i]);
    int f=0,r=-1;
    for(int i=0;i<n;i++)
    {
        if(f<=r&&i-q[f]>=k) f++;
        while(f<=r&&a[q[r]]>=a[i])r--;
        q[++r]=i;
        if(i>=k-1) printf("%d ",a[q[f]]);
    }    
    return 0;
}