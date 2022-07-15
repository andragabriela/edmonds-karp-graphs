#include<vector>
#include<iostream>
#include<fstream>
#include<deque>

using namespace std;

const int NMAX = 1005;
const int inf = 2e9;
int n, m;
int c[NMAX][NMAX], F[NMAX][NMAX], parent[NMAX];
bool viz[NMAX];
vector < int > v[NMAX];
deque < int > q;

int BFS() {
    int node;
    memset(viz, 0, sizeof(viz));
    q.push_back(1);
    viz[1] = 1;
    while (!q.empty()) {
        node = q.front();
        q.pop_front();

        if (node == n) continue;

        for (auto& nxt : v[node]) {
            if (c[node][nxt] == F[node][nxt] || viz[nxt]) continue;
            viz[nxt] = 1;
            q.push_back(nxt);
            parent[nxt] = node;
        }
    }
    return viz[n];
}

int main(int argc, char** argv) {
 
    ifstream f("in.txt");
    ofstream g("data.out");

    int x, y, z, fmin, node;
    f >> n >> m;
    for (int i = 0; i < m; i++) {

        f >> x >> y >> z;
        x++;
        y++;
        v[x].push_back(y);
        v[y].push_back(x);
        c[x][y] += z;
    }

    int flow = 0;
    do {
        for (auto& it : v[n]) {
            if (F[it][n] == c[it][n] || !viz[it])  continue;

            parent[n] = it;
            fmin = inf;

            for (node = n; node != 1; node = parent[node])
                fmin = min(fmin, c[parent[node]][node] - F[parent[node]][node]);

            if (fmin == 0) continue;

            for (node = n; node != 1; node = parent[node]) {
                F[parent[node]][node] += fmin;
                F[node][parent[node]] -= fmin;
            }

            flow += fmin;
        }
    } while (BFS());

    g << flow;


    return 0;
}
