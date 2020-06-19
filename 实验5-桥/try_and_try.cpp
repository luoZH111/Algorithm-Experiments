void solve()
{
	num=0;//��ͨ���� 
	set vis[i] to 0;
	for(i=0 to n-1)
		if(iδ���ʹ�) dfs(i),num++; 
	for(u=0 to n-1){
		for(edge of u:){
			v=cur_edge.v;
			if(v�ѷ���) continue;
			set cur_edge.dele to true;
			if(!ok()){
				�ñ�Ϊ��ߣ�����+1�� 
			}
			set cur_edge.dele to false;
		} 
	} 
	������� 
	for(){
		������е��� 
	}
}
bool ok()//����true��˵����ͨ���������� 
{
	cur=0;
	set vis[i] to 0;
	for(i=0 to n-1)
		if(iδ���ʹ�) dfs(i),cur++;
	if(cur==num)
		return true;
	return false;
}
void dfs(int u)
{
	���uΪ �ѷ��� 
	for(edge of u:){
		v=edge.v;
		if(v�ѷ���) continue;
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
		f[fx]=fy;//����С�ĺϲ����ȴ�� 
		h[fy]++;
		return true;
	}
	return false;
}
void solve()
{
	num=0;//��ͨ���� 
	set vis[i] to 0;
	for(i=0 to n-1)
		if(iδ���ʹ�) dfs(i),num++; 
	for(u=0 to n-1){
		for(edge of u:){
			v=cur_edge.v;
			if(v�ѷ���) continue;
			if(find1(u)==find1(v)) continue;
			set cur_edge.dele to true;
			if(!ok()){
				�ñ�Ϊ��ߣ�����+1�� 
			}
			set cur_edge.dele to false;
			union1(u,v);
		} 
	} 
	������� 
	for(){
		������е��� 
	}
}
//�������鼯�Ż�II
void solve()
{
	for(u=0 to n-1){
		for(edge of u:){
			v=cur_edge.v;
			if(union1(u,v))
				set cur_edge.flag to true;
		} 
	} 
	num=0;//��ͨ���� 
	set vis[i] to 0;
	for(i=0 to n-1)
		if(iδ���ʹ�) dfs(i),num++; 
	for(u=0 to n-1){
		for(edge of u:){
			v=cur_edge.v;
			if(cur_edge.flag==false) continue;
			if(v�ѷ���) continue;
			set cur_edge.dele to true;
			if(!ok()){
				�ñ�Ϊ��ߣ�����+1�� 
			}
			set cur_edge.dele to false;
		} 
	} 
	������� 
	for(){
		������е��� 
	}
} 

//lca
int rmq(int l,int r)//ʱ�临�Ӷ�O(1) 
{
	int m=floor(log((double)(r-l+1))/log(2.0));
	//return min2(mn[l][m],mn[r-(1<<m)+1][m]);
	return min(mn[l][m],mn[r-(1<<m)+1][m]);
}
int lca(int u,int v)//ʱ�临�Ӷ�O(1) 
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

//���ϲ��
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
	set cf[i] to 0;//���ϵ�Ȩ 
	for(i:edge_num){
		u=cur_edge.u;
		v=cur_edge.v;
		if(union2(u,v)){//�������� 
			addedge(u,v);
			addedge(v,u);
		}else{
			edge_no_ontree.push(u,v);//�洢������ 
		} 
	} 
	lca_init();
	for(i:edge_no_ontree){//���ϲ�� 
		u=cur_edge.u;
		v=cur_edge.v;
		cf[u]++;
		cf[v]++;
		cf[lca(u,v)]-=2;
	}
	for(i=0 to n-1)//���cf[i] 
		if(find1(i)==i) dfs2(i);
	
	for(i=0 to n-1){
		if(p[i]==i) continue;//���ĸ���� 
		if(!cf[i]){
			�ñ�Ϊ��ߣ�����+1��
		}
	}
	������� 
	for(){
		������е��� 
	}
} 
//���鼯 ��������

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
			�ñ�Ϊ��ߣ�����+1��
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
		if(union2(u,v)){//�������� 
			addedge(u,v);
			addedge(v,u);
		}else{
			edge_no_ontree.push(u,v);//�洢������ 
		} 
	} 
	
	for(i=0 to n-1)//��ÿ����������ϵ���ȣ��Լ������ϵĸ���� 
		if(find2(i)==i) dfs(i,i,1);//dfs��ÿ�������ȣ������ 
	for(i:edge_no_ontree){
		u=cur_edge.u;
		v=cur_edge.v;
		while(find1(u)!=find1(v)){
			if(deep[u]<deep[v])//��ȴ���Ⱥ��丸���ϲ� 
				swap(u,v);
			union1(u,p[u]);//p[u]Ϊu���ϸ���� 
			u=find1(u);//u����Ϊ��������ͨ������ 
		}
	}
	for(i=0 to n-1)//�������� 
		if(find2(i)==i) df2(i,i);
	
	������� 
	for(){
		������е��� 
	}
} 
