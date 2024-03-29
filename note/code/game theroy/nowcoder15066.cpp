/*
共有n堆石子，已知每堆石子的数量xi，两个人轮流取石子，每次只能选择N堆石子中的一堆取一定数量的石子（最少取一个），
取过子之后，还可以将该堆石子中剩余的石子随意选取几个放到其它的任意一堆或几堆上。
等哪个人无法取子时就表示此人输掉了游戏
判断出先手能否获胜。


首先构造一点小数据看一看
如果只有一堆石子，那么一定是N态，因为先手可以直接取走一堆
如果有两堆石子，且数量相同，那么是P态，每次一个人操作完石子，另一个人可以对称着做，那么两堆石子又相同了
最终两堆石子变成0是P态，因此初始一定是P态
如果两堆石子数量不同 x1 > x2 > 0 那么一定是N态，因为可以操作一次将 x1 减少成 x2，变成 P 态
如果是三堆石子 x1 >= x2 >= x3 那么可以操作成 x2 x2 ，是 P 态，故是N态

结论(1)：如果是偶数堆，且两两配对 那么是P态
证明:一个人操作石子xi，另一个人可以相同操作和 xi配对的石子xj,仍然变成两两配对的状态 最终变成全0的P态

结论(2)：如果是偶数堆，且不是两两配对，那么是N态
证明:假设 x1 >= x2 >= x3 >= ... >= xn 且=不同时取到 那么一定能用 xn操作成 
     x2, x2, x4, x4, x6, x6, ..., xn-2, xn-2, xn, xn
    也就是有 x1 - xn > x2 - x3 + x4 - x5 + x6 -x7 +... + xn-2 -xn-1 即可操作成功
    即证 x1 > x2 - (x3 - x4) - (x5 - x6) - ... - (xn-1 - xn)   由于 = 不会同时取到 故不等式等式成立

结论(3)如果是奇数堆，那么一定是 N态
证明:假设 x1 >= x2 >= x3 >= ... >= xn > 0，如果能操作成 x2, x2, x4, x4, ... ,xn-1, xn-1,
     那么由于两两配对是 P态，故一定是 N态，下证操作x1一定可以变成配对的状态
     即证 x1 > x2 - x3 + x4 -x5 + ... + xn-1 -xn
     即   x1 > x2 - (x3 - x4) - (x5 - x6) - ... - (xn-2 - xn-1) - xn
     由于x1 >= x2 且 xi - xi-1 <= 0 ,xn < 0 ,故不等式成立 得证

*/