/* ------------------------------------------------
문제 풀이 과정
1. N x N의 모든 좌표에서 
 1-1. 서비스 영역 범위에 들어간 집 개수 측정
 1-2. 만약, 서비스 영역(K)로 모든 N x N 영역을 커버하는 경우
  1-2-1. 비용 채크 후 다음 좌표 이동
------------------------------------------------ */
#define _CRT_SECURE_NO_DEPRECATE
#define forn(i,n) for(int i=0; i<int(n); ++i)


#include<iostream>
#include<vector>
#include<algorithm>
#include<cmath>
using namespace std;

int N, M, num, ans;
int arr[20][20];

void solution(int centerY, int centerX, int k) {
	int sy = centerY - (k - 1), sx = centerX - (k - 1);
	int cnt = 0;

	for (int y = sy; y <= centerY + (k - 1); ++y) {
		if (y < 0 || y >= N) continue;
		for (int x = sx; x <= centerX + (k - 1); ++x) {
			if (x < 0 || x >= N) continue;

			if (abs(y - centerY) + abs(x - centerX) < k)
				if (arr[y][x] == 1) cnt++;
		}
	}

	if (pow(k, 2) + pow(k - 1, 2) <= M * cnt)
		ans = max(ans, cnt);
}

int main(int argc, char** argv)
{
	int test_case;
	int T;

	freopen("sample_input.txt", "r", stdin);
	cin >> T;

	for (test_case = 1; test_case <= T; ++test_case)
	{
		cin >> N >> M;
		ans = 0;

		forn(i, N) {
			forn(j, N) {
				cin >> arr[i][j];
				if (arr[i][j] == 1) num++;
			}
		}

		forn(i, N) {
			forn(j, N) {
				for (int k = 1; ; ++k) {
					if (pow(k, 2) + pow(k - 1, 2) > pow(N, 2) * M)
						break;
					solution(i, j, k);
				}				
			}
		}


		cout << '#' << test_case << ' ' << ans << '\n';
	}
	return 0;
}