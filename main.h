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
        void __fastcall StartupTimer(TObject *Sender);
        void __fastcall btnClick(TObject *Sender);
        void __fastcall FixTimerTimer(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TMainForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TMainForm *MainForm;
//---------------------------------------------------------------------------
#endif
