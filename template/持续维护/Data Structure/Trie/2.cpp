
#include <bits/stdc++.h>

using namespace std;

const int N=6e5+10;

int n,m,trie[N*25][2],idx,cnt[N*25],root[N];
int s[N];

void insert(int num,int p,int q)
{
    for(int i=24;i>=0;i--)
    {
        if(p) trie[q][0]=trie[p][0],trie[q][1]=trie[p][1];
        int t=num>>i&1;
        trie[q][t]=++idx;
        p=trie[p][t],q=trie[q][t];
        cnt[q]=cnt[p]+1;
    }
}

int query(int num,int p,int q)
{
    int res=0;
    for(int i=24;i>=0;i--)
    {
        int t=num>>i&1;
        if(cnt[trie[q][t^1]]-cnt[trie[p][t^1]])
            res+=1<<i,t^=1;
        p=trie[p][t];
        q=trie[q][t];
    }
    
    return res;
}

int main()
{
    cin >> n >> m;
    root[0]=++idx,root[1]=++idx;
    insert(0,root[0],root[1]);
    for(int i=1;i<=n;i++)
    {
        int x;
        scanf("%d",&x);
        s[i]=s[i-1]^x;
        root[i+1]=++idx;
        insert(s[i],root[i],root[i+1]);
    }
    
    while(m--)
    {
        char str[2];
        scanf("%s",str);
        if(*str=='A')
        {
            int x;
            scanf("%d",&x);
            n++;
            s[n]=s[n-1]^x;
            root[n+1]=++idx;
            insert(s[n],root[n],root[n+1]);
        }
        else
        {
            int l,r,x;
            scanf("%d%d%d",&l,&r,&x);
            printf("%d\n",query(x^s[n],root[l-1],root[r]));
        }
    }
}