/*
必须是 单峰 且 峰两边严格单增/减 的函数才可以三分
    while(l+2<r)
    {
        int m1=l+(r-l)/3,m2=l+(r-l)/3*2;
        if(f(m1)>f(m2)) l=m1;
        else r=m2;
    }
    ll res=1e18;
    fr(int i=l;i<=r;i++) res=min(res,f(i));

*/