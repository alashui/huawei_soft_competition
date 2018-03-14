#include "predict.h"
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
//"./ecs /xxx/TrainData.txt /xxx/input.txt /xxx/output.txt"
//         data               info                 resultfile

//你要完成的功能总入口
void predict_server(char * info[MAX_INFO_NUM], char * data[MAX_DATA_NUM], int data_num, char * filename)
{
	//需要输出的内容
	char * result_file = (char *)"17\n\n0 8 0 20";

	
		
	//读取要预测的flavor种类
	std::string flavors_input[15];
	int num_flavors_input(0);

	

	int i=0;
	for(;info[i][0]!='f';i++);
	for(;info[i][0]=='f';i++)
	{
		std::string fla_str;
		std::istringstream iss_f(info[i]);
		iss_f >> fla_str;
		flavors_input[num_flavors_input]=fla_str;
		std::cout <<flavors_input[num_flavors_input]<<std::endl;
		num_flavors_input++;				
	}
/*
	//flavor1-15
	for(int i=0;i<15;i++)
	{
		std::ostringstream oss_f;
	  	oss_f << "flavor" <<i+1;
		flavors_input[num_flavors_input]=oss_f.str();
		std::cout <<flavors_input[num_flavors_input]<<std::endl;
		num_flavors_input++;	
	}
*/	

	//统计每种flavor每天出现的次数
	//vector<vector<int>> record_mat;
	int record_array[MAX_DATA_NUM][num_flavors_input];
	
	std::string flavor_str,day_str,day_str_k_1;
	int day_index=0;
	int day_y,day_m,day_d;
	for (int k=0;k<data_num;k++)
	{
		//std::cout <<data[k]<<std::endl;
		
		std::string flavor_str,day_str;
		std::istringstream iss(data[k]);
		
		iss >> flavor_str;
		iss >> flavor_str;		
		iss >> day_str;
		
		if(k==0)
		{
			day_str_k_1=day_str;
			
			//得到日期年月日数值
			std::ostringstream oss_day_y;
	  	    oss_day_y<< day_str[0]<< day_str[1]<< day_str[2]<< day_str[3];
	  	    std::string string_temp=oss_day_y.str();
		    day_y=atoi(string_temp.c_str()); 
		    std::cout <<day_y<<std::endl;
		    
		    std::ostringstream oss_day_m;
		    oss_day_m<< day_str[5]<< day_str[6];
	  	    string_temp=oss_day_m.str();
		    day_m=atoi(string_temp.c_str()); 
		    std::cout <<day_m<<std::endl;
		    
		    std::ostringstream oss_day_d;
		    oss_day_d<< day_str[8]<< day_str[9];
	  	    string_temp=oss_day_d.str();
		    day_d=atoi(string_temp.c_str()); 
		    std::cout <<day_d<<std::endl;
			
		}
		//std::cout <<day_str<<std::endl;
		if(day_str!=day_str_k_1)  //计算两条记录之间相差的天数 
		{
			//得到日期年月日数值
			int day_y_temp,day_m_temp,day_d_temp;
			std::ostringstream oss_day_y;
	  	    oss_day_y<< day_str[0]<< day_str[1]<< day_str[2]<< day_str[3];
	  	    std::string string_temp=oss_day_y.str();
		    day_y_temp=atoi(string_temp.c_str()); 
		    //std::cout <<day_y<<std::endl;
		    
		    std::ostringstream oss_day_m;
		    oss_day_m<< day_str[5]<< day_str[6];
	  	    string_temp=oss_day_m.str();
		    day_m_temp=atoi(string_temp.c_str()); 
		    //std::cout <<day_m<<std::endl;
		    
		    std::ostringstream oss_day_d;
		    oss_day_d<< day_str[8]<< day_str[9];
	  	    string_temp=oss_day_d.str();
		    day_d_temp=atoi(string_temp.c_str()); 
		    //std::cout <<day_d<<std::endl;
		    
			if(day_y_temp==day_y && day_m_temp==day_m)
				day_index=day_index+(day_d_temp-day_d);
			else
				day_index++;	
				
			day_y=day_y_temp;	
		    day_m=day_m_temp;
		    day_d=day_d_temp;
			day_str_k_1=day_str;		
		}
		
		for(int flavor_index=0;flavor_index<num_flavors_input;flavor_index++)
		{
			if (flavors_input[flavor_index]==flavor_str)
			{				
				record_array[day_index][flavor_index]++;
				break;					
			}
		}					
	}

	//显示结果
	for(int iii=0;iii<=day_index;iii++)
	{
		for(int jjj=0;jjj<num_flavors_input;jjj++)
			std::cout << record_array[iii][jjj] <<' ';
		std::cout<<std::endl;	
	}
			
	//输出到txt文件
	//std::string dir_record("../record_1_15.txt");
	std::string dir_record("../record_with_input.txt");
	std::ofstream fout(dir_record);
	for(int iii=0;iii<=day_index;iii++)
	{
		for(int jjj=0;jjj<num_flavors_input;jjj++)
			fout << record_array[iii][jjj] <<' ';
		fout<<std::endl;	
	}
				 																		
	fout.close();

	//直接调用输出文件的方法输出到指定文件中(ps请注意格式的正确性，如果有解，第一行只有一个数据；第二行为空；第三行开始才是具体的数据，数据之间用一个空格分隔开)
	write_result(result_file, filename);
}


