"""
반례 찾는 중..

"""

#include <iostream>
#include <vector>
using namespace std;

struct info{
    int y, x, dir;
    bool life;
};

vector<info> shark;
pair<int,int> arr[20][20];  // (num, k)
vector<vector<int> > dirvec;
const int dy[] = {-1, 1, 0, 0}, dx[] = {0, 0, -1, 1};

int N, M, k;

void spend_time(){
    for(int y=0; y<N; ++y){
        for(int x=0; x<N; ++x){
            if(arr[y][x].second != 0){
                arr[y][x].second--;
                if(arr[y][x].second == 0) arr[y][x].first = 0;
            }
        }
    }
}

int solution(int num){
    int time = 0;

    while(1){
        // 현재 arr 복사
        pair<int,int> arr_copy[20][20];
        for(int y=0; y<N; ++y)
            for(int x=0; x<N; ++x)
                arr_copy[y][x] = arr[y][x];

        // 현재 남은 냄새 시간 1씩 감소
        spend_time();

        for(int csharkNum=1; csharkNum<=M; ++csharkNum){
            info &cshark = shark[csharkNum];
            if(!cshark.life) continue;

            int cy = cshark.y, cx = cshark.x, cdir = cshark.dir;
            bool flag1 = false, flag2 = false;
            pair<int,int> temp_pos;
            int temp_dir = 0;

            for(int j=0; j<4; ++j){
                int ndir = dirvec[csharkNum][cdir*4 + j];
                int ny = cy + dy[ndir], nx = cx + dx[ndir];

                if(ny<0 || ny>=N || nx<0 || nx>=N) continue;

                if(arr_copy[ny][nx].first==0 && arr_copy[ny][nx].second==0){
                    int psharkNum = arr[ny][nx].first;
                    if(psharkNum == 0){
                        arr[ny][nx].first = csharkNum, arr[ny][nx].second = k;
                        cshark.y = ny, cshark.x = nx, cshark.dir = ndir;
                    }
                    else{
                        if(csharkNum > psharkNum)
                            cshark.life = false;
                        else{
                            shark[psharkNum].life = false;
                            arr[ny][nx].first = csharkNum;
                            cshark.y = ny, cshark.x = nx, cshark.dir = ndir;
                        }
                        num--;
                    }
                    flag1 = true;
                    break;
                }
                else if(arr_copy[ny][nx].first == csharkNum && !flag2){
                    temp_pos.first = ny, temp_pos.second = nx;
                    temp_dir = ndir;
                    flag2 = true;
                }
            }
            if(!flag1){
                // 빈 공간이 없는 경우
                arr[temp_pos.first][temp_pos.second].second = k;
                cshark.y = temp_pos.first, cshark.x = temp_pos.second;
                cshark.dir = temp_dir;
            }
        }
        time++;
        if(num == 1) return time;
        else if(time == 1000) return -1;
    }
}


int main(){
    int ans = 0;
    cin >> N >> M >> k;
    shark.resize(M+1);
    dirvec.resize(M+1);

    for(int y=0; y<N; ++y){
        for(int x=0; x<N; ++x){
            int temp;
            cin >> temp;
            if(temp != 0){
                shark[temp].y = y;
                shark[temp].x = x;
                shark[temp].life = true;
                arr[y][x].first = temp;
                arr[y][x].second = k;
            }
        }
    }

    for(int m=1; m<=M; ++m){
        int temp;
        cin >> temp;
        shark[m].dir = temp-1;
    }

    for(int m=1; m<=M; ++m){
        vector<int> vec(16);
        for(int n=0; n<4; ++n){
            int d1, d2, d3, d4;
            cin >> d1 >> d2 >> d3 >> d4;
            vec[n*4] = d1-1, vec[n*4+1] = d2-1, vec[n*4+2] = d3-1, vec[n*4+3] = d4-1;
        }
        dirvec[m] = vec;
    }

    ans = solution(M);
    cout << ans << endl;
    
    return 0;
}
