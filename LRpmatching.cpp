#include<iostream>
#include<bits/stdc++.h>
using namespace std;

vector< pair <float,pair <int,int> > > mainset(vector< pair <float,pair <int,int> > > G,int r)		//Greedy algorithm
{
	vector< pair <float,pair <int,int> > > ans;
	vector<int> trac(r+1,0);
	sort(G.begin(),G.end());
	for(int i=0;i<G.size();i++)
	{
		if(trac[G[i].second.first]==0)
		{
			ans.push_back({G[i].first,G[i].second});
			trac[G[i].second.first]=1;
		}
	}
	return ans;
}

vector< pair <float,pair <int,int> > > perfect_M(vector< pair <float,pair <int,int> > > G,int r)
{
	//Declare the variables
	vector< pair <float,pair <int,int> > > LS;		
	vector< pair <float,pair <int,int> > > RS;
	vector< pair <float,pair <int,int> > > S1;
	vector< pair <float,pair <int,int> > > S2;
	int i,max=-1;
	int a=0,f,f1;
	float epsilon;
	//find the W
	for(i=0;i<G.size();i++)
	{
		if(max<G[i].first)
		{
			max=G[i].first;
		}
	}
	
	epsilon=2*max;
	
	for(i=0;i<G.size();i++)
	{
		LS.push_back({max,{G[i].second.first,G[i].second.second}});
		RS.push_back({G[i].first-max,{G[i].second.second,G[i].second.first}});
	}
		

	
/*_____outer loop start ____________________________*/	
int outer=1;
	while(epsilon>=float(1)/r)
	{	
		for(i=0;i<G.size();i++)
		{
			RS[i].first=G[i].first-LS[i].first;
	    }
	   
	 //    	for(i=0;i<G.size();i++)
		// {
		// 	cout<<"("<<LS[i].first<<"("<<U[i].second.first<<U[i].second.second<<")"<<","<<V[i].first<<"("<<V[i].second.second<<V[i].second.first<<")"<<")  ";
	 //    }
	 //    cout<<endl;
		epsilon/=2;
		S1= mainset(LS,r);
		S2= mainset(RS,r);
		//
	cout<<endl<<"epsilon"<<epsilon<<endl;
		int b_reak=0;
		int iner=0;
		int L,R;
		float lrweight;
		do{
			f1=0;
		
		/*---*/
		iner++;
		cout<<endl<<"iner:"<<iner<<endl;
		//printing B1 and B2
		// for(i=0;i<S1.size();i++)
		// cout<<"("<<S1[i].first<<"("<<S1[i].second.first<<","<<S1[i].second.second<<") )";
		// cout<<endl;
		// for(i=0;i<S2.size();i++)
		// cout<<"("<<S2[i].first<<"("<<S2[i].second.first<<","<<S2[i].second.second<<") )";
		// cout<<endl;	
		
	/*   	*/
	// finding e belongs to {B1-B2}
			for(i=0;i<S1.size();i++)
			{
				int f=0;
				for(int j=0;j<S2.size();j++)
				{
					if(S1[i].second.first==S2[j].second.second&&S1[i].second.second==S2[j].second.first)
					{
						f=1;
						break;
					}
				
				}
				if(!f)
				{
					L=S1[i].second.first;
					R=S1[i].second.second;
					lrweight=S1[i].first;      			//new line added
					f1=1;
					break;
				}
			}
			// break if edge does not exist
			if(!f1)
			break;
			int ui,vi,wi;
			
			for(ui=0;ui<LS.size();ui++)									//finding edge in U Matroid
		  		{
		  			if(L==LS[ui].second.first&&R==LS[ui].second.second)
		  			break;
				}
			for(vi=0;vi<RS.size();vi++)
		  		{
		  			if(R==RS[vi].second.first&&L==RS[vi].second.second)
		  			break;
				}
				  
				  
			for(wi=0;wi<G.size();wi++)
		  		{
		  			if(L==G[wi].second.first&&R==G[wi].second.second)
		  			break;
				}
			  
/*________________________________________________________________*/
			if(LS[ui].first+RS[vi].first==G[wi].first)
			{
				LS[ui].first+=epsilon;
				cout<<endl<<endl<<"{"<<LS[ui].first<<","<<LS[ui].second.first<<"->"<<LS[ui].second.second<<"}"<<endl<<endl;
				int v1,v2;
				v1=LS[ui].second.first;
				v2=LS[ui].second.second;
				float tem=LS[ui].first;
				int uf=0;
				for(int c=0;c<LS.size();c++)
				{
					if(LS[c].first<tem&&LS[c].second.first==v1)
					{
						uf=1;
						v1=LS[c].second.first;
						v2=LS[c].second.second;
						tem=LS[c].first;
				
					}
				}
				if(uf)
				{
				
				S1[i].first=tem;
				S1[i].second.first=v1;
				S1[i].second.second=v2;
			}
			}
	    	else
			{
				RS[vi].first-=epsilon;
				for(int d=0;d<S2.size();d++)
				{
					if(S2[d].second.first==R&&S2[d].first>RS[vi].first)
					{
						S2[d].first=RS[vi].first;
						S2[d].second.first=R;
						S2[d].second.second=L;
						//break;
				
					}
				}
				
			}
			cout<<endl;
		cout<<"("<<L<<", "<<R<< ")"<<"	";
		cout<<endl;
	
	
		}while(f1);		  
		cout<<"outer :"<<outer++<<"("<<iner<<")"<<endl;	

	}
	/* ________________ outer loop end __________________*/
	
	cout<<endl<<"B1:"<<endl;
	for(i=0;i<S1.size();i++)
		cout<<S1[i].first<<",("<<S1[i].second.first<<","<<S1[i].second.second<<") ";
		cout<<endl;
		
		cout<<endl<<"UV"<<":"<<endl;
		for(i=0;i<G.size();i++)
	cout<<"("<<LS[i].first<<")"<<"("<<LS[i].second.first<<","<<LS[i].second.second<<") ";
		cout<<endl;
		for(i=0;i<G.size();i++)
		cout<<"("<<RS[i].first<<")"<<"("<<RS[i].second.first<<","<<RS[i].second.second<<") ";
		cout<<endl<<endl;
		cout<<endl<<"B1"<<endl;
		for(i=0;i<S1.size();i++)
		cout<<S1[i].second.first<<"->"<<S1[i].second.second<<" "<<S1[i].first<<endl;

	
return S2;	
	
}
int main()
{
	int n,v1,v2,w,i,e;
	vector< pair <float,pair <int,int> > > graph;
	cout<<"Enter number of vertices";
	cin>>n;
	cout<<"Enter number of edges";
	cin>>e;
	cout<<"Enter edge and weight";
	for( i=0;i<e;i++)
	{
		cin>>v1>>v2>>w;
		graph.push_back({w,{v1,v2}});
	}
/*	for(i=0;i<n;i++)
		cout<<graph[i].second.first <<"-> "<<graph[i].second.second<<" "<<graph[i].first<<endl;*/
		
	vector< pair <float,pair <int,int> > > ans=perfect_M(graph,n);
	cout<<endl<<"B:  ";
		for(i=0;i<ans.size();i++)
		cout<<ans[i].second.second<<"->"<<ans[i].second.first<<" "<<ans[i].first<<endl;
}




/*
3 
3
1 3 5
1 2 10
2 3 15
*/

/*
3 
7
1 1 1
1 2 3
2 1 4
2 2 5
2 3 6
3 2 8
3 3 7
*/
/*
3
5
1 1 2
2 2 3
3 3 4
2 3 6
3 2 8
*/
