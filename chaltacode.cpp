#include<bits/stdc++.h>
using namespace std;
class station
{
    public:
    string stname;
    int x;
    int y;
    vector<string> line;
    void enter_station_info(string,int,int,vector<string> );
    bool operator< (const station& userObj) const
    {
        if(userObj.stname<this->stname)
            return true;
    }
}s[1000];

void station::enter_station_info(string st,int a,int b,vector<string> v)
{
    stname=st;
    x=a;
    y=b;
    line=v;
}

template<typename T>
class Graph{
    map<T,list<pair<T,int> > > h;
public:

	void addEdge(T u,T v,int d,bool bidir=true){
		h[u].push_back(make_pair(v,d));
		if(bidir){
			h[v].push_back(make_pair(u,d));
		}
	}

	void print(){
		for(auto node:h){
			cout<<node.first.stname<<"-->";
			for(auto neighbours:node.second){
				cout<<"("<<neighbours.first.stname<<","<<neighbours.second<<")";
			}cout<<endl;
		}
	}


     int metrofare(int x)
    {
        int m_fare=10+1*(x);
        return m_fare;
    }


	void dijkstras(T src,string d,int n){
		map<T,int> dist;
		set<pair<int,T> >s;

		int k;

		for(auto node:h){
			dist[node.first]=INT_MAX;
		}


		dist[src]=0;
		s.insert(make_pair(0,src));

		while(!s.empty()){
			auto p=*(s.begin());
			s.erase(s.begin());

			T parent=p.second;
			int ParentDist=p.first;

			for(auto children:h[parent]){
				if(dist[children.first]>(ParentDist+children.second)){
					auto f=s.find(make_pair(dist[children.first],children.first));
					if(f!=s.end()){
						s.erase(f);
					}
					dist[children.first]=ParentDist+children.second;
					s.insert(make_pair(dist[children.first],children.first));
				}
			}


		}

		//print path

		for(auto i:dist){
			if(i.first.stname==d)
            {
                cout<<"\n\nDistance of "<<i.first.stname<<" from "<<src.stname<<" is = "<<i.second<<" kms"<<endl;
                k=i.second;
                break;
            }
			//cout<<"Distance of "<<i.first.stname<<" from "<<src.stname<<" is "<<i.second<<endl;
		}
        //print path

        cout<<endl;

        int mfare=metrofare(k);
        cout<<"Your Metro fare= Rs."<<mfare<<endl;


	}


   void bfs(T src){
		queue<T> q;
		map<T,bool> visited;

		q.push(src);
		visited[src]=true;

		while(!q.empty()){
			T temp=q.front();
			q.pop();
			cout<<temp<<" ";

			for(auto children:h[temp]){
				if(!visited[children.first]){
					q.push(children.first);
					visited[children.first]=true;
				}
			}
		}
		cout<<endl;
	}

};


vector<string> blue={"NEC","Noida Sec-18","Rajiv Chowk","Yamuna Bank","Janakpuri","Dwarka Sec-21"};
vector<string> red={"Rohini","Pitampura","Shahdara","Kashmere Gate","Inderlok","Dilshad Garden"};
vector<string> yellow={"Jahangirpuri","Kashmere Gate","Chandni Chowk","Rajiv Chowk","Hauz Khas","Huda City"};
vector<string> magenta={"Kalindi Kunj","Okhla","Janakpuri","Chandni Chowk","Palam","Munirka"};
vector<string> green={"Punjabi Bagh","Inderlok","Shivaji Park","Janakpuri","Paschim Vihar","City Park"};



void view_map()
{
    cout<<"BLUE LINE:\n";
    for(auto i:blue)
    {
        cout<<"\t"<<i<<endl;
    }
    cout<<endl;

    cout<<"YELLOW LINE:\n";
    for(auto i:yellow)
    {
        cout<<"\t"<<i<<endl;
    }
    cout<<endl;

    cout<<"RED LINE:\n";
    for(auto i:red)
    {
        cout<<"\t"<<i<<endl;
    }
    cout<<endl;

    cout<<"GREEN LINE:\n";
    for(auto i:green)
    {
        cout<<"\t"<<i<<endl;
    }
    cout<<endl;

    cout<<"MAGENTA LINE:\n";
    for(auto i:magenta)
    {
        cout<<"\t"<<i<<endl;
    }
    cout<<endl;
}


int roadfare(int x)
{
    int r_fare=5+2*(x);
    return r_fare;
}


