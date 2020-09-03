#include<bits/stdc++.h>
#include <chrono>
#include <thread>
using namespace std;

class node
{
    public:
        bool right,down;//path maker
        char ch;//obstacle or not
        bool vis;//visited or not
        pair<int,int>prev;//previous element
        
        node()
        {
            ch='.';
            vis=false;
            right=false;
            down=false;
            prev={-1,-1};
        }
};

class matrix
{
    public:
        int m,n;//rows,columns
        node **boa;//matrix of nodes
        pair<int,int>start,end;//starting node,ending node
        
        matrix(int M,int N)
        {
            m=M;
            n=N;
            boa=new node*[m];
            for(int i=0;i<m;i++)
               boa[i]=new node[n];
        }
        
        void print()//printing the matrix
        {
            int i,j;
            for(i=0;i<m;i++)
            {
                for(j=0;j<n;j++)
                {
                    cout<<boa[i][j].ch;//printing character
                    if(boa[i][j].right)
                        cout<<"__";//right path
                    else
                        cout<<"  ";
                }
                cout<<'\n';    
                for(j=0;j<n;j++)
                {
                    if(boa[i][j].down)
                        cout<<"|  ";//down path
                    else
                        cout<<"   ";
                }
                cout<<'\n';
            }
        }
        
        void BFS()//finding the path
        {
            using namespace std::this_thread;     // sleep_for, sleep_until
            using namespace std::chrono_literals; // ns, us, ms, s, h, etc.
            using std::chrono::system_clock;
            int i,j,x,y;
            pair<int,int>p;
            queue<pair<int,int>> q;
            q.push(start);
            boa[start.first][start.second].vis=true;
            while(!q.empty())
            {
                p=q.front();
                q.pop();
                if(p==end)
                    break;
                x=p.first;
                y=p.second;
                if(x!=m-1 && boa[x+1][y].vis==false && boa[x+1][y].ch!='X')
                {
                    boa[x+1][y].vis=true;//visited
                    boa[x+1][y].prev={x,y};//update previous 
                    q.push({x+1,y});//push to the queue
                }
                if(x!=0 && boa[x-1][y].vis==false && boa[x-1][y].ch!='X')
                {
                    boa[x-1][y].vis=true;
                    boa[x-1][y].prev={x,y};
                    q.push({x-1,y});
                }
                if(y!=n-1 && boa[x][y+1].vis==false && boa[x][y+1].ch!='X')
                {
                    boa[x][y+1].vis=true;
                    boa[x][y+1].prev={x,y};
                    q.push({x,y+1});
                }
                if(y!=0 && boa[x][y-1].vis==false && boa[x][y-1].ch!='X')
                {
                    boa[x][y-1].vis=true;
                    boa[x][y-1].prev={x,y};
                    q.push({x,y-1});
                }
            }
            if(p!=end)//No path exist
            {
                cout<<"There's no path that connects starting point to destination!!!"<<'\n';
                return ;
            }
            //backtracking using prev
            vector<pair<int,int>>v;
            p=end;
            v.push_back(end);
            x=p.first;
            y=p.second;
            while(p!=start)
            {
                p=boa[x][y].prev;
                x=p.first;
                y=p.second;
                v.push_back(p);
            }
            reverse(v.begin(),v.end());
            for(int i=1;i<v.size();i++)
            {
                if(v[i].first>v[i-1].first)
                    boa[v[i-1].first][v[i-1].second].down=true;//down path
                else if(v[i].first<v[i-1].first)
                    boa[v[i].first][v[i].second].down=true;
                else if(v[i].second < v[i-1].second)
                    boa[v[i].first][v[i].second].right=true;//right path
                else
                    boa[v[i-1].first][v[i-1].second].right=true;
                sleep_until(system_clock::now() + 500ms); //delay
                system("clear");//clearing the screen
                print();    //reprinting
            }
        }
};

int main()
{
    int m,n,i,x,y,z;
    system("clear");
    cout<<"Enter the rows and columns of matrix"<<'\n';
    cin>>m>>n;//rows,columns
    matrix b(m,n);
    cout<<"Enter the starting coordinates"<<'\n';
    cin>>x>>y;
    while(x<0 || x>m-1 || y<0 || y>n-1)//while invalid coordinate
    {
        cout<<"Enter a valid coordinate!!!"<<'\n';
        cout<<"x-coordinate should lie between 0 to "<<m-1<<'\n';
        cout<<"y-coordinate should lie between 0 to "<<n-1<<'\n';
        cin>>x>>y;
    }
    b.boa[x][y].ch='S';
    b.start={x,y};
    //boa[x][y].vis=true;
    cout<<"Enter the destination coordinates"<<'\n';
    cin>>x>>y;
    while(x<0 || x>m-1 || y<0 || y>n-1)//while invalid coordinate
    {
        cout<<"Enter a valid coordinate!!!"<<'\n';
        cout<<"x-coordinate should lie between 0 to "<<m-1<<'\n';
        cout<<"y-coordinate should lie between 0 to "<<n-1<<'\n';
        cin>>x>>y;
    }
    b.boa[x][y].ch='D';
    b.end={x,y};
    cout<<"Enter the number of obstacles"<<'\n';
    cin>>z;
    while(z>n*m-2)//while obstacles greater than size of matrix
    {
        cout<<"Number of obstacle must be less than or equal to"<<n*m-2<<'\n';
        cin>>z;
    }
    for(i=0;i<z;i++)
    {
        system("clear");
        b.print();
        cout<<"Enter the coordinate of the obstacle "<<i+1<<'\n';
        cin>>x>>y;
        while(x<0 || x>m-1 || y<0 || y>n-1 || (b.boa[x][y].ch != '.'))//while invalid coordinate
        {
            if(x<0 || x>m-1 || y<0 || y>n-1)//out of bound
            {
                cout<<"Enter a valid coordinate!!!"<<'\n';
                cout<<"x-coordinate should lie between 0 to "<<m-1<<'\n';
                cout<<"y-coordinate should lie between 0 to "<<n-1<<'\n';
            }
            else if(b.boa[x][y].ch=='S')//starting coordinate
                cout<<"Starting point cannot be an obstacle"<<'\n';
            else if(b.boa[x][y].ch=='D')//destination coordinate
                cout<<"Destination point cannot be an obstacle"<<'\n';
            else
                cout<<"You have already entered this coordinate!!"<<'\n';
            cin>>x>>y;
        }
        b.boa[x][y].ch='X';
    }
    b.BFS();//finding the path
    return 0;
}
