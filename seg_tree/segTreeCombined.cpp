// ------Author---@Darthrider212------//
#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
#pragma GCC optimize("O3", "unroll-loops")
#pragma GCC target("avx2")
using namespace __gnu_pbds;
using namespace std;
#define DARTH11 ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL)

#ifndef Darthrider212
#define debug(x) cerr << #x<<" "; _print(x); cerr << endl;
#else
#define debug(x);
#endif
#define nline "\n"
typedef long long ll;


    class segTree{
    public:
        vector<ll> seg,lazy;
        ll n;
        segTree(ll _n){
            seg.clear();
            n=1;
            while(n<_n)n*=2;
            seg.assign(4*n+1,0);
            lazy.assign(4*n+1,0);
        }
        //range update i.e lazy propogation
        void update(ll index,ll low,ll high,ll L,ll R,ll val){
            // complete overlap [L low high R]
            if(low>=L and high<=R){
                lazy[index]+=val;
                if(low!=high){
                    lazy[2*index+1]+=lazy[index];
                    lazy[2*index+2]+=lazy[index];
                }
                seg[index]+=lazy[index];
                lazy[index]=0;
                return;
            }
            // no overlap [L R][low high] [L R]
            if(R< low or high<L){
                if(low!=high){
                    lazy[2*index+1]+=lazy[index];
                    lazy[2*index+2]+=lazy[index];
                }
                seg[index]+=lazy[index];
                lazy[index]=0;
                return;
            }
            lazy[2*index+1]+=lazy[index];
            lazy[2*index+2]+=lazy[index];
            lazy[index]=0;
            ll mid= (low+high)>>1;
            update(2*index+1,low,mid,L,R,val);
            update(2*index+2,mid+1,high,L,R,val);
        }
        //range update
        void update(ll L,ll R,ll val){
            update(0,0,n-1,L,R,val);
        }

        //point update
        void update2(ll index,ll low,ll high,ll L,ll R,ll val){
            //complete overlap
            if(low>=L and high<=R){
                if(low!=high){
                    lazy[2*index+1]+=lazy[index];
                    lazy[2*index+2]+=lazy[index];
                }
                lazy[index]=0;
                seg[index]=val;
                return;
            }

            //no overlap
            if(L>high or R<low){
                if(low!=high){
                    lazy[2*index+1]+=lazy[index];
                    lazy[2*index+2]+=lazy[index];
                }
                seg[index]+=lazy[index];
                lazy[index]=0;
                return;
            }
            lazy[2*index+1]+=lazy[index];
            lazy[2*index+2]+=lazy[index];
            lazy[index]=0;
            ll mid=(low+high)>>1;
            update2(2*index+1,low,mid,L,R,val);
            update2(2*index+2,mid+1,high,L,R,val);
        }

        //point update
        void update2(ll index,ll val){
            update2(0,0,n-1,index,index,val);
        }

        ll query(ll index,ll low,ll high,ll L,ll R){
            if(high<=R and low>=L){
                if(low!=high){
                    lazy[2*index+1]+=lazy[index];
                    lazy[2*index+2]+=lazy[index];
                }
                seg[index]+=lazy[index];
                lazy[index]=0;
                return seg[index];
            }
            if(R<low or high<L){
                if(low!=high){
                    lazy[2*index+1]+=lazy[index];
                    lazy[2*index+2]+=lazy[index];
                }
                seg[index]+=lazy[index];
                lazy[index]=0;
                return 0ll;
            }
            lazy[2*index+1]+=lazy[index];
            lazy[2*index+2]+=lazy[index];
            lazy[index]=0;
            ll mid=(low+high)>>1;
            ll left=query(2*index+1,low,mid,L,R);
            ll right=query(2*index+2,mid+1,high,L,R);
            return left+right;
        }
        ll query(ll index){
            return query(0,0,n-1,index,index);
        }

    };
   



//__________________________________________________________________________________________________________________________________

void RuntimeTerror() {
    
    ll n,m;cin>>n>>m;
    segTree ss(n+5);
    vector<ll> a(n),b(m);
    for(ll& i:a)cin>>i;
    for(int i=0;i<n;i++){
        ss.update(i,i,a[i]);
    }
    for(int i=0;i<m;i++){
        cin>>b[i];
        ll val=ss.query(b[i]);
        ss.update2(b[i],0);
        ll overall=val/n;
        val%=n;
        ss.update(0,n-1,overall);
        if(b[i]+val>=n){
            ss.update(b[i]+1,n-1,1);
            val-=(n-1-(b[i]+1)+1);
            ss.update(0,val-1,1);
        }else{
            ss.update(b[i]+1,b[i]+val,1);
        }
    }
    for(int i=0;i<n;i++){
        ll val=ss.query(i);
        cout<<val<<" ";
    }
    cout<< nline;
    
    
    

}
//___________________________________________________________________________________________________________________________________

int main() {
    DARTH11;
#ifndef Darthrider212
    freopen("Error.txt", "w", stderr);
#endif
    // 48-57:0-9 / 65-90:A-Z / 97-122:a-z
    // DECIMAL:       cout<<fixed<<setprecision(8)<<ans;
    // PREFIX+SUFFIX: exclude a element in the array
    // PREFIX_SUM:    binary array
    // DFS/BFS:       states being visited again
    // BINARY_SEARCH: maximize the minimum possible/minimize the maximum possible

    ll sample_test = 1;
    // sieve();
    // cin >> sample_test;

    while (sample_test--) {

        ll t = 1;
        // cin >> t;
        // ll t1 = 0;
        while (t--) {
            // t1++;
            RuntimeTerror();
        }
    }
}
