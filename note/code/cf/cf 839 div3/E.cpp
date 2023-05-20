/*
博弈论
给定一个长度为 n <= 5e5 的排列 a ,每个数都有颜色，初始为红色。
两人在排列上玩游戏，轮流操作，每一回合可以选择以下操作中的一个
1.选择一个数，将其染成蓝色
2.选择一些蓝色的数，将其任意排列
3，什么都不做
若最后整个排列为升序，则先手获胜，若最后整个排列为降序，则后手获胜。如果两个人一直打下去则平局
两人都以最优策略玩游戏，问给定序列谁胜或平局


对于先手，如果 a[i]=i 则先手不需要花费一次操作来染色。（因为已经在先手想要的位置上了
同理，对于后手，a[i]=n-i+1 则后手也不需要花费。

注意存在 a[i]==i==n-i+1 的情况。

for (int i = 1; i <= n; i++) {
    cin >> a[i];
    if (a[i] == i && a[i] == n - i + 1)
        first++, second++;
    else if (a[i] == i)
        first++;
    else if (a[i] == n - i + 1)
        second++;
    else
        other++;
}
先手想要获胜，必须要对second和other染色。
后手想要获胜，必须要对first和other染色。

如果 second + other <= first  那么先手在完成了染色目标后，后手还没染完，先手获胜。
如果 first + other < second  后手获胜
但是注意，这里没有等号，因为如果相等的话，后手染色完，下一轮到先手，先手就重新排序了。

否则的话，二者就会僵持下去，两个人会剩下一个地方没有染色，但是谁都不敢染，因为染色了，对手就会排序。

*/
#include <bits/stdc++.h>

using namespace std;

const int N=5e5+10;

int a[N],n,t;

int main()
{
    cin >> t;
    while(t--)
    {
        cin >> n;
        for(int i=1;i<=n;i++) scanf("%d",a+i);

        int x1=0,x2=0,x=0;
        for(int i=1;i<=n;i++)
        {
            if(a[i]==i&&a[i]==n-i+1) x1++,x2++;
            else if(a[i]==i) x2++;
            else if(a[i]==n-i+1) x1++;
            else x++;
        } 

        if(x1+x<=x2) printf("First\n");
        else if(x2+x<x1) printf("Second\n");
        else printf("Tie\n");
    }

    return 0;
}