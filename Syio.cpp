//#include "stdhdrs.h"
#include "windows.h"
#include "string.h"

#include "syio.h"   


Moxa::Moxa()
{
	nTimer = 0;
	m_timer = 500;
	m_transac = FALSE;
	m_status = FALSE;
	m_control = FALSE;
	strcpy(m_mens,"");

	serial = new CommPort();
	if (serial == NULL)
		{
			m_status = FALSE;
			MessageBox(NULL,"", "No se pudo abrir el puerto serial",0);
			//PostQuitMessage(0);
		}

}

Moxa::~Moxa()
{

	if (serial!=NULL)
		delete serial;
	Close();
}

BOOL Moxa::Open()
{

    int i;
	m_status = FALSE;

    if ((i = MSAInit()) <= 0)
    	{ 				
		//	wsprintf(szASL, "MOXA INIT error %d \nNo se pudo inicializar la tarjeta", i);     
		//	MessageBox(NULL, szASL, NULL, MB_OK | MB_ICONHAND);
			
    	}  
    	else	m_status = TRUE; 
    	
    	

return m_status;


}

Moxa::Close()
{
	MSAEnd();
	return TRUE;
}



void  Moxa::ATMProc()

{
	   
	int i	,	n=0; 
   	char 	*pStr;
	frame_t rxFrame;
   	
   	
   	//SetWindowText(NULL, (LPSTR) szTemp);
   	   	   	
   	if (m_status) 
	{
    	if (nTimer > 10000)
    	  	{
    		nTimer = 0;
    		serial->WriteBlock((LPSTR) "FIN", 3);
    		}
    	else if (nTimer > 0)
    		{
    			nTimer += m_timer;
    		 }
      
   	        memset( szTemp, 0, TXQUEUE) ;
			if  ((i = MSARead(szTemp, TXQUEUE)) > 0)
			{
	
				rxFrame.addr = szTemp[0];
        		rxFrame.byte = szTemp[1];
	    		if (SDLCDecodeRx(&rxFrame, szASL) == INFO)
				{
						SetWindowText(m_wnd, (LPSTR) szASL);
						m_control = FALSE;
						memset( szASL, 0, TXQUEUE) ;
    					for(n=0;i>=n;n++)	if (!szTemp[n]) szTemp[n]=' ';
			 
    					if (IfFirst(szTemp) != NULL)
    		 			{
    		 			m_transac = TRUE;
    		 			serial->WriteBlock((LPSTR) "INICIO", 6);
    		 	
						strcpy(szASL, IfFirst(szTemp)-10);
						//strcpy(szBuf, szTemp + 37);
    		 			strcpy(szTemp, szASL);
    		 			nTimer = m_timer;
    		 			}
    		 
    					if (IfLast(szTemp) != NULL)
    		 				{
    		 				strcpy(szASL, szTemp + 5);
							pStr = IfLast(szASL);
							*pStr = '\0';
 							}
    		 
    					if ((IfFirst(szTemp) == NULL) &&  (IfLast(szTemp) == NULL) && m_transac)
    		  				strcpy(szASL, szTemp + 5);
    		  
    					if (m_transac)
    		  				{
    		  				serial->WriteBlock((LPSTR) szASL, strlen(szASL));
 							}
 			  
						if (IfLast(szTemp) != NULL)
 			  				{
    		 				m_transac = FALSE;
							}
 			  	    		      		    					
				} else
					{
					m_control = TRUE;
					SetWindowText(m_wnd, (LPSTR) szASL);
					//serial->WriteCommBlock((LPSTR) szASL, strlen(szASL));
					//nTimer = 0;
					}
    		}    
    MSAIsUnderRun();
    }  
}



char *Moxa::IfFirst(char *pStr)
{
 pStr=strstr(pStr, "BBVA");
 return pStr;
}

char *Moxa::IfLast(char *pStr)
{
 pStr=strchr(pStr, 12);
 return pStr;
}

BOOL
Moxa::IsOk()

{

	return m_status;
}

void
Moxa::Init()
{
	BOOL m_status_sync;
	BOOL m_status_serial;


	SetWindowText(m_wnd, "Inicializando...");
	strcpy(m_mens,"");
    
    
	if (serial->m_status)
		serial->Close();
	
	if (!serial->m_status)
	{
		serial->Init();
		if (serial->m_status)
		{
			serial->Send((LPSTR) "Puerto Serial Ok...");
			m_status_serial=TRUE;
		}
		else
		{
			m_status_serial = FALSE;
			strcat(m_mens,"Error:Puertos seriales");
		}
	}
	
	Close();
	if (Open())
	{
		m_status_sync =  TRUE;
	}
	else
	{
		strcat(m_mens,"Error:Tarjeta Sync");
		m_status_sync = FALSE;
	}

	if (m_status_serial && m_status_sync)
		m_status = TRUE;
	else
		m_status = FALSE;

}

/*
 ** SDLCDecodeRx()
 *
 *  PARAMETERS: frame     => BYTE array containing the start of the received packet
 *              OutString => Display string in which to put the interpreted data
 *
 *  DESCRIPTION: Interpret the first two bytes of a received SDLC packet and
 *               build a corresponding display string.
 *
 *  RETURNS: INFO        => The interpreted packet is an INFO frame
 *           UNNUMBERED  => The interpreted packet is an UNNUMBERED frame
 *           SUPERVISORY => The interpreted packet is an SUPERVISORY frame
 *
 */

int Moxa::SDLCDecodeRx(frame_t *frame, char *OutString)
{
    /* Display the address */
//    AddHex(frame->addr, OutString);
//    OutString += 3;
   
   /* Check for the type of frame */
    if ((frame->byte & UNNUMBERED) == UNNUMBERED)
    {
       switch (frame->u.Type & ~POLL_FINAL_BIT)
       {
           case UI:
               strcat(OutString, "UI");
              break;
               
            case SIM:
               strcat(OutString, "SIM");
               break;
               
            case UP:
               strcat(OutString, "UP");
               break;
               
            case DISC:
               strcat(OutString, "DISC");
               break;
               
            case SNRM:
               strcat(OutString, "SNRM");
               break;
               
            case XID:
               strcat(OutString, "XID ");
               break;
               
            case CFGR:
               strcat(OutString, "CFGR");
               break;
               
            case SNRME:
               strcat(OutString, "SNRME");
               break;
               
            case TEST:
               strcat(OutString, "TEST");
               break;
           
            default:
               /* No Unnumbered command that we recognize */
               wsprintf(OutString, "Unrecognized Unnumbered frame [%X]",
                    frame->byte );
               break;
       }
        return (UNNUMBERED);
       
    }
    else if (frame->i.zero == 0)
    {
       /* Info frame (rrrP sss0) */
        //sprintf(OutString, "I [Nr %2d,Ns %2d] : INFO", frame->i.Nr, frame->i.Ns);
		strcpy(OutString, "");
        return (INFO);
    }
    else
    {
        /* Supervisory modulo 8 frame (rrrP xxx1) */
       switch (frame->s.Type)
       {
           case RR:
               wsprintf(OutString, "RR [Nr = %d]", frame->s.Nr);
              break;
               
           case RNR:
               wsprintf(OutString, "RNR [Nr = %d]", frame->s.Nr);
              break;
               
           case REJ:
               wsprintf(OutString, "REJ [Nr = %d]", frame->s.Nr);
              break;
               
            default:
               /* No Unnumbered command that we recognize */
               wsprintf(OutString, "Unrecognized Supervisory frame [%X]",
                    frame->byte );
               break;
       }
        return(SUPERVISORY);
    }

} /* SDLCDecodeRx() */