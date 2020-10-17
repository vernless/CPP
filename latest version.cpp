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
#define PI 3.1415926 
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
		{
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
void cul(string str)
{
	string *cunqv=new string[100];
	int fore=0,back=0,cha,num=0;					              	//fore是前下标，back是后下标 
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
		}	
	}
	check(cunqv,num);
	for (int i=0;i<num;i++)				//转换运算式中的进制 
	{
		if(cunqv[i]!="+"&&cunqv[i]!="-"&&cunqv[i]!="/"&&cunqv[i]!="*")
		cunqv[i]=jzzh(cunqv[i]);
	}
	for(int i=0;i<num;)					
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
				fst*=sec; 
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
				fst*=sec; 
				cunqv[i-1]="-";
				cunqv[i]=SS1(fst);	
				for(int j=i+1;j<x-2;j++)
				{
					cunqv[j]=cunqv[j+2];
				}
				i=0;continue;	
			}
		}
		if(cunqv[i]=="/")   
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
				fst/=sec; 
				cunqv[i-1]="-";
				cunqv[i]=SS1(fst);	
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
	if(cunqv[0]!="-"&&cunqv[0]!="+")
	{
		for(int i=0;i<num;)		
		{
			double fst,sec;
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
					if(num==2)break;								
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
						if(num==2)break;					
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
					if(num==2)break;			
				}		
			}
		}
	}
	if(num==1)
	{
		cout<<cunqv[0]<<endl;
	}	
	if(num==2)
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
int main(int argc, char** argv) {
	cout<<"1 进制转换"<<endl; 
	cout<<"2 四则运算"<<endl;	
	cout<<"3 对数"<<endl;
	cout<<"4 三角函数"<<endl;
	cout<<"5 幂运算"<<endl;	
	cout<<"6 比较"<<endl;
	cout<<"7 最小公倍数"<<endl;
	cout<<"8 最大公约数"<<endl;
	cout<<"9 一元n次函数"<<endl;
	cout<<"10 指数"<<endl;
	cout<<"11 反比例函数"<<endl;
	cout<<"12 结束"<<endl; 
	int mode;
	while(cin>>mode)
	{
		if(mode==12)break;
		switch(mode)
		{
			case 1://进制转换 
				{
					cout<<"先输入进制，后输入所求数"<<endl; 
					double x;  
					cin>>x;
					string str;
					cin>>str;
					cout<<"="<<ten(str,x)<<endl;
					cout<<endl; 
					break;
				}
			case 2:// 四则运算 
				{
					string str;
					cin>>str;
					cul(str);
					cout<<endl;
					break;
				}	 
			case 3://对数 
				{
					string str,str1,str2; //log(x)  log10(x)  logx(y)
					cin>>str;
					int fore,back;
					double x,y;
					for(int i=0;i<str.length();i++)
					{
						if(str[i]=='(')
						{
							fore=i+1;					
						}
						if(str[i]==')')
						{
							back=i-1;					
						}					
					}
					str1.append(str,fore,back-fore+1);	//log(2)  log4(3)
					str2.append(str,3,fore-4);
					x=SS(str1);	y=SS(str2);			
					if(str[3]=='(')
					{
						cout<<"="<<log(x)<<endl;
					}
					else
					{
						cout<<"="<<log(x)/log(y)<<endl;					
					}
					cout<<endl;
					break;					
				} 
			case 4://三角函数 
				{	
					string str,str1,str2;
					cin>>str;
					int fore,back;
					double x;
					for(int i=0;i<str.length();i++)
					{
						if(str[i]=='(')
						{
							fore=i+1;					
						}
						if(str[i]==')')
						{
							back=i-1;					
						}					
					}
					str1.append(str,fore,back-fore+1);	
					str2.append(str,0,fore-1);
					x=SS(str1)*PI/180.0d;	
					if(str2=="sin")
					{
						cout<<"="<<sin(x)<<endl;			
					}
					if(str2=="sinh")
					{
						cout<<"="<<sinh(x)<<endl;
					}
					if(str2=="cos")
					{
						cout<<"="<<cos(x)<<endl;	
					}
					if(str2=="cosh")
					{
						cout<<"="<<cosh(x)<<endl;		
					}
					if(str2=="tan")
					{
						cout<<"="<<tan(x)<<endl;
					}
					if(str2=="tanh")
					{
						cout<<"="<<tanh(x)<<endl;		
					}					
					if(str2=="atan")
					{
						cout<<"="<<atan(x)<<endl;	
					}				
					if(str2=="asin")
					{
						cout<<"="<<asin(x)<<endl;	
					}					
					if(str2=="acos")
					{
						cout<<"="<<acos(x)<<endl;	
					}	
					cout<<endl;					
					break;								
				}
			case 5://幂函数 
				{
					cout<<"先输入指数，后可多次输入底数"<<endl; 
					string x,y;//计算x的y次幂
					cin>>y;
					while(cin>>x)
					{
						if(x=="out")break;
						if(x!="e")
						{
							double a,b;
							a=SS(x);
							b=SS(y);
							cout<<"="<<pow(a,b)<<endl;						
						}
						else
						{
							double a;
							a=SS(x);
							cout<<"="<<exp(a)<<endl;
						}						
					}
					cout<<endl;
					break; 
				}
			case 6://比较 
				{
					cout<<"输入所求的两个数"<<endl;				 
					string str1,str2,a,b;
					cin>>str1>>str2;
					if(str1[0]=='-'&&str2[0]!='-')
					{
						cout<<"<";
					}
					if(str2[0]=='-'&&str1[0]!='-')
					{
						cout<<">";
					}
					if(str1[0]=='-'&&str2[0]=='-') //-1.1
					{
						a.append(str1,1,str1.length()-1);
						b.append(str2,1,str2.length()-1);
						if(a>b)
						{
							cout<<"<";
						}
						if(a<b)
						{
							cout<<">";
						}
						if(a==b)cout<<"=";
					}	
					if(str1[0]!='-'&&str2[0]!='-')
					{
						a.append(str1,1,str1.length()-1);
						b.append(str2,1,str2.length()-1);
						if(a>b)
						{
							cout<<">";
						}
						if(a<b)
						{
							cout<<"<";
						}
						if(a==b)cout<<"=";
					}
					cout<<endl<<endl;
					break;
				}
			case 7://最小公倍数 
				{
					cout<<"输入所求的两个数"<<endl;					
					long long a,b,min,max;
					cin>>a>>b;
					min=a<b?a:b;
					max=a>b?a:b;
					if(max%min==0)
					{
						cout<<max;
					}
					else
					{
						long long arr[10000]={0};
						long long j=0;					
						for (int i=1;i<=max/2;i++)
						{
							if(a%i==0&&b%i==0)
							{
								arr[j]=i;j++ ;
							}		
						}
						if(arr[j-1]==1)
						{
							cout<<"="<<min*max;
						}
						else
						{
							cout<<"="<<min*max/arr[j-1];								
						}
					}
					cout<<endl<<endl;
					break;
				}
			case 8://最大公约数 
				{
					cout<<"输入所求的两个数"<<endl;
					long long  a,b;	
					cin>>a>>b;
					long long arr[10000]={0},max;
					long long j=0;
					max=a>b?a:b;					
					for (int i=1;i<=max/2;i++)
					{
						if(a%i==0&&b%i==0)
						{
							arr[j]=i;j++ ;
						}		
					}	
					cout <<"="<<arr[j-1]<<endl;
					cout<<endl;
					break;	
				}
			case 9:   //y=x+3;
				{
					cout<<"y=";
					string str0,str1,str2;
					cin>>str0;
					cout<<"输入x"<<endl;
					while(cin>>str2)
					{
						str1=str0;
						if(str2=="out")break;
						double a;
						a=SS(str2);
						for(int i=0;i<str1.length();i++)
						{
							if(str1[i]=='x')
							str1[i]=a+'0';
						}
						cul(str1);
					}
					break;
				}
			case 10://指数函数 
				{
					cout<<"先输入底数，后可多次输入指数"<<endl; 
					string x,y;
					cin>>x;
					while(cin>>y)
					{
						if(y=="out")break;
						if(x!="e")
						{
							double a,b;
							a=SS(y);
							b=SS(x);
							cout<<"="<<pow(b,a)<<endl;						
						}
						else
						{
							double a;
							a=SS(y);
							cout<<"="<<exp(a)<<endl;
						}						
					}
					cout<<endl;
					break;
				}
			case 11://反比例函数 
				{
					cout<<"y=";
					string str0,str1,str2;
					cin>>str0;
					while(cin>>str2)
					{
						str1=str0;
						if(str2=="out")break;
						double a;
						a=SS(str2);
						for(int i=0;i<str1.length();i++)
						{
							if(str1[i]=='x')
							str1[i]=a+'0';
						}
						cul(str1);
					}
					cout<<endl;
					break;					
				}
			default:break;		
		}
		continue;
	}
	return 0;
}