int metrofare(int x)
{
    int m_fare=10+1*(x);
    return m_fare;
}


int enterchoice()
{
    system("cls");
    int i;
    int choice;
    system("cls");
    cout<<"Last Mile Connectivity\n";
    for(i=1;i<=40;i++)
    {
         cout<<"_ ";
    }
    cout<<"\n\nSelect an Option:";
    cout<<"\n\n1.Find the shortest path to your destination\n2.Add a new station(Admin only)\n3.Fare charges\n4.View Map(Line-wise)\n5.Quit";
    cout<<"\n\nEnter your choice:";
    cin>>choice;
    return choice;
}

void get_shortest_path(int n,auto &g)
{
    string loc;
    string dest;
    int lx,ly;
    cout<<"\nEnter your location name:\n";
    cin>>loc;
    cout<<"\nEnter your coordinates:\n";
    cin>>lx>>ly;
    s[n].stname=loc;
    s[n].x=lx;
    s[n].y=ly;

    int d;
    int j;
    int min=INT_MAX;
    for(int i=0;i<n;i++)
    {
        d=sqrt(pow((s[i].x-s[n].x),2)+pow((s[i].y-s[n].y),2));
        if(d<min)
        {
            j=i;
            min=d;
        }
    }

    cout<<"\nThe nearest metro station to your location is: "<<s[j].stname<<" ("<<s[j].x<<","<<s[j].y<<")";

    //g.addEdge(s[n],s[j],min,false);

    cout<<"\n\nEnter the station you want to go to:\n";
    cin>>dest;

    g.dijkstras(s[j],dest,n);
    int rfare=roadfare(min);
    //int mfare=0;
    cout<<"Your Road fare= Rs."<<rfare<<endl;
    //cout<<"Your Metro fare= "<<mfare<<endl;


}




//get_shortest_path_fn

