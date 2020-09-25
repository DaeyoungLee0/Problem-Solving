#include <iostream>
#include <vector>
using namespace std;

#define INF 987654321;

int N, H, W, dx[] = {0,0,-1,1}, dy[] = {-1,1,0,0};
int arr[15][12];
int ans = INF;
int num = 0;

void remove(int y, int x, int n){
    for(int i=0; i<4; ++i){
        int ny = y, nx = x;
        for(int j=0; j<n-1; ++j){
            ny += dy[i], nx += dx[i];
            if(ny<0 || ny>=H || nx<0 || nx>=W) break;

            int temp = arr[ny][nx];
            if(temp != 0){
                arr[ny][nx] = 0; num--;
                if(temp > 1) remove(ny, nx, temp);
            }
        }
    }
}

void arrange(){
    for(int x=0; x<W; ++x){
        int preY = -1;

        for(int y=H-1; y>=0; --y){
            if(arr[y][x] == 0 && preY == -1) preY = y;
            else if(arr[y][x] != 0 && preY != -1){
                arr[preY][x] = arr[y][x];
                arr[y][x] = 0;
                preY--;
            }
        }
    }
}

void solution(int cnt){
    if(cnt == N){
        ans = min(ans, num);
        // if(ans == num){
        //     for(int y=0; y<H; y++){
        //         for(int x=0; x<W; ++x){
        //             cout << arr[y][x] << ' ';
        //         }
        //         cout << endl;
        //     }
        //     cout << endl;
        // }
        return;
    }

    int num_copy = num;
    int arr_copy[15][12];
    for(int y=0; y<15; y++)
        for(int x=0; x<12; ++x)
            arr_copy[y][x] = arr[y][x];

     for(int x=0; x<W; ++x){
        for(int y=0; y<H; ++y){
            int temp = arr[y][x];
            if(temp == 0) continue;
            else{
                arr[y][x] = 0; num--;
                if(temp > 1) remove(y, x, temp);
                break;
            }            
        }
        arrange();
        solution(cnt+1);
        num = num_copy;
        for(int y=0; y<H; y++)
            for(int x=0; x<W; ++x)
                arr[y][x] = arr_copy[y][x];        
    }
}

int main(int argc, char** argv)
{
	int test_case;
	int T;

	// freopen("input.txt", "r", stdin);
	cin>>T;

	for(test_case = 1; test_case <= T; ++test_case)
	{
        memset(arr, 0, sizeof(arr));
        num = 0, ans = INF;

        cin >> N >> W >> H;
        for(int y=0; y<H; ++y){
            for(int x=0; x<W; ++x){
                cin >> arr[y][x];
                if(arr[y][x] != 0) num++;
            }
        }

		solution(0);
        cout << "#" << test_case << ' ' << ans << endl;
	}
	return 0;
}
