// O(n * m)
#include <iostream>

using namespace std;

const int N=1010;

char s1[N],s2[N];
int n,m,f[N][N];

int main()
{
    scanf("%d%d%s%s",&n,&m,s1+1,s2+1);
    
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=m;j++)
        {
            f[i][j]=max(f[i-1][j],f[i][j-1]);
            if(s1[i]==s2[j]) f[i][j]=max(f[i][j],f[i-1][j-1]+1);
        }
    }
    
    printf("%d\n",f[n][m]);
    return 0;
}