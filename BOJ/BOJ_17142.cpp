/* ------------------------------------------------
문제 풀이 과정
1. M개의 활성 상태 바이러스 선택(DFS?)
2. M개 선택 후 BFS로 바이러스 이동
 2-1. visit 배열, 빈칸 개수 초기화
 2-2. 빈칸 개수가 0일 때 진행 시간 return
 2-3. 비활성 바이러스 통과 가능(빈칸 개수 변동x)
3. 모든 가능한 활성 상태 조합에 1-2 반복, 최소값
------------------------------------------------ */

#define forn(i,n) for(int i=0; i<int(n); ++i)
#define INF 98765

#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>
using namespace std;

const int dy[] = { -1,1,0,0 }, dx[] = { 0,0,-1,1 };
int N, M, ans = INF, num_space = 0;
int arr[50][50];
vector<vector<bool> > visit(50, vector<bool>(50, false));
vector<pair<int, int>> virus, virus_sel;

int move_virus() {
	int time = 0;
	queue<pair<int, int>> q;
	forn(i, virus_sel.size()) q.push(virus_sel[i]);
	
	int num_space_copy = num_space;
	vector<vector<bool> > visit_copy(visit);

	while (!q.empty())
	{
		int qsize = q.size();
		forn(i, qsize) {
			int cy = q.front().first, cx = q.front().second;
			q.pop();

			forn(n, 4) {
				int ny = cy + dy[n], nx = cx + dx[n];
				if (ny < 0 || ny >= N || nx < 0 || nx >= N) continue;

				if (!visit_copy[ny][nx] && arr[ny][nx] != 1) {
					visit_copy[ny][nx] = true;
					if(arr[ny][nx] == 0)	num_space_copy--;
					q.push({ ny,nx });
				}
			}
		}
		time++;
		if (time >= ans) return INF;
		if (num_space_copy == 0) return time;
	}
	return INF;
}

void select_virus(int n, int m) {
	if (m == M) {
		ans = min(ans, move_virus());
		return;
	}
	if (n == virus.size()) return;

	for (int i = n; i < virus.size(); ++i) {
		virus_sel.push_back(virus[i]);
		visit[virus[i].first][virus[i].second] = true;
		select_virus(i + 1, m + 1);
		virus_sel.pop_back();
		visit[virus[i].first][virus[i].second] = false;
	}
}


int main(int argc, char** argv)
{
	cin >> N >> M;
	
	forn(y, N) {
		forn(x, N) {
			int temp;
			cin >> temp;
			arr[y][x] = temp;
			if (temp == 2) virus.push_back({ y,x });
			else if (temp == 0) num_space++;
		}
	}

	if (num_space == 0) cout << 0 << endl;
	else {
		select_virus(0, 0);
		if (ans == INF) cout << -1 << endl;
		else cout << ans << endl;
	}

	return 0;
}