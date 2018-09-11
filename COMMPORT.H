// This class handles creation of a system-tray icon & menu

class CommPort;

#if (!defined(_WIN_CommPort))
	#define _WIN_CommPort


#include "windows.h"



#define GWL_NPTTYINFO        0
#define TTYEXTRABYTES        sizeof( LONG )



#define ATOM_TTYINFO       0x100

// hard coded maximum number of ports for device under Win32

#define MAXPORTS        4


#define USECOMM      // yes, we need the COMM API




#define MAXLEN_TEMPSTR  81

//#define RXQUEUE         4096
//#define TXQUEUE         4096


// Flow control flags

#define FC_DTRDSR       0x01
#define FC_RTSCTS       0x02
#define FC_XONXOFF      0x04

// ascii definitions

#define ASCII_BEL       0x07
#define ASCII_BS        0x08
#define ASCII_LF        0x0A
#define ASCII_CR        0x0D
#define ASCII_XON       0x11
#define ASCII_XOFF      0x13


// CRT mappings to NT API

#define _fmemset   memset
#define _fmemmove  memmove


// The tray menu class itself
class  CommPort
{
public:
	CommPort();
	~CommPort();
	void Init();

	
	BOOL Open( );
	BOOL Open(UINT Port);
	BOOL Close( );
	BOOL WriteBlock( LPSTR lpByte , DWORD dwBytesToWrite);
	DWORD ReadBlock( LPSTR lpByte , DWORD dwBytesToRead);
	BOOL Send( LPSTR lpByte );
	BOOL m_status;
	BOOL OpenOk() { return m_status; } ;
	void SetPort(UINT port) { m_port=port;};
	UINT GetPort();

	int				m_port; 
	int				m_hcomm;
	DCB 			dcb;

	DWORD dwError;
	
};


#endif
