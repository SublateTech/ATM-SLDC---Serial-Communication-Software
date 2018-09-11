// Implementation of service-oriented functionality of ATM32

#include "windows.h"
#include "string.h"
#include "stdlib.h"
#include "CommPort.h"
#include "bbva.h"



// Error message logging
void LogErrorMsg(char *message);


CommPort::CommPort()
{
	m_port = GetPort();
	m_status = FALSE;
	
}


void CommPort::Init()
{
if (Open())
	m_status = TRUE;
else
	m_status = FALSE;
}

CommPort::~CommPort()
{

if (m_status)
	Close();

}

BOOL CommPort::Open(UINT Port)
{
	m_port = Port;
	return (Open());
}

BOOL CommPort::Open()
{
   char szASL[80];
   int err;
   
   wsprintf(szASL, "COM%i", m_port);
      
   m_hcomm = OpenComm( szASL, RXQUEUE, TXQUEUE );
    if (m_hcomm < 0)
 	{ 
 	  // MessageBox(NULL,"OpenComm","Error",MB_OK | MB_ICONHAND);
       return ( FALSE ) ;
    }
      
   strcat(szASL,":19200,n,8,1");
   
   err = BuildCommDCB(szASL, &dcb);
   if (err < 0) {
    	//MessageBox(NULL, "BuildCommDCB","Error", MB_OK | MB_ICONHAND); 
     	return FALSE;
		}     
		         
	err = SetCommState(&dcb);
	if (err < 0) {
    	//MessageBox(NULL, "SetCommState","Error", MB_OK | MB_ICONHAND); 
    	return FALSE;
	}
    
    m_status = TRUE; 
return TRUE;
}


BOOL  CommPort::Close()
{

if (m_status)
{
   CloseComm( m_hcomm ) ;
   m_status = FALSE;
 
}
   return ( TRUE ) ;

} // end of CloseConnection()


BOOL  CommPort::WriteBlock( LPSTR lpByte , DWORD dwBytesToWrite)
{

   BOOL        fWriteStat ;
//   DWORD       dwBytesWritten ;
//   char        szError[ 128 ] ;


   
   fWriteStat = WriteComm( m_hcomm, lpByte, (UINT) dwBytesToWrite) ;

    return ( fWriteStat ) ;

} // end of WriteCommBlock()

DWORD  CommPort::ReadBlock( LPSTR lpByte , DWORD dwBytesToRead)
{

    return ( ReadComm( m_hcomm, lpByte, (UINT) dwBytesToRead) ) ;
} 


BOOL CommPort::Send( LPSTR lpByte )
{
  
    
    return ( WriteBlock( lpByte, _fstrlen(lpByte))) ;

}

UINT CommPort::GetPort()
{
	char szASL[80];
	int  dPort;
	
	GetPrivateProfileString("ATM", "Output", "0", szASL, 80, "BBVA.ini");
	if (!strcmp(szASL, "0"))
	   dPort = 5;
	else
	   dPort = atoi(szASL);  
    
    return  dPort;

}