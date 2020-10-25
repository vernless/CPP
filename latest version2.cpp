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
void other(string a,double r)	//十进制转r进制 
{
	int temp,num1=0,x;
	x=static_cast<int>(r);
	long int Sumz=SS(a);
	int num[1000]={0},index;   //储存整数 
	double Sumx=SS(a),temp2=0;
	Sumx-=static_cast<int>(Sumx);//小数部分 
	for(index=0 ;Sumz>0;index++)//整数部分
	{
		temp=Sumz%x;
		num[index]=temp;
		Sumz/=x;
	}
	for(int i=index-1;i>=0;i--)//输出整数部分 
	{
		if(num[i]==10)
		cout<<"a";
		else if(num[i]==11)
		cout<<"b";
		else if(num[i]==12)
		cout<<"c";
		else if(num[i]==13)
		cout<<"d";
		else if(num[i]==14)
		cout<<"e";
		else if(num[i]==15)
		cout<<"f";
		else  cout<<num[i];
	}
	cout<<"."; 
	for(int i=0;i<6;i++)//小数部分 
	{
		temp2=Sumx*x;
		num1=static_cast<int>(temp2);
		Sumx=temp2-num1;
		cout<<num1;
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
void cul(string str,double r)
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
			if(i==0&&str[i]=='-')									//若str首字符是 -则存 
			{
				cunqv[num]=str[i];
				num++;
				fore++;
				back++;
				i++;
			}
			if((str[i]=='+'||str[i]=='*'||str[i]=='/'||(str[i]=='-'&&i!=0))&&str[i+1]!='-')//若是在串中遇见运算符则存其前一段数据，再存这个运算符
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
		cunqv[i]=ten(cunqv[i],r);
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
			else i++;check(cunqv,num);
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
	cout<<"1 		进制转换"<<endl; 
	cout<<"2 		四则运算"<<endl;	
	cout<<"3 		对数"<<endl;
	cout<<"4 		三角函数"<<endl;
	cout<<"5 		幂运算"<<endl;	
	cout<<"6 		比较"<<endl;
	cout<<"7 		最小公倍数"<<endl;
	cout<<"8 		最大公约数"<<endl;
	cout<<"9 		一元一次及二次函数"<<endl;
	cout<<"10 		指数"<<endl;
	cout<<"11 		反比例函数"<<endl;
	cout<<"12 		结束"<<endl<<endl; 
	int mode;
	cout<<"选择模式："; 
	while(cin>>mode)
	{
		if(mode==12)break;
		switch(mode)
		{
			case 1://进制转换 
				{
					double x,y;  					
					cout<<"输入操作数的进制：";  
					cin>>x;
					cout<<"输入目标数的进制："; 
					cin>>y;								
					string str;
					cout<<"输入操作数：";
					cin>>str;
					cout<<"输出目标数：";
					other(ten(str,x),y);
					cout<<'\n'<<'\n'<<"选择模式："; 
					break;
				}
			case 2:// 四则运算 
				{
					double x;
					cout<<"输入运算数的进制：" ;
					cin>>x;
					cout<<"输入运算式(如1+1+*1/1=，记得加=)：";
					string str;
					cin>>str;
					cout<<"运算结果：";
					cul(str,x);
					cout<<'\n'<<"选择模式：";
					break;
				}	 
			case 3://对数 
				{
					cout<<"求自然对数则输入log(x)，求其他对数则输入logx(y)"<<endl; 
					cout<<"输入对数："; 
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
						cout<<"结果="<<log(x)<<endl;
					}
					else
					{
						cout<<"结果="<<log(x)/log(y)<<endl;					
					}
					cout<<endl;
					cout<<'\n'<<"选择模式：";
					break;					
				} 
			case 4://三角函数 
				{	
					cout<<"三角函数形如sin(x),cos(y)，括号内的参数单位为角度"<<endl;
					cout<<"输入三角函数：";
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
						cout<<"结果："<<sin(x)<<endl;			
					}
					if(str2=="sinh")
					{
						cout<<"结果："<<sinh(x)<<endl;
					}
					if(str2=="cos")
					{
						cout<<"结果："<<cos(x)<<endl;	
					}
					if(str2=="cosh")
					{
						cout<<"结果："<<cosh(x)<<endl;		
					}
					if(str2=="tan")
					{
						cout<<"结果："<<tan(x)<<endl;
					}
					if(str2=="tanh")
					{
						cout<<"结果："<<tanh(x)<<endl;		
					}					
					if(str2=="atan")
					{
						cout<<"结果："<<atan(x)<<endl;	
					}				
					if(str2=="asin")
					{
						cout<<"结果："<<asin(x)<<endl;	
					}					
					if(str2=="acos")
					{
						cout<<"结果："<<acos(x)<<endl;	
					}	
					cout<<endl;	
					cout<<'\n'<<"选择模式：";				
					break;								
				}
			case 5://幂函数 
				{
					cout<<"先输入指数，后可多次输入底数"<<endl; 
					string x,y;//计算x的y次幂
					cout<<"输入指数："; 
					cin>>y;
					cout<<"输入底数（若为“out”则结束当前模式)：";
					while(cin>>x)
					{	
						if(x=="out")break;
						if(x!="e")
						{
							double a,b;
							a=SS(x);
							b=SS(y);
							cout<<"结果："<<pow(a,b)<<endl;						
						}
						else
						{
							double a;
							a=SS(y);
							cout<<"结果："<<exp(a)<<endl;
						}
						cout<<"输入底数（若为“out”则结束当前模式）:";						
					}
					cout<<endl;
					cout<<'\n'<<"选择模式：";
					break; 
				}
			case 6://比较 
				{
					string str1,str2,a,b;
					cout<<"输入第一个数：";	
					cin>>str1;
					cout<<"输入第二个数：";				 
					cin>>str2;
					if(str1[0]=='-'&&str2[0]!='-')
					{
						cout<<"结果：<";
					}
					if(str2[0]=='-'&&str1[0]!='-')
					{
						cout<<"结果：>";
					}
					if(str1[0]=='-'&&str2[0]=='-') //-1.1
					{
						a.append(str1,1,str1.length()-1);
						b.append(str2,1,str2.length()-1);
						if(a>b)
						{
							cout<<"结果：<";
						}
						if(a<b)
						{
							cout<<"结果：>";
						}
						if(a==b)cout<<"结果：=";
					}	
					if(str1[0]!='-'&&str2[0]!='-')
					{
						a.append(str1,1,str1.length()-1);
						b.append(str2,1,str2.length()-1);
						if(a>b)
						{
							cout<<"结果：>";
						}
						if(a<b)
						{
							cout<<"结果：<";
						}
						if(a==b)cout<<"结果：=";
					}
					cout<<endl;
					cout<<'\n'<<"选择模式：";
					break;
				}
			case 7://最小公倍数 
				{				
					long long a,b,min,max;
					cout<<"输入第一个数：";	
					cin>>a;
					cout<<"输入第二个数：";	
					cin>>b;
					min=a<b?a:b;
					max=a>b?a:b;
					if(max%min==0)
					{
						cout<<"结果为："<<max;
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
							cout<<"结果为："<<min*max;
						}
						else
						{
							cout<<"结果为："<<min*max/arr[j-1];								
						}
					}
					cout<<endl<<endl;
					cout<<"选择模式：";
					break;
				}
			case 8://最大公约数 
				{
					long long  a,b;	
					cout<<"输入第一个数：";	
					cin>>a;
					cout<<"输入第二个数：";	
					cin>>b;
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
					cout <<"结果为："<<arr[j-1]<<endl;
					cout<<endl;
					cout<<"选择模式：";
					break;	
				}
			case 9:   //y=x+3;
				{
					cout<<"输入函数（若为一次则如：a*x+b=，若为二次则如：a*x*x+b*x+c=。“*”与“=”不可缺少）y=";
					string str0,str1,str2;
					cin>>str0;
					cout<<"输入x(若输入“out”则结束当前模式)=";
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
						cout<<"结果："; 
						cul(str1,10);
						cout<<"输入x(若输入“out”则结束当前模式)=";						
					}
					cout<<endl<<"选择模式：";					
					break;
				}
			case 10://指数函数 
				{
					cout<<"输入底数："; 
					string x,y;
					cin>>x;
					cout<<"输入指数(若为“out”则结束当前模式)："; 
					while(cin>>y)
					{
						if(y=="out")break;
						if(x!="e")
						{
							double a,b;
							a=SS(y);
							b=SS(x);
							cout<<"结果："<<pow(b,a)<<endl;						
						}
						else
						{
							double a;
							a=SS(y);
							cout<<"结果："<<exp(a)<<endl;
						}
						cout<<"输入指数(若为“out”则结束当前模式)：";						
					}
					cout<<endl<<"选择模式：";					
					break;
				}
			case 11://反比例函数 
				{
					cout<<"输入函数（形如：k/x=。“/”“=”不可缺少） y="; 
					string str0,str1,str2;
					cin>>str0;
					cout<<"输入x(若为“out”则结束当前模式)：";					
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
						cout<<"结果：";
						cul(str1,10);
						cout<<"输入指数(若为“out”则结束当前模式)：";
					}
					cout<<endl<<"选择模式：";
					break;					
				}
			default:break;		
		}
		continue;
	}
	return 0;
}
