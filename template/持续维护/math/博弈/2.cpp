/*
一.普通Bash
n个物品，每次取 1 - m 个，最后无法取的人输

归纳知，SG(x) = x % (m+1), 故若 n % (m+1) == 0, P态， 否则是 N态
最优策略就是,如果当前 x % (m+1) != 0 ,则取 x % (m+1) 个， 否则任取


二.chomp！游戏
n*m矩阵，每个格子放饼干，每次可以选则一块饼干(x,y)，并且将以这块饼干为左上角的矩形全部吃掉，
吃到(1,1)这块饼干的人输

结论: 如果 n = m = 1 ,P态，否则是 N态
证明(存在性证明) ：现在假设先手取(n,m),如果后手必输，那么得证，否则如果后手有必胜策略(a,b),
                  那么先手就可以取(a,b)而不是(n,m),因此一定是先手必胜
由于是存在性证明，因此并不能给出必胜策略，目前还没有构造出具体的必胜策略

扩展：可以扩展到任意一个存在最大元的有限偏序集S，每次选择x并且移走x和所有比x大的元素，取走最后一个元素的人输
结论: 如果S中元素个数 > 1 那么先手必胜
当然也可以是有最小元，每次移走比x小的元素，那么先手必胜
具体例子
(1)三维chomp游戏
(2)由n的因子构成的集合，x<=y 当且仅当 x|y
    n是最大元，故 n>1，N态， n=1，P态
(3)1 - n个数，每次选择一个集合中的数x，并删除集合中所有x的约数，取走最后一个元素的人输
    1是最小元，故 n>1 先手必胜
(4)给定有根树，初始节点为白色，每次可以选择一个白色节点并将此节点到根的路径上所有的节点全部染黑，无法染色的人赢
    root相当于最大元，因此如果节点个数 > 1，先手必胜


三.Wythoff游戏
两堆石子n,m，每次可以从一堆中取出若干个，或者从两堆石子同时取走若干个
(等价的游戏：在棋盘上移动，每次可以向左/上移动若干步，或者向左上45度移动若干步)

打表观察得到结论：假设 n <= m ,得到 P态的一堆数对(a,b)，
规律是 ai = [i*C] , bi = [i*C*C] , 其中 C = (1 + 根号5) / 2, []代表下取整
且 ai = mex(aj,bj) j<i,  bi = ai + i

Beatty序列：由一个正无理数r产生的序列 Br = [r*1], [r*2], [r*3], ... 
Rayleigh定理: 如果正无理数 r,s 满足 1/r + 1/s = 1,那么 Br 与 Bs是全体正整数的一个分割
              即任意一个正整数存在且仅存在于 Br 或 Bs 中
如何判断： n,m, n <= m, i = m-n, if(n==i*C) P态，else  N态
最优策略：同取 if(n>i*C) n,m -> i*C,i*C+i
         取n  i = (m-1)/(C*C) + 1 , t = i * C ,if(n>t) n -> t
         取m  i = (n-1)/C + 1 , t = i * C*C ,if(m>t) n -> t

四.树上删边
给定一棵树，每次删一条边，删除之后如果某个支不与地面/根相连，那么也一并删去

1.如果树是一条链， 那么 = nim游戏 ， sg(x) = x
2.Colon原则：假设G1,G2是两个树上删边游戏，如果sg(G1) = sg(G2) ,那么将G1的根新加一条边连到更低的节点作为新的根(地面)
变成一个新的树上删边游戏 H1,同理G2变成 H2, 那么有结论 sg(H1) = sg(H2)
证明: 已知 sg(G1) = sg(G2), 证明 sg(H1) = sg(H2)， 等价于证明 H1 + H2 是 P态
      假设先手删 H1 新加的那条边，那么后山删 H2新加的边 ,后手胜
      否则，先手删 G1内部的边,那么有两种情况
      (1) sg(G1') < sg(G1) , 那么后手一定可以操作使得 sg(G2') = sg(G1') ,因为 sg(G1) = sg(G2),
      (2) sg(G1') > sg(G1) , 那么后手也操作 G1 , 使得 sg(G1') 变回 sg(G1),由 sg的定义知这是一定可以的
      故后手能一直保持 sg(G1) = sg(G2)，直到 sg(G1) = sg(G2) = 0 ,这时先手只能选择新加的边，因此是 P态
      故 sg(H1) ^ sg(H2) = 0 , sg(H1) = sg(H2)
3.结论 由1，2，假设 G2是链，那么 sg(H2) = sg(G2) + 1,故 sg(H1) = sg(G1) + 1
       故得出结论 sg(u) = xorsum (sg(v) + 1) , v是u所有的儿子
*/

// Wythoff
#include <bits/stdc++.h>

using namespace std;
 
int main()
{
	int a, b, cha, c;
	double k=(sqrt(5.0)+1)/2;	
	while(scanf("%d%d", &a, &b) && (a+b)!=0)
	{
		if(a==b) //如果相同，可以一次取完
		{
			printf("1\n0 0\n");
			continue;
		}
		if(a>b) swap(a, b);//a代表小的，代表大的
		cha=b-a;//求差
		c=int(cha*k);//计算如果b固定的话，a应该是多少
		if(c==a)//如果相等，那么先手必输
			printf("0\n");
		else
		{
			printf("1\n");
			int bb=c+cha;//计算如果c当做小的，大的应该是多少
			if(b-bb==a-c)//判断这个可不可以两堆同时拿
				printf("%d %d\n", c, bb);
			for(int i=a-1, j=1; i>=1; i--, j++)//固定a，求另一个数
			{
				if(int(j*k)==i)
				{
					printf("%d %d\n", int(j*k), a);
					break;
				}
			}
			for(int i=b-1, j=1; i>=1; i--, j++)//固定b，求另一个数
			{
				if(int(j*k)==i)
				{
					printf("%d %d\n", int(j*k), b);
				}
			}
		}
	}
	return 0;
 }