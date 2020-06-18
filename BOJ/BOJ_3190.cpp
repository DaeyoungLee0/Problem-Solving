/* ---------------------------------------------------
문제 풀이 과정
1. NxN 배열 0 초기화 및 사과 1 위치
2. 방향 변환 정보 입력(오:1, 왼: 2, 나머지 시간: 0)
 2-1. 변환 정보와 현재 방향에 따른 다음 방향 배열 설정
3. dequeue를 사용한 뱀의 이동
 3-1. 이동시 벽이거나 자기자신 충돌 체크
--------------------------------------------------- */

#include<iostream>
#include<cstring>
#include<deque>
#include<algorithm>
using namespace std;

#define forn(i,n) for(int i=0; i<int(n); ++i)

int board[102][102];
int dirArr[100001] = { 0, };

const int dy[] = { -1,1,0,0 }, dx[] = { 0,0,-1,1 };
const int nextDir[3][4] = {	// [방향 변환 정보 - 0: 방향 유지, 1: 오른쪽 회전, 2: 왼쪽 회전][현재 방향]
	{0,1,2,3},
	{3,2,0,1},
	{2,3,1,0}
};


int solution(int N) {
	int currD = 3;
	int cy = 1, cx = 1, cnt = 0;
	deque<pair<int, int>> snake;
	snake.push_front({ cy,cx });

	while (1) {
		cnt++;

		int ny = cy + dy[currD], nx = cx + dx[currD];
		// 벽이거나
		if (ny<1 || ny>N || nx<1 || nx>N) break;
		// 자기자신 몸과 충돌
		if (find(snake.begin(), snake.end(), make_pair(ny,nx)) != snake.end()) break;

		// 이동 및 사과 유무 확인
		snake.push_front({ ny,nx });
		if (board[ny][nx] == 0) {
			snake.pop_back();
		}
		else {
			board[ny][nx] = 0;
		}

		cy = ny, cx = nx;
		currD = nextDir[dirArr[cnt]][currD];
	}

	return cnt;
}


int main() {
	int N, K, L, ans;

	cin >> N >> K;

	memset(board, 0, sizeof(board));

	forn(i, K) {
		int y, x;
		cin >> y >> x;
		board[y][x] = 1;
	}

	cin >> L;
	forn (i, L) {
		int X;
		char C;
		cin >> X >> C;
		if (C == 'D') dirArr[X] = 1;
		else dirArr[X] = 2;
	}

	ans = solution(N);
	cout << ans << endl;

	return 0;
}