int main(){
    int n;
	Graph<station> g;
    vector<string> l;

    l.push_back("Red");
    s[1].enter_station_info("Rohini",16,45,l);
    l.clear();

	l.push_back("Red");
    s[2].enter_station_info("Pitampura",22,43,l);
    l.clear();

	l.push_back("Red");
    s[3].enter_station_info("Shahdara",26,42,l);
    l.clear();

	l.push_back("Red");
	l.push_back("Yellow");
    s[4].enter_station_info("Kashmere Gate",31,41,l);
    l.clear();

	l.push_back("Red");
	l.push_back("Green");
    s[5].enter_station_info("Inderlok",40,38,l);
    l.clear();

	l.push_back("Red");
    s[6].enter_station_info("Dilshad Garden",44,36,l);
    l.clear();

	l.push_back("Magenta");
    s[7].enter_station_info("Munirka",18,38,l);
    l.clear();

	l.push_back("Magenta");
    s[8].enter_station_info("Palam",22,36,l);
    l.clear();

	l.push_back("Magenta");
	l.push_back("Yellow");
    s[9].enter_station_info("Chandni Chowk",27,35,l);
    l.clear();

	l.push_back("Magenta");
	l.push_back("Green");
	l.push_back("Blue");
    s[10].enter_station_info("Janakpuri",37,34,l);
    l.clear();

	l.push_back("Magenta");
    s[11].enter_station_info("Okhla",39,31,l);
    l.clear();

	l.push_back("Magenta");
    s[12].enter_station_info("Kalindi Kunj",43,28,l);
    l.clear();

	l.push_back("Blue");
    s[13].enter_station_info("NEC",16,28,l);
    l.clear();

	l.push_back("Blue");
    s[14].enter_station_info("Noida Sec-18",20,29,l);
    l.clear();
	l.push_back("Blue");
	l.push_back("Yellow");
    s[15].enter_station_info("Rajiv Chowk",25,31,l);
    l.clear();

	l.push_back("Blue");
    s[16].enter_station_info("Yamuna Bank",30,32,l);
    l.clear();

	l.push_back("Blue");
    s[17].enter_station_info("Dwarka Sec-21",42,32,l);
    l.clear();

	l.push_back("Yellow");
    s[18].enter_station_info("Jahangirpuri",32,44,l);
    l.clear();

	l.push_back("Yellow");
    s[19].enter_station_info("Hauz Khas",23,27,l);
    l.clear();

	l.push_back("Yellow");
    s[20].enter_station_info("Huda City",21,20,l);
    l.clear();

	l.push_back("Green");
    s[21].enter_station_info("Punjabi Bagh",41,41,l);
    l.clear();

	l.push_back("Green");
    s[22].enter_station_info("Shivaji Park",39,35,l);
    l.clear();

	l.push_back("Green");
    s[23].enter_station_info("Paschim Vihar",35,30,l);
    l.clear();

	l.push_back("Green");
    s[24].enter_station_info("City Park",34,26,l);
    l.clear();

    n=24;

    int fi,fj;
    int di;

    fi=1;
    fj=2;
    di=sqrt(pow((s[fi].x)-(s[fj].x),2) + pow((s[fi].y)-(s[fj].y),2));
	g.addEdge(s[fi],s[fj],di);

    fi=2;
    fj=3;
    di=sqrt(pow((s[fi].x)-(s[fj].x),2) + pow((s[fi].y)-(s[fj].y),2));
	g.addEdge(s[fi],s[fj],di);

	fi=3;
    fj=4;
    di=sqrt(pow((s[fi].x)-(s[fj].x),2) + pow((s[fi].y)-(s[fj].y),2));
	g.addEdge(s[fi],s[fj],di);

	fi=4;
    fj=5;
    di=sqrt(pow((s[fi].x)-(s[fj].x),2) + pow((s[fi].y)-(s[fj].y),2));
	g.addEdge(s[fi],s[fj],di);

	fi=5;
    fj=6;
    di=sqrt(pow((s[fi].x)-(s[fj].x),2) + pow((s[fi].y)-(s[fj].y),2));
	g.addEdge(s[fi],s[fj],di);

	fi=7;
    fj=8;
    di=sqrt(pow((s[fi].x)-(s[fj].x),2) + pow((s[fi].y)-(s[fj].y),2));
	g.addEdge(s[fi],s[fj],di);

	fi=8;
    fj=9;
    di=sqrt(pow((s[fi].x)-(s[fj].x),2) + pow((s[fi].y)-(s[fj].y),2));
	g.addEdge(s[fi],s[fj],di);

	fi=9;
    fj=10;
    di=sqrt(pow((s[fi].x)-(s[fj].x),2) + pow((s[fi].y)-(s[fj].y),2));
	g.addEdge(s[fi],s[fj],di);

	fi=10;
    fj=11;
    di=sqrt(pow((s[fi].x)-(s[fj].x),2) + pow((s[fi].y)-(s[fj].y),2));
	g.addEdge(s[fi],s[fj],di);

	fi=11;
    fj=12;
    di=sqrt(pow((s[fi].x)-(s[fj].x),2) + pow((s[fi].y)-(s[fj].y),2));
	g.addEdge(s[fi],s[fj],di);

	fi=13;
    fj=14;
    di=sqrt(pow((s[fi].x)-(s[fj].x),2) + pow((s[fi].y)-(s[fj].y),2));
	g.addEdge(s[fi],s[fj],di);

	fi=15;
    fj=14;
    di=sqrt(pow((s[fi].x)-(s[fj].x),2) + pow((s[fi].y)-(s[fj].y),2));
	g.addEdge(s[fi],s[fj],di);

	fi=15;
    fj=16;
    di=sqrt(pow((s[fi].x)-(s[fj].x),2) + pow((s[fi].y)-(s[fj].y),2));
	g.addEdge(s[fi],s[fj],di);

	fi=16;
    fj=10;
    di=sqrt(pow((s[fi].x)-(s[fj].x),2) + pow((s[fi].y)-(s[fj].y),2));
	g.addEdge(s[fi],s[fj],di);

	fi=10;
    fj=17;
    di=sqrt(pow((s[fi].x)-(s[fj].x),2) + pow((s[fi].y)-(s[fj].y),2));
	g.addEdge(s[fi],s[fj],di);

	fi=18;
    fj=4;
    di=sqrt(pow((s[fi].x)-(s[fj].x),2) + pow((s[fi].y)-(s[fj].y),2));
	g.addEdge(s[fi],s[fj],di);

	fi=4;
    fj=9;
    di=sqrt(pow((s[fi].x)-(s[fj].x),2) + pow((s[fi].y)-(s[fj].y),2));
	g.addEdge(s[fi],s[fj],di);

	fi=9;
    fj=15;
    di=sqrt(pow((s[fi].x)-(s[fj].x),2) + pow((s[fi].y)-(s[fj].y),2));
	g.addEdge(s[fi],s[fj],di);

	fi=15;
    fj=19;
    di=sqrt(pow((s[fi].x)-(s[fj].x),2) + pow((s[fi].y)-(s[fj].y),2));
	g.addEdge(s[fi],s[fj],di);

	fi=19;
    fj=20;
    di=sqrt(pow((s[fi].x)-(s[fj].x),2) + pow((s[fi].y)-(s[fj].y),2));
	g.addEdge(s[fi],s[fj],di);

	fi=21;
    fj=5;
    di=sqrt(pow((s[fi].x)-(s[fj].x),2) + pow((s[fi].y)-(s[fj].y),2));
	g.addEdge(s[fi],s[fj],di);

	fi=5;
    fj=22;
    di=sqrt(pow((s[fi].x)-(s[fj].x),2) + pow((s[fi].y)-(s[fj].y),2));
	g.addEdge(s[fi],s[fj],di);

	fi=10;
    fj=22;
    di=sqrt(pow((s[fi].x)-(s[fj].x),2) + pow((s[fi].y)-(s[fj].y),2));
	g.addEdge(s[fi],s[fj],di);

	fi=10;
    fj=23;
    di=sqrt(pow((s[fi].x)-(s[fj].x),2) + pow((s[fi].y)-(s[fj].y),2));
	g.addEdge(s[fi],s[fj],di);

	fi=23;
    fj=24;
    di=sqrt(pow((s[fi].x)-(s[fj].x),2) + pow((s[fi].y)-(s[fj].y),2));
	g.addEdge(s[fi],s[fj],di);

 //switch

    int flag=0;
    string newst;
    string li;
    int nx;

    char c;
	do
    {
        int ch=enterchoice();
        if(ch==5)
        {
            exit(0);
        }
        else
        {
            switch(ch)
            {
             case 1:
                 system("cls");
                 cout<<"SHORTEST PATH TO YOUR DESTINATION\n";
                 get_shortest_path(n,g);
                 break;

             case 2:
                 system("cls");
                 cout<<"ADD A NEW STATION\n";
                 n++;
                 cout<<"\nEnter the name of the station:\n";
                 cin>>s[n].stname;
                 cout<<"\n Enter the x coordinate:\n";
                 cin>>s[n].x;
                 cout<<"\n Enter the y coordinate:\n";
                 cin>>s[n].y;
                 cout<<"\n Enter the no. of lines it is on:\n";
                 cin>>nx;
                 for(int z=1;z<=nx;z++)
                 {
                     cout<<"\n Enter the name of the "<<z<<"th line it is on:\n";
                     cin>>li;
                     //s[n].l.push_back(line);
                     if(li=="Yellow")
                     {
                         yellow.push_back(s[n].stname);
                     }
                     else if(li=="Red")
                     {
                         red.push_back(s[n].stname);
                     }
                     else if(li=="Blue")
                     {
                         blue.push_back(s[n].stname);
                     }
                     else if(li=="Magenta")
                     {
                         magenta.push_back(s[n].stname);
                     }
                     else if(li=="Green")
                     {
                         green.push_back(s[n].stname);
                     }
                     else
                     {
                        cout<<"Wrong metro line option\n";
                        flag=1;
                        break;
                     }
                     s[n].line.push_back(li);
                 }
                 cout<<"\nEnter the no. of stations it is connected to:\n";
                 cin>>nx;
                 for(int z=1;z<=nx;z++)
                 {
                     cout<<"\n Enter the name of the "<<z<<"th station it is connected to:\n";
                     cin>>newst;
                     for(int i=1;i<n;i++)
                     {
                         if(s[i].stname==newst)
                         {
                             di=sqrt(pow((s[n].x)-(s[i].x),2) + pow((s[n].y)-(s[i].y),2));
                             g.addEdge(s[n],s[i],di);
                             break;
                         }
                     }
                 }
                 if(flag==0)
                 {
                     cout<<"Station Added Successfully!!!!\n";
                 }
                 break;

             case 3:
                 system("cls");
                 cout<<"TRAVELLING CHARGES\n";
                 cout<<"\nRoad charges: 5+2*(kms travelled)\n";
                 cout<<"\nMetro charges: 10+1*(kms travelled)\n\n";
                 break;

             case 4:
                system("cls");
                view_map();
                break;

             default:
                system("cls");
                cout<<"\nWrong Choice ! Try Again";
                //getch();
           }
        }
    cout<<"\n\n\nDo you want to go to the main page or not?(Y/N)\n";
    cin>>c;
    system("cls");
    }while(c=='y' || c=='Y');



   return 0;
}
