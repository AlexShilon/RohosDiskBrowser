/**
��� �������� ��� ��������� �������

*/
/*
class COpenedFiles
{
   public:
    int _Count;// ������ ������
	int _Ichel;// Index of CHanged ELement
     
	struct
	{
		char Path[500];// ���� � �����
		char FileName[500];// ��� �����
		LPFILETIME Time;// ����� ����� ���� ��� ������ � ��������� ���

	} _FList[50];//  ��� ������


	FILETIME* GetFileTimeByName(CString fname, int FullPathFlag=0, LPFILETIME Created=NULL);// �� ����� ����� ���������� ���� � ����� ��� ���������� ���������
	int Add(char *Path, char *FileName);//��������� � ����� ������ ��� ���� ����
	int DeleteElement(DWORD in);//������� �� ������ �������� ������� 
	int Clear();//�������� ��� �������� 
	int CheckForChanges(void);//��������� ��� �������� ����� �� ���������


		COpenedFiles();
		~COpenedFiles();	
};
*/



// ofList.cpp: implementation of the COpenedFiles class.
//
//////////////////////////////////////////////////////////////////////
#include "pub.h"

#include "Shlwapi.h"// PathFileExists(...);
//#include "Dlg_FilesChanged.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction //////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
//---------------------------------------------------------------------------------
COpenedFiles::COpenedFiles()
{
	_Count=0;
}
COpenedFiles::~COpenedFiles(){}
//////////////////////////////////////////////////////////////////////////////////
//  ��������� � ������ ��� ���� ������� ///////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
int COpenedFiles::Add(char *Path, char *FileName)
{ 
	// ���� � ���������� "�" �� ���������� �� ����� ������� ����� ������� ���������
	// � ���� ���������� �� �.�. ����� ������� i-���
	DWORD k=_Count;
	bool add=true;// ��������������� ����

	//��������� �� ������� ������������� ������ ������
	for(int i=0;i<=(_Count-1);i++)
	{
		//  ���� ������� '���� � ��� �����' ��������� � ������� i-���� ��������
		if( !_tcscmp(_FList[i].Path,Path)  &&  !_tcscmp(_FList[i].FileName, FileName)   )
		{	
			// �� ����� ������� ���� ������� � ������� - i
			k=i;			
			add=false;// ����������� ������ �� ����
			break;
		}
	}

   _tcscpy(_FList[k].Path    , Path);// ������ ������ ���� 
   _tcscpy(_FList[k].FileName, FileName);// � ����� �����
      
   _FList[k].Time=new FILETIME;
    
   //   ���������� ����      �����  ���������   �����    �����
   _FList[k].Time=GetFileTimeByName(FileName);
   
    // ���� ���� ��������� ������ ��
   if(add)
   {
	   _Count++;// ������ �������������
   }
 
   return 1;
}
//--------------------------------------------------------------------------------
//////////////////////////////////////////////////////////////////////////////////
//  ������� �� ������ �������� ������� ///////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
//--------------------------------------------------------------------------------
int COpenedFiles::DeleteElement(DWORD in)
{
	//		     i->	               -|
	//
	//				  <=      <=            <=
	//	[0][..][in][..][..][..][..][_Count-1][_Count]
	//			  <=	  <=      <=                
	//	������ ����������� ������� ����������� ��� ��� ����� � ����� �� ����
	for (int i=in;i<=(_Count-1);i++)	 
	{
		_tcscpy(_FList[i].Path    , _FList[i+1].Path);// ����
		_tcscpy(_FList[i].FileName, _FList[i+1].FileName);// ��� �����
		_FList[i].Time=_FList[i+1].Time;//  ����� ��������� �����
	}
	
	_Count--;// ������ �����������
	
	return 1;
	
}
//////////////////////////////////////////////////////////////////////////////////
//  �������� ��� �������� ////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
int COpenedFiles::Clear()
{ 
	// ����� ����� ������
	for(int i=0;i<=(_Count-1);i++)
	{ 
		// ��������� i - ���� ��������
		_tcscpy(_FList[i].FileName,"");
		_tcscpy(_FList[i].Path,"");
		        _FList[i].Time=NULL;
		
	}
	_Count=0;// ��������� ������� ������

	return 1;
}
//////////////////////////////////////////////////////////////////////////////////
//  ��������� ��� �������� ����� �� ��������� ////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
int COpenedFiles::CheckForChanges(void)
{
    //  ����� ����� ������
	for (int i=0; i<= (_Count -1); i++)
	{ 
		LPFILETIME ft=new FILETIME;

		ft=GetFileTimeByName(_FList[i].FileName);/// ���������� ���� �� �����
		if(!ft)		
		{
			// � ���� ������ �� ����������
			// ������ �����...
			continue;
		}
			// ���� ���� ��� ������
		if(0 != CompareFileTime( ft, _FList[i].Time) )
		{
			// �������� ����� ��������� i-���� �������� ������ �������� ������
			_FList[i].Time=ft;
			  _Ichel=i; 
		    return 1;
		}
	}
	
	return 0;
}
//------------------------------------------------------------------------------
//////////////////////////////////////////////////////////////////////////////////
// �� ����� ����� ���������� ���� � ����� ��� ���������� ��������� ///////////////
// ����� ���� ���������� ��������� ������� ���������� ���� �������� ����� ////////
//  ����� �������� �������� - Created ////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
FILETIME* COpenedFiles::GetFileTimeByName(CString fname, int FullPathFlag, LPFILETIME Created)
{ 
	
	LPFILETIME ft;
	ft=new FILETIME; 

	TCHAR pnp[500];// pnp = ��� ������ ����

	
	// ���� "fname" ��� ������ ��� ����� ������������ ��� ������
	if(!FullPathFlag)
	{
	    GetPodNogamiPath_Temp(pnp);
		// ����� ����� �����: "D:\rohos\DiskViewer\TL_NTFSREADER___Win32_Debug\temporary files\"
	}
	else
	{// ���� "fname" ��� ������ ���� � �����
		_tcscpy(pnp, "");	 
	}

	 //����� �����:
	_tcscat(pnp,fname);
	// pnp= "D:\rohos\DiskViewer\TL_NTFSREADER___Win32_Debug\temporary files\filename.ext"
	
	// Handle to opened file
	HANDLE hfile = CreateFile(pnp, 0,
								FILE_SHARE_WRITE | FILE_SHARE_READ, NULL,	OPEN_EXISTING,
									FILE_ATTRIBUTE_NORMAL,NULL);
	// ���� ����� �� �������
	if(hfile==INVALID_HANDLE_VALUE)
	{
		 WriteLog("INVALID_HANDLE_VALUE: Filename:(%s)",pnp);			
		 // ����� ������ ������ ������
		 return NULL;
	}
	// ����������� �� ����� ���������� � ��� ��������, �������� � ���������
	if( !GetFileTime(hfile, Created/*created*/, NULL/*last acces*/, ft/*last write*/) )
	{
		CloseHandle(hfile);
		// �� ����������...
	 //AfxMessageBox(get_msg(MSG_GETFILETIME_ERROR), MB_ICONINFORMATION);
		return NULL;
	}
	CloseHandle(hfile);
    return ft;
}
