#include <bits/stdc++.h>
using namespace std;
const int maxn=1e5+10,mod=1e9+7;
typedef long long ll;
int n,m,k,t;
int cmp;
struct KDnode
{
    int x[5];
    bool operator<(const KDnode&p)const
    {
        return x[cmp]<p.x[cmp];
    }
    ll dis(KDnode y)
    {
        ll ret=0;
        for(int i=0;i<m;i++)
            ret+=(y.x[i]-x[i])*(y.x[i]-x[i]);
        return ret;
    }
}p[maxn],qu;
struct KDT
{
    int dims;
    ll dis;
    priority_queue<pair<ll,KDnode> >pq;
    KDT(int dims){this->dims = dims;}
    void build(int l,int r,int d)
    {
        if(l>=r)return;
        cmp = d % dims;
        int mid=l+r>>1;
        nth_element(p+l,p+mid,p+r+1);
        build(l,mid-1,d+1);
        build(mid+1,r,d+1);
    }
    void dfs(int l,int r,int d)
    {
        if(l>r)return;
        cmp = d % dims;
        int mid=l+r>>1;
        ll distance = qu.dis(p[mid]);
        ll off = qu.x[cmp] - p[mid].x[cmp];
        if(off<=0)dfs(l,mid-1,d+1);
        else dfs(mid+1,r,d+1);
        if((int)pq.size()<k || pq.top().first>distance)
        {
            pq.push(make_pair(distance,p[mid]));
            if((int)pq.size()>k)pq.pop();
            dis = pq.top().first;
        }
        if((int)pq.size()<k || dis>off*off)
        {
            if(off<=0)dfs(mid+1,r,d+1);
            else dfs(l,mid-1,d+1);
        }
    }
};
int main()
{
    int i,j;
    //freopen("in.txt","r",stdin);
    while(~scanf("%d%d",&n,&m))
    {
        for(i=1;i<=n;i++)
        {
            for(j=0;j<m;j++)
            {
                scanf("%d",&p[i].x[j]);
            }
        }
        KDT kdt = KDT(m);
        kdt.build(1,n,0);
        int q;
        scanf("%d",&q);
        while(q--)
        {
            for(i=0;i<m;i++)scanf("%d",&qu.x[i]);
            scanf("%d",&k);
            kdt.dfs(1,n,0);
            printf("the closest %d points are:\n",k);
            stack<KDnode>stk;
            while(!kdt.pq.empty())
                stk.push(kdt.pq.top().second),kdt.pq.pop();
            while(!stk.empty())
            {
                KDnode now = stk.top();
                stk.pop();
                for(i=0;i<m;i++)
                {
                    printf("%d%c",now.x[i]," \n"[i==m-1]);
                }
            }
        }
    }
    return 0;
}
