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
using namespace std;

void main_5()
{
	ifstream tf("D:\\laser\\cxyz_pointcloud_15000000pts.txt", std::ios::in);//打开文件

	srand(int(time(0)));
	char s[100] = { 0 };
	string v = "";
	string x = "";
	string y = "";
	string z = "";
	string r = "";
	string g = "";
	string b = "";
	string c = "";

	bool show_elevation = false;
	float bias = 0;
	float loop = 20;
	int ground_cnt = 0;
	vector<float> vx, vy, vz, vf, vr, vg, vb;
	//类别
	vector<int> vc;

	int i = 0;
	while (!tf.eof())
	{
		tf.getline(s, sizeof(s));//逐行读取
		stringstream word(s);
		word >> c;
		word >> x;
		word >> y;
		word >> z;
		word >> r;
		word >> g;
		word >> b;
		//string类型转float类型
		int c_c = atoi(c.c_str());
		float p_x = atof(x.c_str());
		float p_y = atof(y.c_str());
		float p_z = atof(z.c_str());
		float c_r = atof(r.c_str());
		float c_g = atof(g.c_str());
		float c_b = atof(b.c_str());
		float c_f = atof(v.c_str());

		vc.push_back(c_c);
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
	ofstream of("D:\\laser\\cxyz_pointcloud_15000000pts.off", ios::ate);
	of << "COFF" << endl;
	of << vx.size() << " 0 0" << endl;


	for (i = 0; i < vx.size(); i++)
	{
		if (vc[i] == 1) 
		{
			of << vx[i] << " " << vy[i] << " " << vz[i] << " " << "135" << " " << "87" << " " << "0" << " 255" << endl;
		}
		else if (vc[i] == 2)
		{
			of << vx[i] << " " << vy[i] << " " << vz[i] << " " << "255" << " " << "255" << " " << "255" << " 255" << endl;
		}
		else if (vc[i] == 3)
		{
			of << vx[i] << " " << vy[i] << " " << vz[i] << " " << "0" << " " << "255" << " " << "255" << " 255" << endl;
		}
		else if (vc[i] == 4)
		{
			of << vx[i] << " " << vy[i] << " " << vz[i] << " " << "255" << " " << "0" << " " << "0" << " 255" << endl;
		}
		//else if (vc[i] == 13)
		//{
		//	of << vx[i] << " " << vy[i] << " " << vz[i] << " " << "50" << " " << "50" << " " << "50" << " 255" << endl;
		//}
		//else if (vc[i] == 12)
		//{
		//	of << vx[i] << " " << vy[i] << " " << vz[i] << " " << "150" << " " << "250" << " " << "150" << " 255" << endl;
		//}
	}

	tf.close();
	of.close();
	system("pause");
}