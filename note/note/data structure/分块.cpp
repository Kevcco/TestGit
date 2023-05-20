/*

1.要求维护一堆数  (1) O(根号n) 插入一个数 ai (ai <= n)   (2) O(1) 查询小于 ai 的数的个数
    值域分块 + 前缀和  tag[i] 表示前 i-1 块内的数的个数 cnt[i] 表示i所在的块内 <i 的数的个数
    （如果查询大于就是后缀和)
    insert(x) {
        for(int i = x/len+1; i <= limit; i++) tag[i]++;
        in right = x.len*len+len-1;
        for(int i = x; i <= right; i++) cnt[i]++;
    }
    query(x) {
        return tag[x/len] + st[x]
    }


    
*/