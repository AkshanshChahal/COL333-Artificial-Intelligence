#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string>
#include <cstring>
#include <fstream>
#include <algorithm>
#include <string.h>
#include <cstdlib>
#include <vector>
#include <cstdio>
#include <iomanip>
#include <bitset>
#define max 10000
using namespace std;

struct bid
{
	int comp_id;
	double value;
	int nor;
	// int reg[max];
	vector<int> v;

	bid(int a,double b,int c,vector<int> d)
	{
		comp_id=a;
		value=b;
		nor=c;
		v=d;
	}
};

vector<bid> bid_list;

bool *state;
bool *ans_state;
double tt;
bool *mystate;
double revenue,ans_rev, rev;

double timex;
int noc;
int noreg;
int nob;
int mx;

double countrev,revmax;

bool fn(pair<int,int> a, pair<int,int> b){
    return a.first > b.first;
}



//function to take input - read from console by redirection
void readFile(string str1)
{
	cout<<"reading file"<<endl;
	//ifstream infile("/home/himanshu/Desktop/benchmarks/1.txt");
	ifstream infile (str1);
	//ofstream outfile("output1.txt");
	string s;
	//if(!infile.eof())
	{
		getline(infile,s);
	}
	timex=(stod(s.c_str()));
	getline(infile,s);
	getline(infile,s);
	noreg=atoi(s.c_str());
	getline(infile,s);
	getline(infile,s);
	nob=atoi(s.c_str());
	getline(infile,s);
	getline(infile,s);
	noc=atoi(s.c_str());
	vector<int> abc;
	int t=0;int j=0;
	int cc,nn;
	double vv;
	//cout<<timex<<" "<<noreg<<" "<<noc<<" "<<nob<<endl;
	getline(infile,s);
	for(int i=0;i<nob;i++)
	{
		getline(infile,s);
		t=0;j=0;

		//vector<int> rr;
		abc.clear();
		string ch1="";

		while(s[t]!=' ')
		{
			ch1+=s[t];
			j++;t++;
		}
		cc=stoi(ch1);
		ch1="";
		j=0,t++;
		while(s[t]!=' ')
		{
			ch1+=s[t];
			j++;t++;
		}
		vv=stod (ch1);;
		t++;
		ch1="";
		while(true)
		{
			if(s[t]==' ')
			{	
				abc.push_back(stoi(ch1));
				ch1="";
				t++;
				continue;
			}
			if(s[t]=='#')
				break;
			ch1+=s[t];
			t++;

		}
		struct bid bd(cc,vv,abc.size(),abc);
		bid_list.push_back(bd);
		getline(infile,s);
	}
	cout<<"completed reading file"<<endl;
}


bool **conflict;
bool *arr1;
bool *state1;
bool *temp_state;
int bidno;
int counter;

pair<int,int> *c;



	int ix,jx,kx,lx;
	int dx;bool bz;

void start(double &revenue, bool state[], bool ans_state[], int nobx, int &mx, pair<int,int> c[]){

	if(mx==0){
		time_t seconds;
		time(&seconds);
		srand((unsigned int) seconds);
		mx++;
	}
	
	// cout<<"case 1.1"<<endl;
		
	// pair<int,int> c[nobx];
	

	// cout<<"case 1.2"<<endl;

	for(ix=0;ix<nobx ;ix++){
		dx = rand()%(2*nobx);
		// d = d/(double)100; 
		c[ix].first = dx;
		c[ix].second = ix;
		// cout<<d<<" ";
	}

	// cout<<endl<<"case 1.3"<<endl;

	sort(c, c+nobx, fn);

	// cout<<"case 1.4"<<endl;

	state[c[0].second] = true;
	// cout<<c[0].second<<" ";
	ans_state[c[0].second] = true;
	revenue = bid_list[c[0].second].value;
	ans_rev = revenue;
	bz = true;
	// cout<<"case 1.5"<<endl;
	for(ix=1;ix<nobx;ix++){
		kx = c[ix].second;
		bz = true;
		for(jx=0;jx<nobx;jx++){	// jo bhi state mein hain, unke saath checking if conflict
			if(state[jx]){
				if(conflict[kx][jx] || conflict[jx][kx]){
					bz = false;
					break;
				}
			}
		}
		if(bz){
			state[kx] = true;
			ans_state[kx] = true;
			revenue += bid_list[kx].value;
			ans_rev = revenue;
			// cout<<k<<" ";
		}
	}

}


