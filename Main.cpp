// ConsoleApplication1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <io.h>
#include <fcntl.h>
#include <string>
#include<string.h>
#include<Windows.h>
#include <windows.h>
#include <assert.h>
#include<vector>
#include <sstream>
#include <fstream>
#include <cstdlib>
#include<map>
#include <codecvt>
#include <locale>
#define ff first
#define ss second
using namespace std;

//

void split_substr(wstring s, vector<wstring>&mvt,int &k)
{
	int pos1 = 0, pos2 = 0;
	for (int i = 0; i < s.size(); i++)
	{
		if (s[i] == L','  || s[i] == L'?')
			s.erase(i, 1);
		if (s[i] == L'.')
		{
			s.erase(i, 1);
			k = mvt.size()+1;
		}
		if (s[i] == ' ')
		{
			pos2 = i;
			mvt.push_back(s.substr(pos1, pos2 - pos1));
			pos1 = pos2 + 1;
		}
	}
	mvt.push_back(s.substr(pos1, s.size() - pos1));
}
void recognize_obj(vector<wstring>mvt, int k, wstring &obj,wstring &unit)
{
	wstring temp1,temp2;
	int i;
	for (i = k + 1; i < mvt.size(); i++)
	{	
		//trước từ "có bao nhiêu"
		if (0 == (wcscmp(mvt[i].c_str(), (L"có"))) || 0 == (wcscmp(mvt[i].c_str(), (L"trong"))) || (0 == (wcscmp(mvt[i].c_str(), (L"bao"))) && 0 == (wcscmp(mvt[i + 1].c_str(), (L"nhiêu")))))
		{
			break;
		}
		temp1.append(mvt[i] + L" ");
	}
	//lấy đơn vị
	for (i=i+1;i < mvt.size();i++)
	{
		if ( (0 == (wcscmp(mvt[i].c_str(), (L"bao")))) ||(0 == (wcscmp(mvt[i].c_str(), L"nhiêu"))) || (0 == (wcscmp(mvt[i].c_str(), L"mấy"))))
			continue;
		temp2.append(mvt[i] + L" ");
	}
	obj=temp1;
	unit = temp2;
}
void recognize_number(vector<wstring>mvt, vector<pair<int,int>>&num,int k)
{
	int n = 0;;
	for (int i = 0; i < mvt.size(); i++)
	{
		int b = (_wtoi(mvt[i].c_str()));
		if (b)
		{	
			if (i <= k)
			{
				num.push_back(make_pair(b,0));
			}
			else
				num.push_back(make_pair(b,1));
		}
	}
}
void print_answer_solution(wstring unit, wstring obj,vector<pair<int, int>>num,int chiso)
{
	wcout << "\n\n\t\t\t\t" << L"Lời Giải:\n\n";
	wcout << L"\t\t\tSố " << unit << obj << L"là: \n";
	//cộng 0 
	//trừ 1
	//nhân 2
	//chia 3
	int a =1, b = 1;
	if (num.size() == 0)
		wcout << L"LỖI hàm in số chứ số";
	else
	{
		a = num[0].first, b = num[1].first;
	}
	switch (chiso)
	{
	case 0:
	{
		wcout <<"\t\t\t"<< a << " + " << b <<" = "<< a + b << " (" << unit << ")";
		wcout << "\n\t\t\t\t\t" << L"Đáp số: " << a+b << " (" << unit << ")\n\n\n";
		break;
	}
	case 1:
	{
		if (a < b)
			swap(a, b);
		wcout << "\t\t\t" << a << " - " << b << " = " << a-b << " (" << unit << ")";
		wcout << "\n\t\t\t\t\t" << L"Đáp số: " << a - b << " (" << unit << ")\n\n\n";
		break;
	}
	case 2:
	{
		swap(a, b);
		wcout << "\t\t\t" << a << " x " << b << " = " << a * b << " (" << unit << ")";
		wcout << "\n\t\t\t\t\t" << L"Đáp số: " << a * b << " (" << unit << ")\n\n\n";
		break;
	}
	case 3:
	{
		if (a < b)
			swap(a, b);
		wcout << "\t\t\t" << a << " / " << b << " = " << a / b << " (" << unit << ")";
		wcout << "\n\t\t\t\t\t" << L"Đáp số: " << a / b << " (" << unit << ")\n\n\n";
		break;
	}
	default:
	{
		wcout << "LỖI! Hàm in kết quả!";
	}

		break;
	}
}
void init_mymap(map<wstring, int>&mm)
{
	std::wifstream fin(L"filein.txt");
	std::locale loc(std::locale(), new std::codecvt_utf8<wchar_t>);
	if (!fin) {
		std::wcout << L"Không thể đọc file Đữ liệu - Kiểm tra lỗi\n";
	}
	else
	{
		while (!fin.eof())
		{
			wstring a;
			fin.imbue(loc);
			getline(fin, a);
			mm[a] = 0;
		}
	}
}
void nhan_1(wstring obj, wstring unit, vector<pair<int, int>>num)
{
	//print_answer_solution(unit, obj);
}
void cong_1(wstring obj, wstring unit, vector<pair<int, int>>num)
{
	//print_answer_solution(unit, obj);
}
void tru_1(wstring obj, wstring unit, vector<pair<int, int>>num)
{
	//print_answer_solution(unit, obj);
}
void chia_1(wstring obj, wstring unit, vector<pair<int, int>>num)
{
	//print_answer_solution(unit, obj);
}

