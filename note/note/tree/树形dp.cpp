/*
树形dp : 找 父节点 和 子节点 的信息之间的 递推关系
换根dp : 以树上不同点为根,其解不同 / 要求以不同点为根
        1，指定某个节点为根节点。
        2，第一次搜索完成预处理（如子树大小等），同时得到根节点的解。
        3，第二次搜索进行换根的动态规划，由已知解的节点推出子节点的解
        

一.树的直径 : 树中最长的路径
1.无边权的树的直径长度
    经典做法 两次dfs/bfs:1.任取一点a,找到距离这一点最远的一点u
                        2.找最远点u的最远点 两点距离即为直径

    证明:等价于证明 u 是某一条直径的一个端点 如果 u 是直径端点 那么找u的最远点一定是直径
         假设存在一条直径 bc 分两种情况 
         (1) bc 和 au 相交,那么设交点 x xu >= xc  因此 bu >= bc u 一定是某一直径端点
         (2) bc 和 au 不交， 假设 bc 和 au 之间连通路径 xy 那么 xu >= xy + yc  bu >= bc
    当然不如 dp 好写

2.带边权的树的直径
    树形dp 考虑经过某一节点u的所有路径
    考虑求这些路径的最大值 则 res 就是考虑完所有节点的最大值
    求经过 u 的所有路径 的最大值: 求以u为起点的子树的最长路径和次长路径
    则 max = d1 + d2 (考虑负数情况 d1 d2初始化为 0)
    求子树最长路径：dfs递归求

    时间复杂度 O(n)



二.树的重心 : 去掉重心后 剩下的几个连通块大小的最大值 最小
    点 u 的各个子树大小可以 递归 求得 
    而 u 的父节点的连通块大小 可以通过 n- sum(子树大小) -1 得到
   一个树有一个或两个重心，重心性质:
   重心的每个子树大小不大于整棵树的一半
   每个子树大小不大于整棵树的点一定是重心
   重心到其他所以点的距离和最小


三.树的中心 : 中心 到其他点的距离的最大值 最小
    换根dp
    考虑 求 任意一点到其他点距离的最大值 分成 向上(父节点) 和 向下(子树) 
    到各个子树的最大距离可以递归求得 而经过父节点的最大距离可以分为两类
    (1)经过父节点 + 父节点的子树  需要判断当前子树是否是父节点的子树中距离最远的
        如果是 则此种情况的最远距离是 到父节点距离+父节点的子树中的次远距离
        如果不是 到父节点距离+父节点子树最远距离
        因此要递归求节点 u 的子树中  最远距离 最远距离子树编号 次远距离  三个信息
    (2)经过父节点 + 父节点的父节点 此种情况可以使用父节点的向上最远距离

因此  第一遍 dfs递归 求 各节点的子树最远距离 次远距离 最远距离子树编号 (通过子节点更新父节点)
     第二遍 dfs 尾递归 求 各节点向上的最远距离 通过父节点更新子节点
            up_maxlenth[son] = max (up_maxlenth[father] , down_maxlenth[father]) + w[edge] 
       or   up_maxlenth[son] = max (up_maxlenth[father] , down_secondmaxlenth[father]) + w[edge] 

 

四.树的最大深度和 : 以某一点为根的树的深度和 最大 / 到其他所有点的距离和 最大
    换根dp
    假定已确定树根  考虑任意的一点u的深度和 和 u的父节点 fa 的关系
    dp[u] = dp[fa] - size[u] + (size - size[u])
    size[u] 表示以u为根的子树的节点个数  size 表示总节点个数

    - size[u] 代表 u 这个子树在 fa 这点多算的深度
    + (size - size[u]) 代表 u 的 fa 这一子树 在 计算fa时 少算的深度 

    观察可知 递推起点是 dp[root] 通过 fa 去更新 u子节点
    因此 先dfs 求出 size[i] 和 dp[root]
    再 dfs 递推

    扩展: 点带权 边带权 (深度为点权*边权)思考可知
    dp[u] = dp[fa] - size[u]*w[fa->u] + (size[1] - size[u])*w[fa->u]
    Luogu 2986


    cf 1324f
    POJ 3585
    换根dp时 父节点更新子节点时 将这一子节点对父节点的贡献减去

    Luogu 3047
    定义dp[i][j]表示离i点的距离为j节点权重和
    第一遍dfs 求出 子树意义下的 dp[i][j]
    第二遍dfs 考虑递推求真正的dp[i][j]
    dp[u][j] 应是子树中距离为j的 加上 距离父节点为j-1且不考虑自己这颗树的和
    dp[u][j] += dp[fa][j-1] - dp[u][j-2]
    其中dp[fa][j-1] 是考虑全部的 而dp[u][j-2] 是只考虑子树的 因此更新时 j要从大到小更新
    注意特判 dp[u][1] += dp[fa][0]

    cf 708c   waiting...
*/
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int> pii;

const int mod=1e9+7,N=2e5+10;

int n;
int h[N],e[N*2],ne[N*2],w[N*2],idx;

//求树的重心
int res,cnt,maxd[N],wei[2];
int dfs(int u,int fa)
{
    int sum=1;
    int maxv=0;
    for(int i=h[u];~i;i=ne[i])
    {
        int j=e[i];
        if(j==fa) continue;
        int d=dfs(j,u);
        sum+=d;
        maxv=max(maxv,d);
    }
    
    maxv=max(maxv,n-sum-1);
    res=min(res,maxv);
    
    return sum;
}

void query()
{
    res=n;
    dfs(1,0);
    for(int i=1;i<=n;i++)
        if(maxd[i]==res) wei[cnt++]=i;
}