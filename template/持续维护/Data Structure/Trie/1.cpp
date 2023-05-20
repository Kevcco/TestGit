
#include <iostream>

using namespace std;

const int N=1e5+10;

int trie[N][26],cnt[N],n,idx;

char s[N];

void insert()
{
    int p=0;
    for(int i=0;s[i];i++)
    {
        int t=s[i]-'a';
        if(!trie[p][t]) trie[p][t]=++idx;
        p=trie[p][t];
    }
    cnt[p]++;
}

int find()
{
    int p=0;
    for(int i=0;s[i];i++)
    {
        int t=s[i]-'a';
        if(!trie[p][t]) return 0;
        p=trie[p][t];
    }
    
    return cnt[p];
}

int main()
{
    cin >> n;
    while(n--)
    {
        char str[2];
        scanf("%s%s",str,s);
        if(str[0]=='I') insert();
        else printf("%d\n",find());
    }
    return 0;
}