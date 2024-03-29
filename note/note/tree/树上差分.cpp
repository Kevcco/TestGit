/*
当想修改整个子树的信息时，那么就维护一个点到根节点的路径信息和
修改子树信息就变成了单点修改这个子树的根节点的信息，因为这棵子树的任意节点到根的路径一定经过这个子树的根
查询原节点的值相当于查询当前节点和父亲节点的差值
也可拉dfs序 修改子树相当于修改区间 转化成差分数组维护


1.维护树上差分数组 ： 真正的节点值是整棵子树的差分数组值之和
当想修改一条路径上的所有信息时，那么就维护树上差分，即真正的节点值是整棵子树的值之和
(1)修改路径上的所有点：变成修改单点的信息，修改一点，那么这一点到根的路径上的所有点的真实值都会修改
(2)求单点点权 ： 子树和
(3)求子树和 ： 推公式 与点的深度有关
具体来说:
(1) 点差分 ：修改 u -> v 的路径上的所有点  --> 修改 u -> lca 和 v -> lca的下面一个节点 两条链
            也就是 d[u]++,d[v]++,d[lca.father]--,d[lca]--;
(2) 边差分 ： 定义某一点代表这个点到其父亲节点的边 那么修改 u -> v 路径上的所有边
            也就是 d[u]++,d[v]--,d[lca]-=2;
最后dfs一遍求所有点的点权
如果要边修改边询问 ： 维护dfs序的树状数组
(1) 求单点的值 ： 求[l[u],r[u]] 的区间和
(2) 求子树和 ： 维护两个树状数组，另一个维护 depth[u]*d[u] 的值
                那么u的子树和就是 sum2(l[u],r[u]) - (depth[u]-1) * sum1(l[u],r[u]);
                
2.维护点到根的路径和的dfs序列差分 ：dfs序 每个点的值代表点到根的路径上所有点权和 然后再对这个序列差分
(1)单点修改 ： 变成子树修改，也就是原数组区间修改 ，也就是差分数组的单点修改
(2)子树修改 ： 推公式
(3)求两点之间路径的点权和 ： 转化成求原数组的两条链的点权和 ，转化成单点值，转化成差分数组的前缀和
(4)求单点 ： 等于求链
*/