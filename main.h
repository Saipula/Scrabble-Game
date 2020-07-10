//---------------------------------------------------------------------------

#ifndef mainH
#define mainH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Menus.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Imaging.jpeg.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TEdit *Edit1;
	TButton *StartBtn;
	TMainMenu *MainMenu1;
	TMenuItem *Next;
	TMenuItem *Pause;
	TListBox *ListBox1;
	TLabel *Label1;
	TTimer *Timer1;
	TLabel *Label2;
	TImage *Back;
	TLabel *Label3;
	TButton *Check;
	TMenuItem *Statistic1;
	TMenuItem *Games1;
	TMenuItem *Vins1;
	TMenuItem *TimeSr1;
	TListBox *Stat;
	void __fastcall StartBtnClick(TObject *Sender);
	void __fastcall KnopochkaClick(TObject *Sender);
	void __fastcall NextClick(TObject *Sender);
	void __fastcall PauseClick(TObject *Sender);
	void __fastcall Timer1Timer(TObject *Sender);
	void __fastcall Edit1KeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall Edit1KeyUp(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall CheckClick(TObject *Sender);
	void __fastcall Statistic1Click(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
private:	// User declarations
public:		// User declarations
	__fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
