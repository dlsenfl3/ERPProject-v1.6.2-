//---------------------------------------------------------------------------

#ifndef MainUH
#define MainUH
//---------------------------------------------------------------------------
#include "ObjectU.h"
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "cxBarEditItem.hpp"
#include "cxButtonEdit.hpp"
#include "cxButtons.hpp"
#include "cxCalendar.hpp"
#include "cxClasses.hpp"
#include "cxContainer.hpp"
#include "cxControls.hpp"
#include "cxCustomData.hpp"
#include "cxData.hpp"
#include "cxDataControllerConditionalFormattingRulesManagerDialog.hpp"
#include "cxDataStorage.hpp"
#include "cxDBData.hpp"
#include "cxEdit.hpp"
#include "cxFilter.hpp"
#include "cxGraphics.hpp"
#include "cxGrid.hpp"
#include "cxGridCustomTableView.hpp"
#include "cxGridCustomView.hpp"
#include "cxGridDBTableView.hpp"
#include "cxGridLevel.hpp"
#include "cxGridTableView.hpp"
#include "cxImage.hpp"
#include "cxImageList.hpp"
#include "cxLookAndFeelPainters.hpp"
#include "cxLookAndFeels.hpp"
#include "cxMaskEdit.hpp"
#include "cxNavigator.hpp"
#include "cxSpinEdit.hpp"
#include "cxStyles.hpp"
#include "cxTextEdit.hpp"
#include "dxBar.hpp"
#include "dxGDIPlusClasses.hpp"
#include "dxRibbon.hpp"
#include "dxRibbonCustomizationForm.hpp"
#include "dxRibbonSkins.hpp"
#include "dxSkinBlack.hpp"
#include "dxSkinBlue.hpp"
#include "dxSkinBlueprint.hpp"
#include "dxSkinCaramel.hpp"
#include "dxSkinCoffee.hpp"
#include "dxSkinDarkRoom.hpp"
#include "dxSkinDarkSide.hpp"
#include "dxSkinDevExpressDarkStyle.hpp"
#include "dxSkinDevExpressStyle.hpp"
#include "dxSkinFoggy.hpp"
#include "dxSkinGlassOceans.hpp"
#include "dxSkinHighContrast.hpp"
#include "dxSkiniMaginary.hpp"
#include "dxSkinLilian.hpp"
#include "dxSkinLiquidSky.hpp"
#include "dxSkinLondonLiquidSky.hpp"
#include "dxSkinMcSkin.hpp"
#include "dxSkinMetropolis.hpp"
#include "dxSkinMetropolisDark.hpp"
#include "dxSkinMoneyTwins.hpp"
#include "dxSkinOffice2007Black.hpp"
#include "dxSkinOffice2007Blue.hpp"
#include "dxSkinOffice2007Green.hpp"
#include "dxSkinOffice2007Pink.hpp"
#include "dxSkinOffice2007Silver.hpp"
#include "dxSkinOffice2010Black.hpp"
#include "dxSkinOffice2010Blue.hpp"
#include "dxSkinOffice2010Silver.hpp"
#include "dxSkinOffice2013DarkGray.hpp"
#include "dxSkinOffice2013LightGray.hpp"
#include "dxSkinOffice2013White.hpp"
#include "dxSkinOffice2016Colorful.hpp"
#include "dxSkinOffice2016Dark.hpp"
#include "dxSkinPumpkin.hpp"
#include "dxSkinsCore.hpp"
#include "dxSkinsDefaultPainters.hpp"
#include "dxSkinSeven.hpp"
#include "dxSkinSevenClassic.hpp"
#include "dxSkinSharp.hpp"
#include "dxSkinSharpPlus.hpp"
#include "dxSkinSilver.hpp"
#include "dxSkinSpringTime.hpp"
#include "dxSkinStardust.hpp"
#include "dxSkinSummer2008.hpp"
#include "dxSkinTheAsphaltWorld.hpp"
#include "dxSkinTheBezier.hpp"
#include "dxSkinValentine.hpp"
#include "dxSkinVisualStudio2013Blue.hpp"
#include "dxSkinVisualStudio2013Dark.hpp"
#include "dxSkinVisualStudio2013Light.hpp"
#include "dxSkinVS2010.hpp"
#include "dxSkinWhiteprint.hpp"
#include "dxSkinXmas2008Blue.hpp"
#include "TadCommon.h"
#include "TadFileLogger.h"
#include <Data.DB.hpp>
#include <System.ImageList.hpp>
#include <Vcl.Dialogs.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.ImgList.hpp>
#include <Vcl.Mask.hpp>
#include <Vcl.Menus.hpp>
#include "TadDatabase.h"
//---------------------------------------------------------------------------
enum TDBState {eLogin, eLogout, eExit, eGrdUser, eGrdStock};
enum TFormGrid {eStock, eReceive, eRelease, eUsage, eRepair, eTemple, eItem, eUser};
//---------------------------------------------------------------------------
class TMainF : public TForm
{
__published:	// IDE-managed Components
	TdxRibbon *dxRibbon1;
	TdxRibbonTab *dxRibbon1Tab1;
	TcxButton *btLogout;
	TPanel *pnMain;
	TPanel *pnWinBar;
	TcxButton *cxButton1;
	TcxButton *cxButton2;
	TcxButton *cxButton3;
	TPanel *Panel2;
	TImage *Image1;
	TPanel *pnLoginUser;
	TPanel *pnMainLogin;
	TPanel *pnDatabase;
	TLabel *Label1;
	TLabel *lbDBNameT;
	TLabel *lbDBUserT;
	TLabel *lbDBPasswdT;
	TLabel *lbDBSessionCntT;
	TLabel *lbDBSessionChkT;
	TMaskEdit *edDBUserV;
	TMaskEdit *edDBPasswdV;
	TcxButton *btnSave;
	TcxSpinEdit *edDBSessionChkV;
	TcxImage *cxImage1;
	TcxSpinEdit *edDBSessionCntV;
	TMaskEdit *edDBNameV;
	TPanel *pnDatabaseState;
	TLabel *lbDBConnCntT;
	TLabel *Label4;
	TLabel *lbDBQueueCntT;
	TLabel *lbDBConnCntV;
	TLabel *lbDBQueueCntV;
	TcxButton *btMainAdminReg;
	TPanel *Panel3;
	TcxButton *btLoginExit;
	TPanel *Panel4;
	TImage *Image2;
	TPanel *pnLogin;
	TLabel *Label2;
	TLabel *Label3;
	TMaskEdit *edUsername;
	TMaskEdit *edPassword;
	TcxImage *imLogin;
	TcxImage *cxImage2;
	TcxButton *btMainUserReg;
	TcxImageList *cxImageList1;
	TdxBarManager *dxBarManager1;
	TdxBar *dxBarManager1Bar1;
	TdxBarLargeButton *dxBarLargeButton10;
	TdxBarLargeButton *dxBarLargeButton13;
	TdxBarLargeButton *dxBarLargeButton14;
	TdxBarLargeButton *dxBarLargeButton15;
	TdxBarLargeButton *dxBarLargeButton16;
	TdxBarLargeButton *dxBarLargeButton17;
	TdxBarLargeButton *dxBarLargeButton19;
	TdxBarLargeButton *dxBarLargeButton20;
	TdxBarLargeButton *dxBarLargeButton22;
	TcxBarEditItem *cxBarEditItem1;
	TcxBarEditItem *cxBarEditItem2;
	TdxBarLargeButton *dxBarLargeButton1;
	TdxBarButton *dxBarButton1;
	TCustomdxBarCombo *CustomdxBarCombo1;
	TadFileLogger *adFileLogger1;
	TTimer *tmMain;
	TSaveDialog *SaveDialog1;
	TcxGrid *cxGrid1;
	TcxGridDBTableView *cxGrid1DBTableView1;
	TcxGridLevel *cxGrid1Level1;
	void __fastcall dxBarLargeButton10Click(TObject *Sender);
	void __fastcall dxBarLargeButton13Click(TObject *Sender);
	void __fastcall dxBarLargeButton14Click(TObject *Sender);
	void __fastcall dxBarLargeButton15Click(TObject *Sender);
	void __fastcall dxBarLargeButton16Click(TObject *Sender);
	void __fastcall dxBarLargeButton17Click(TObject *Sender);
	void __fastcall dxBarLargeButton20Click(TObject *Sender);
	void __fastcall dxBarLargeButton19Click(TObject *Sender);
	void __fastcall tmMainTimer(TObject *Sender);
	void __fastcall cxButton1Click(TObject *Sender);
	void __fastcall cxButton2Click(TObject *Sender);
	void __fastcall cxButton3Click(TObject *Sender);
	void __fastcall pnWinBarDblClick(TObject *Sender);
	void __fastcall pnWinBarMouseMove(TObject *Sender, TShiftState Shift, int X,
          int Y);
	void __fastcall Panel3MouseMove(TObject *Sender, TShiftState Shift, int X,
          int Y);
	void __fastcall edUsernameKeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall edPasswordKeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall btMainUserRegClick(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall FormDestroy(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall cxImage2Click(TObject *Sender);
	void __fastcall imLoginClick(TObject *Sender);
	void __fastcall btnSaveClick(TObject *Sender);
	void __fastcall cxImage1Click(TObject *Sender);
	void __fastcall btLogoutClick(TObject *Sender);
	void __fastcall btMainAdminRegClick(TObject *Sender);
	void __fastcall dxBarLargeButton22Click(TObject *Sender);
	void __fastcall edUsernameClick(TObject *Sender);
	void __fastcall btLoginExitClick(TObject *Sender);


private:
	TApplicationInfo *m_pAppInfo;
	TadFileLogger	 *m_pFileLogger;
	TadDatabase		 *m_pDatabase;
	TDBState		  m_eDBState;
	TFormGrid		  m_eFormState;
	int 			  m_iDBQueue;
	int               m_iKeyCount;
	int               m_iLockCount;
	int				  m_iCountValue;
private:	// User declarations
	void __fastcall CreateParams(TCreateParams& Params); //폼을 Resizeable 하게 만드는 코드
	void __fastcall fnSetVisibleLogin();
	void __fastcall fnSetVisibleLogout();
	void __fastcall fnExeDeleteFormInfo();
private:
	void __fastcall fnWriteAppStatus(UnicodeString a_sMsg);
	void __fastcall fnWriteFileLog(UnicodeString a_sLogMsg);
	void __fastcall fnFileLoggerStop(TObject *Sender);

	void __fastcall fnOnDatabaseAfterStopped(TObject *a_pSender);
	void __fastcall fnOnDatabaseConnected(TObject *a_pSender, int a_iSessionNo);
	void __fastcall fnOnDatabaseDisconnected(TObject *a_pSender, int a_iSessionNo);
	void __fastcall fnProcDBResponse(TMessage a_stMsg);
private:
	void __fastcall fnLoginCheck(TadResQuery *a_pResQry);



public:		// User declarations
	__fastcall  TMainF(TComponent* Owner);
	__fastcall ~TMainF();

//

BEGIN_MESSAGE_MAP
	VCL_MESSAGE_HANDLER(WM_DB_RESPONSE, TMessage, fnProcDBResponse);
END_MESSAGE_MAP(TForm);
};
//---------------------------------------------------------------------------
extern PACKAGE TMainF *MainF;
//---------------------------------------------------------------------------
#endif
