/* ---------------------------------------------------
���� Ǯ�� ����
1. NxN �迭 0 �ʱ�ȭ �� ��� 1 ��ġ
2. ���� ��ȯ ���� �Է�(��:1, ��: 2, ������ �ð�: 0)
 2-1. ��ȯ ������ ���� ���⿡ ���� ���� ���� �迭 ����
3. dequeue�� ����� ���� �̵�
 3-1. �̵��� ���̰ų� �ڱ��ڽ� �浹 üũ
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
const int nextDir[3][4] = {	// [���� ��ȯ ���� - 0: ���� ����, 1: ������ ȸ��, 2: ���� ȸ��][���� ����]
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
		// ���̰ų�
		if (ny<1 || ny>N || nx<1 || nx>N) break;
		// �ڱ��ڽ� ���� �浹
		if (find(snake.begin(), snake.end(), make_pair(ny,nx)) != snake.end()) break;

		// �̵� �� ��� ���� Ȯ��
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