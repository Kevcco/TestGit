
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int mod=1e9+7,N=2e5+10;

int n;
char s[N*2];

void getmin()
{
    for(int i=1;i<=n;i++) s[i+n]=s[i];
    int i=1,j=2;
    while(j<=n)
    {
        int k=0;
        while(k<n&&s[i+k]==s[j+k]) k++;
        if(s[i+k]>s[j+k]) i+=k+1;
        else j+=k+1;
        if(i==j) j++;
        if(i>j) swap(i,j);
    }

    for(int l=i;l<=i+n-1;l++) printf("%c",s[l]);
}