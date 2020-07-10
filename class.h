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
	int TimeSr, vins, games;  //Среднее время игры, победы, игры

	//Загрузка статистики из файла
	Stats(TListBox *List);
    //Обновление статистики
	void add(int TimeInGame, int vins);
	void save(TListBox *List);
};

class Game{
    //Лист, который подгружает слова из файла
	TListBox *FullList;

	void Max();  //Находит максимальную длинну слова, для создания максимального
	//Количества кнопок, что бы в будущем их только включать и выключать
public:
	Stats *stats;
	//Конструктор
	Game(TListBox *List);

	//Вектор слов
	std::vector<AnsiString> slova;
	//Вектор слов из слова
	std::vector<TListBox *> PodSlova;
	//Вектор кнопок, которые видны на форме
	std::vector<TButton *> bt;
	//iter - № слова, которое отображается. max - максимальное кол-во букв в slova
	int iter, max, step, vins, TimeInGame, FullSteps;

	//Загрузка слов из слова
	void LoadPodSlova();
	//Следующий (rand lvl)
	void next();
    //Отображение кнопок
	void ShowBut();
	//Проверяет нажата ли кнопка есть в слове
	bool prowKey(char Key);
    //Когда стирается буква, она снова стаёт доступной
	void Show1(char Key);
    //Когда игра закончена, происходит обнуление
    void reastart();
};

#endif
