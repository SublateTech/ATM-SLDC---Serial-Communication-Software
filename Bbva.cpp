
#define STRICT



#include <windows.h>
#include <string.h>
#include "resource.h"
#include "BBVA.h"
#include "syio.h"
#include "commport.h"

#include "msa.h"
#include "Bbva.h"

#include "DiskId.h"
#include "About.h"



//---------------------------------------------------------------------
//
//  member functions for class BbvaWindow.
//
//  these are mostly self-explanatory.
//
//---------------------------------------------------------------------

BOOL BbvaWindow::registerClass()
{
    WNDCLASS wc;

    wc.style = 0;
    wc.lpfnWndProc = Window::wndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance =(HINSTANCE) hInst;
    wc.hIcon = LoadIcon(hInst, "BBVA" ); //LoadIcon( NULL, IDI_APPLICATION );
    wc.hCursor = LoadCursor( NULL, IDC_ARROW );
    wc.hbrBackground =(HBRUSH) GetStockObject( WHITE_BRUSH );
    wc.lpszMenuName  = NULL;
    wc.lpszClassName = "SDLCClass";

    return RegisterClass( &wc );
}

BOOL BbvaWindow::createWindow()
{
	     //if (FindWindow("SDLCClass", NULL) != NULL)
    	//	exit (FALSE);

          
                              
          hWindow = CreateWindow(
				"SDLCClass",
				"ATM16 v1.0.2",
				WS_POPUPWINDOW | WS_ICONIC,
				200,
				100,
				290,
				00,
				NULL,
				NULL,
				(HINSTANCE)hInst,
				NULL
    			);



        if( hWnd() == 0 )
        return FALSE;

    insert();                   // insert this window into the window list

    HMENU   hMenu;  	
  	hMenu = GetSystemMenu(hWnd(), FALSE);
      	
  	RemoveMenu(hMenu, 0, MF_BYPOSITION);
  	RemoveMenu(hMenu, 0, MF_BYPOSITION);
  	RemoveMenu(hMenu, 0, MF_BYPOSITION);
  	RemoveMenu(hMenu, 0, MF_BYPOSITION);
    RemoveMenu(hMenu, 0, MF_BYPOSITION);        
    InsertMenu(hMenu, 0, MF_STRING, IDM_ABOUT, "&Acerca de...");
    InsertMenu(hMenu, 0, MF_STRING, IDM_RINIT, "&Reinicializar...");
    
            	
    	
        
        m_disk	=	new DiskId( (HWND)hWnd() );        
        
        m_sync = new  Moxa();
        if (m_sync == NULL)
			{
			m_sync->m_status = FALSE;
			}
                
        m_sync->m_wnd = hWnd();
        	
        Init();
        
        SetTimer(hWnd(), ID_MYTIMER, m_sync->m_timer , NULL);    


    
    ShowWindow( (HWND)hWnd(), show );
    UpdateWindow( (HWND)hWnd() );
    return TRUE;
}

void BbvaWindow::aboutBox()
{       
    AboutBox ab( (HWND)hWnd() );
    ab.run();
}



BOOL BbvaWindow::TestVSPD()
		{
			char szTest[12];
			BOOL lStatus;
			
			lStatus = FALSE;
			CommPort m_Port_1;
			CommPort m_Port_2;
			if (!m_Port_1.Open(m_sync->serial->GetPort()))
				return FALSE;
			if (!m_Port_2.Open(m_sync->serial->GetPort()+1))
				{
				m_Port_1.Close();
				return FALSE;
				}
				
			m_Port_2.Send("T");
			//Sleep(800);
			if (m_Port_1.ReadBlock(szTest, 1) == 1)
				{
				lStatus = TRUE;
				}
			
			m_Port_1.Close();
			m_Port_2.Close();
			

			
			return lStatus;
		}

void BbvaWindow::Init()
		{
		    		    
		    if (m_sync->serial->m_status)
		    	m_sync->serial->Close();
		    
		    m_disk->TestSerialId();
		    
		    if (TestVSPD())
		       	{
		       	m_sync->Init();
    	    	if (!m_sync->m_status)
        			SetWindowText(hWnd(), m_sync->m_mens);
        	     else
        	    	SetWindowText(hWnd(), "VSPD Demo");
        	    }
			return;
		}


void BbvaWindow::GateWay(HWND hWnd, char wParam )
		{
	
   		char  szTemp[ TXQUEUE ];
   		
   		memset( szTemp, 0, TXQUEUE) ;
   		*szTemp = wParam;
   		SetWindowText(hWnd, (LPSTR) szTemp);
   		m_sync->serial->Send((LPSTR) szTemp);
		}

//---------------------------------------------------------------------
//
//  BOOL BbvaWindow::processCommand( WPARAM wParam, LPARAM lParam );
//
//  dispatches commands to the appropriate member functions.
//
//---------------------------------------------------------------------

BOOL BbvaWindow::processCommand( WPARAM wParam, LPARAM lParam )
{
    switch( wParam )
        {
        
        
/*        case IDM_QUIT:
	    SendMessage((HWND)hWnd(), WM_CLOSE, 0, 0L);
            return TRUE;
        */
        
        case IDM_RINIT:
            Init();
            return TRUE;
   
        case IDM_ABOUT:
            aboutBox();
            return TRUE;

        default:         
        	return FALSE;
        }
}

//---------------------------------------------------------------------
//
//  LONG BbvaWindow::dispatch( UINT msg, WPARAM wParam, LPARAM lParam );
//
//  dispatches messages to the appropriate member functions.
//
//---------------------------------------------------------------------

LONG BbvaWindow::dispatch( UINT msg, WPARAM wParam, LPARAM lParam )
{
    switch( msg )
        {
       	case WM_CHAR:
		 	GateWay(hWnd(), (char) wParam);
		 	break;

        case WM_TIMER:
        		m_sync->ATMProc();
        		break;
        case WM_COMMAND:
        case WM_SYSCOMMAND:

            if( processCommand( wParam, lParam ) == TRUE )
                {
//                listBox.focus();
                return 0;
                }
            break;

        case WM_MOVE:
        case WM_SIZE:

            //moveListBox();
            return 0;

        case WM_QUERYENDSESSION:
            return TRUE;

        case WM_CLOSE:

            //checkSave();
	    	DestroyWindow( (HWND)hWnd() );
            return 0;

        case WM_DESTROY:
        case WM_QUIT:

            delete m_disk;		
            delete m_sync;
            PostQuitMessage( 0 );
            break;
        }
        return Window::dispatch( msg, wParam, lParam );
}

//---------------------------------------------------------------------
//
//  int PASCAL WinMain( HINSTANCE, HINSTANCE, LPSTR, int );
//
//  the main entry point for the program.
//
//---------------------------------------------------------------------

int PASCAL WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
    BbvaWindow td;
    td.create();
    return td.run();
}

