//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <iostream.h>
#include <cstdlib.h>
#include <mmsystem.hpp>
#include "main.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TMainForm *MainForm;
AnsiString btn_file_name="btn.bmp";
AnsiString form_align_x="none";
AnsiString form_align_y="none";
int custom_x=0;
int custom_y=0;
int hover_alpha=255;
int no_hover_alpha=0;
bool visible_no_alpha=false;
bool enable_hover=false;
bool in_alpha=false;
int hover_speed_timer=1;
int hover_speed=1;
int no_hover_interval=2000;
//---------------------------------------------------------------------------
__fastcall TMainForm::TMainForm(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::StartupTimer(TObject *Sender)
{
        Startup->Enabled=false;
        if(!FileExists("config.txt"))config->Lines->SaveToFile("config.txt");
        else config->Lines->LoadFromFile("config.txt");
        for(int i=0;i<=500;i++)
        {
                AnsiString cur_str=config->Lines->Strings[i];
                AnsiString next_str=config->Lines->Strings[i+1];
                if(cur_str==":endconfig")break;
                if(cur_str==":form_align_x")form_align_x=next_str;
                if(cur_str==":form_align_y")form_align_y=next_str;
                if(cur_str==":custom_x")custom_x=StrToInt(next_str);
                if(cur_str==":custom_y")custom_y=StrToInt(next_str);
                if(cur_str==":button")btn_file_name=next_str;
                if(cur_str==":hover_alpha")hover_alpha=StrToInt(next_str);
                if(cur_str==":taskbar_fix" && next_str=="true")visible_no_alpha=true;
                if(cur_str==":top_fix" && next_str=="true")FixTimer->Enabled=true;
                if(cur_str==":top_fix_interval")FixTimer->Interval=StrToInt(next_str);
                if(cur_str==":greenscreen" && next_str=="true")MainForm->TransparentColor=true;
                if(cur_str==":no_hover_alpha")no_hover_alpha=StrToInt(next_str);               
                if(cur_str==":no_hover_interval")
                {
                        no_hover_interval=StrToInt(next_str);
                        HoverTimer->Interval=no_hover_interval;
                        ChangeAlpha->Interval=no_hover_interval;
                }                                                       
                if(cur_str==":hover_speed")hover_speed=StrToInt(next_str);
                if(cur_str==":hover_slow_timer")hover_speed_timer=StrToInt(next_str);
                if(cur_str==":hover" && next_str=="true")enable_hover=true;
        }
        if(no_hover_alpha<1)no_hover_alpha=1;
        if(hover_alpha<1)hover_alpha=1;
        if(no_hover_alpha>255)no_hover_alpha=255;
        if(hover_alpha>255)hover_alpha=255;
        btn->Left=0;
        btn->Top=0;
        if(FileExists(btn_file_name))
        {
                btn->Picture->LoadFromFile(btn_file_name);
        }
        else
        {
                Application->MessageBox("Could not find button image!","Error!",MB_ICONERROR);
        }
        MainForm->Width=btn->Width;
        MainForm->Height=btn->Height;
        if(form_align_x=="right")
        {
                MainForm->Left=Screen->Width-MainForm->Width;
        }
        else if(form_align_x=="center")
        {
                MainForm->Left=Screen->Width/2-MainForm->Width/2;
        }
        else if(form_align_x=="left")
        {
                MainForm->Left=0;
        }
        else
        {
                MainForm->Left=custom_x;
        }
        if(form_align_y=="down")
        {
                MainForm->Top=Screen->Height-MainForm->Height;
        }
        else if(form_align_y=="center")
        {
                MainForm->Top=Screen->Height/2-MainForm->Height/2;
        }
        else if(form_align_y=="left")
        {
                MainForm->Top=0;
        }
        else
        {
                MainForm->Top=custom_y;
        }
        MainForm->AlphaBlendValue=hover_alpha;
        if(enable_hover)HoverTimer->Enabled=true;
}
//---------------------------------------------------------------------------


void __fastcall TMainForm::btnClick(TObject *Sender)
{
        if(in_alpha==false){
        MainForm->AlphaBlendValue=0;
        if(visible_no_alpha==true)MainForm->Visible=false;
        HDC dc = GetDC(0);
        Graphics::TCanvas *ScrCanvas = new Graphics::TCanvas;
        ScrCanvas->Handle = dc;
        ScreenShotBox->Picture->Bitmap->Width = Screen->Width;
        ScreenShotBox->Picture->Bitmap->Height= Screen->Height;
        TRect rt = Rect(0,0,Screen->Width, Screen->Height);
        ScreenShotBox->Picture->Bitmap->Canvas->CopyRect(rt, ScrCanvas, rt);
        ScreenShotBox->Align = alClient;
        delete ScrCanvas;
        ReleaseDC(NULL,dc);
        if(Save->Execute())
        {
                AnsiString filename_to_save=Save->FileName;
                if(filename_to_save.SubString(filename_to_save.Length()-3,4)!=".bmp")
                {
                        filename_to_save+=".bmp";
                }
                bool can_save_filename=true;
                if(FileExists(filename_to_save))
                {
                        if(Application->MessageBox("File is already exists.\nReplace it?","Question!", MB_ICONQUESTION+MB_YESNO)==ID_NO)
                        {
                                can_save_filename=false;
                        }
                }
                if(can_save_filename==true)
                {
                        ScreenShotBox->Picture->SaveToFile(filename_to_save);
                }
        }
        MainForm->AlphaBlendValue=hover_alpha;
        if(visible_no_alpha==true)MainForm->Visible=true;
        }                 
        ChangeAlpha->Enabled=false;
        MainForm->AlphaBlendValue=hover_alpha;
        in_alpha=false;
        if(enable_hover==true)HoverTimer->Enabled=true;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::FixTimerTimer(TObject *Sender)
{
        MainForm->FormStyle=fsStayOnTop;        
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::HoverTimerTimer(TObject *Sender)
{
        if(in_alpha==false)
        {
                in_alpha=true;
                HoverTimer->Interval=hover_speed;
        }
        else
        {
                MainForm->AlphaBlendValue-=hover_speed;
                if(MainForm->AlphaBlendValue<=no_hover_alpha)
                {
                        HoverTimer->Enabled=false;
                        HoverTimer->Interval=no_hover_interval;
                        MainForm->AlphaBlendValue=no_hover_alpha;
                        in_alpha=false;
                }
        }
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::FormMouseMove(TObject *Sender,
      TShiftState Shift, int X, int Y)
{
        if(in_alpha==false)
        {
                if(enable_hover==true)
                {
                        HoverTimer->Enabled=false;
                        if(MainForm->AlphaBlendValue==no_hover_alpha)
                        {
                                in_alpha=true;
                                ChangeAlpha->Enabled=true;
                        }
                        else HoverTimer->Enabled=true;
                }
        }
}
//---------------------------------------------------------------------------


void __fastcall TMainForm::ChangeAlphaTimer(TObject *Sender)
{
        if(MainForm->AlphaBlendValue>=hover_alpha)
        {
                ChangeAlpha->Enabled=false;
                MainForm->AlphaBlendValue=hover_alpha;
                in_alpha=false;
                HoverTimer->Enabled=true;
        }
        else
        {
                MainForm->AlphaBlendValue+=hover_speed;
        }
}
//---------------------------------------------------------------------------


