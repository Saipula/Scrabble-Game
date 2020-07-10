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

//����������� �����----------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
	TListBox *List;
	List = new TListBox(this);
	List->Parent = this;
	List->Visible = false;   //true ��� ����������

	game = new Game(List);
	game->stats = new Stats(Stat);

	//�������� ������� TListBox ��� �������� ���� �� �����
	for (int i = 0; i < game->slova.size(); i++) {
		game->PodSlova.push_back(new TListBox(this));
		game->PodSlova[i]->Parent = this;
		game->PodSlova[i]->Visible = false;
	}
	//�������� ���� ����
	game->LoadPodSlova();

    //�������� ������������� ���������� ������
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

//������ �����---------------------------------------------------------------
void __fastcall TForm1::StartBtnClick(TObject *Sender)
{
	//�������� ���� ���������� �����������
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

//������� ��� ������ � �������-----------------------------------------------
void __fastcall TForm1::KnopochkaClick(TObject *Sender)
{
	if (!pause) {
		TButton *but = static_cast<TButton*>(Sender);
		but->Enabled = false;
		slovo += but->Caption;
		Edit1->Text = slovo;
	}
}

//��������� ���--------------------------------------------------------------
void __fastcall TForm1::NextClick(TObject *Sender)
{
	game->TimeInGame += TimeInGame;
	TimeInGame = 0;
	game->FullSteps += game->step;
    game->step = 0;
	//�������� �� ��������� �� ����� ���� � ����������� �����
	//���� ��, �� ����� ����� ����
	if (game->iter == game->slova.size()-1) {
		//���������� ���������� �����������
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

	//�������� ���������� ������ ����
	game->next();
	//������� ������ ������
	ListBox1->Clear();

	slovo = "";
	Edit1->Text = "";
	Edit1->SetFocus();

	//����������� �����(���� ����) � ��������������� ������
	pause = false;
	Timer1->Enabled = false;
	Timer1->Enabled = true;

	int tmp = game->PodSlova[game->iter]->Count - ListBox1->Items->Count;
	Label1->Caption = "Words left: " + IntToStr(tmp);

	Label2->Caption = "Time in game: " + IntToStr(TimeInGame);
	Label3->Caption = "Steps: " + IntToStr(game->step);
}

//�����----------------------------------------------------------------------
void __fastcall TForm1::PauseClick(TObject *Sender)
{
	pause = !pause;
	Timer1->Enabled = !pause;
}

//������� ������� � ����-----------------------------------------------------
void __fastcall TForm1::Timer1Timer(TObject *Sender)
{
	TimeInGame++;
	Label2->Caption = "Time in game: " + IntToStr(TimeInGame);
}

//�������� ������� ������----------------------------------------------------
void __fastcall TForm1::Edit1KeyPress(TObject *Sender, System::WideChar &Key)
{
	if (!pause) {   //���� �����, �� ������ �� �����
		if (Key == 13) {  //���� �����, �������� ����� �� ����������
            CheckClick(Sender);
		}
		//���� �������� �����, ��� ���� ���������
		else if (Key == VK_BACK) {
			game->Show1(Edit1->Text[Edit1->Text.Length()]);
		}
		//���� ������ ���� � �����, �� ��� ������������ � ���������� �����������
		else if (game->prowKey((char)Key)) return;
		//� ����� ������ ������ ������ ���������
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
	//���� ����� � Edit ��������� �� ����� �� ������� ���� � �������� �����
	//� ��� ��� ���� � ListBox1 �� ��� ������������ � ListBox1
	for (int i = 0; i < ListBox1->Items->Count; i++)
		if (ListBox1->Items->Strings[i] == Edit1->Text) prov = 0;

	for (int i = 0; i < game->PodSlova[game->iter]->Items->Count && prov; i++) {
		if (Edit1->Text == game->PodSlova[game->iter]->Items->Strings[i]) {
			ListBox1->Items->Add(Edit1->Text);
		}
	}

	//������� �����
	game->ShowBut();
	Edit1->Text = "";
    Edit1->SetFocus();
	slovo = "";

	//����������� ����� ���������� ����
	int tmp = (game->PodSlova[game->iter]->Items->Count - ListBox1->Items->Count);
	Label1->Caption = "Words left: " + IntToStr(tmp);

	game->step++;
	Label3->Caption = "Steps: "+IntToStr(game->step);

	//���� 0, ������ ������
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

