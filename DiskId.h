#if !defined( __DISKID_H )
	#define __DISKID_H


#include <Windows.h>
#include "BBVAWin.h"

struct MID
		{
		WORD 	midInfoLevel;
		DWORD	midSerialNum;
		char 	midVolLabel[11];
		char 	midFileSysType[8];
		};


class DiskId : public ModalDialog
{

public:

    DiskId( HWND );
    
    void TestSerialId();
        
	
private:

    UINT 	m_lastdrive;
	UINT 	m_drive;
	char	m_VolLabel[11];
	char	m_Serial[20]; 
	char	m_FileSysType[8];
	DWORD 	m_SerialNum;
	DWORD 	m_IpNum;
	char	m_Ip[20];
	char	m_szATMKey[80];     
	char	m_ATMKey[20]; 	

    
    virtual LPSTR getDialogName();
    virtual BOOL dispatch( HWND, UINT, WPARAM, LPARAM );
    
    	
	
	Disk( HWND);
	LPSTR GetFileSysType(UINT Drive);
	LPSTR GetVolLabel(UINT Drive);
	LPSTR GetSerial(UINT Drive);
	LPSTR GetSerialId(UINT Drive);
	LPSTR GetHostIp();
	void  GetInfo();
	LPSTR  GetATMKey();
	


};


class TodoEntry;                // forward reference



//---------------------------------------------------------------------
//
//  inline functions
//
//---------------------------------------------------------------------

inline DiskId::DiskId( HWND hOwner ) : ModalDialog( hOwner )
{
}


#endif  // __TODODLGS_H

