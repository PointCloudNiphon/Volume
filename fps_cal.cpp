#include<iostream> 
#include<fstream>
#include<time.h> 
#include<stdio.h> 
#include<string>

using namespace std;

string get_string_time()
{
	time_t t = time(0); 
	char tmp[64]; 
	strftime( tmp, sizeof(tmp), "%Y/%m/%d %X ",localtime(&t) );
	
	return string(tmp);
}
int new_minute(string time_before,string now)//判断是不是新的一分钟
{
	//cout<<now<<"s："<<now[18]<<endl;
	return (time_before[18]!=now[18]);
} 
int write_txt(string dst,string &before_time,int &counter)
{
	const char* dst_char=dst.c_str();
	ofstream out(dst_char,ios::out|ios::app);
	if(!out)
	{
		cout<<"read error!"<<endl;
		return -1;
	}
	string info=get_string_time();
	before_time=info;
	string counter_s=to_string(counter);	
	out<<info+"counter:"+counter_s<<endl;
	counter=0;	
	out.close();
}
void fps_cal(string filename,string &time_initializer,int &fps_counter)
{
	fps_counter++; 
	string now=get_string_time(); 
	if(new_minute(now,time_initializer))
		write_txt(filename,time_initializer,fps_counter);	
}
int main()
{
	string dst="C:\\Users\\Administrator\\Desktop\\out.txt";
	string time_initializer("----------------------------");//记录上一次存储的时间 ，放在循环外,初始值最好不是时间戳 
	int counter = 0;
	while(1)
	{
		fps_cal(dst,time_initializer,counter);
	 } 
		
	return 0;
}
