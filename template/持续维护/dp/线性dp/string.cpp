/*
POJ 1159.将给定字符串插入最少的元素变成回文串
定义f[i][j]为将i-j变成回文串的最少操作次数
状态计算: f[i][j] = min ( f[i + 1][j] , f[i][j - 1] ) + 1;
if(s[i]==s[j]) f[i][j] = min( f[i + 1][j - 1] , f[i][j] );
*/
#include <iostream>

using namespace std;

const int N=5e3+10;

char s[N];
int f[2][N],n;

int main()
{
    cin >> n;
    cin >> s+1;
    
    for(int i=n-1;i;i--)
    {
        int cur=i&1,pre=cur^1;
        for(int j=i+1;j<=n;j++)
        {
            f[cur][j]=min(f[cur][j-1],f[pre][j])+1;
            if(s[i]==s[j]) f[cur][j]=min(f[cur][j],f[pre][j-1]);
        }
        
    }   
    printf("%d",f[1][n]);
    
    return 0;
}

