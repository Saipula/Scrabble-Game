//---------------------------------------------------------------------------

#pragma hdrstop

#include "class.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

//Конструктор
Game::Game(TListBox *List){
	List->Items->LoadFromFile("words.txt", TEncoding::UTF8);
	FullList = List;

	for (int i = 0; i < List->Items->Count; i++){
		if (List->Items->Strings[i] == "-") {
			i++;
			slova.push_back(List->Items->Strings[i]);
		}
	}

	iter = -1;
	max = 0;
	step = 0;
	FullSteps = 0;
	Max();
	vins = 0;
	TimeInGame = 0;

	List = FullList;
}

//Загрузка слов из слова
void Game::LoadPodSlova(){
	int count = -1;
	for (int i = 0; i < FullList->Items->Count; i++){
		if (FullList->Items->Strings[i] == "-") {
			i++;
			count++;
		}
		else{
			PodSlova[count]->Items->Add(FullList->Items->Strings[i]);
        }
	}
}

//Максимальное по длине слова
void Game::Max(){
	for (int i = 0; i < slova.size(); i++) {
		if (max < slova[i].Length())   max = slova[i].Length();
	}
}

void Game::next(){
	iter++;
	ShowBut();
}

void Game::ShowBut(){
	AnsiString tmp = slova[iter];
	for (int i = 0; i < max; i++) {
		bt[i]->Visible = false;
		bt[i]->Enabled = true;
		if (slova[iter].Length() > i){
			bt[i]->Visible = true;
			bt[i]->Caption = tmp[i+1];
		}
	}
}

bool Game::prowKey(char Key){
	for (int i = 0; i < slova[iter].Length(); i++)
		if (bt[i]->Enabled)
			if (bt[i]->Caption[1] == Key) {
				bt[i]->Enabled = false;
				return true;
			}
	return false;
}

void Game::Show1(char Key){
    for (int i = 0; i < slova[iter].Length(); i++)
		if (!bt[i]->Enabled)
			if (bt[i]->Caption[1] == Key) {
				bt[i]->Enabled = true;
				return;
			}
}

void Game::reastart(){
	for (int i = 0; i < bt.size(); i++) bt[i]->Visible = false;
	iter = -1;
	vins = 0;
	TimeInGame = 0;
	FullSteps = 0;
}

Stats::Stats(TListBox *List){
	List->Items->LoadFromFile("stats.txt", TEncoding::UTF8);
	games = StrToInt(List->Items->Strings[0]);
	vins = StrToInt(List->Items->Strings[1]);;
	TimeSr = StrToInt(List->Items->Strings[2]);
}

void Stats::add(int TimeInGame, int vins){
	TimeSr *= games;
	TimeSr += TimeInGame;
	games++;
	TimeSr /= games;

	this->vins += vins;
}

void Stats::save(TListBox *List){
	List->Clear();
	DeleteFile("stats.txt");

	List->Items->Add(games);
	List->Items->Add(vins);
	List->Items->Add(TimeSr);

	List->Items->SaveToFile("stats.txt");
}
