/*
给定n个节点n-1条边的树 初始时有一个节点被染黑
接下来n-1次操作 每次选择一个未被染色的节点染上黑色
对于每次操作 询问当前所有黑色节点中 两两之间的最小距离



根号分治： 
定义一个dist[] 数组，代表某一节点到所有黑色节点的最短距离
每次从当前染色节点开始 bfs 遇到 dist[son] > dist[u]+1 并且 dist[u]+1<ans 才去更新
首先如果 dist[son] > dist[u]+1 说明son节点离另外某个黑色节点更近 也就不必更新son以及son之后的了
如果  dist[u]+1 >= ans 则可以直接不更新 因为ans更小 不影响答案准确性

时间复杂度分析 : 
    前 根号n 次操作 最坏 O(n*sqrt(n))
    
    根号n次操作之后 ans 一定 <= sqrt(n)  ******
    也就是 插入 sqrt(n) 个点 两两之间的距离的最小值一定 <= sqrt(n)
    (在数轴上也有这个结论)
    剩下的操作 考虑任意节点 最多入队 sqrt(n) 次 因为每次入队都会减小 dist 而 dist <= sqrt(n)
    因此 最坏情况下某个点的出边最多访问sqrt(n) 某一条边最多访问 2*sqrt(n)  所以是O(n*sqrt(n))
总时间  O(n*sqrt(n)) 
*/
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int> pii;

int n,m,k;

void solve()
{
    cin >> n >> m;
    vector<vector<int>> h(n+1);
    vector<int> op;
    op.push_back(m);
    for(int i=1;i<n;i++)
    {
        int x;
        scanf("%d",&x);
        op.push_back(x);
    }
    for(int i=1;i<n;i++)
    {
        int a,b;
        scanf("%d%d",&a,&b);
        h[a].push_back(b);
        h[b].push_back(a);
    }
    vector<int> dist(n+1,n);
    int ans=n;
    for(int i=0;i<n;i++)
    {
        int t=op[i];
        ans=min(ans,dist[t]);
        if(i) printf("%d ",ans);
        queue<int> q;
        dist[t]=0;
        q.push(t);
        while(!q.empty())
        {
            int x=q.front();
            q.pop();
            for(auto i : h[x])
            {
                if(dist[i]>dist[x]+1&&dist[x]+1<ans)
                {
                    dist[i]=dist[x]+1;
                    q.push(i);
                }
            }
        }
    }
    puts("");
}

int main()
{
    int _;
    cin >> _;
    while(_--) solve();
    return 0;
}