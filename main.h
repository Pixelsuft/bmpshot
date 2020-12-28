//---------------------------------------------------------------------------

#ifndef mainH
#define mainH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
#include <Dialogs.hpp>
//---------------------------------------------------------------------------
class TMainForm : public TForm
{
__published:	// IDE-managed Components
        TImage *btn;
        TTimer *Startup;
        TImage *ScreenShotBox;
        TSaveDialog *Save;
        TMemo *config;
        TTimer *FixTimer;
        TTimer *HoverTimer;
        void __fastcall StartupTimer(TObject *Sender);
        void __fastcall btnClick(TObject *Sender);
        void __fastcall FixTimerTimer(TObject *Sender);
        void __fastcall HoverTimerTimer(TObject *Sender);
        void __fastcall FormMouseMove(TObject *Sender, TShiftState Shift,
          int X, int Y);
private:	// User declarations
public:		// User declarations
        __fastcall TMainForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TMainForm *MainForm;
//---------------------------------------------------------------------------
#endif
