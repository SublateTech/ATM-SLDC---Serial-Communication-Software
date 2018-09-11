
#define STRICT

#include <Windows.h>
#include <String.h>
#include <dos.h>
#include "winsock.h"
#include "DiskId.h"
#include "resource.h"



LPSTR DiskId::getDialogName()
{
    return "IDD_KEY";
}

BOOL DiskId::dispatch( HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam )
{
    switch( msg )
        {

        case WM_INITDIALOG:
            
            SetDlgItemText(hDlg, IDC_KEY, m_szATMKey);
            return TRUE;        // no initialization.

        case WM_COMMAND:

            switch (wParam)
            	{
            	case IDOK:
            		char szKey [10];
	           		GetDlgItemText(hDlg, IDC_ATM, szKey,10);
	           		WritePrivateProfileString("ATM", "ATMKey", szKey,  "BBVA.ini");
	           		            	
            	case IDCANCEL:
            	     EndDialog( hDlg, TRUE );  // selecting OK or Cancel
                	 return TRUE;              // terminates the dialog
                }

        default:                // if we don't handle it, pass it
                                // to our parent.

            return ModalDialog::dispatch( hDlg, msg, wParam, lParam );

        }
}


LPSTR DiskId::GetHostIp()
        {
        	
        
        	#define WINSOCK_VERSION 0x0101
        
        	char 		szTemp[80];
        	WSADATA 	wsaData;
        	LPHOSTENT 	lpHostEntry;				// Estructura de datos del anfitrión en Internet
        	DWORD 		dwIPAddr;					// Dirección IP como un entero doble sin signo
        	char 		szUserEntry[20];
        	UINT 		*p1;		
        
			// 	Aquí inicia el programa
			WSAStartup(WINSOCK_VERSION, &wsaData);
		
			strcpy(szUserEntry, "");
		
			lpHostEntry = gethostbyname(szUserEntry);
		
			if (!lpHostEntry)
				dwIPAddr = inet_addr(szUserEntry);
			
			if ((!lpHostEntry)  && (dwIPAddr == INADDR_NONE) ) 
				{
				wsprintf(szTemp,"No se puede resolver %s\n",szUserEntry);
				MessageBox(NULL, szTemp,"",0);
		    	}
		
			//wsprintf(szTemp,"Host name  : %s	\nIP Address  : %s", lpHostEntry->h_name, inet_ntoa(*(LPIN_ADDR)*(lpHostEntry->h_addr_list)));
    		
    		dwIPAddr = inet_addr(inet_ntoa(*(LPIN_ADDR)*(lpHostEntry->h_addr_list)));
    		
    		p1= (UINT *) &dwIPAddr;
			wsprintf(szTemp, "%04X-%04X", *(p1) , *(p1+1));

    		//MessageBox(NULL, szTemp,"",0);
    			        
                
			WSACleanup();
			
			_fstrcpy(m_Ip, szTemp);
      		return (m_Ip);
			
			
                     
        }   
        
        
LPSTR DiskId::GetATMKey()
{
 	DWORD dwC;  //Serial Drive C
	DWORD dwD;  //Serial Drive D
	DWORD dwIp; //Serial Ip
	UINT 		*p1;		
			  
	
	m_drive	= 3;
	GetInfo();
	dwC 	=  	m_SerialNum;
	_fmemset(m_szATMKey, 0, sizeof(m_szATMKey));
	_fstrcpy(m_szATMKey, m_Serial);
	m_drive	= 4;
	GetInfo();
	dwD 	=   m_SerialNum;       
	_fstrcat(m_szATMKey, "-");
	_fstrcat(m_szATMKey, m_Serial);
	GetHostIp();
	dwIp 	=   m_IpNum;
	_fstrcat(m_szATMKey, "-");
	_fstrcat(m_szATMKey, m_Ip);
	
	
	//Calculamos
		
	dwC = dwC | dwD;
	dwC = dwC | dwIp;
	
	p1= (UINT *) &dwC;
	_fmemset(m_ATMKey, 0, sizeof(m_ATMKey));
	wsprintf(m_ATMKey, "%04X-%04X", *(p1) , *(p1+1));
	                    	
	//MessageBox(NULL,m_ATMKey,"",0); 	
	return (m_ATMKey);	
}	

void DiskId::TestSerialId()
		{
		      			  
			  char szASL[80];
			  char szATM[80];
			  
			  GetPrivateProfileString("ATM", "ATMKey", "", szASL, 80, "BBVA.ini");
			  
			  _fstrcpy(szATM,GetATMKey());
			  
			  if (_fstrcmp(szASL,szATM ))
			  		{
			  	    	 						
						//DialogBox(hAppInstance, (LPCSTR) IDD_KEY,  hAppWnd,  (DLGPROC) Disk::DlgKey);  
			  			//WritePrivateProfileString("ATM", "ATMKey", szATM,  "BBVA.ini");
			  			
			  			this->run();
			  		}
				
		
}

void DiskId::GetInfo()
{                       		
                      	          	
          	if (m_lastdrive != m_drive)	   
           
           		{	    
                    
                    
          			union REGS r;
      				struct SREGS s;
      				
          			UINT  *p1;
          
   					UINT  drive;
   					MID	_far *MediaID;
        	        
        	        MediaID = new  MID;
        	        
        	        drive = m_drive;
      				      
      				r.x.ax 	= 	0x6900;
      				r.x.bx 	= 	drive;
      				r.h.ch 	=	0x08;
					r.h.cl	=	0x66;
					r.x.ax	=	0x440D;    
					
					r.x.dx	=	_FP_OFF(MediaID);	 	//ds:dx MID
						      				
      				segread(&s);
      				s.ds	=	_FP_SEG(MediaID);
      				
      				intdosx(&r, &r, &s);
      				if (r.x.cflag)
            			*m_Serial = '\0';
            		
            		m_lastdrive			=	m_drive;
			    	
			    
			    	
			        _fmemset(m_VolLabel, 0, sizeof(m_VolLabel));
			    	_fstrncpy(m_VolLabel, MediaID->midVolLabel,11);
			    	_fmemset(m_FileSysType, 0, sizeof(m_FileSysType));
			        _fstrncpy(m_FileSysType, MediaID->midFileSysType,8);
			    			    	
			    	
			    	m_SerialNum 		= 	MediaID->midSerialNum;       
			    	p1= (UINT *) &MediaID->midSerialNum;	
            		_fmemset(m_Serial, 0, sizeof(m_Serial));
            		wsprintf(m_Serial, "%04X-%04X", *(p1+1) , *p1);
			    	//MessageBox(NULL, m_Serial, "",0);
			    				    				    	
			    	
			    	delete MediaID;
			    	
			    	
			    	
			    }
   			
}
    
LPSTR  DiskId::GetVolLabel(UINT Drive)
{
m_drive = Drive;
GetInfo();
return (m_VolLabel);
}


LPSTR DiskId::GetSerial(UINT Drive)
{
	m_drive = Drive;
	GetInfo();
        
	return (m_Serial);
      				
return (m_Serial);
}
