#include <bits/stdc++.h>
using namespace std;
#define DARTH11 ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL)

#ifndef Darthrider212
#define debug(x) cerr << #x<<" "; _print(x); cerr << endl;
#else
#define debug(x);
#endif
#define nline "\n"


class SegTree{
	vector<int> seg;
public:
	SegTree(int n){
		seg.resize(4*n+1);
	}
	void build(int index,int low ,int high,int arr[]){
		if(low==high){seg[index]=arr[low];return;}
		int mid=(low+high)>>1;
		build(2*index+1,low,mid,arr);
		build(2*index+2,mid+1,high,arr);
		seg[index]=min(seg[2*index+1],seg[2*index+2]);
	}
	void update(int index,int low,int high,int i,int val){
		if(low==high){
			seg[index]=val;
			return;
		}
		int mid=(low+high)>>1;
		if(i<=mid)update(2*index+1,low,mid,i,val);
		else update(2*index+2,mid+1,high,i,val);
		seg[index]=min(seg[2*index+1],seg[2*index+2]);

	}
	int query(int index,int low,int high,int l,int r){
		// no overlap [low,high][l,r] or [l,r][low,high];
		if(high<l or r<low) return INT_MAX;
		//complete overlap [l low high r]
		if(low>=l and high<=r)return seg[index];

			int mid=(low+high)>>1;
			int left=query(2*index+1,low,mid,l,r);
			int right=query(2*index+2,mid+1,high,l,r);
			return min(left,right);
		}
};

int main(){
	    DARTH11;
#ifndef Darthrider212
    freopen("Error.txt", "w", stderr);
#endif

    int n,q; cin>>n>>q;
    int a[n];
    for(int i=0;i<n;i++)cin>>a[i];
    SegTree s1(n);
	s1.build(0,0,n-1,a);
	cout<<s1.query(0,0,n-1,0,2)<<nline;
	while(q--){
		int type;cin>>type;
		if(type==1){
			int low,high;cin>>low>>high;
			int x=s1.query(0,0,n-1,low,high);
			cout<< x<< nline;
		}else if(type==2){
			int i,val;cin>>i>>val;
			s1.update(0,0,n-1,i,val);
			a[i]=val;
		}

	}


	return 0;
}