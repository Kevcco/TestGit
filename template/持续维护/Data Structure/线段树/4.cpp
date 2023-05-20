// 区间第k小
#include <bits/stdc++.h>

using namespace std;

const int N=1e5+10,INF=1e9+5;

int n,m,idx;
int root[N],a[N];

struct node
{
    int l,r;
    int cnt;
}tr[N*40];

void pushup(int u)
{
    tr[u].cnt=tr[tr[u].l].cnt+tr[tr[u].r].cnt;
}

void modify(int p,int q,int L,int R,int x)
{
    tr[q]=tr[p];
    if(L==R)
    {
        tr[q].cnt++;
        return;
    }
    
    int mid=L+R-1>>1;
    if(x>mid)
    {
        tr[q].r=++idx;
        modify(tr[p].r,tr[q].r,mid+1,R,x);
    }
    else
    {
        tr[q].l=++idx;
        modify(tr[p].l,tr[q].l,L,mid,x);
    }
    pushup(q);
}

int query(int p,int q,int L,int R,int k)
{
    if(L==R) return L;
    int mid=L+R-1>>1;
    int cnt=tr[tr[q].l].cnt-tr[tr[p].l].cnt;
    if(cnt>=k) return query(tr[p].l,tr[q].l,L,mid,k);
    else return query(tr[p].r,tr[q].r,mid+1,R,k-cnt);
    
}

int main()
{
    cin >> n >> m;
    root[0]=++idx;
    for(int i=1;i<=n;i++) scanf("%d",a+i);
    for(int i=1;i<=n;i++)
    {
        root[i]=++idx;
        modify(root[i-1],root[i],-INF,INF,a[i]);
    }
    
    while(m--)
    {
        int l,r,k;
        scanf("%d%d%d",&l,&r,&k);
        printf("%d\n",query(root[l-1],root[r],-INF,INF,k));
    }
}