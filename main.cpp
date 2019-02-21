#include <iostream>
#include <queue>
#include <fstream>

using namespace std;
struct Point{
    int x=-1,y=-1,weight=-1;
    Point(int x,int y,int weight){
        this->x=x;
        this->y=y;
        this->weight=weight;
    }
};
class Compare {
public:
    bool operator() (const Point& lhs,const Point& rhs) {
        return lhs.weight>rhs.weight;
    }
};
int grid[1000][1000];

int main(int argc, char* argv[]) {
    ios_base::sync_with_stdio(false);
    if (argc != 3) {
        cout << "Run the code with the following command: ./project4 [input_file] [output_file]" << endl;
        return 1;
    }
    ifstream input(argv[1]);
    ofstream out(argv[2]);
    int n,m;
    input >> n >> m;
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            int a;
            input >> a;
            grid[i][j]= a;
        }
    }
    int k;
    input >> k;
    for(int i=0;i<k;i++){
        vector<vector<bool>> isFound(n);
        for(int j=0;j<n;j++){
            isFound[j].resize(m);
        }
        int xBegin,yBegin,xEnd,yEnd;
        input >> xBegin >>yBegin >>xEnd >>yEnd;
        Point current(xBegin-1,yBegin-1,0);
        priority_queue<Point,vector<Point>,Compare>* heap = new priority_queue<Point,vector<Point>,Compare>();
        heap->push(current);
        while(true){
            current = heap->top();
            heap->pop();
            if(current.x==xEnd-1&&current.y==yEnd-1){
                out << current.weight << endl;
                break;
            }
            int x = current.x;
            int y = current.y;
            isFound[x][y]=true;
            if(m>y+1&&!isFound[x][y+1]){
                Point newPoint(x,y+1,max(current.weight,abs(grid[x][y]-grid[x][y+1])));
                heap->push(newPoint);
            }
            if(x-1>-1&&!isFound[x-1][y]){
                Point newPoint(x-1,y,max(current.weight,abs(grid[x][y]-grid[x-1][y])));
                heap->push(newPoint);
            }
            if(y-1>-1&&!isFound[x][y-1]) {
                Point newPoint(x,y-1, max(current.weight, abs(grid[x][y]-grid[x][y-1])));
                heap->push(newPoint);
            }
            if(n>x+1&&!isFound[x+1][y]){
                Point newPoint(x+1,y,max(current.weight,abs(grid[x][y]-grid[x+1][y])));
                heap->push(newPoint);
            }
        }
        delete heap;
    }

    return 0;
}