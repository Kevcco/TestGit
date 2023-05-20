#include <bits/stdc++.h>

using namespace std;

int n;

void todo(){}

void solve()
{
    // 枚举 i 的所有非空子集    O(3^n)
    for(int i = 1; i < 1<<n; i++)
        for(int j = i; j; j = (j-1)&i)
            todo();

    // 枚举 i 的所有超集    O(3^n)
    for(int  i = 1; i < 1<<n; i++)
        for(int j = i; j < 1<<n ; j = (j+1)|i)    
            todo();
}
