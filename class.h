//---------------------------------------------------------------------------

#ifndef classH
#define classH

#include <vector>
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <vector>
#include <ctime>
//---------------------------------------------------------------------------

class Stats{
public:
	int TimeSr, vins, games;  //������� ����� ����, ������, ����

	//�������� ���������� �� �����
	Stats(TListBox *List);
    //���������� ����������
	void add(int TimeInGame, int vins);
	void save(TListBox *List);
};

class Game{
    //����, ������� ���������� ����� �� �����
	TListBox *FullList;

	void Max();  //������� ������������ ������ �����, ��� �������� �������������
	//���������� ������, ��� �� � ������� �� ������ �������� � ���������
public:
	Stats *stats;
	//�����������
	Game(TListBox *List);

	//������ ����
	std::vector<AnsiString> slova;
	//������ ���� �� �����
	std::vector<TListBox *> PodSlova;
	//������ ������, ������� ����� �� �����
	std::vector<TButton *> bt;
	//iter - � �����, ������� ������������. max - ������������ ���-�� ���� � slova
	int iter, max, step, vins, TimeInGame, FullSteps;

	//�������� ���� �� �����
	void LoadPodSlova();
	//��������� (rand lvl)
	void next();
    //����������� ������
	void ShowBut();
	//��������� ������ �� ������ ���� � �����
	bool prowKey(char Key);
    //����� ��������� �����, ��� ����� ���� ���������
	void Show1(char Key);
    //����� ���� ���������, ���������� ���������
    void reastart();
};

#endif
