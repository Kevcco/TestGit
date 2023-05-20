/*
给定 n 个 1-m 的排列   n<=5e4  m<=10
定义一个排列的漂亮值为 a1=1,a2=2,a3=3,...,ak=k,最大的k值，相当于最大前缀
定义两个排列 a*b 生成一个新排列 c   ci=b[ai]
询问对所有  1 <= i <= n  ai * aj 的最大漂亮值是多少  j任取 



对一个排列 a 而言 找一个b  使得  a*b 漂亮值最大 假设漂亮值是 m 可以由 a 反推 b
 a1 a2 a3 a4
 则 b: b[a1]=1,b[a2]=2,b[a3]=3,b[a4]=4
又由于漂亮值是前缀匹配 因此相当于 找一个序列能匹配的最大前缀 

想到trie解决寻找最大前缀匹配问题
具体而言插入每个排列的期望排列
寻找时直接寻找原排列的最大匹配
理解: a 期望排列  a'     b 期望排列  b'
      a 如果匹配到 b' 也就是相当于 a' 匹配到 b
      并且用b' 去匹配 a 保证了是前缀顺序匹配
      如果用 a' 去匹配 b 无法保证前缀顺序

多组测试数据 trie清空:由于trie很庞大 每次直接memset会花大量时间
可以在每组测试数据的结尾
利用 idx 也就是本组使用了多少节点 将这idx+1（多一个0）个节点清空即可

其他的情况如数组的清空 还有一种方法是要用多少就清空多少
*/

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int> pii;

const int mod=1e9+7,N=5e4+10;

int n,m,k;
int p[N][11];
int t[11];
int trie[N*11][11],idx;


void insert()
{
    int x=0;
    for(int i=1;i<=m;i++)
    {
        if(!trie[x][t[i]]) trie[x][t[i]]=++idx;
        x=trie[x][t[i]];
    }
}

void query(int u)
{
    int x=0;
    int cnt=0;
    for(int i=1;i<=m;i++)
    {
        if(!trie[x][p[u][i]]) break;
        cnt++;
        x=trie[x][p[u][i]];
    }
    printf("%d ",cnt);
}

void solve()
{
    cin >> n >> m;
    idx=0;
    for(int i=0;i<n;i++)
    {
        for(int j=1;j<=m;j++)
        {
            int x;
            scanf("%d",&x);
            t[x]=j;
            p[i][j]=x;
        }
        insert();
    }

    for(int i=0;i<n;i++)
    {
        query(i);
    }
    puts("");
    for(int i=0;i<=idx;i++)
        memset(trie[i],0,sizeof(trie[i]));
}

int main()
{
    int _;
    cin >> _;
    while(_--) solve();
    return 0;
}