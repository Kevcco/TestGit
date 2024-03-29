/*
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