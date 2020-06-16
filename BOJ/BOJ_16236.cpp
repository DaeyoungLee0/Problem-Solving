/* ------------------------------------------------
문제 풀이 과정
1. 상어가 먹을 수 있는 모든 물고기 좌표 찾기
2. 현재 상어 좌표에서 각 좌표까지의 최단 거리 탐색
 2-1. BFS 이용
 2-2. 그중 가장 가까운 물고기 먹기
 2-3. 모든 물고기 좌표에 도달할 수 없는 경우 종료
3. 상어 크기, 좌표 및 시간 업데이트
4. 1-3 반복
------------------------------------------------ */

#define forn(i,n) for(int i=0; i<int(n); ++i)
#define INF 98765

#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>
#include<cstring>
using namespace std;

int N, shark_size = 2, num_fish = 0, num_eat = 0;
pair<int, int> shark_pos;
int arr[20][20];
bool visit[20][20];
const int dy[] = { -1,1,0,0, }, dx[] = { 0,0,-1,1 };


int shark_move(pair<int, int> goal, int y, int x) {
	queue<pair<int, int>> q; q.push({ y,x });
	int ret = 0;

	while (!q.empty())
	{
		int qsize = q.size();
		forn(i, qsize) {
			int cy = q.front().first, cx = q.front().second;	q.pop();

			forn(n, 4) {
				int ny = cy + dy[n], nx = cx + dx[n];

				if (ny == goal.first && nx == goal.second) {
					return ret+1;
				}

				if (ny < 0 || ny >= N || nx < 0 || nx >= N) continue;
				if (!visit[ny][nx] && arr[ny][nx] <= shark_size) {
					visit[ny][nx] = true;
					q.push({ ny,nx });
				}
			}
		}
		ret++;
	}
	return INF;
}


int solution() {
	int total_time = 0;
	while (num_fish != 0) {
		vector<pair<int, int>> fish_pos;

		forn(y, N) {
			forn(x, N) {
				if (arr[y][x] < shark_size && arr[y][x] != 0) {
					fish_pos.push_back({ y,x });
				}
			}
		}

		if (fish_pos.empty()) break;

		int time = INF, cy = shark_pos.first, cx = shark_pos.second;
		pair<int, int> next_pos;

		for (auto pos : fish_pos) {			
			memset(visit, false, sizeof(visit));
			visit[cy][cx] = true;

			int time_temp = shark_move(pos, cy, cx);
			
			if (time_temp == INF)	continue;
			else if (time > time_temp) {
				time = time_temp;
				next_pos = pos;
			}			
		}

		if (time == INF) break;
		else {
			total_time += time;
			shark_pos = next_pos;
			num_eat++;
			if (num_eat == shark_size) {
				shark_size++;
				num_eat = 0;
			}
			arr[next_pos.first][next_pos.second] = 0;	num_fish--;
		}
	}
	return total_time;
}



int main(int argc, char** argv)
{
	int ans = 0;

	cin >> N;
	forn(y, N) {
		forn(x, N) {
			cin >> arr[y][x];
			if (arr[y][x] == 9) {
				shark_pos.first = y;
				shark_pos.second = x;
				arr[y][x] = 0;
			}
			else if (arr[y][x] != 0) num_fish++;
		}
	}

	ans = solution();
	cout << ans << endl;

	return 0;
}