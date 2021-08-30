//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <tchar.h>
//---------------------------------------------------------------------------
USEFORM("RegisterU\ReceiveU.cpp", ReceiveF);
USEFORM("RegisterU\ReleaseCheckU.cpp", ReleaseCheckF);
USEFORM("RegisterU\ReleaseU.cpp", ReleaseF);
USEFORM("RegisterU\ItemUpdU.cpp", ItemUpdF);
USEFORM("RegisterU\LoginU.cpp", LoginF);
USEFORM("RegisterU\ReceiveCheckU.cpp", ReceiveCheckF);
USEFORM("RegisterU\RepairCheckU.cpp", CheckF);
USEFORM("RegisterU\UsageU.cpp", UsageF);
USEFORM("RegisterU\UserU.cpp", UserF);
USEFORM("RegisterU\UserUpdU.cpp", UserUpdF);
USEFORM("RegisterU\RepairU.cpp", RepairF);
USEFORM("RegisterU\TempleU.cpp", TempleF);
USEFORM("RegisterU\TempleUpdU.cpp", TempleUpdF);
USEFORM("FormGridU\ReleaseGridU.cpp", ReleaseGridF);
USEFORM("FormGridU\RepairGridU.cpp", RepairGridF);
USEFORM("FormGridU\StockGridU.cpp", StockGridF);
USEFORM("FormGridU\ItemGridU.cpp", ItemGridF);
USEFORM("FormGridU\ReceiveGridU.cpp", ReceiveGridF);
USEFORM("FormGridU\TempleGridU.cpp", TempleGridF);
USEFORM("RegisterU\ItemU.cpp", ItemF);
USEFORM("FormGridU\UsageGridU.cpp", UsageGridF);
USEFORM("FormGridU\UserGridU.cpp", UserGridF);
USEFORM("MainU.cpp", MainF);
//---------------------------------------------------------------------------
int WINAPI _tWinMain(HINSTANCE, HINSTANCE, LPTSTR, int)
{
	HANDLE Mutex;
	try
	{
        const wchar_t ProgMutex[] = L"ErpProject";

		if((Mutex=OpenMutex(MUTEX_ALL_ACCESS, false, ProgMutex))==NULL){
			Mutex = CreateMutex(NULL, true, ProgMutex);
		}else{
			return 0;
		}

		Application->Initialize();
		Application->MainFormOnTaskBar = true;
		Application->CreateForm(__classid(TMainF), &MainF);
		Application->Run();
	}
	catch (Exception &exception)
	{
		Application->ShowException(&exception);
	}
	catch (...)
	{
		try
		{
			throw Exception("");
		}
		catch (Exception &exception)
		{
			Application->ShowException(&exception);
		}
	}
    ReleaseMutex(Mutex);
	return 0;
}
//---------------------------------------------------------------------------
