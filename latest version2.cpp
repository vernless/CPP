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
void other(string a,double r)	//ʮ����תr���� 
{
	int temp,num1=0,x;
	x=static_cast<int>(r);
	long int Sumz=SS(a);
	int num[1000]={0},index;   //�������� 
	double Sumx=SS(a),temp2=0;
	Sumx-=static_cast<int>(Sumx);//С������ 
	for(index=0 ;Sumz>0;index++)//��������
	{
		temp=Sumz%x;
		num[index]=temp;
		Sumz/=x;
	}
	for(int i=index-1;i>=0;i--)//����������� 
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
	for(int i=0;i<6;i++)//С������ 
	{
		temp2=Sumx*x;
		num1=static_cast<int>(temp2);
		Sumx=temp2-num1;
		cout<<num1;
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
void cul(string str,double r)
{
	string *cunqv=new string[100];
	int fore=0,back=0,cha,num=0;					              	//fore��ǰ�±꣬back�Ǻ��±� 
	for(int i=0;i<str.length();)
	{
		if(str[i]!='+'&&str[i]!='-'&&str[i]!='*'&&str[i]!='/')		//���������������±��һ 
		{
			back++;i++;
		}
		if(str[i]=='+'||str[i]=='-'||str[i]=='*'||str[i]=='/')		//��������� 
		{
			if(i==0&&str[i]=='-')									//��str���ַ��� -��� 
			{
				cunqv[num]=str[i];
				num++;
				fore++;
				back++;
				i++;
			}
			if((str[i]=='+'||str[i]=='*'||str[i]=='/'||(str[i]=='-'&&i!=0))&&str[i+1]!='-')//�����ڴ�����������������ǰһ�����ݣ��ٴ���������
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
		}	
	}
	check(cunqv,num);
	for (int i=0;i<num;i++)				//ת������ʽ�еĽ��� 
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
					if(num==2)break;								
				}
			}
			else i++;check(cunqv,num);
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
	cout<<"1 		����ת��"<<endl; 
	cout<<"2 		��������"<<endl;	
	cout<<"3 		����"<<endl;
	cout<<"4 		���Ǻ���"<<endl;
	cout<<"5 		������"<<endl;	
	cout<<"6 		�Ƚ�"<<endl;
	cout<<"7 		��С������"<<endl;
	cout<<"8 		���Լ��"<<endl;
	cout<<"9 		һԪһ�μ����κ���"<<endl;
	cout<<"10 		ָ��"<<endl;
	cout<<"11 		����������"<<endl;
	cout<<"12 		����"<<endl<<endl; 
	int mode;
	cout<<"ѡ��ģʽ��"; 
	while(cin>>mode)
	{
		if(mode==12)break;
		switch(mode)
		{
			case 1://����ת�� 
				{
					double x,y;  					
					cout<<"����������Ľ��ƣ�";  
					cin>>x;
					cout<<"����Ŀ�����Ľ��ƣ�"; 
					cin>>y;								
					string str;
					cout<<"�����������";
					cin>>str;
					cout<<"���Ŀ������";
					other(ten(str,x),y);
					cout<<'\n'<<'\n'<<"ѡ��ģʽ��"; 
					break;
				}
			case 2:// �������� 
				{
					double x;
					cout<<"�����������Ľ��ƣ�" ;
					cin>>x;
					cout<<"��������ʽ(��1+1+*1/1=���ǵü�=)��";
					string str;
					cin>>str;
					cout<<"��������";
					cul(str,x);
					cout<<'\n'<<"ѡ��ģʽ��";
					break;
				}	 
			case 3://���� 
				{
					cout<<"����Ȼ����������log(x)������������������logx(y)"<<endl; 
					cout<<"���������"; 
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
						cout<<"���="<<log(x)<<endl;
					}
					else
					{
						cout<<"���="<<log(x)/log(y)<<endl;					
					}
					cout<<endl;
					cout<<'\n'<<"ѡ��ģʽ��";
					break;					
				} 
			case 4://���Ǻ��� 
				{	
					cout<<"���Ǻ�������sin(x),cos(y)�������ڵĲ�����λΪ�Ƕ�"<<endl;
					cout<<"�������Ǻ�����";
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
						cout<<"�����"<<sin(x)<<endl;			
					}
					if(str2=="sinh")
					{
						cout<<"�����"<<sinh(x)<<endl;
					}
					if(str2=="cos")
					{
						cout<<"�����"<<cos(x)<<endl;	
					}
					if(str2=="cosh")
					{
						cout<<"�����"<<cosh(x)<<endl;		
					}
					if(str2=="tan")
					{
						cout<<"�����"<<tan(x)<<endl;
					}
					if(str2=="tanh")
					{
						cout<<"�����"<<tanh(x)<<endl;		
					}					
					if(str2=="atan")
					{
						cout<<"�����"<<atan(x)<<endl;	
					}				
					if(str2=="asin")
					{
						cout<<"�����"<<asin(x)<<endl;	
					}					
					if(str2=="acos")
					{
						cout<<"�����"<<acos(x)<<endl;	
					}	
					cout<<endl;	
					cout<<'\n'<<"ѡ��ģʽ��";				
					break;								
				}
			case 5://�ݺ��� 
				{
					cout<<"������ָ������ɶ���������"<<endl; 
					string x,y;//����x��y����
					cout<<"����ָ����"; 
					cin>>y;
					cout<<"�����������Ϊ��out���������ǰģʽ)��";
					while(cin>>x)
					{	
						if(x=="out")break;
						if(x!="e")
						{
							double a,b;
							a=SS(x);
							b=SS(y);
							cout<<"�����"<<pow(a,b)<<endl;						
						}
						else
						{
							double a;
							a=SS(y);
							cout<<"�����"<<exp(a)<<endl;
						}
						cout<<"�����������Ϊ��out���������ǰģʽ��:";						
					}
					cout<<endl;
					cout<<'\n'<<"ѡ��ģʽ��";
					break; 
				}
			case 6://�Ƚ� 
				{
					string str1,str2,a,b;
					cout<<"�����һ������";	
					cin>>str1;
					cout<<"����ڶ�������";				 
					cin>>str2;
					if(str1[0]=='-'&&str2[0]!='-')
					{
						cout<<"�����<";
					}
					if(str2[0]=='-'&&str1[0]!='-')
					{
						cout<<"�����>";
					}
					if(str1[0]=='-'&&str2[0]=='-') //-1.1
					{
						a.append(str1,1,str1.length()-1);
						b.append(str2,1,str2.length()-1);
						if(a>b)
						{
							cout<<"�����<";
						}
						if(a<b)
						{
							cout<<"�����>";
						}
						if(a==b)cout<<"�����=";
					}	
					if(str1[0]!='-'&&str2[0]!='-')
					{
						a.append(str1,1,str1.length()-1);
						b.append(str2,1,str2.length()-1);
						if(a>b)
						{
							cout<<"�����>";
						}
						if(a<b)
						{
							cout<<"�����<";
						}
						if(a==b)cout<<"�����=";
					}
					cout<<endl;
					cout<<'\n'<<"ѡ��ģʽ��";
					break;
				}
			case 7://��С������ 
				{				
					long long a,b,min,max;
					cout<<"�����һ������";	
					cin>>a;
					cout<<"����ڶ�������";	
					cin>>b;
					min=a<b?a:b;
					max=a>b?a:b;
					if(max%min==0)
					{
						cout<<"���Ϊ��"<<max;
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
							cout<<"���Ϊ��"<<min*max;
						}
						else
						{
							cout<<"���Ϊ��"<<min*max/arr[j-1];								
						}
					}
					cout<<endl<<endl;
					cout<<"ѡ��ģʽ��";
					break;
				}
			case 8://���Լ�� 
				{
					long long  a,b;	
					cout<<"�����һ������";	
					cin>>a;
					cout<<"����ڶ�������";	
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
					cout <<"���Ϊ��"<<arr[j-1]<<endl;
					cout<<endl;
					cout<<"ѡ��ģʽ��";
					break;	
				}
			case 9:   //y=x+3;
				{
					cout<<"���뺯������Ϊһ�����磺a*x+b=����Ϊ�������磺a*x*x+b*x+c=����*���롰=������ȱ�٣�y=";
					string str0,str1,str2;
					cin>>str0;
					cout<<"����x(�����롰out���������ǰģʽ)=";
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
						cout<<"�����"; 
						cul(str1,10);
						cout<<"����x(�����롰out���������ǰģʽ)=";						
					}
					cout<<endl<<"ѡ��ģʽ��";					
					break;
				}
			case 10://ָ������ 
				{
					cout<<"���������"; 
					string x,y;
					cin>>x;
					cout<<"����ָ��(��Ϊ��out���������ǰģʽ)��"; 
					while(cin>>y)
					{
						if(y=="out")break;
						if(x!="e")
						{
							double a,b;
							a=SS(y);
							b=SS(x);
							cout<<"�����"<<pow(b,a)<<endl;						
						}
						else
						{
							double a;
							a=SS(y);
							cout<<"�����"<<exp(a)<<endl;
						}
						cout<<"����ָ��(��Ϊ��out���������ǰģʽ)��";						
					}
					cout<<endl<<"ѡ��ģʽ��";					
					break;
				}
			case 11://���������� 
				{
					cout<<"���뺯�������磺k/x=����/����=������ȱ�٣� y="; 
					string str0,str1,str2;
					cin>>str0;
					cout<<"����x(��Ϊ��out���������ǰģʽ)��";					
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
						cout<<"�����";
						cul(str1,10);
						cout<<"����ָ��(��Ϊ��out���������ǰģʽ)��";
					}
					cout<<endl<<"ѡ��ģʽ��";
					break;					
				}
			default:break;		
		}
		continue;
	}
	return 0;
}
