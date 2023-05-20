/*
树哈希: 一棵确定形状的有根树 -> 唯一的哈希值
主要用于判断树是否同构

对于有根树 shift() 是哈希函数
hash[fa] = 1 + sum ( shift( hash[son] ) )
hash值 一般使用 ull 自然溢出



模板
const ull mask = std::chrono::steady_clock::now().time_since_epoch().count();

ull shift(ull x) {
  x ^= mask;
  x ^= x << 13;
  x ^= x >> 7;
  x ^= x << 17;
  x ^= mask;
  return x;
}

ull hh[N];

void dfs(int u,int fa)
{
    hh[u]=1;
    for(int i=h[u];~i;i=ne[i])
    {
        int j=e[i];
        if(j==fa) continue;
        dfs(j,u);
        hh[u]+=shift(hh[j]);
    }
}



应用
1.判断有根树同构 : 根hash值相同
2.判断无根树同构 （1）分别以n个点为根求 hash 取最小(or最大)的 hash 值
                      暴力 or 换根dp
                      换根: hash[j] += shift( hash[u] - shift(hash[j]) );
                 (2) 求以树的重心 (最多两个) （如果两个取最小）为根的hash值 
                   若hash值相同则同构
                Luogu 5043
3.判断有根树是否对称 cf 855 G


*/
