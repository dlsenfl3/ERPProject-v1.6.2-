//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "MainU.h"
#include "StockGridU.h"
#include "ReceiveGridU.h"
#include "ReleaseGridU.h"
#include "UsageGridU.h"
#include "RepairGridU.h"
#include "TempleGridU.h"
#include "ItemGridU.h"
#include "UserGridU.h"
#include "UserU.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "cxBarEditItem"
#pragma link "cxButtonEdit"
#pragma link "cxButtons"
#pragma link "cxCalendar"
#pragma link "cxClasses"
#pragma link "cxContainer"
#pragma link "cxControls"
#pragma link "cxCustomData"
#pragma link "cxData"
#pragma link "cxDataControllerConditionalFormattingRulesManagerDialog"
#pragma link "cxDataStorage"
#pragma link "cxDBData"
#pragma link "cxEdit"
#pragma link "cxFilter"
#pragma link "cxGraphics"
#pragma link "cxGrid"
#pragma link "cxGridCustomTableView"
#pragma link "cxGridCustomView"
#pragma link "cxGridDBTableView"
#pragma link "cxGridLevel"
#pragma link "cxGridTableView"
#pragma link "cxImage"
#pragma link "cxImageList"
#pragma link "cxLookAndFeelPainters"
#pragma link "cxLookAndFeels"
#pragma link "cxMaskEdit"
#pragma link "cxNavigator"
#pragma link "cxSpinEdit"
#pragma link "cxStyles"
#pragma link "cxTextEdit"
#pragma link "dxBar"
#pragma link "dxGDIPlusClasses"
#pragma link "dxRibbon"
#pragma link "dxRibbonCustomizationForm"
#pragma link "dxRibbonSkins"
#pragma link "dxSkinBlack"
#pragma link "dxSkinBlue"
#pragma link "dxSkinBlueprint"
#pragma link "dxSkinCaramel"
#pragma link "dxSkinCoffee"
#pragma link "dxSkinDarkRoom"
#pragma link "dxSkinDarkSide"
#pragma link "dxSkinDevExpressDarkStyle"
#pragma link "dxSkinDevExpressStyle"
#pragma link "dxSkinFoggy"
#pragma link "dxSkinGlassOceans"
#pragma link "dxSkinHighContrast"
#pragma link "dxSkiniMaginary"
#pragma link "dxSkinLilian"
#pragma link "dxSkinLiquidSky"
#pragma link "dxSkinLondonLiquidSky"
#pragma link "dxSkinMcSkin"
#pragma link "dxSkinMetropolis"
#pragma link "dxSkinMetropolisDark"
#pragma link "dxSkinMoneyTwins"
#pragma link "dxSkinOffice2007Black"
#pragma link "dxSkinOffice2007Blue"
#pragma link "dxSkinOffice2007Green"
#pragma link "dxSkinOffice2007Pink"
#pragma link "dxSkinOffice2007Silver"
#pragma link "dxSkinOffice2010Black"
#pragma link "dxSkinOffice2010Blue"
#pragma link "dxSkinOffice2010Silver"
#pragma link "dxSkinOffice2013DarkGray"
#pragma link "dxSkinOffice2013LightGray"
#pragma link "dxSkinOffice2013White"
#pragma link "dxSkinOffice2016Colorful"
#pragma link "dxSkinOffice2016Dark"
#pragma link "dxSkinPumpkin"
#pragma link "dxSkinsCore"
#pragma link "dxSkinsDefaultPainters"
#pragma link "dxSkinSeven"
#pragma link "dxSkinSevenClassic"
#pragma link "dxSkinSharp"
#pragma link "dxSkinSharpPlus"
#pragma link "dxSkinSilver"
#pragma link "dxSkinSpringTime"
#pragma link "dxSkinStardust"
#pragma link "dxSkinSummer2008"
#pragma link "dxSkinTheAsphaltWorld"
#pragma link "dxSkinTheBezier"
#pragma link "dxSkinValentine"
#pragma link "dxSkinVisualStudio2013Blue"
#pragma link "dxSkinVisualStudio2013Dark"
#pragma link "dxSkinVisualStudio2013Light"
#pragma link "dxSkinVS2010"
#pragma link "dxSkinWhiteprint"
#pragma link "dxSkinXmas2008Blue"
#pragma link "TadCommon"
#pragma link "TadFileLogger"
#pragma link "TadDatabase"
#pragma resource "*.dfm"
TMainF *MainF;
//---------------------------------------------------------------------------
__fastcall TMainF::TMainF(TComponent* Owner)
	: TForm(Owner)
{
	m_pAppInfo = new TApplicationInfo();
	m_pAppInfo->fnLoadConfig();                                              // 설정파일 로드

	m_pFileLogger		  = new TadFileLogger(NULL);
	m_pFileLogger->MQMgr  = m_pAppInfo->MQMgr;
//	m_pFileLogger->OnStop = fnFileLoggerStop;

	m_pDatabase						  = new TadDatabase(NULL);
	m_pDatabase->MQMgr 				  = m_pAppInfo->MQMgr;
	m_pDatabase->FileLoggerID         = m_pAppInfo->FileLoggerID;
	m_pDatabase->DatabaseKind         = dbkMYSQL;
	m_pDatabase->DatabaseName         = m_pAppInfo->DB_ServerName;
	m_pDatabase->UserName	          = m_pAppInfo->DB_UserName;
	m_pDatabase->Password	          = m_pAppInfo->DB_Password;
	m_pDatabase->MinSessionCount      = m_pAppInfo->DB_MinSessionCnt;
	m_pDatabase->MaxSessionCount      = m_pAppInfo->DB_MaxSessionCnt;
	m_pDatabase->MessageResponse      = WM_DB_RESPONSE;
	m_pDatabase->MessageResult	      = WM_DB_RESULT;
//	함수의 주소값 전달
	m_pDatabase->OnAfterStopped	      = fnOnDatabaseAfterStopped;      // 데이터베이스가 멈춘뒤에 호출할 함수
	m_pDatabase->OnDatabaseConnect    = fnOnDatabaseConnected;         // 데이터베이스가 연결 되었을때 호출할 함수
	m_pDatabase->OnDatabaseDisconnect = fnOnDatabaseDisconnected;      // 데이터베이스가 연결이 끊겼을때 호출할 함수

	m_iDBQueue						  = 0;
	m_iKeyCount                       = 0;
	m_iLockCount			          = 0;
	m_iCountValue					  = 3;



	fnSetVisibleLogout();
	Application->ShowMainForm = false;
}
//---------------------------------------------------------------------------
__fastcall TMainF::~TMainF()
{
	delete m_pAppInfo;
//	delete m_pFileLogger;         // Error???
	delete m_pDatabase;

	fnExeDeleteFormInfo();
}
//---------------------------------------------------------------------------
void __fastcall TMainF::fnExeDeleteFormInfo()
{
	if(StockGridF 	!= NULL) delete StockGridF	;
	if(ReceiveGridF != NULL) delete ReceiveGridF;
	if(ReleaseGridF != NULL) delete ReleaseGridF;
	if(UsageGridF 	!= NULL) delete UsageGridF	;
	if(RepairGridF  != NULL) delete RepairGridF ;
	if(TempleGridF  != NULL) delete TempleGridF ;
	if(ItemGridF 	!= NULL) delete ItemGridF   ;
	if(UserGridF 	!= NULL) delete UserGridF   ;

}
//---------------------------------------------------------------------------
void __fastcall TMainF::fnSetVisibleLogin()
{
	m_eDBState						  = eLogin;
	MainF->pnWinBar->Visible 		  = true;
//	MainF->dxRibbon1->Visible 		  = true;
	MainF->pnMain->Visible 			  = true;
	MainF->btLogout->Visible		  = true;
	MainF->Constraints->MaxWidth 	  = 0;
	MainF->Constraints->MaxHeight 	  = 0;
	MainF->Constraints->MinWidth 	  = 1350;
	MainF->Constraints->MinHeight 	  = 700;
	MainF->Position					  = poScreenCenter;
	MainF->WindowState				  = wsMaximized;
	MainF->pnLoginUser->Caption		  = m_pAppInfo->LoginUser;
	pnMainLogin->Visible 			  = false;

	dxBarLargeButton10->Click();
	// 사찰, 제품목록, 사용자 (일반사용자) 버튼 막기
	if(m_pAppInfo->UserAuth == 0){
		dxBarLargeButton13->Enabled = false;
		dxBarLargeButton20->Enabled = false;
		dxBarLargeButton19->Enabled = false;
//		dxBarLargeButton17->Enabled = false;
	}else{
		dxBarLargeButton13->Enabled = true;
		dxBarLargeButton20->Enabled = true;
		dxBarLargeButton19->Enabled = true;
//		dxBarLargeButton17->Enabled = true;
	}
//	dxBarLargeButton22->Enabled = false;    // 엑셀저장 버튼
}
//---------------------------------------------------------------------------
void __fastcall TMainF::fnSetVisibleLogout()
{
	m_eDBState						  = eLogout;
	MainF->pnWinBar->Visible 		  = false;
//	MainF->dxRibbon1->Visible 		  = false;
	MainF->btLogout->Visible		  = false;
	MainF->pnMain->Visible 			  = false;
	MainF->Constraints->MaxWidth 	  = 560;
	MainF->Constraints->MaxHeight 	  = 360;
	MainF->Constraints->MinWidth 	  = 560;
	MainF->Constraints->MinHeight 	  = 360;
	Left				   = m_pAppInfo->AppPosX;
	Top					   = m_pAppInfo->AppPosY;
	pnMainLogin->Visible 			  = true;

//	dxBarLargeButton20->Enabled = true;
//	dxBarLargeButton19->Enabled = true;
//	dxBarLargeButton17->Enabled = true;
}
//---------------------------------------------------------------------------
void __fastcall TMainF::fnFileLoggerStop(TObject *Sender)
{

}
//---------------------------------------------------------------------------
void __fastcall TMainF::fnWriteAppStatus(UnicodeString a_sMsg)
{
	TadLogFileInfo *pLFI;

	if(m_pAppInfo->FileLoggerID == 0) return;
	a_sMsg = L"[" + Now().FormatString(L"hh:nn:ss.zzz") + L"] " + a_sMsg + L"\r\n";
	pLFI = new TadLogFileInfo(m_pAppInfo->MQMgr);
	pLFI->FileName = L"APP_STATUS_" + Now().FormatString(L"hh") + ".log";
	pLFI->Text = a_sMsg;
	pLFI->fnWriteLogFile(m_pAppInfo->FileLoggerID);
}
//---------------------------------------------------------------------------
void __fastcall TMainF::fnWriteFileLog(UnicodeString a_sLogMsg)               // ??????  에러 발생시 호출
{
	try {
		HANDLE     	  hFile;
		DWORD      	  dwWriteSize;
		UnicodeString sFName;
		AnsiString    sMsg  = a_sLogMsg;
		TDateTime 	  dtNow = Now();

		sFName  = ExtractFilePath(Application->ExeName) + "LOG\\" + dtNow.FormatString("yyyy-mm-dd");
		sFName += "\\PROC_DEBUG_" + dtNow.FormatString("hh") + ".LOG";
		if((hFile = CreateFileW(sFName.c_str(),
							   GENERIC_READ|GENERIC_WRITE,
							   FILE_SHARE_READ,
							   NULL,
							   OPEN_ALWAYS,
							   FILE_ATTRIBUTE_NORMAL,
							   NULL)) == INVALID_HANDLE_VALUE) return;
		SetFilePointer(hFile, 0, NULL, FILE_END);

		sMsg = "[" + dtNow.FormatString("hh:nn:ss.zzz") + "] " + sMsg + "\r\n";
		WriteFile(hFile, sMsg.c_str(), sMsg.Length() * sMsg.ElementSize(), &dwWriteSize, NULL);
		CloseHandle(hFile);
	}
	catch ( const Sysutils::Exception &E ) {

	}
}
//---------------------------------------------------------------------------
void __fastcall TMainF::fnOnDatabaseAfterStopped(TObject *a_pSender)
{
	try {

	}catch(Exception &E){
		fnWriteAppStatus(L"OnDatabaseAfterStopped\r\n" + E.Message);
	}
}
//---------------------------------------------------------------------------
void __fastcall TMainF::fnOnDatabaseConnected(TObject *a_pSender, int a_iSessionNo)
{
	try {
		if(!m_pAppInfo->DBPM) {
			m_pAppInfo->DBPM = m_pDatabase->DatabaseProcessID;
		}

		lbDBConnCntV->Caption = IntToStr(m_pDatabase->ActiveSessionCount) + L" / " + IntToStr(m_pDatabase->MaxSessionCount);
		lbDBConnCntV->Update();
	}catch(Exception &E){
		fnWriteAppStatus(L"OnDatabaseConnected\r\n" + E.Message);
	}
}
//---------------------------------------------------------------------------
void __fastcall TMainF::fnOnDatabaseDisconnected(TObject *a_pSender, int a_iSessionNo)
{
	try {
		lbDBConnCntV->Caption = IntToStr(m_pDatabase->ActiveSessionCount) + L" / " + IntToStr(m_pDatabase->MaxSessionCount);
		lbDBConnCntV->Update();
	}catch(Exception &E){
		fnWriteAppStatus(L"ACPM OnDatabaseDisconnected\r\n" + E.Message);
	}
}
//---------------------------------------------------------------------------
void __fastcall TMainF::tmMainTimer(TObject *Sender)
{
//	static bool bFirst = true;
	TDateTime dtCurr   = Now();

	if (m_pAppInfo->MQMgr->QueueCount > 30000) {                  // ????
		fnWriteFileLog("Message Queue Max.. (Quit)");

		UnicodeString sKill = "/t /f /im " + ExtractFileName(Application->ExeName);
		ShellExecute(NULL, L"open", L"taskKill.exe", sKill.c_str(), L"c:\\windows\\system32", SW_HIDE);
		Sleep(100);
	}

//	if (bFirst) {
//		bFirst = false;
		if(!m_pDatabase->DatabaseName.IsEmpty()){
			m_pDatabase->fnStart();                           // 데이터베이스 연결
		}
//	}

	m_iDBQueue = m_pDatabase->QueueCount;

	lbDBQueueCntV->Caption = IntToStr(m_iDBQueue) + L"EA";
	lbDBQueueCntV->Update();


	tmMain->Enabled = false;
	Application->ShowMainForm = true;
	Show();
}
//---------------------------------------------------------------------------
void __fastcall TMainF::fnProcDBResponse(TMessage a_stMsg)
{
	UnicodeString sErrorLog;
	TadResQuery *pResQry;
	pResQry = (TadResQuery*)a_stMsg.WParam;

	try{
//		enum TadDBResult      {drFail, drSuccess, drUnknown};
		if(pResQry->Result == drSuccess){                       // sql파일 경로가 잘못 되어있을 경우 drFail
			if(pResQry->JobID == 0000){
				fnLoginCheck(pResQry);
			}else if(pResQry->JobID == 8000){
//				fnGetUserGridInfo(pResQry);
			}else if(pResQry->JobID == 1000){
//				fnGetStockGridInfo(pResQry);
			}

		}else{
			sErrorLog  = "DB Result Error !! \r\n";
			sErrorLog += "==> Error Code : " + pResQry->ErrorCode + L"\r\n";
			sErrorLog += "==> Error Kind : " + IntToStr(pResQry->ErrorKind) + L"\r\n";
			sErrorLog += "==> Error Msg  : " + pResQry->ErrorMsg + L"\r\n";
			sErrorLog += "==> Error Msg  : " + pResQry->SQLText  + L"\r\n";
			sErrorLog += "DESCRIPTION : " + pResQry->Params->fnGetParamByNameStr("DESCRIPTION");
			fnWriteFileLog(sErrorLog);
		}
		delete pResQry;
	}catch(Exception &E){
		fnWriteAppStatus(L"ProcDBResponse\r\n" + E.Message);
	}
}
//---------------------------------------------------------------------------
void __fastcall TMainF::fnLoginCheck(TadResQuery *a_pResQry)
{
	if(a_pResQry->RecordCount){
		m_pAppInfo->LoginUser   = a_pResQry->fnFieldByName(L"NAME")->AsString;
		m_pAppInfo->UserAuth = a_pResQry->fnFieldByName(L"AUTHORITY")->AsInteger;
		fnSetVisibleLogin();
//		MainF->Show();
	}else{
		ShowMessage("아이디 혹은 비밀번호가 일치하지 않습니다.");
		edUsername->Text = "";
		edPassword->Text = "";
		edUsername->SetFocus();
	}
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
void __fastcall TMainF::cxButton1Click(TObject *Sender)
{
	MainF->Close();
}
//---------------------------------------------------------------------------
void __fastcall TMainF::cxButton2Click(TObject *Sender)
{
	if(WindowState == wsNormal){
		MainF->WindowState = wsMaximized;
		cxButton2->OptionsImage->ImageIndex = 1;
	}else{
		MainF->WindowState = wsNormal;
		cxButton2->OptionsImage->ImageIndex = 2;
	}
}
//---------------------------------------------------------------------------
void __fastcall TMainF::cxButton3Click(TObject *Sender)
{
	MainF->WindowState = wsMinimized;
}
//---------------------------------------------------------------------------
//	폼 드래그 기능
void __fastcall TMainF::pnWinBarMouseMove(TObject *Sender, TShiftState Shift, int X,
		  int Y)
{
	ReleaseCapture();
	MainF->Perform(WM_SYSCOMMAND, 0xf012,0);
}
//---------------------------------------------------------------------------
// 폼을 Resizeable 하게 만드는 코드(상단 보더부분 흰색 바가 생기는 오류있음.)
void __fastcall TMainF::CreateParams(TCreateParams& Params)
{
	if(m_eDBState == eLogin){
		TForm::CreateParams(Params);
		Params.Style = WS_POPUP | WS_THICKFRAME;
	}
}
//---------------------------------------------------------------------------
// 상단 보더 흰색 바 부분을 없애는 코드(모달폼 호출시 모달폼 클릭이 안되는 오류있음.)
// WndProc virtual method override
//void __fastcall TForm1::WndProc(TMessage &M)
//{
//  static RECT rect = {0};
//
//  switch (M.Msg)
//  {
//  case WM_CREATE:
//	  AdjustWindowRectEx(&rect, GetWindowLongPtr(Handle, GWL_STYLE) & ~WS_CAPTION, FALSE, NULL);
//	  rect.left *= -1;
//	  rect.top *= -1;
//	  return;
//
//  case WM_NCACTIVATE:
//	  return;
//
//  case WM_NCCALCSIZE:
//	  if (M.LParam)
//	  {
//		  NCCALCSIZE_PARAMS* sz = (NCCALCSIZE_PARAMS*)M.LParam;
//		  sz->rgrc[0].top += 3; //상단 보더를 완전히 없애려면 코멘트 처리
//		  sz->rgrc[0].left += rect.left;
//		  sz->rgrc[0].right -= rect.right;
//		  sz->rgrc[0].bottom -= rect.bottom;
//		  return;
//	  }
//	  break;
//
//  default:
//	  TForm::WndProc(M);
//  }
//}//---------------------------------------------------------------------------
void __fastcall TMainF::pnWinBarDblClick(TObject *Sender)
{
	if(WindowState == wsNormal){
		MainF->WindowState = wsMaximized;
		cxButton2->OptionsImage->ImageIndex = 1;
	}else{
		MainF->WindowState = wsNormal;
		cxButton2->OptionsImage->ImageIndex = 2;
	}
}
//---------------------------------------------------------------------------

void __fastcall TMainF::FormClose(TObject *Sender, TCloseAction &Action)
{
	Action = caFree;
}
//---------------------------------------------------------------------------

void __fastcall TMainF::FormDestroy(TObject *Sender)
{
	MainF = NULL;
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//===================== 각 버튼별 그리드폼 띄우는 코드 ======================

void __fastcall TMainF::dxBarLargeButton10Click(TObject *Sender)
{

	if(StockGridF == NULL){
		StockGridF = new TStockGridF(pnMain);
		StockGridF->Parent = pnMain;
		StockGridF->Align = alClient;
		StockGridF->AppInfo = m_pAppInfo;
		StockGridF->Show();
	}else{
		StockGridF->Parent = pnMain;
		StockGridF->Align = alClient;
		StockGridF->Show();
		StockGridF->btSearchClick(Sender);
	}
	dxBarLargeButton22->Enabled = true;
	cxGrid1 = StockGridF->cxGrid1;


//	dxBarLargeButton10->Down = true;
//	dxBarLargeButton13->Down = false;
//	dxBarLargeButton14->Down = false;
//	dxBarLargeButton15->Down = false;
//	dxBarLargeButton16->Down = false;
//	dxBarLargeButton17->Down = false;
//	dxBarLargeButton19->Down = false;
//	dxBarLargeButton20->Down = false;

//	m_eFormState = eStock;
}
//---------------------------------------------------------------------------

void __fastcall TMainF::dxBarLargeButton13Click(TObject *Sender)
{

	if(ReceiveGridF == NULL){
		ReceiveGridF = new TReceiveGridF(pnMain);
		ReceiveGridF->Parent = pnMain;
		ReceiveGridF->Align = alClient;
		ReceiveGridF->AppInfo = m_pAppInfo;
		ReceiveGridF->Show();
	}else{
		ReceiveGridF->Parent = pnMain;
		ReceiveGridF->Align = alClient;
		ReceiveGridF->Show();
		ReceiveGridF->btSearchClick(Sender);
	}
	dxBarLargeButton22->Enabled = true;
	cxGrid1 = ReceiveGridF->cxGrid1;


//	dxBarLargeButton10->Down = false;
//	dxBarLargeButton13->Down = true;
//	dxBarLargeButton14->Down = false;
//	dxBarLargeButton15->Down = false;
//	dxBarLargeButton16->Down = false;
//	dxBarLargeButton17->Down = false;
//	dxBarLargeButton19->Down = false;
//	dxBarLargeButton20->Down = false;
//	m_eFormState = eReceive;
}
//---------------------------------------------------------------------------

void __fastcall TMainF::dxBarLargeButton14Click(TObject *Sender)
{

	if(ReleaseGridF == NULL){
		ReleaseGridF = new TReleaseGridF(pnMain);
		ReleaseGridF->Parent = pnMain;
		ReleaseGridF->Align = alClient;
		ReleaseGridF->AppInfo = m_pAppInfo;
		ReleaseGridF->Show();
	}else{
		ReleaseGridF->Parent = pnMain;
		ReleaseGridF->Align = alClient;
		ReleaseGridF->Show();
		ReleaseGridF->btSearchClick(Sender);
	}
	if(m_pAppInfo->UserAuth == 0){
		ReleaseGridF->btCheck->Visible = false;
		ReleaseGridF->btCheck->Enabled = false;
	}else{
		ReleaseGridF->btCheck->Visible = true;
		ReleaseGridF->btCheck->Enabled = true;
	}
	dxBarLargeButton22->Enabled = true;
	cxGrid1 = ReleaseGridF->cxGrid1;


//	dxBarLargeButton10->Down = false;
//	dxBarLargeButton13->Down = false;
//	dxBarLargeButton14->Down = true;
//	dxBarLargeButton15->Down = false;
//	dxBarLargeButton16->Down = false;
//	dxBarLargeButton17->Down = false;
//	dxBarLargeButton19->Down = false;
//	dxBarLargeButton20->Down = false;
//	m_eFormState = eRelease;
}
//---------------------------------------------------------------------------

void __fastcall TMainF::dxBarLargeButton15Click(TObject *Sender)
{

	if(UsageGridF == NULL){
		UsageGridF = new TUsageGridF(pnMain);
		UsageGridF->Parent = pnMain;
		UsageGridF->Align = alClient;
		UsageGridF->AppInfo = m_pAppInfo;
		UsageGridF->Show();
	}else{
		UsageGridF->Parent = pnMain;
		UsageGridF->Align = alClient;
		UsageGridF->Show();
		UsageGridF->btSearchClick(Sender);
	}
	if(m_pAppInfo->UserAuth == 0){
		UsageGridF->btCheck->Visible = false;
		UsageGridF->btCheck->Enabled = false;

		UsageGridF->btDelete->Visible = false;
		UsageGridF->btDelete->Enabled = false;

	}else{
		UsageGridF->btCheck->Visible = true;
		UsageGridF->btCheck->Enabled = true;

		UsageGridF->btDelete->Visible = true;
		UsageGridF->btDelete->Enabled = true;
	}
	dxBarLargeButton22->Enabled = true;
	cxGrid1 = UsageGridF->cxGrid1;


//	dxBarLargeButton10->Down = false;
//	dxBarLargeButton13->Down = false;
//	dxBarLargeButton14->Down = false;
//	dxBarLargeButton15->Down = true;
//	dxBarLargeButton16->Down = false;
//	dxBarLargeButton17->Down = false;
//	dxBarLargeButton19->Down = false;
//	dxBarLargeButton20->Down = false;
//	m_eFormState = eUsage;
}
//---------------------------------------------------------------------------

void __fastcall TMainF::dxBarLargeButton16Click(TObject *Sender)
{

	if(RepairGridF == NULL){
		RepairGridF = new TRepairGridF(pnMain);
		RepairGridF->Parent = pnMain;
		RepairGridF->Align = alClient;
		RepairGridF->AppInfo = m_pAppInfo;
		RepairGridF->Show();
	}else{
		RepairGridF->Parent = pnMain;
		RepairGridF->Align = alClient;
		RepairGridF->Show();
		RepairGridF->btSearchClick(Sender);
	}

	if(m_pAppInfo->UserAuth == 0){
		RepairGridF->btCheck->Visible = false;
		RepairGridF->btCheck->Enabled = false;
	}else{
		RepairGridF->btCheck->Visible = true;
		RepairGridF->btCheck->Enabled = true;
	}
	dxBarLargeButton22->Enabled = true;
	cxGrid1 = RepairGridF->cxGrid1;


//	dxBarLargeButton10->Down = false;
//	dxBarLargeButton13->Down = false;
//	dxBarLargeButton14->Down = false;
//	dxBarLargeButton15->Down = false;
//	dxBarLargeButton16->Down = true;
//	dxBarLargeButton17->Down = false;
//	dxBarLargeButton19->Down = false;
//	dxBarLargeButton20->Down = false;
//	m_eFormState = eRepair;
}
//---------------------------------------------------------------------------

void __fastcall TMainF::dxBarLargeButton17Click(TObject *Sender)
{

	if(TempleGridF == NULL){
		TempleGridF = new TTempleGridF(pnMain);
	}
		TempleGridF->Parent = pnMain;
		TempleGridF->Align = alClient;
		TempleGridF->AppInfo = m_pAppInfo;
		TempleGridF->Show();
		TempleGridF->btSearchClick(Sender);

	dxBarLargeButton22->Enabled = true;
	cxGrid1 = TempleGridF->cxGrid1;


//	dxBarLargeButton10->Down = false;
//	dxBarLargeButton13->Down = false;
//	dxBarLargeButton14->Down = false;
//	dxBarLargeButton15->Down = false;
//	dxBarLargeButton16->Down = false;
//	dxBarLargeButton17->Down = true;
//	dxBarLargeButton19->Down = false;
//	dxBarLargeButton20->Down = false;
//	m_eFormState = eTemple;

//	if(TempleGridF == NULL){
//		TempleGridF = new TTempleGridF(pnMain);
//		TempleGridF->Parent = pnMain;
//		TempleGridF->Align = alClient;
//		TempleGridF->AppInfo = m_pAppInfo;
//		TempleGridF->Show();
//	}else{
//		TempleGridF->Parent = pnMain;
//		TempleGridF->Align = alClient;
//		TempleGridF->Show();
//		TempleGridF->btSearchClick(Sender);
//	}
}
//---------------------------------------------------------------------------

void __fastcall TMainF::dxBarLargeButton19Click(TObject *Sender)
{

	if(m_pAppInfo->UserAuth == 0){
		MessageBox(Handle, L"일반사용자 접근불가.", L"제품목록", 0);
		return;
	}else{
		if(ItemGridF == NULL){
			ItemGridF = new TItemGridF(pnMain);
		}
			ItemGridF->Parent = pnMain;
			ItemGridF->Align = alClient;
			ItemGridF->AppInfo = m_pAppInfo;
			ItemGridF->Show();
			ItemGridF->btSearchClick(Sender);
	}
	dxBarLargeButton22->Enabled = true;
	cxGrid1 = ItemGridF->cxGrid1;


//	dxBarLargeButton10->Down = false;
//	dxBarLargeButton13->Down = false;
//	dxBarLargeButton14->Down = false;
//	dxBarLargeButton15->Down = false;
//	dxBarLargeButton16->Down = false;
//	dxBarLargeButton17->Down = false;
//	dxBarLargeButton19->Down = true;
//	dxBarLargeButton20->Down = false;
//	m_eFormState = eItem;

//	if(ItemGridF == NULL){
//		ItemGridF = new TItemGridF(pnMain);
//		ItemGridF->Parent = pnMain;
//		ItemGridF->Align = alClient;
//		ItemGridF->AppInfo = m_pAppInfo;
//		ItemGridF->Show();
//	}else{
//		ItemGridF->Parent = pnMain;
//		ItemGridF->Align = alClient;
//		ItemGridF->Show();
//		ItemGridF->btSearchClick(Sender);
//	}
}
//---------------------------------------------------------------------------

void __fastcall TMainF::dxBarLargeButton20Click(TObject *Sender)
{

	if(m_pAppInfo->UserAuth == 0){
		MessageBox(Handle, L"일반사용자 접근불가.", L"사용자", 0);
		return;
	}else{
		if(UserGridF == NULL){
			UserGridF = new TUserGridF(pnMain);
		}
			UserGridF->Parent = pnMain;
			UserGridF->Align = alClient;
			UserGridF->AppInfo = m_pAppInfo;
			UserGridF->Show();
			UserGridF->btSearchClick(Sender);
	}
	dxBarLargeButton22->Enabled = true;
	cxGrid1 = UserGridF->cxGrid1;



//	dxBarLargeButton10->Down = false;
//	dxBarLargeButton13->Down = false;
//	dxBarLargeButton14->Down = false;
//	dxBarLargeButton15->Down = false;
//	dxBarLargeButton16->Down = false;
//	dxBarLargeButton17->Down = false;
//	dxBarLargeButton19->Down = false;
//	dxBarLargeButton20->Down = true;

//	m_eFormState = eUser;

//	if(UserGridF == NULL){
//		UserGridF = new TUserGridF(pnMain);
//		UserGridF->Parent = pnMain;
//		UserGridF->Align = alClient;
//		UserGridF->AppInfo = m_pAppInfo;
//		UserGridF->Show();
//	}else{
//		UserGridF->Parent = pnMain;
//		UserGridF->Align = alClient;
//		UserGridF->Show();
//		UserGridF->btSearchClick(Sender);
//	}

}
//===========================================================================
//===========================================================================


//---------------------------------------------------------------------------

void __fastcall TMainF::Panel3MouseMove(TObject *Sender, TShiftState Shift, int X,
		  int Y)
{
	ReleaseCapture();
	MainF->Perform(WM_SYSCOMMAND, 0xf012,0);
}
//---------------------------------------------------------------------------

void __fastcall TMainF::imLoginClick(TObject *Sender)
{
	TadReqQuery *pReqQry;
	UnicodeString sSql;

	try{
		pReqQry = new TadReqQuery(m_pAppInfo->MQMgr);
		pReqQry->JobID     = 0000;
//		enum TadDBJobType     {djtSelect, djtInsert, djtUpdate, djtDelete, djtCancel, djtClear, djtInsertArray, djtTransaction};
		pReqQry->JobType   = djtSelect;
//		enum TadDBQueryType   {dqtExecute, dqtOpen};
		pReqQry->QueryType = dqtOpen;
		pReqQry->SQLFile   = GetCurrentDir() + "\\Sql\\GridSql\\UserGrid.sql";	// sql파일 경로 지정

		pReqQry->FixedSession = false;
		pReqQry->NeedResponse = true;

		if(edUsername->Text.IsEmpty()){
			ShowMessage("아이디를 입력하세요.");
			edUsername->SetFocus();
			return;
		}else{
			if(edPassword->Text.IsEmpty()){
				ShowMessage("비밀번호를 입력하세요.");
				edPassword->SetFocus();
				return;
			}else{
				sSql.sprintf(L"WHERE USER_ID = '%s' AND PASSWORD = '%s';",
									edUsername->Text, edPassword->Text);
			}
		}
		pReqQry->Variables->fnSetSQLVarByName("A1", sSql);


		pReqQry->fnSetFormHandle(Handle);
		pReqQry->fnSendRequest(m_pAppInfo->DBPM);       // 데이터 요청
	}catch(Exception &E){
		fnWriteAppStatus(L"imLoginClick\r\n" + E.Message);
	}

}
//---------------------------------------------------------------------------

void __fastcall TMainF::edUsernameKeyPress(TObject *Sender, System::WideChar &Key)

{
	if(Key == VK_RETURN){
		imLoginClick(Sender);
	}
}
//---------------------------------------------------------------------------

void __fastcall TMainF::edPasswordKeyPress(TObject *Sender, System::WideChar &Key)

{
	if(Key == VK_RETURN){
		imLoginClick(Sender);
	}
}
//---------------------------------------------------------------------------

void __fastcall TMainF::btnSaveClick(TObject *Sender)
{
	try{
		m_pAppInfo->DB_ServerName	 = edDBNameV->Text;
		m_pAppInfo->DB_UserName		 = edDBUserV->Text;
		m_pAppInfo->DB_Password		 = edDBPasswdV->Text;
		m_pAppInfo->DB_MaxSessionCnt = edDBSessionCntV->Value;
		m_pAppInfo->DB_SessionChkInt = edDBSessionChkV->Value;

		m_pAppInfo->AppPosX			 = Left;
		m_pAppInfo->AppPosY			 = Top;

		m_pAppInfo->fnSaveConfig();   	// 실행파일 폴더에 config.tmp파일로 데이터저장
	}catch(const Sysutils::Exception &E){

	}
}
//---------------------------------------------------------------------------

void __fastcall TMainF::FormShow(TObject *Sender)
{
	m_pFileLogger->BaseFilePath = GetCurrentDir();
	m_pFileLogger->Active		= true;
	m_pAppInfo->FileLoggerID	= m_pFileLogger->FileLoggerID; 		// 이 명령 실행 후 로그폴더생성 및 로그폴더안에 현재날짜폴더 생성
	fnWriteAppStatus(L"MAIN : Start the FileLogger");

	edDBNameV->Text		   = m_pAppInfo->DB_ServerName;
	edDBUserV->Text		   = m_pAppInfo->DB_UserName;
	edDBPasswdV->Text	   = m_pAppInfo->DB_Password;
	edDBSessionCntV->Value = m_pAppInfo->DB_MaxSessionCnt;
	edDBSessionChkV->Value = m_pAppInfo->DB_SessionChkInt;

//	Left				   = m_pAppInfo->AppPosX;
//	Top					   = m_pAppInfo->AppPosY;

	MainF->Position		   = poScreenCenter;
	tmMain->Enabled 	   = true;                                  // 타이머 실행
	edUsername->SetFocus();
}
//---------------------------------------------------------------------------

void __fastcall TMainF::cxImage2Click(TObject *Sender)
{
	if(m_iKeyCount == m_iCountValue){
		pnDatabase->Visible = true;
		pnLogin->Visible = false;
		m_iKeyCount = 0;
	}
	m_iKeyCount++;
}
//---------------------------------------------------------------------------

void __fastcall TMainF::cxImage1Click(TObject *Sender)
{
	if(m_iLockCount == m_iCountValue){
		pnLogin->Visible = true;
		pnDatabase->Visible = false;
		m_iLockCount = 0;
	}
	m_iLockCount++;
}
//---------------------------------------------------------------------------

void __fastcall TMainF::btLogoutClick(TObject *Sender)
{
	fnExeDeleteFormInfo();
	fnSetVisibleLogout();
}
//---------------------------------------------------------------------------
void __fastcall TMainF::btMainUserRegClick(TObject *Sender)
{
	if(UserF == NULL){
		UserF = new TUserF(NULL);
		UserF->AppInfo = m_pAppInfo;
	}

	UserF->lbAuth->Visible = false;
	UserF->pnAuth->Visible = false;

	if(UserF->ShowModal() == mrOk){
		MessageBox(Handle, L"등록 되었습니다.", L"사용자", 0);
	}else{
		MessageBox(Handle, L"등록 취소", L"사용자", 0);
	}

	delete UserF;
//	btSearchClick(Sender);
}
//---------------------------------------------------------------------------


void __fastcall TMainF::btMainAdminRegClick(TObject *Sender)
{
	if(UserF == NULL){
		UserF = new TUserF(NULL);
		UserF->AppInfo = m_pAppInfo;
	}

	if(UserF->ShowModal() == mrOk){
		MessageBox(Handle, L"등록 되었습니다.", L"사용자", 0);
	}else{
		MessageBox(Handle, L"등록 취소", L"사용자", 0);
	}

	delete UserF;
}
//---------------------------------------------------------------------------


void __fastcall TMainF::dxBarLargeButton22Click(TObject *Sender)
{

   String fileName;
   SaveDialog1->DefaultExt = "xls";
   if(SaveDialog1->Execute()) {
		 fileName = SaveDialog1->FileName;
   }
   else
	return;
   ExportGridToExcel(fileName, cxGrid1, true, true, true, "xls");

   if (MessageDlg("File saved on " + fileName + "\Open?", mtInformation, TMsgDlgButtons() << mbYes << mbNo, 0L) == mrYes) {
	   ShellExecute (Handle, L"open", (wchar_t *)fileName.c_str(), NULL, NULL, SW_SHOWNORMAL);
   }



//	if(m_eFormState == eStock){
//	}else if(m_eFormState = eReceive){
//	}else if(m_eFormState = eRelease){
//	}else if(m_eFormState = eUsage){
//	}else if(m_eFormState = eRepair){
//	}else if(m_eFormState = eTemple){
//	}else if(m_eFormState = eItem){
//	}else if(m_eFormState = eUser){
//	}
}
//---------------------------------------------------------------------------

void __fastcall TMainF::edUsernameClick(TObject *Sender)
{
	edUsername->SelectAll();
}
//---------------------------------------------------------------------------





void __fastcall TMainF::btLoginExitClick(TObject *Sender)
{
		MainF->Close();
}
//---------------------------------------------------------------------------

