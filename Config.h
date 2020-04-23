#pragma once
/****************************************************************************
*   ����:  2014-12-5
*   Ŀ��:  ��ȡ�����ļ�����Ϣ����map����ʽ����
*   Ҫ��:  �����ļ��ĸ�ʽ����#��Ϊ��ע�ͣ����õ���ʽ��key = value���м���п�
��Ҳ��û�пո�
*****************************************************************************/
#define COMMENT_CHAR '#'
#include <string>
#include <map>

//using namespace std;

bool ReadConfig(const std::string & filename, std::map<std::string, std::string> & m);

void PrintConfig(const std::map<std::string, std::string> & m);
