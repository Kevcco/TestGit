/*
对于一个DAG,定义每个点的SG函数 SG(u) = mex { SG(v) | v属于 F(u) } F(u)为所有u指向的点之集

SG函数与 P/N 态的关系(正常游戏,不能移动的输):
SG(u) = 0  <=>  u 为 P态
SG(u) > 0  <=>  u 为 N态

组合游戏的和:多个组合游戏，玩家可以任选一个游戏，按其规则移动一次，如果所有游戏都不能移动，则玩家输
G = G1 + G2 + ... + Gn , 
V = V1 X V2 X ... X Vn ，V的邻接顶点为任选一个 Vi , 走到对应的Gi中Vi的邻接顶点，其他点不变

SG定理：设有n个组合游戏,则 SG(u1, u2, ..., un) = SG1(u1) ^ SG2(u2) ^ ... ^ SGn(un)
证明 : 即证(1)任意 A < SG(u) , 存在 v属于 F(u),使得 SG(v) = A   (2) 不存在 SG(v) = SG(u) 
(1) 找到 A ^ SG(u) 的最高位1，由于 A < SG(u) ,故最高位1一定是 SG(u) = 1,A = 0产生，故一定存在 SGi(ui) 这一位是1
    又 SGi(ui) ^ (A ^ SG(u)) < SGi(ui),故一定可以让 SGi(ui) 走到 SGi(ui) ^ A ^ SG(u)，
    故此时的 SG(v) = SG(u) ^ A ^ SG(u) = A ,故构造出合法解
(2) 假设存在 SG(v) = SG(u), 那么对应的 SGi(ui) = SGi(vi) ，按照SG函数的定义，这是不可能的，故不存在 

这样便可以将组合游戏的和拆成多个组合游戏分别计算,从而由乘法复杂度变成加法复杂度，以此来计算 SG(G)
如何得到最优策略 : 如上证明的构造方法，找 SG(v) = 0

*/