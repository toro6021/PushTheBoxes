#include<bits/stdc++.h>
#include<conio.h>
#include<io.h>
#include<windows.h>
using namespace std;

const int dx[]={-1,0,1,0};
const int dy[]={0,-1,0,1};

#define pii pair<int,int>   
#define X first
#define Y second

int N,M;
pii P;
pii Q[255]; int Qcnt=0;
int grid[55][55];

namespace tool
{
	int ws(int xx)
	{
		int res=0;
		while(xx!=0)
		{
			xx/=10;
			res++;
		}
		return res;
	}
	
	void colorfulop(string op,char color)
	{
		auto ist=FOREGROUND_INTENSITY;
		auto rrr=FOREGROUND_RED;
		auto ggg=FOREGROUND_GREEN;
		auto bbb=FOREGROUND_BLUE;
		__typeof(ist) col;
		if(color=='W') col=(ist|rrr|ggg|bbb);
		if(color=='R') col=(ist|rrr);
		if(color=='G') col=(ist|ggg);
		if(color=='B') col=(ist|bbb);
		if(color=='Y') col=(ist|rrr|ggg);
		if(color=='P') col=(ist|rrr|bbb);
		if(color=='I') col=(ist|ggg|bbb);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),col);
		cout<<op;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),ist);
	}
	
	void getFiles(string path,int dep)
	{
		_finddata_t fileinfo;
		string p;
		int hFile=_findfirst(p.assign(path).append("\\*").c_str(), &fileinfo);
		if(hFile!=-1)
		{
			do
			{
				if((fileinfo.attrib&  _A_SUBDIR))
				{
					if(strcmp(fileinfo.name,".")!=0 && strcmp(fileinfo.name,"..")!=0)
					{
						cout<<"   ";
						for(int i=1;i<=dep+1;i++) cout<<">";
						string ot=p.assign(path).append("\\").append(fileinfo.name);
						cout<<ot.substr(path.size()+1)<<endl;
						getFiles(p.assign(path).append("\\").append(fileinfo.name),dep+1);						
					}
				} 
				else
				{
					cout<<"   ";
					string rs;
					for(int i=1;i<=dep+1;i++) rs+=">";
					string ot=p.assign(path).append("\\").append(fileinfo.name);
					string oo=rs+ot.substr(path.size()+1,ot.size()-path.size()-5)+"\n";
					tool::colorfulop(oo,'Y');
				}
			} while(_findnext(hFile,&fileinfo)==0);
			_findclose(hFile);
		}
	}
	
	void curgoto(int x,int y)
	{
		COORD pos={(short)x,(short)y};
		HANDLE hOut=GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleCursorPosition(hOut, pos);
	}
}
namespace IandO
{
	int GET_KEY()
	{
		char ch='!';
		while(true)
		{
			switch(ch)
			{
				case 'w': case 'W': return 0;
				case 'a': case 'A': return 1;
				case 's': case 'S': return 2;
				case 'd': case 'D': return 3;
				
				case 'p': case 'P': return 5;
				
				default : ch=getch();
			}		
		}
	}
	
	void change(int x,int y,char v)
	{
		swap(x,y);
		tool::curgoto(x+1,y+1);
		cout<<v;
		tool::curgoto(0,N+2);
	}
	
	void output()
	{
		system("cls");
		for(int i=0;i<M+2;i++) cout<<"-";
		cout<<endl;
		for(int i=0;i<N;i++)
		{
			cout<<"|";
			for(int j=0;j<M;j++)
			{
				switch(grid[i][j])
				{
					case 0: cout<<"."; break;
					case 1: cout<<"#"; break;
					case 2: cout<<"+"; break;
					case 3: cout<<"O"; break;
					case 4: cout<<"@"; break;
				}
			}
			cout<<"|";
			cout<<endl;
		}
		for(int i=0;i<M+2;i++) cout<<"-";
		cout<<endl;
	}
}
namespace init
{
	void init()
	{
		auto ist=FOREGROUND_INTENSITY;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),ist);
		
		string MapID;
		
		system("cls");
		cout<<endl;
		cout<<"  Choose map......"<<endl;
		cout<<endl;
		tool::getFiles("maps",0);
		cout<<endl;
		cout<<"   "; getline(cin,MapID);
		cout<<"   ";
		system("cls");
		
		string FileF="./maps/"+MapID+".txt";
		ifstream fin(FileF);
		
		fin>>N>>M;
		for(int i=0;i<N;i++)
		{
			for(int j=0;j<M;j++)
			{
				fin>>grid[i][j];
			}
		}
		for(int i=0;i<N;i++)
		{
			for(int j=0;j<M;j++)
			{
				if(grid[i][j]==2)
				{
					P.X=i;P.Y=j;
				}
				if(grid[i][j]==3)
				{
					Q[++Qcnt].X=i;Q[++Qcnt].Y=j;
				}
			}
		}
		fin.close();
		IandO::output();
	}
}
namespace gameover
{
	void gameover()
	{
		system("cls");
		cout<<endl;
		cout<<"  gameover."<<endl;
		cout<<endl;
		cout<<"  thanks..."<<endl;
		getch();
		
		exit(0);
	}
}
namespace work
{
	bool succeed()
	{
		for(int i=0;i<N;i++)
		{
			for(int j=0;j<M;j++)
			{
				if(grid[i][j]==4) return false;
			}
		}
		return true;
	}
	
	bool ok(int xx,int yy)
	{
		return (xx>=0 && xx<N && yy>=0 && yy<M);
	}
	
	bool work(int op)
	{
		if(op==5)
		{
			gameover::gameover();
		}
		
		pii NP=pii(P.X+dx[op],P.Y+dy[op]);
		if(ok(NP.X,NP.Y))
		{
			if(grid[NP.X][NP.Y]==0)
			{
				grid[P.X][P.Y]=0;   IandO::change(P.X,P.Y,'.');
				grid[NP.X][NP.Y]=2; IandO::change(NP.X,NP.Y,'+');
				P=NP;
			}
			else if(grid[NP.X][NP.Y]==3)
			{
				pii NQ=pii(NP.X+dx[op],NP.Y+dy[op]);
				if( ok(NQ.X,NQ.Y) && (grid[NQ.X][NQ.Y]==0 || grid[NQ.X][NQ.Y]==4) )
				{
					grid[P.X][P.Y]=0;   IandO::change(P.X,P.Y,'.');
					grid[NP.X][NP.Y]=2; IandO::change(NP.X,NP.Y,'+');
					grid[NQ.X][NQ.Y]=3; IandO::change(NQ.X,NQ.Y,'O');
					P=NP;
					for(int i=1;i<=Qcnt;i++)
					{
						if(Q[i]==NP) Q[i]=NQ;
					}
				}
			}
		}
		return succeed();
	}
}

int main()
{
	init::init();
	while(true)
	{
//		IandO::output();
		if( work::work( IandO::GET_KEY() ) ) gameover::gameover();
	}
}































