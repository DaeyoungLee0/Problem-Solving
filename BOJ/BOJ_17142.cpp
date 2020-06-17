/* ------------------------------------------------
���� Ǯ�� ����
1. M���� Ȱ�� ���� ���̷��� ����(DFS?)
2. M�� ���� �� BFS�� ���̷��� �̵�
 2-1. visit �迭, ��ĭ ���� �ʱ�ȭ
 2-2. ��ĭ ������ 0�� �� ���� �ð� return
 2-3. ��Ȱ�� ���̷��� ��� ����(��ĭ ���� ����x)
3. ��� ������ Ȱ�� ���� ���տ� 1-2 �ݺ�, �ּҰ�
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