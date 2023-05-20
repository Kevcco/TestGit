
#include <iostream>

using namespace std;

const int N=50001;

int p[N*3],n,k,res;

int find(int k)
{
    if(p[k]!=k) p[k]=find(p[k]);
    return p[k];
}

void uni(int a,int b)
{
    p[find(a)]=find(b);
}

void check()
{
    int d,x,y;
    cin >> d >> x >> y;
    
    if(x>n||y>n)
    {
        res++;
        return;
    }

    if(d==1)
    {
        if(find(x)==find(y+n)||find(x+n)==find(y)) res++;
        else
        {
            uni(x,y);
            uni(x+n,y+n);
            uni(x+2*n,y+2*n);
        }
    }
    else
    {
        if(x==y||find(x)==find(y)||find(y)==find(x+n)) res++;
        else
        {
            uni(x,y+n);
            uni(x+n,y+2*n);
            uni(x+2*n,y);
        }
    }
}

int main()
{
    cin >> n >> k;
    for(int i=1;i<3*n;i++)p[i]=i;
    
    while(k--) check();

    cout << res;    
    return 0;
}