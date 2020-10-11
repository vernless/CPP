#include<iostream>
#include<algorithm>
#include<stdlib.h>
#include<cstdlib>
#include<string>
#include<sstream>
#include<math.h>
#include<cstdio>
#include<string.h>
#include<iomanip>
using namespace std;
double SS(string a)					//string转double 
{
	double des;
	stringstream ss;
	ss<<a;
	ss>>des;
	return des;
}
string SS1(double a)				//double 转string 
{
	string str;
	stringstream ss;
	ss<<a;
	ss>>str;
	return str;
}
string ten(string a,double r) 
{
	int len1;
	for(len1=0;len1<a.length();len1++)//统计整数部分长度 
	{
		if(a[len1]=='.')
		break;
	} 
	int k=len1+1;//将k指向小数部分第一位 
	int cetz=0,cetx=-1;
	long Sumz=0;
	double Sumx=0;
	for(  ;len1>0;len1--)//整数部分逆向累加 
	{
		Sumz+=(a[len1-1]-'0')*pow(r,cetz);
		cetz++;
	}
	for(  ;k<a.length();k++)//小数部分正向累加 
	{
		Sumx+=(a[k]-'0')*pow(r,cetx);
		cetx--;
	}
	return SS1(Sumz+Sumx);
}
string jzzh(string a)
{
	string y;
	int x=a.length();
	if(a[0]=='0'&&a[1]=='x')
	{
		for(int i=0;i<x-2;i++)
		{
			a[i]=a[i+2]; 
		}
		y.append(a,0,x-2);
		return ten(y,16);	 
	}
	if(a[0]=='0'&&a[1]=='b')
	{
		for(int i=0;i<x-2;i++)
		{//1+1
			a[i]=a[i+2];	
		} 
		y.append(a,0,x-2); 
		return ten(y,2);
	}
	if((a[0]=='0'&&a.length()==1)||a[0]!='0')
	{
		y=a;
		return ten(y,10);
	}
}
void check(string cunqv[],int& num)
{
	for(int i=0;i<num;)								//检查符号 
	{
		if(cunqv[i]=="-"&&cunqv[i+1]=="-"&&cunqv[i+2]=="-") //1--1*-1 ->  1---1= ->1-1=
		{
			int x=num;
			num-=2;
			for(int j=i+1;j<x-2;j++)
			{
				cunqv[j]=cunqv[j+2];           
			}
			i=0;continue;
		}	
		if(cunqv[i]=="-"&&cunqv[i+1]=="-"&&cunqv[i+2]!="-")//  1--1= ,1+1= ,5-1=4
		{
			int x=num;
			num--;
			cunqv[i]="+";
			for(int j=i+1;j<x-1;j++)
			{
				cunqv[j]=cunqv[j+1];
			}
			i=0;continue;
		}
		if(((cunqv[i]=="+"&&cunqv[i+1]=="-")||(cunqv[i]=="-"&&cunqv[i+1]=="+"))&&cunqv[i+2]!="-"&&cunqv[i+2]!="+")
		{//1+-1
			int x=num;
			num--;
			cunqv[i]="-";
			for(int j=i+1;j<x-1;j++)
			{
				cunqv[j]=cunqv[j+1];
			}
			i=0;continue;
		}			
		if(cunqv[i]=="+"&&cunqv[i+1]=="-"&&cunqv[i+2]=="-")	//1+-1*-1 -> 1+--1
		{
			int x=num;
			num--;
			cunqv[i]="+";
			for(int j=i+1;j<x-2;j++)
			{
				cunqv[j]=cunqv[j+2];
			}
			i=0;continue;			
		}
		i++;		
	}
} 
int main(){
	string str;
	while(cin>>str)
	{
		string *cunqv=new string[100];
		int fore=0,back=0,cha,num=0;						//fore是前下标，back是后下标 
		for(int i=0;i<str.length();)
		{
			if(str[i]!='+'&&str[i]!='-'&&str[i]!='*'&&str[i]!='/')		//遇见非运算符则后下标加一 
			{
				back++;i++;
			}
			if(str[i]=='+'||str[i]=='-'||str[i]=='*'||str[i]=='/')		//遇见运算符 
			{
				if(i==0&&str[i]=='-')									//若str首字符是 -”则存 
				{
					cunqv[num]=str[i];
					num++;
					fore++;
					back++;
					i++;
				}
				if((str[i]=='+'||str[i]=='*'||str[i]=='/'||(str[i]=='-'&&i!=0))&&str[i+1]!='-')//若是在串中遇见运算符则存其前一段数据，
																								//再存这个运算符 
				{
					cha=back-fore;
					cunqv[num].append(str,fore,cha);
					fore=i+1;
					back=fore;
					num++;
					cunqv[num]=str[i];
					num++;
					i++;
				}
				if((str[i]=='+'||str[i]=='*'||str[i]=='/'||(str[i]=='-'&&i!=0))&&str[i+1]=='-')   //若加减一个负数 ，则两个符号都存进去 
				{
					cha=back-fore;
					cunqv[num].append(str,fore,cha);
					num++;
					cunqv[num]=str[i];
					num++;
					cunqv[num]=str[i+1];
					num++;
					fore=i+2;
					back=fore;
					i+=2;
				}
			}
			if(str[i]=='=')						//存“=”前一段的数据 
			{
				cha=back-fore;
				cunqv[num].append(str,fore,cha);
				num++;
				cunqv[num]='=';
				num++;
			}	
		}
		check(cunqv,num);
		for (int i=0;i<num;i++)				//转换运算式中的进制 
		{
			if(cunqv[i]!="+"&&cunqv[i]!="-"&&cunqv[i]!="/"&&cunqv[i]!="*"&&cunqv[i]!="=")
			cunqv[i]=jzzh(cunqv[i]);
		//	cout<<cunqv[i]<<endl; 
		}
		for(int i=0;i<num;)								//乘法   1*1=   1=
		{
			double fst,sec;
			if(cunqv[i]=="*")
			{
				if(cunqv[i+1]!="-")
				{
					int x=num;
					num-=2;
					fst=SS(cunqv[i-1]);
					sec=SS(cunqv[i+1]);
					fst*=sec; //cout<<fst<<endl;
					cunqv[i-1]=SS1(fst);//cout<<cunqv[i-1]<<endl;
					for(int j=i;j<x-2;j++)
					{
						cunqv[j]=cunqv[j+2];
					}//cout<<cunqv[i]<<endl;
					i=0;continue;				
				}
				else
				{
					int x=num;      //1*-1  -1=
					num-=2;
					fst=SS(cunqv[i-1]);
					sec=SS(cunqv[i+2]);
					fst*=sec; //cout<<fst<<endl;
					cunqv[i-1]="-";//cout<<cunqv[i-1]<<endl;
					cunqv[i]=SS1(fst);		//cout<<cunqv[i]<<endl;
					for(int j=i+1;j<x-2;j++)
					{
						cunqv[j]=cunqv[j+2];
					}
					i=0;continue;	
				}
			}
			if(cunqv[i]=="/")       //除法 
			{
				if(cunqv[i+1]!="-")
				{
					int x=num;
					num-=2;
					fst=SS(cunqv[i-1]);
					sec=SS(cunqv[i+1]);
					fst/=sec; 
					cunqv[i-1]=SS1(fst);
					for(int j=i;j<x-2;j++)
					{
						cunqv[j]=cunqv[j+2];
					}
					i=0;continue;			
				}
				else
				{
					int x=num;
					num-=2;
					fst=SS(cunqv[i-1]);
					sec=SS(cunqv[i+2]);
					fst/=sec; //cout<<fst<<endl;
					cunqv[i-1]="-";//cout<<cunqv[i-1]<<endl;
					cunqv[i]=SS1(fst);	//	cout<<cunqv[i]<<endl;
					for(int j=i+1;j<x-2;j++)
					{
						cunqv[j]=cunqv[j+2];
					}
					i=0;continue;	
				}
			}
			i++;
		}
		check(cunqv,num);
//	cout<<num<<endl;
//	for(int i=0;i<num;i++)
//	{
//		cout<<cunqv[i]<<endl;
//	}
		if(cunqv[0]!="-"&&cunqv[0]!="+")
		{
			for(int i=0;i<num;)								//加法   10*-1+1= 
			{
				double fst,sec;//     1+1= 1=
				if(cunqv[i]=="+")
				{
					int x=num;
					num-=2;
					fst=SS(cunqv[i-1]);
					sec=SS(cunqv[i+1]);
					fst+=sec; 
					cunqv[i-1]=SS1(fst);
					for(int j=i;j<x-2;j++)
					{
						cunqv[j]=cunqv[j+2];
					}
					i=0;
				}
				else i++;
			}
			for(int i=0;i<num;)								//减法   1-2= -1= 
			{
				double fst,sec;
				if(cunqv[i]=="-")
				{
					int x=num;
					fst=SS(cunqv[i-1]);
					sec=SS(cunqv[i+1]);
					if((fst-sec)>=0)
					{
						num-=2;
						fst-=sec;
						cunqv[i-1]=SS1(fst);
						for(int j=i;j<x-2;j++)
						{
							cunqv[j]=cunqv[j+2];
						}
						i=0;					
					}
					else				//1-3=  -2=
					{
						num-=1;
						sec-=fst;			
						cunqv[i-1]="-";  
						cunqv[i]=SS1(sec);
						for(int j=i+1;j<x-1;j++)
						{
							cunqv[j]=cunqv[j+1];
						}
						i=0;
						if(num==3)break;								
					}
				}
				else i++;
				check(cunqv,num);
			}				
		}
		else      //第一个字符是“-” 
		{
			if(cunqv[0]!="+")
			{
				for(int i=0;i<num;)
				{
					double fst,sec;				
					if(cunqv[0]=="-")
					{
						i++;continue;
					}		
					if(cunqv[i]=="+")     //-1+2=  1=    -3+1=   -2=
					{
						int x=num;
						fst=SS(cunqv[i-1]);
						sec=SS(cunqv[i+1]);
						if(cunqv[i-2]=="-")
						{
							if((fst-sec)>=0)
							{
								fst-=sec;
								cunqv[i-1]=SS1(fst);
								num-=2;
								for(int j=i;j<x-2;j++)
								{
									cunqv[j]=cunqv[j+2];
								}
							}
							else
							{
								sec-=fst;
								cunqv[i-2]=SS1(sec); 
								num-=3;
								for(int j=i-1;j<x-3;j++)
								{
									cunqv[j]=cunqv[j+3];
								}
							}	 
							i=0;
							if(num==3)break;					
						}					
					}
					if(cunqv[i]=="-")
					{                 //-1-3=   -4=
						int x=num;
						fst=SS(cunqv[i-1]);
						sec=SS(cunqv[i+1]);
						if(cunqv[i-2]=="-")	
						{
							fst+=sec;
							cunqv[i-1]=SS1(fst);
							num-=2;	
							for(int j=i;j<x-2;j++)
							{
								cunqv[j]=cunqv[j+2];
							}							
						}
						if(num==3)break;			
					}		
				}
			}
		}
		if(num==2)
		{
			cout<<cunqv[0]<<endl;
		}	
		if(num==3)
		{
			if(cunqv[0]=="-")
			{
				cout<<cunqv[0]<<cunqv[1]<<endl;
			}
			if(cunqv[0]=="+")
			{
				cout<<cunqv[1]<<endl; 
			}
		}	
		delete []cunqv;	
	} 
	return 0;
}
