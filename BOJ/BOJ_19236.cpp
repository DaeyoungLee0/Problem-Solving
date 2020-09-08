#include <iostream>
#include <vector>

using namespace std;

int dy[] = {-1,-1,0,1,1,1,0,-1}, dx[] = {0,-1,-1,-1,0,1,1,1};

struct info{
    int x,y;
    int dir;
    bool life = true;
};

info fishs[17];
info shark;
int arr[4][4], ans = 0;

void fish_move(){
    for(int n=1; n<=16; ++n){
        if(!fishs[n].life) continue;
        int cdir = fishs[n].dir;
        int cy = fishs[n].y, cx = fishs[n].x;       

        for(int d=0; d<8; ++d){
            int ndir = (cdir + d) % 8;
            int ny = cy + dy[ndir], nx = cx + dx[ndir];

            if(ny<0 || ny>=4 || nx<0 || nx>=4) continue;
            if(ny==shark.y && nx==shark.x) continue;

            if(arr[ny][nx] == 0){
                arr[ny][nx] = n;
                arr[cy][cx] = 0;
                fishs[n].y = ny, fishs[n].x = nx;
                fishs[n].dir = ndir;
            }
            else{
                int temp = arr[ny][nx];
                arr[ny][nx] = n;
                arr[cy][cx] = temp;
                fishs[n].y = ny, fishs[n].x = nx;
                fishs[temp].y = cy, fishs[temp].x = cx;
                fishs[n].dir = ndir;
            }
            break;
        }
    }
}

void shark_move(int num){
    int cdir = shark.dir, cx = shark.x, cy = shark.y;
    int arrC[4][4];
    info fishsC[17];
    fish_move();    

    for(int i=1; i<=16; ++i)
        fishsC[i] = fishs[i];

    for(int i=0; i<4; ++i)
        for(int j=0; j<4; ++j)
            arrC[i][j] = arr[i][j];    

    for(int n=1; n<=3; ++n){
        int nx = cx + dx[cdir]*n;
        int ny = cy + dy[cdir]*n;
        if(ny<0 || ny>=4 || nx<0 || nx>=4) break;

        int fish_num = arr[ny][nx];
        if(fish_num == 0) continue;
        shark.y = ny, shark.x = nx;
        shark.dir = fishs[fish_num].dir;
        arr[ny][nx] = 0, fishs[fish_num].life = false;        

        shark_move(num+fish_num);

        for(int i=0; i<4; ++i)
            for(int j=0; j<4; ++j)
                arr[i][j] = arrC[i][j];

        for(int i=1; i<=16; ++i)
            fishs[i] = fishsC[i];
        
        fishs[fish_num].life = true;        
        shark.dir = cdir;        
        shark.y = cy, shark.x = cx;
    }

    ans = max(ans, num);
}


int main(){    
    for(int y=0; y<4; ++y){
        int a,b;
        for(int x=0; x<4; ++x){
            cin >> a >> b;
            info temp;
            temp.y = y, temp.x = x;
            temp.dir = b-1;
            fishs[a] = temp;
            arr[y][x] = a;
        }
    }

    shark.y = 0, shark.x = 0;
    shark.dir = fishs[arr[0][0]].dir;
    fishs[arr[0][0]].life = false;
    ans = arr[0][0];
    arr[0][0] = 0;
    
    shark_move(ans);
    cout << ans << endl;
    return 0;
}
