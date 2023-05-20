/*
在预处理和询问的复杂度之间寻找平衡 通常以 根号 作为分界线 
规模小于根号的询问可以 n * sqrt(n) 预处理
规模大于根号的询问直接暴力求解 由于规模大于根号的询问不会超过 sqrt(n) 个 故 T = O( n * sqrt(n))
因从总的时间复杂度 O( n * sqrt(n) )

1.k个数相加不超过 n , 则 这k个数中 不同的数有 不超过 sqrt(n) 个 取等情况是 1+2+3+...+x = x*(x+1)/2
  x*(x+1) <= 2*n  x < sqrt(2*n)
  Niuke 小白 59 F

2.长为 n 的数轴上 放 sqrt(n) 个点 那么任意两个点之间距离的最小值 <= sqrt(n)
  在树上有相同结论 有n个点的树 染黑 sqrt(n) 个点 任意两个点之间距离的最小值 <= sqrt(n)
  cf 847 F

3. cf 858 E

4. abc 258 G
   给定无向图 n个点 m条边 求三元环的个数  (一种做法是bitset二层循环枚举i,j,找k  O( n^3/64 ) )
   根号分治
   按 点的度 重新建边 任意一条边 点度小的指向点度大的 点度相同的，编号小的指向编号大的 变成新图
   不难知道新图是有向无环的

   点度小的指向点度大的 保证了 新图 任意一个点的出度 <= sqrt(m)
   证明 对于原图中 点的度 <= sqrt(m) 的, 新图中 点的出度一定小于等于 sqrt(m)
   对于原图中 点度 > sqrt(m) 的 ,新图中 只会和 >=这个点的度 的点连边 而这样的点 不会超过 sqrt(m) 个
   (一共m条边 度大于sqrt(m)的点不会超过 O(sqrt(m)) 个)
   因此 新图中任意一个点的出度 都 <= sqrt(m)

   而原图中的任意三元环 i-j-k  i<j<k 在新图中一定会以 i->j j->k i->k 出现
   因此第一层循环点 i 第二层循环出边 对应的点j 第三层循环点j的出边 对应点k 判断i是否指向k (预处理)


   按 点的度 重新建图 任意一条边 点度小的指向点度大的 
   新图满足任意一点出度 <= sqrt(m) 这种建新图的方式常用

5. 给一个长为n的数组 n<=2e5 要求需要处理q个如下操作 q<=2e5
    1.给 所有 下标i mod x = y 的元素 + d
    2.查询 a[x] 的值

    考虑操作1: 相当于每隔 x 个元素就操作一次 如果 x > sqrt(n) 那么直接暴力 O(sqrt(n))
              否则 x < sqrt(n) 那么打上标记 tag[x][y] += d  其中 tag[sqrt(n)][sqrt(n)]
    考虑操作2：查询单点 直接暴力统计tag再加上数组的值即可 O(sqrt(n))

    所以总时间 O(n*sqrt(n))

6. 给一个n点m边的图，每个点初始为白色 q 个询问 有两种类型  n <= 2e5  m,q <= 4e5
   1.将一个点变色 即白变黑 黑变白
   2.查询一个点邻接有多少个黑点

   n个点 按照度的不同 分成两类 deg > sqrt(n) 的称为大点 个数不超过 sqrt(n) 个
   deg < sqrt(n) 的称为小点
   考虑查询 : 如果是 小点 那么可以直接暴力统计  如果是大点 那么不能暴力统计了 可以修改时维护大点的答案 O(sqrt(n))
   考虑修改 : 要维护大点的答案 所以将这个点所有邻接的大点的答案都修改一下 O(sqrt(n)) 当然每个点周围的大点需要先预处理 O(m)
*/