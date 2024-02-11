#include <bits/stdc++.h>
using namespace std;
#define DARTH11 ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL)

#ifndef Darthrider212
#define debug(x) cerr << #x<<" "; _print(x); cerr << endl;
#else
#define debug(x);
#endif
#define nline "\n"


class segTree{
public:
    vector<int> seg,lazy;
    segTree(int n){
        seg.resize(4*n+1);
        lazy.resize(4*n+1);
    }
    void build(int index,int low,int high,int arr[]){
        if(low==high){
            seg[index]=arr[low];
            return;
        }
        int mid=(low+high)>>1;
        build(2*index+1,low,mid,arr);
        build(2*index+2,mid+1,high,arr);
        seg[index]=seg[2*index+1]+seg[2*index+2];
    }
    void update(int index,int low,int high,int L,int R,int val){
        //update the previous remaining updates and propogate downwards
        if(lazy[index]!=0){
            seg[index]+=(high-low+1)*lazy[index];//basically the number of children
            //for index will be (high-low+1) and as indivisually everyone will be updated
            //so we multiply with lazy[index] as it the updates we have to do

            // now we propogate the lazy updates downwards for the remaining nodesto get updated
            if(low!=high){
                // if low==high it means that it is leaf node and leaf nodes doesn't have children
                lazy[2*index+1]+=lazy[index];
                lazy[2*index+2]+=lazy[index];
            }
            // now reset the value of lazy index
            lazy[index]=0;
        }//lazy update done

        // no overlap don't do anything 
        // [low high] [L R] or [L R] [low high]
        if(high<L or low>R)return ;

        //complete overlap [L low high R]
        if(low>=L and high<=R){
            seg[index]+=(high-low+1)*val;

            //if not leaf it will have children so propogate down
            if(low!=high){
                lazy[2*index+1]+=val;
                lazy[2*index+2]+=val;
            }
            return;
        }
        //parital overlap
        int mid=(low+high)>>1;
        update(2*index+1,low,mid,L,R,val);
        update(2*index+2,mid+1,high,L,R,val);
        seg[index]=seg[2*index+1]+seg[2*index+2];
    }

    int query(int index,int low,int high,int L,int R){
        //update if any updates are remaining as the node will stay fresh and updated
        if(lazy[index]!=0){
            seg[index]+=(high-low+1)*lazy[index];
            //propogate down the lazy updates for the remaining nodes to get updated
            if(low!=high){
                lazy[2*index+1]+=lazy[index];
                lazy[2*index+2]+=lazy[index];
            }
            lazy[index]=0;
        }

        // no overlap [low high][L R] or [L R][low high]
        if(high<L or low>R)return 0;

        //complete overlap [L low high R]
        if(low>=L and high<=R)return seg[index];

        //partial overlaps
        int mid=(low+high)>>1;
        int left= query(2*index+1,low,mid,L,R);
        int right=query(2*index+2,mid+1,high,L,R);
        return left+right;
    }
};

int main(){

    DARTH11;
#ifndef Darthrider212
    freopen("Error.txt", "w", stderr);
#endif
    int n; cin>>n;
    int arr[n];
    for(int i=0;i<n;i++)cin>>arr[i];
    segTree sg(n);
    sg.build(0,0,n-1,arr);

    int q;cin>>q;
    while(q--){
        int type;cin>>type;
        if(type==1){
            int l,r;cin>>l>>r;
            int d=sg.query(0,0,n-1,l,r);
            cout<< d<<nline;
        }
        else{
            int l,r,val;cin>>l>>r>>val;
            sg.update(0,0,n-1,l,r,val);
        }
    }



    return 0;
}