/*
https://ac.nowcoder.com/acm/contest/46810/F

每次从地图左上走到右下角，中间有障碍，只能向右和下走，从起点走到终点后可以返回起点重走
问最多能经过多少格子

正反dp  只有 正着走能走到 且 反着走能走到 才计入答案

*/

#include <bits/stdc++.h>
using namespace std;
#define int long long

#define inf 0x3f3f3f3f
#define finf -0x3f3f3f3f
#define MS(i,j) memset(i,j,sizeof (i))
#define endl '\n'
#define pii pair<int,int>
int gcd(int a,int b){ return b==0?a:gcd(b,a%b);}
int lcm(int a,int b){ return (a*b)==0?0:a*b/gcd(a,b);}

const int N = 5e5+10;
const int mod = 1e9+7;

int k,t,n,m,ma=0,mi=inf;
int cnt,temp,total;
char arr[N];
string str;
int a[N],b[N];
vector<int> vec;
bool mp1[N][5]={0},mp2[N][5]={0},mp[N][5]={0};
void solve()
{
    cin>>t;
    while(t--){
        cin>>n>>k;
        for(int i=0;i<=n;i++){
            for(int j=0;j<=3;j++){
                mp[i][j]=mp1[i][j]=mp2[i][j]=0;
            }
        }
        cnt=0;
        int l,r;
        for(int i=0;i<k;i++){
            cin>>l>>r;
            mp[l][r]^=1;
        }
        mp1[1][1]=1;
        mp2[n][3]=1;
        for(int i=1;i<=n;i++)
            for(int j=1;j<=3;j++){
                if(!mp[i][j]&&(mp1[i-1][j]||mp1[i][j-1]))
                    mp1[i][j]=1;
        }
        for(int i=n;i>=1;i--)
            for(int j=3;j>=1;j--){
                if(!mp[i][j]&&(mp2[i+1][j]||mp2[i][j+1]))
                    mp2[i][j]=1;
        }
        for(int i=1;i<=n;i++){
            for(int j=1;j<=3;j++){
                if(mp1[i][j]&&mp2[i][j])cnt++;
            }
        }
        if(cnt)
        cout<<cnt-1<<endl;
        else
        cout<<cnt<<endl;
    }
    
}

signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
}