/* alexok2006 */
#include<bits/stdc++.h>

#define all(x) x.begin(),x.end()
#define rall(x) x.rbegin(),x.rend()
#define ll long long
#define ld long double
#define LLM 1e17
#define pp pair<int,int>
using namespace std;
template<class F,class S> ostream& operator<<(ostream& os,pair<F,S>& cur) { os<<"("<<cur.first<<";"<<cur.second<<")"; return os;}
template<class T> ostream& operator<<(ostream& os,vector<T>& arr) { for(auto i:arr) os<<i<<" "; return os;}
template<class T> istream& operator>>(istream& is,vector<T>& arr) { for(auto& i:arr) is>>i; return is;}

template<typename T> struct min_generator_target {    T& target;    template<typename U> T& operator=(const U& value) {        if(value < target) {            target = value;        }        return target;    }};struct min_generator_t {    template<typename T> friend auto operator+(T& target, min_generator_t) {        return min_generator_target<T>{target};    }    template<typename... Args> auto operator()(Args&&... args) const {        return std::min(std::forward<Args>(args)...);    }    template<typename T> auto operator()(std::initializer_list<T> ilist) const {return std::min(ilist);}template<typename T, typename Compare> auto operator()(std::initializer_list<T> ilist, Compare comp) const {return std::min(ilist, comp);    }} min_generator;
template<typename T> struct max_generator_target {    T& target;    template<typename U> T& operator=(const U& value) {        if(value > target) {            target = value;        }        return target;    }};struct max_generator_t {    template<typename T> friend auto operator+(T& target, max_generator_t) {        return max_generator_target<T>{target};    }    template<typename... Args> auto operator()(Args&&... args) const {        return std::max(std::forward<Args>(args)...);    }    template<typename T> auto operator()(std::initializer_list<T> ilist) const {        return std::max(ilist);    }    template<typename T, typename Compare> auto operator()(std::initializer_list<T> ilist, Compare comp) const {        return std::max(ilist, comp);    }} max_generator;
#define mins + min_generator
#define maxs + max_generator

void solve() {
    int n;
    cin >> n;
    string s[2];
    cin >> s[0] >> s[1];
    int mult = 0;
    
    for (int i = 0; i < n; i++) {
        if (i == n-1) {
           if ( int(s[0][n-1] == '#')+int(s[1][n-1] == '#') == 1) {cout << "None\n"; return;}
           break;
        }
        int c0 = int(s[0][i] == '#')+int(s[1][i] == '#');
        // #.
        // #.
        if (c0 == 2) continue; 

        int c1 = int(s[0][i+1] == '#')+int(s[1][i+1] == '#');      
        // ..
        // ..
        if (c0+c1 == 0) { mult = 1; s[0][i] = s[1][i] = '#'; continue;}         
        // .?
        // .?
        if (c0 == 0) { s[0][i] = s[1][i] = '#'; continue;}
        // ..
        // #?
        if (s[0][i] == '.' && s[0][i+1] == '.') {
           s[0][i+1]='#'; continue;
        }
        // #?
        // ..
        if (s[1][i] == '.' && s[1][i+1] == '.') {
           s[1][i+1]='#'; continue;
        } 
        cout <<"None\n";
        return;

    }
 
    if (mult) cout << "Multiple\n";
    else {
      cout << "Unique\n";
    }  
}

signed main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout<<setprecision(20);
  int t;
  cin >> t;
  while(t-->0)
    solve();
}