int main(int narg,char*argv[])
{
	mx = 0;

	clock_t tStart = clock();
    /* Do your stuff here */
    
    string str1=argv[1];
	string str2=argv[2];

    readFile(str1);

	c = new pair<int,int>[nob];

	state=new bool[nob];
	ans_state=new bool[nob];
	state1=new bool[nob];
	temp_state=new bool[nob];
	mystate=new bool[nob];
	
	for(int i=0;i<nob;i++){
		state[i]=false;
		ans_state[i]=false;
		state1[i]=false;
		temp_state[i]=false;
		mystate[i] = false;
	}

	conflict=new bool*[nob];
	arr1=new bool[noreg];
	//arr2=new bool[noreg];

	for(int i=0;i<noreg;i++){
		arr1[i]=false;
	}

	for(int i=0;i<nob;i++)
		conflict[i] = new bool[nob];


	int i,j,k,x,y, x1,x2,y1,y2, l1,l2;
	vector<int> v1, v2;
	bool bx;
	
	for(i=0;i<nob;i++){
		for(j=0;j<nob;j++){
			conflict[i][j] = false;
		}
	}

	//cout<<" NOB:-----"<<nob<<endl;

	for(i=0;i<nob;i++){
		x1 = bid_list[i].comp_id;
		v1 = bid_list[i].v;
		l1 = v1.size();
		
		for(j=0;j<nob;j++){	
			bx = false;
			// cout<<i<<" "<<j<<endl;
			x2 = bid_list[j].comp_id;
			if(x1==x2){
				conflict[i][j]=true;
				continue;
			}
			v2 = bid_list[j].v;
			l2 = v2.size();
	

			for(x=0;x<l1;x++){
				for(y=0;y<l2;y++){	
					if(v1[x]==v2[y]){
						conflict[i][j]=true;
						bx = true;
						break;
					}
				}
				if(bx) break;
			}
		}
	}

	revenue = 0.0;
	ans_rev = 0.0;
	rev = 0.0;


	start(revenue, state, ans_state, nob, mx,c);

	ans_rev = revenue;

	counter=0;
	time_t seconds;
	time(&seconds);
	srand((unsigned int) seconds);

	double prob;
	double probx;

	// Local Search Starts

	bool bb=false;
	while(true){


		for(counter=0;counter<100000000;counter++)
		{


			tt = (double)(clock() - tStart)/CLOCKS_PER_SEC;
			if(tt > timex*60 - 1){
				bb = true;
				break;
			}

			prob = (rand()%101);
			prob = prob/(double)100;
			

			if(false)//(prob<=0.1)
			{

				// cout<<"inside 0.3"<<endl;

				bidno=rand()%nob;
				// cout<<"trying to add bid no: "<<bidno<<endl;
				bid any_bd=bid_list[bidno];

				for(int ss=0;ss<nob;ss++)
				{
					if(state[ss])
					{
						// cout<<"ss: "<<ss<<endl;
						if((conflict[bidno][ss]||conflict[ss][bidno]))
						{
							// cout<<"conflict"<<bidno<<" "<<ss<<endl;
							state[ss]=false;
							revenue-=bid_list[ss].value;
							// cout<< fixed;
							// cout<< setprecision(2)<< revenue<<endl;
						}
					}
				}
				state[bidno]=true;
				revenue+=bid_list[bidno].value;
							// cout<< fixed;
							// cout<< setprecision(2)<< revenue<<endl;
				if(revenue>ans_rev)
				{
					ans_rev=revenue;
					//ans_state=state;
					for(int ii=0;ii<nob;ii++)
					{
						ans_state[ii]=state[ii];
					}
				}
			}
			else{
				
				//cout<<"inside 0.7"<<endl;
				//state1=state;
				countrev=revenue,revmax=0;
				for(int i=0;i<nob;i++)
				{
					//cout<<"trying to add bid: "<<i<<endl; 
					for(int ii=0;ii<nob;ii++)
					{
						state1[ii]=state[ii];
					}
					countrev=revenue;
				for(int ss=0;ss<nob;ss++)
				{
					if(state1[ss])
					{
						if((conflict[i][ss]||conflict[ss][i]))
						{
							state1[ss]=false;
							countrev-=bid_list[ss].value;
						}
					}
				}
				countrev=countrev+bid_list[i].value;
				state1[i]=true;
				if(countrev>revmax)
				{
					revmax=countrev;
					for(int ii=0;ii<nob;ii++)
					{
						temp_state[ii]=state1[ii];
						//cout<<temp_state[ii]<<" ";
					}


					//cout<<endl;
				}

				}

				if(revenue >= revmax){
					// CAN PUT PROBABILITY HERE ................
					prob = (rand()%26);
					prob = prob/(double)100;

					prob += 0.75;

					probx = (rand()%101);
					probx = probx/(double)100;
					// // cout<<prob<<"  -------";


					if(probx < prob)
					// 	// cout<<"Breaked !!!"<<endl;
						break;
					// }

				}


				for(int ii=0;ii<nob;ii++)
					{
						state[ii]=temp_state[ii];
					}

				revenue=revmax;
				if(revenue>ans_rev)
				{
					ans_rev=revenue;
					//ans_state=state;
					for(int ii=0;ii<nob;ii++)
					{
						ans_state[ii]=state[ii];
					}
				}
				//cout<<endl;
			}


		}

		if(rev<ans_rev)
		{

			rev = ans_rev;
			//ans_state=state;
			for(int ii=0;ii<nob;ii++)
			{
				mystate[ii]=ans_state[ii];
			}
		}

		if(bb) break;

		////////////////////////////
		// 	DO RANDOM RESTART ...
		for(int i=0;i<nob;i++){
			state[i]=false;
			ans_state[i]=false;
			state1[i]=false;
			temp_state[i]=false;
			//mystate[i] = false;
		}

		revenue = 0.0;
		ans_rev = 0.0;

		start(revenue, state, ans_state, nob, mx,c);

		ans_rev = revenue;

	}
				ofstream myfile;
			myfile.open (argv[2]);
	for(int i=0;i<nob;i++)
	{
		if(mystate[i]==true)
			{myfile<<i;
			myfile<<" ";}
	}
	myfile<<"#";

	
/*	cout<<endl;
	cout<<setprecision(11)<<"Ans revenue: "<<rev<<endl;

	

    cout<<"Time Taken: ";
    // cout;
    cout<<setprecision(7)<<((double)(clock() - tStart)/CLOCKS_PER_SEC)<<" sec"<<endl;*/
	
	return 0;
}

