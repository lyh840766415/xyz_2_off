#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <limits>
#include <algorithm>
#include <numeric>
#include <cstdlib>
#include <ctime>
#include <math.h>
#include <map>
#include "Config.h"
using namespace std;

void main_1()
{
	std::map<std::string, std::string> serial_cfg;
	ReadConfig("config.txt", serial_cfg);
	std::cout << "Powerline = " << serial_cfg["powerline"] << std::endl;
	std::cout << "Ground = " << serial_cfg["ground"] << std::endl;
	std::cout << "savedfile = " << serial_cfg["output"] << std::endl;


	if (atoi(serial_cfg["elevation"].c_str()))
		std::cout << "show elevation" << std::endl;

	if (atoi(serial_cfg["powerline_no_color"].c_str()))
		std::cout << "powerline_no_color" << std::endl;

	std::cout << "bias = " << atof(serial_cfg["bias"].c_str()) << std::endl;
	std::cout << "loop = " << atof(serial_cfg["loop"].c_str()) << std::endl;

	system("pause");

	ifstream tf(serial_cfg["ground"], std::ios::in);//打开文件
	ifstream pw(serial_cfg["powerline"], std::ios::in);//打开文件

	srand(int(time(0)));
	char s[100] = { 0 };
	string v = "";
	string x = "";
	string y = "";
	string z = "";
	string r = "";
	string g = "";
	string b = "";

	int show_elevation = atoi(serial_cfg["elevation"].c_str());
	int powerline_no_color = atoi(serial_cfg["powerline_no_color"].c_str());
	float bias = atof(serial_cfg["bias"].c_str());
	float loop = atof(serial_cfg["loop"].c_str());
	int ground_cnt = 0;
	vector<float> vx, vy, vz, vf, vr, vg, vb;

	int i = 0;
	while (!tf.eof())
	{
		tf.getline(s, sizeof(s));//逐行读取
		stringstream word(s);
		word >> x;
		word >> y;
		word >> z;
		word >> r;
		word >> g;
		word >> b;
		word >> v;
		//string类型转float类型
		float p_x = atof(x.c_str());
		float p_y = atof(y.c_str());
		float p_z = atof(z.c_str());
		float c_r = atof(r.c_str());
		float c_g = atof(g.c_str());
		float c_b = atof(b.c_str());

		float c_f = atof(v.c_str());
		vx.push_back(p_x);
		vy.push_back(p_y);
		vz.push_back(p_z);
		vf.push_back(c_f);
		vr.push_back(c_r);
		vg.push_back(c_g);
		vb.push_back(c_b);

		i++;
		if (i % 100000 == 0)
			cout << "i = " << i << "x = " << p_x << ",y = " << p_y << ",z = " << p_z << "r = " << c_r << ",g = " << c_g << ",b = " << c_b << endl;
	}
	cout << "Ground Read" << endl;
	ground_cnt = vx.size();
	system("pause");


	while (!pw.eof())
	{
		pw.getline(s, sizeof(s));//逐行读取
		stringstream word(s);
		word >> x;
		word >> y;
		word >> z;
		word >> r;
		word >> g;
		word >> b;
		word >> v;
		//string类型转float类型
		float p_x = atof(x.c_str());
		float p_y = atof(y.c_str());
		float p_z = atof(z.c_str());
		float c_r = atof(r.c_str());
		float c_g = atof(g.c_str());
		float c_b = atof(b.c_str());

		float c_f = atof(v.c_str());
		vx.push_back(p_x);
		vy.push_back(p_y);
		vz.push_back(p_z);
		vf.push_back(c_f);
		vr.push_back(c_r);
		vg.push_back(c_g);
		vb.push_back(c_b);

		i++;
		if (i % 100000 == 0)
			cout << "i = " << i << "x = " << p_x << ",y = " << p_y << ",z = " << p_z << "r = " << c_r << ",g = " << c_g << ",b = " << c_b << endl;
	}
	cout << "Powerline Read" << endl;
	system("pause");

	double x_tot = 0, y_tot = 0, z_tot = 0, x_mean = 0, y_mean = 0, z_mean = 0;
	x_tot = accumulate(vx.begin(), vx.end(), 0.0);
	y_tot = accumulate(vy.begin(), vy.end(), 0.0);
	z_tot = accumulate(vz.begin(), vz.end(), 0.0);

	x_mean = x_tot / (i*1.0);
	y_mean = y_tot / (i*1.0);
	z_mean = z_tot / (i*1.0);

	cout << " x_tot = " << x_tot << " , x_mean = " << x_mean << endl;
	cout << " y_tot = " << y_tot << " , y_mean = " << y_mean << endl;
	cout << " z_tot = " << z_tot << " , z_mean = " << z_mean << endl;

	system("pause");
	ofstream of(serial_cfg["output"], ios::ate);
	of << "COFF" << endl;
	of << vx.size() << " 0 0" << endl;

	if (show_elevation) 
	{
		for (i = 0; i < vx.size(); i++)
		{
			float color = vz[i];
			if (color > bias)
				color = fmod(color - bias, loop) / loop;
			else 
				color = 1 - (fmod(bias - color, loop) / loop);

			if (i > ground_cnt)
			{
				if (powerline_no_color) 
				{
					color = 0;
					of << vx[i] << " " << vy[i] << " " << vz[i] << " " << int(color * 255) << " " << int(color * 255) << " " << int(color * 255) << " 255" << endl;
				}
				else 
				{
					of << vx[i] << " " << vy[i] << " " << vz[i] << " " << int(color * 255) << " " << int((1 - abs(color - 0.5) * 2) * 255) << " " << int((1 - color) * 255) << " 255" << endl;
				}

			}
			else 
			{
				of << vx[i] << " " << vy[i] << " " << vz[i] << " " << vr[i] << " " << vg[i] << " " << vb[i] << " 255" << endl;
			}
			if (i % 100000 == 0)
				cout << "i = " << i << "x = " << vx[i] << ",y = " << vy[i] << ",z = " << vz[i] << endl;
		}
	}
	else 
	{
		for (i = 0; i < vx.size(); i++)
		{

			if (i > ground_cnt && powerline_no_color )
			{
				float color = 0;
				of << vx[i] << " " << vy[i] << " " << vz[i] << " " << int(color * 255) << " " << int(color * 255) << " " << int(color * 255) << " 255" << endl;
				//of << vx[i] << " " << vy[i] << " " << vz[i] << " " << vr[i] << " " << vg[i] << " " << vb[i] << " 255" << endl;
			}
			//if (i > ground_cnt)
			//{
			//	float color = 0;
			//	of << vx[i] << " " << vy[i] << " " << vz[i] << " " << vr[i] << " " << vg[i] << " " << vb[i] << " 255" << endl;
			//	//of << vx[i] << " " << vy[i] << " " << vz[i] << " " << vr[i] << " " << vg[i] << " " << vb[i] << " 255" << endl;
			//}
			else
			{
				of << vx[i] << " " << vy[i] << " " << vz[i] << " " << vr[i] << " " << vg[i] << " " << vb[i] << " 255" << endl;
			}
			//else 
			//{
			//	float color = vz[i];
			//	if (color > bias)
			//		color = fmod(color - bias, loop) / loop;
			//	else
			//		color = 1 - (fmod(bias - color, loop) / loop);
			//	of << vx[i] << " " << vy[i] << " " << vz[i] << " " << int(color * 255) << " " << int((1 - abs(color - 0.5) * 2) * 255) << " " << int((1 - color) * 255) << " 255" << endl;
			//}
			if (i % 100000 == 0)
				cout << "i = " << i << "x = " << vx[i] << ",y = " << vy[i] << ",z = " << vz[i] << endl;
		}
	}
	
	tf.close();
	pw.close();
	of.close();
	system("pause");
}