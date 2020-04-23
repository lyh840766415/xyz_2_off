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

void main_2()
{
	ifstream tf("C:/Users/lyh84/Desktop/taizhou_uniform.xyz", std::ios::in);//打开文件
	srand(int(time(0)));
	char s[100] = { 0 };
	string v = "";
	string x = "";
	string y = "";
	string z = "";

	double x_tot = 0, y_tot = 0, z_tot = 0, f_tot = 0;
	double x_min = (numeric_limits<double>::max)();
	double x_max = -1*(numeric_limits<double>::max)();
	double y_min = (numeric_limits<double>::max)();
	double y_max = -1*(numeric_limits<double>::max)();
	double z_min = (numeric_limits<double>::max)();
	double z_max = -1*(numeric_limits<double>::max)();
	double f_min = (numeric_limits<double>::max)();
	double f_max = -1 * (numeric_limits<double>::max)();

	double x_mean, y_mean, z_mean, f_mean;

	vector<float> vx, vy, vz, vf;
	vector<float> vox, voy, voz, vof;
	int protect_height = 70;
	float min_height = -5, max_height = 70;
	float downsample_ratio = 0.05;

	cout << x_max << " , " << x_min << endl;
	int i = 0;
	while (!tf.eof())
	{
		tf.getline(s, sizeof(s));//逐行读取
		stringstream word(s);
		word >> x;
		word >> y;
		word >> z;
		word >> v;
		//string类型转float类型
		float a = atof(x.c_str());
		float b = atof(y.c_str());
		float c = atof(z.c_str());
		float d = atof(v.c_str());
		vx.push_back(a);
		vy.push_back(b);
		vz.push_back(c);
		vf.push_back(d);
		//cout << "x = " << a << ",y = " << b << ",z = " << c << endl;
		//x_tot += a;
		//y_tot += b;
		//z_tot += c;
		//x_max = a > x_max ? a : x_max;
		//y_max = b > y_max ? b : y_max;
		//z_max = c > z_max ? c : z_max;
		//x_min = a < x_min ? a : x_min;
		//y_min = b < y_min ? b : y_min;
		//z_min = c < z_min ? c : z_min;
		

		i++;
		if(i%100000 == 0)
			cout << "i = " << i << "x = " << a << ",y = " << b << ",z = " << c << endl;
	}
	//x_tot /= i;
	//y_tot /= i;
	//z_tot /= i;



	system("pause");

	x_max = *max_element(vx.begin(), vx.end());
	x_min = *min_element(vx.begin(), vx.end());
	x_tot = accumulate(vx.begin(), vx.end(), 0.0);

	y_max = *max_element(vy.begin(), vy.end());
	y_min = *min_element(vy.begin(), vy.end());
	y_tot = accumulate(vy.begin(), vy.end(), 0.0);

	z_max = *max_element(vz.begin(), vz.end());
	z_min = *min_element(vz.begin(), vz.end());
	z_tot = accumulate(vz.begin(), vz.end(), 0.0);

	f_max = *max_element(vf.begin(), vf.end());
	f_min = *min_element(vf.begin(), vf.end());
	f_tot = accumulate(vf.begin(), vf.end(), 0.0);

	x_mean = x_tot / (i*1.0);
	y_mean = y_tot / (i*1.0);
	z_mean = z_tot / (i*1.0);
	f_mean = f_tot / (i*1.0);

	cout << "x_max = " << x_max << " , x_min = " << x_min << " , x_tot = " << x_tot << " , x_mean = " << x_mean << endl;
	cout << "y_max = " << y_max << " , y_min = " << y_min << " , y_tot = " << y_tot << " , y_mean = " << y_mean << endl;
	cout << "z_max = " << z_max << " , z_min = " << z_min << " , z_tot = " << z_tot << " , z_mean = " << z_mean << endl;
	cout << "f_max = " << f_max << " , f_min = " << f_min << " , f_tot = " << f_tot << " , f_mean = " << f_mean << endl;


	system("pause");

	for (i = 0; i < vx.size(); i++)
	{
		if (vx[i] > x_mean + 10 || vx[i] < x_mean - 10)
			continue;
		if (vy[i] > y_mean + 10 || vy[i] < y_mean - 10)
			continue;

		if (vz[i] < protect_height) 
		{
			if ((rand() % 100) / 100.0 > downsample_ratio)
				continue;
		}
		vox.push_back(vx[i]);
		voy.push_back(vy[i]);
		voz.push_back(vz[i]);
		vof.push_back(vf[i]);
	}



	for (i = 0; i < vox.size(); i++)
	{
		vox[i] -= x_mean;
		voy[i] -= y_mean;
		voz[i] -= z_mean;

		if (i % 100000 == 0)
			cout << "i = " << i << "x = " << vx[i] << ",y = " << vy[i] << ",z = " << vz[i] << endl;
	}

	x_max = *max_element(vox.begin(), vox.end());
	x_min = *min_element(vox.begin(), vox.end());
	x_tot = accumulate(vox.begin(), vox.end(), 0.0);

	y_max = *max_element(voy.begin(), voy.end());
	y_min = *min_element(voy.begin(), voy.end());
	y_tot = accumulate(voy.begin(), voy.end(), 0.0);

	z_max = *max_element(voz.begin(), voz.end());
	z_min = *min_element(voz.begin(), voz.end());
	z_tot = accumulate(voz.begin(), voz.end(), 0.0);

	x_mean = x_tot / (i*1.0);
	y_mean = y_tot / (i*1.0);
	z_mean = z_tot / (i*1.0);

	cout << "x_max = " << x_max << " , x_min = " << x_min << " , x_tot = " << x_tot << " , x_mean = " << x_mean << endl;
	cout << "y_max = " << y_max << " , y_min = " << y_min << " , y_tot = " << y_tot << " , y_mean = " << y_mean << endl;
	cout << "z_max = " << z_max << " , z_min = " << z_min << " , z_tot = " << z_tot << " , z_mean = " << z_mean << endl;

	system("pause");

	
	ofstream of("taizhou_uniform.off", ios::ate);
	of << "COFF" << endl;
	of << vox.size() << " 0 0" << endl;
	for (i = 0; i < vox.size(); i++)
	{
		float color = voz[i];
		if (color > max_height || color < min_height)
			color = 0;
		
		color = fmod(color - min_height, 30) / 30;
		//color = (color - min_height) / (max_height - min_height);
		//color = sqrt(sqrt(color));
		of << vox[i] << " " << voy[i] << " " << voz[i] << " " << int(color * 255) << " " << int((1 - abs(color - 0.5) * 2) * 255) << " " << int((1 - color) * 255) << " 255" << endl;
		if (i % 100000 == 0)
			cout << "i = " << i << "x = " << vox[i] << ",y = " << voy[i] << ",z = " << voz[i] << endl;
	}

	tf.close();
	of.close();
	system("pause");

}