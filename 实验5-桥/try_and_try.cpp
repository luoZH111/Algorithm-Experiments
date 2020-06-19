void solve()
{
	num=0;//连通块数 
	set vis[i] to 0;
	for(i=0 to n-1)
		if(i未访问过) dfs(i),num++; 
	for(u=0 to n-1){
		for(edge of u:){
			v=cur_edge.v;
			if(v已访问) continue;
			set cur_edge.dele to true;
			if(!ok()){
				该边为割边，桥数+1； 
			}
			set cur_edge.dele to false;
		} 
	} 
	输出桥数 
	for(){
		输出所有的桥 
	}
}
bool ok()//返回true，说明连通分量数不变 
{
	cur=0;
	set vis[i] to 0;
	for(i=0 to n-1)
		if(i未访问过) dfs(i),cur++;
	if(cur==num)
		return true;
	return false;
}
void dfs(int u)
{
	标记u为 已访问 
	for(edge of u:){
		v=edge.v;
		if(v已访问) continue;
		dfs(v);
	} 
}
void init()
{
	for(int i=0;i<n;i++){
		f[i]=i;
		h[i]=1;
	}
} 
int find1(int x)
{
	return x==f[x]?x:find1(f[x]);
}
int find1(int x)
{
	return x==f[x]?x:f[x]=find1(f[x]);
}
bool union1(int x,int y)
{
	int fx=find1(x),fy=find1(y);
	if(fx!=fy){
		f[fx]=fy;
		return true;
	}
	return false;
}

bool union1(int x,int y)
{
	int fx=find1(x),fy=find1(y);
	if(fx!=fy){
		if(h[fx]>h[fy]) swap(fx,fy);
		f[fx]=fy;//将秩小的合并到秩大的 
		h[fy]++;
		return true;
	}
	return false;
}
void solve()
{
	num=0;//连通块数 
	set vis[i] to 0;
	for(i=0 to n-1)
		if(i未访问过) dfs(i),num++; 
	for(u=0 to n-1){
		for(edge of u:){
			v=cur_edge.v;
			if(v已访问) continue;
			if(find1(u)==find1(v)) continue;
			set cur_edge.dele to true;
			if(!ok()){
				该边为割边，桥数+1； 
			}
			set cur_edge.dele to false;
			union1(u,v);
		} 
	} 
	输出桥数 
	for(){
		输出所有的桥 
	}
}
//暴力并查集优化II
void solve()
{
	for(u=0 to n-1){
		for(edge of u:){
			v=cur_edge.v;
			if(union1(u,v))
				set cur_edge.flag to true;
		} 
	} 
	num=0;//连通块数 
	set vis[i] to 0;
	for(i=0 to n-1)
		if(i未访问过) dfs(i),num++; 
	for(u=0 to n-1){
		for(edge of u:){
			v=cur_edge.v;
			if(cur_edge.flag==false) continue;
			if(v已访问) continue;
			set cur_edge.dele to true;
			if(!ok()){
				该边为割边，桥数+1； 
			}
			set cur_edge.dele to false;
		} 
	} 
	输出桥数 
	for(){
		输出所有的桥 
	}
} 

//lca
int rmq(int l,int r)//时间复杂度O(1) 
{
	int m=floor(log((double)(r-l+1))/log(2.0));
	//return min2(mn[l][m],mn[r-(1<<m)+1][m]);
	return min(mn[l][m],mn[r-(1<<m)+1][m]);
}
int lca(int u,int v)//时间复杂度O(1) 
{
	if(p2[u]>p2[v])
		swap(u,v);
	int k=rmq(p2[u],p2[v]);
	return f3[k];
}
void lca_init()
{
	
}
for(int i=0;i<n;i++)
		if(find2(i)==i) dfs(i,i),ve.push_back(i);
	//for(int i=0;i<n;i++) if(p[i]!=i) printf("p[%d]:%d\n",i,p[i]);
	init_mn(cnt);

//树上差分
void dfs2(int u)
{
	vis[u]=1;
	set vis[u] to true;
	for(edge of u:){
		v=cur_edge.v;
		if(vis[v]) continue;
		dfs2(v);
		cf[u]+=cf[v];
	} 
}
void solve()
{
	set cf[i] to 0;//树上点权 
	for(i:edge_num){
		u=cur_edge.u;
		v=cur_edge.v;
		if(union2(u,v)){//建生成树 
			addedge(u,v);
			addedge(v,u);
		}else{
			edge_no_ontree.push(u,v);//存储非树边 
		} 
	} 
	lca_init();
	for(i:edge_no_ontree){//树上差分 
		u=cur_edge.u;
		v=cur_edge.v;
		cf[u]++;
		cf[v]++;
		cf[lca(u,v)]-=2;
	}
	for(i=0 to n-1)//求解cf[i] 
		if(find1(i)==i) dfs2(i);
	
	for(i=0 to n-1){
		if(p[i]==i) continue;//树的根结点 
		if(!cf[i]){
			该边为割边，桥数+1；
		}
	}
	输出桥数 
	for(){
		输出所有的桥 
	}
} 
//并查集 树上缩点

void dfs(int u,int fa,int d)
{
	
	p[u]=fa;deep[u]=d;
	for(i:edge linked to u){
		v=cur_edge.v;
		if(v==fa) continue;
		dfs(v,u,d+1);
	} 
}
void dfs2(int u,int fa)
{
	for(i:edge linked to u){
		v=cur_edge.v;
		if(v==fa) continue;
		if(find1(v)!=find1(u)){
			该边为割边，桥数+1；
		}
		dfs2(v,u);
	} 
}
void solve()
{
	int u,v;
	for(i:edge_num){
		u=cur_edge.u;
		v=cur_edge.v;
		if(union2(u,v)){//建生成树 
			addedge(u,v);
			addedge(v,u);
		}else{
			edge_no_ontree.push(u,v);//存储非树边 
		} 
	} 
	
	for(i=0 to n-1)//求每个结点在树上的深度，以及其树上的父结点 
		if(find2(i)==i) dfs(i,i,1);//dfs求每个结点深度，父结点 
	for(i:edge_no_ontree){
		u=cur_edge.u;
		v=cur_edge.v;
		while(find1(u)!=find1(v)){
			if(deep[u]<deep[v])//深度大的先和其父结点合并 
				swap(u,v);
			union1(u,p[u]);//p[u]为u树上父结点 
			u=find1(u);//u更新为其所在连通块根结点 
		}
	}
	for(i=0 to n-1)//求所有桥 
		if(find2(i)==i) df2(i,i);
	
	输出桥数 
	for(){
		输出所有的桥 
	}
} 
