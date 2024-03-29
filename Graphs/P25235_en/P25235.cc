#include<iostream>
#include<queue>
#include<vector>
#include<map>
#include<stack>
using namespace std;

typedef pair<int,int> arc;
typedef vector<vector<arc> > Mat;

const int MAXDIST = 1e9;
vector<arc> pare;
vector<int> d;
vector<int> steps;

arc result(int d, int x){
  int steps = 0, cont = 0;
  while(d != x){
    ++steps;
    cont += pare[d].second;
    d = pare[d].first;
  }
  return arc(cont,steps);
}

void dijkstra(const Mat& mat, int x, int y){
  map<int,int> ant;
  priority_queue<arc> Q;
  int n = mat.size();
  pare = vector<arc> (n);
  d = vector<int> (n,MAXDIST);
  steps = vector<int> (n,0);
  d[x] = 0;
  ant.insert(arc(x,x));
  Q.push(make_pair(0,x));
  while(not Q.empty()){
    arc w = Q.top(); Q.pop();
    int dist = -w.first;
    int u = w.second;
    if(dist == d[u]){
      for(int i = 0; i < mat[u].size(); ++i){
        int v = mat[u][i].second;
        int distv = dist + mat[u][i].first;
        if(distv < d[v]){
          ++steps[v];
          d[v] = distv;
          Q.push(arc(-distv,v));
          pare[v] = arc(u,mat[u][i].first);
        }
        else if(distv == d[v] and steps[v] + 1 < steps[u]) steps[u] = steps[v] + 1;
      }
    }
  }
}

int main(){
  int n, m, x, y, u, v, c;
  while(cin >> n >> m){
    Mat mat(n);
    for(int i = 0; i < m; ++i){
      cin >> u >> v >> c;
      mat[u].push_back(arc(c,v));
    }
    cin >> x >> y;
    dijkstra(mat,x,y);
    if(d[y] != MAXDIST){
      arc pair1 = result(y,x);
      cout << "cost " << pair1.first << ", " << pair1.second << " step(s)" << endl;
    }
    else cout << "no path from " << x << " to " << y << endl;
  }
}
