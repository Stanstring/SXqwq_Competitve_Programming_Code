#include<bits/stdc++.h>
using namespace std;
constexpr int N = 100000010;
int n,m,i,a,j,b;
int c[N];
int edge_tot,h[N],to[N],nxt[N];
int dfn_tot,dfn[20000005],low[200000005];
int stk[200000005],idx,col[200000005];
bool vis[200000005];
int bl_tot;
void add_edge(int x,int y){
	to[++edge_tot]=y;
	nxt[edge_tot]=h[x];
	h[x]=edge_tot;
}
void tarjan(int x){
	dfn[x]=low[x]=++dfn_tot;
	stk[++idx]=x;
	vis[x]=1; 
    for(int i=h[x];i;i=nxt[i]){
        int y=to[i];
        if(!dfn[y]){
            tarjan(y);
            low[x]=min(low[x],low[y]);
        }
        else if(vis[y]) low[x]=min(low[x],dfn[y]);
    }
    if(dfn[x]==low[x]){
        bl_tot++;
        while(stk[idx]!=x){
            col[stk[idx]]=bl_tot;
            vis[stk[idx]]=0;
            --idx;
        }
        col[stk[idx]]=bl_tot;
        vis[stk[idx]]=0;
        --idx;
    }
}
int main(){
	scanf("%d%d",&n,&m);
	while(m--){
		scanf("%d%d%d%d",&i,&a,&j,&b);
        if(a==0&&b==0){
            add_edge(i+n,j);
            add_edge(j+n,i);
        }
        if(a==0&&b==1){
            add_edge(i+n,j+n); 
            add_edge(j,i);
        }
        if(a==1&&b==0){
            add_edge(i,j); 
            add_edge(j+n,i+n); 
        }
        if(a==1&&b==1){
            add_edge(i,j+n); 
            add_edge(j,i+n); 
        }
	}
	for(int i=1;i<=2*n;i++)
		if(!dfn[i]) tarjan(i);
	for(int i=1;i<=n;i++)
		if(col[i]==col[i+n]){
			printf("IMPOSSIBLE");
			return 0;
		}
	printf("POSSIBLE\n");
	for(int i=1;i<=n;i++)
		printf("%d",col[i]>col[i+n]),putchar(' ');
	return 0;
}