int read_file(wstring a, map<wstring, int>&mm)
{
	a = a + L".txt";
	std::wifstream fin(a);
	int flat = 0;
	std::locale loc(std::locale(), new std::codecvt_utf8<wchar_t>);
	if (!fin) {
		std::wcout << L"Không thể đọc file Đữ liệu - Kiểm tra lỗi (Hàm đọc file con)\n";
	}
	else
	{
		while (!fin.eof())
		{
			wstring a;
			fin.imbue(loc);

			getline(fin, a);
			
			flat += mm[a];
		}
	}
	return flat;
}
void solving(map<wstring, int>&mm, vector<wstring>mvt, int k, wstring obj, wstring unit, vector<pair<int, int>>num)
{
	map<wstring, int>::iterator it1,it2;
	mvt.push_back(L"test1");
	wstring temp;
	for (int i = 0; i < mvt.size()-1; i++)
	{
		it1 = mm.find(mvt[i]);
		temp = mvt[i] + mvt[i + 1];
		it2 = mm.find(temp);
		if (&it1 != NULL)
			mm[mvt[i]] += 1;
		if (&it2 != NULL)
			mm[temp] += 1;
	}
	//cộng
	wstring pheptinh[4] = { L"cong",L"tru",L"nhan",L"chia" };
	int q[4],cc;
	q[0]=read_file(pheptinh[0], mm);
	q[1]=read_file(pheptinh[1], mm);
	q[2]=read_file(pheptinh[2], mm);
	q[3]=read_file(pheptinh[3], mm);
	int qmax = 0;
	for(int i=0;i<4;i++)
		if (qmax < q[i])
		{
			qmax = q[i];
			cc = i;
		}
	print_answer_solution(unit, obj, num, cc);



}
int _tmain(int argc, _TCHAR* argv[])
{
	_setmode(_fileno(stdin), _O_U16TEXT);
	_setmode(_fileno(stdout), _O_U16TEXT);
	SetConsoleTitleW(L"Cùng nhau giải toán");
	HANDLE hdlConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_FONT_INFOEX consoleFont;
	consoleFont.cbSize = sizeof(consoleFont);
	GetCurrentConsoleFontEx(hdlConsole, FALSE, &consoleFont);
	memcpy(consoleFont.FaceName, L"Consolas", sizeof(consoleFont.FaceName));
	SetCurrentConsoleFontEx(hdlConsole, FALSE, &consoleFont);
	

	std::wstring test;

	std::getline(std::wcin, test);
	std::vector<std::wstring>myvector;
	// lưu vị trí bắt đầu câu thứ 2
	int k;

	// tách chuỗi thành từng từ và lưu vị trí câu thứ 2
	split_substr(test, myvector, k);

	// lưu các đối tượng, đơn vị
	wstring obj, unit;

	//mảng lưu số cần giải quyết
	vector<pair<int, int>>number;

	//nhận diện đối tượng, đơn vị
	recognize_obj(myvector, k, obj, unit);
	//nhận diện các số
	recognize_number(myvector, number, k);
	
	//map lưu các chữ cần chú ý để suy ra phép tính
	map<wstring, int>mymap;
	map<wstring, int>::iterator it;
	init_mymap(mymap);
	solving(mymap,myvector,k,obj,unit,number);






	//In lời giải
	//print_answer_solution(unit, obj);
	return 0;
}

