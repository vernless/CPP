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
double SS(string a)					//stringתdouble 
{
	double des;
	stringstream ss;
	ss<<a;
	ss>>des;
	return des;
}
string SS1(double a)				//double תstring 
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
	for(len1=0;len1<a.length();len1++)//ͳ���������ֳ��� 
	{
		if(a[len1]=='.')
		break;
	} 
	int k=len1+1;//��kָ��С�����ֵ�һλ 
	int cetz=0,cetx=-1;
	long Sumz=0;
	double Sumx=0;
	for(  ;len1>0;len1--)//�������������ۼ� 
	{
		Sumz+=(a[len1-1]-'0')*pow(r,cetz);
		cetz++;
	}
	for(  ;k<a.length();k++)//С�����������ۼ� 
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
	for(int i=0;i<num;)								//������ 
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
		int fore=0,back=0,cha,num=0;						//fore��ǰ�±꣬back�Ǻ��±� 
		for(int i=0;i<str.length();)
		{
			if(str[i]!='+'&&str[i]!='-'&&str[i]!='*'&&str[i]!='/')		//���������������±��һ 
			{
				back++;i++;
			}
			if(str[i]=='+'||str[i]=='-'||str[i]=='*'||str[i]=='/')		//��������� 
			{
				if(i==0&&str[i]=='-')									//��str���ַ��� -����� 
				{
					cunqv[num]=str[i];
					num++;
					fore++;
					back++;
					i++;
				}
				if((str[i]=='+'||str[i]=='*'||str[i]=='/'||(str[i]=='-'&&i!=0))&&str[i+1]!='-')//�����ڴ�����������������ǰһ�����ݣ�
																								//�ٴ��������� 
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
				if((str[i]=='+'||str[i]=='*'||str[i]=='/'||(str[i]=='-'&&i!=0))&&str[i+1]=='-')   //���Ӽ�һ������ �����������Ŷ����ȥ 
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
			if(str[i]=='=')						//�桰=��ǰһ�ε����� 
			{
				cha=back-fore;
				cunqv[num].append(str,fore,cha);
				num++;
				cunqv[num]='=';
				num++;
			}	
		}
		check(cunqv,num);
		for (int i=0;i<num;i++)				//ת������ʽ�еĽ��� 
		{
			if(cunqv[i]!="+"&&cunqv[i]!="-"&&cunqv[i]!="/"&&cunqv[i]!="*"&&cunqv[i]!="=")
			cunqv[i]=jzzh(cunqv[i]);
		//	cout<<cunqv[i]<<endl; 
		}
		for(int i=0;i<num;)								//�˷�   1*1=   1=
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
			if(cunqv[i]=="/")       //���� 
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
			for(int i=0;i<num;)								//�ӷ�   10*-1+1= 
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
			for(int i=0;i<num;)								//����   1-2= -1= 
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
		else      //��һ���ַ��ǡ�-�� 
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
