#include <bits/stdc++.h>
using namespace std;
const int maxn=1e5+10,mod=1e9+7;
typedef long long ll;
int n,m,k,t;
int cmp,cas;
int pa[maxn];
struct KDnode
{
    ll x[2];
    int id;
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
bool xylt(KDnode x,KDnode y)
{
    for(int i=0;i<m;i++)
    {
        if(x.x[i]==y.x[i])continue;
        return x.x[i]<y.x[i];
    }
    return true;
}
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
        if(((int)pq.size()<k || pq.top().first>distance || (pq.top().first == distance && xylt(p[mid],pq.top().second))) && qu.id != p[mid].id)
        {
            if((int)pq.size()==k)pq.pop();
            pq.push(make_pair(distance,p[mid]));
            dis = pq.top().first;
        }
        if((int)pq.size()<k || dis>=off*off)
        {
            if(off<=0)dfs(mid+1,r,d+1);
            else dfs(l,mid-1,d+1);
        }
    }
};
int find(int x){return pa[x]==x?x:pa[x]=find(pa[x]);}
int main()
{
    int i,j;
    //freopen("in.txt","r",stdin);
    scanf("%d",&t);
    while(t--)
    {
        int q;
        scanf("%d%d",&n,&q);
        //dims = 2
        m=2;
        for(i=1;i<=n;i++)
        {
            for(j=0;j<2;j++)
            {
                scanf("%lld",&p[i].x[j]);
            }
            p[i].id=i;
            pa[i]=i;
        }
        KDT kdt = KDT(m);
        kdt.build(1,n,0);
        //nearest neighbour
        k=1;
        for(i=1;i<=n;i++)
        {
            qu = p[i];
            kdt.dfs(1,n,0);
            pa[find(qu.id)]=find(kdt.pq.top().second.id);
            kdt.pq.pop();
        }
        printf("Case #%d:\n",++cas);
        while(q--)
        {
            int x,y;
            scanf("%d%d",&x,&y);
            puts(find(x)==find(y)?"YES":"NO");
        }
    }
    return 0;
}
