//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "main.h"
#include <vector>
#include "class.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;

Game *game;
AnsiString slovo;
bool pause = 0;
int TimeInGame = 0;

//Уонструктор формы----------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
	TListBox *List;
	List = new TListBox(this);
	List->Parent = this;
	List->Visible = false;   //true для тестировки

	game = new Game(List);
	game->stats = new Stats(Stat);

	//Создания вектора TListBox для хранения слов из слова
	for (int i = 0; i < game->slova.size(); i++) {
		game->PodSlova.push_back(new TListBox(this));
		game->PodSlova[i]->Parent = this;
		game->PodSlova[i]->Visible = false;
	}
	//Загрузка Этих слов
	game->LoadPodSlova();

    //Создания максимального количества кнопок
	for (int i = 0; i < game->max; i++) {
		game->bt.push_back(new TButton(this));
		game->bt[i]->Parent = this;
		game->bt[i]->Width = 50;
		game->bt[i]->Height = game->bt[i]->Width;
		game->bt[i]->Left = i * 50 + 5 + 250;
		game->bt[i]->Top = 90;
		game->bt[i]->Visible = false;
		game->bt[i]->Font->Size = 25;
		game->bt[i]->Font->Name = "Times New Roman";
		game->bt[i]->OnClick = KnopochkaClick;
	}

	Back->Align = alClient;
	Back->Picture->LoadFromFile("fon1.jpg");
}

//Кнопка старт---------------------------------------------------------------
void __fastcall TForm1::StartBtnClick(TObject *Sender)
{
	//Влючение всех визуальных компонентов
	StartBtn->Visible = false;
	Edit1->Visible = true;
	Label1->Visible = true;
	Label2->Visible = true;
	Label3->Visible = true;
	ListBox1->Visible = true;
	Next->Visible = true;
	Pause->Visible = true;
	Back->Visible = true;
	Check->Visible = true;
	Statistic1->Visible = true;

	NextClick(Sender);
}

//Событие для кнопок с буквами-----------------------------------------------
void __fastcall TForm1::KnopochkaClick(TObject *Sender)
{
	if (!pause) {
		TButton *but = static_cast<TButton*>(Sender);
		but->Enabled = false;
		slovo += but->Caption;
		Edit1->Text = slovo;
	}
}

//Следующий лвл--------------------------------------------------------------
void __fastcall TForm1::NextClick(TObject *Sender)
{
	game->TimeInGame += TimeInGame;
	TimeInGame = 0;
	game->FullSteps += game->step;
    game->step = 0;
	//Проверка не ровняется ли номер лвла с количиством лвлов
	//если да, то будет конец игры
	if (game->iter == game->slova.size()-1) {
		//Отключение визуальных компонентов
        PauseClick(Sender);
		ShowMessage("You End game!\nVins: " + IntToStr(game->vins)
			+"\nFull time: " + IntToStr(game->TimeInGame) + "sec"
			+"\nFull steps: " + IntToStr(game->FullSteps));

		game->stats->add(game->TimeInGame, game->vins);

		StartBtn->Visible = true;
		Edit1->Visible = false;
		Label1->Visible = false;
		Label2->Visible = false;
		Label3->Visible = false;
		ListBox1->Visible = false;
		Next->Visible = false;
		Pause->Visible = false;
		Back->Visible = false;
		Check->Visible = false;
		Statistic1->Visible = false;

		game->reastart();
		return;
	}

	//Загрузка следующего набора букв
	game->next();
	//Очистка старых ответо
	ListBox1->Clear();

	slovo = "";
	Edit1->Text = "";
	Edit1->SetFocus();

	//Отключается пауза(Если была) и перезапускается таймер
	pause = false;
	Timer1->Enabled = false;
	Timer1->Enabled = true;

	int tmp = game->PodSlova[game->iter]->Count - ListBox1->Items->Count;
	Label1->Caption = "Words left: " + IntToStr(tmp);

	Label2->Caption = "Time in game: " + IntToStr(TimeInGame);
	Label3->Caption = "Steps: " + IntToStr(game->step);
}

//Пауза----------------------------------------------------------------------
void __fastcall TForm1::PauseClick(TObject *Sender)
{
	pause = !pause;
	Timer1->Enabled = !pause;
}

//Счётчик времени в игре-----------------------------------------------------
void __fastcall TForm1::Timer1Timer(TObject *Sender)
{
	TimeInGame++;
	Label2->Caption = "Time in game: " + IntToStr(TimeInGame);
}

//Проверка нажатой кнопки----------------------------------------------------
void __fastcall TForm1::Edit1KeyPress(TObject *Sender, System::WideChar &Key)
{
	if (!pause) {   //Если пауза, то ничего не будет
		if (Key == 13) {  //Есои ентер, проверка слова на совпадение
            CheckClick(Sender);
		}
		//Если стираешь букву, она стаёт доступной
		else if (Key == VK_BACK) {
			game->Show1(Edit1->Text[Edit1->Text.Length()]);
		}
		//Если символ есть в слове, то она отображается и становится недоступной
		else if (game->prowKey((char)Key)) return;
		//В лубом другом случае символ стирается
		else Key = 0;
	}
}

//---------------------------------------------------------------------------
void __fastcall TForm1::Edit1KeyUp(TObject *Sender, WORD &Key, TShiftState Shift)

{
    slovo = Edit1->Text;
}

//Check Click----------------------------------------------------------------
void __fastcall TForm1::CheckClick(TObject *Sender)
{
	bool prov = 1;
	//Если слово в Edit совпадает из одным из заданых слов к Длинному слову
	//и его ещё нету в ListBox1 то оно записывается в ListBox1
	for (int i = 0; i < ListBox1->Items->Count; i++)
		if (ListBox1->Items->Strings[i] == Edit1->Text) prov = 0;

	for (int i = 0; i < game->PodSlova[game->iter]->Items->Count && prov; i++) {
		if (Edit1->Text == game->PodSlova[game->iter]->Items->Strings[i]) {
			ListBox1->Items->Add(Edit1->Text);
		}
	}

	//Очистка полей
	game->ShowBut();
	Edit1->Text = "";
    Edit1->SetFocus();
	slovo = "";

	//Отображение колва оставшихся слов
	int tmp = (game->PodSlova[game->iter]->Items->Count - ListBox1->Items->Count);
	Label1->Caption = "Words left: " + IntToStr(tmp);

	game->step++;
	Label3->Caption = "Steps: "+IntToStr(game->step);

	//Если 0, значит победа
	if ((game->PodSlova[game->iter]->Items->Count - ListBox1->Items->Count) == 0) {
		Timer1->Enabled = false;
		game->vins++;
		ShowMessage("You win!\nTime: " + IntToStr(TimeInGame) + "sec"
			+ "\nSteps: " + IntToStr(game->step));
		NextClick(Sender);
	}
}

//Statistic------------------------------------------------------------------
void __fastcall TForm1::Statistic1Click(TObject *Sender)
{
	Games1->Caption = "Games: " + IntToStr(game->stats->games);
	Vins1->Caption = "Vins: " + IntToStr(game->stats->vins);
	TimeSr1->Caption = "TimeSr: " + IntToStr(game->stats->TimeSr);
}

//Save stats-----------------------------------------------------------------
void __fastcall TForm1::FormClose(TObject *Sender, TCloseAction &Action)
{
	game->stats->save(Stat);
}
//---------------------------------------------------------------------------

