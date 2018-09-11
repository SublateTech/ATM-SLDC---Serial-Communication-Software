#if !defined( __TODOLIST_H )
#define __TODOLIST_H
#define	ID_MYTIMER	1

//---------------------------------------------------------------------
//
//  TODOLIST.H
//
//      Copyright (c) 1991, 1992 by Borland International
//      All Rights Reserved.
//
//  defines the following classes, used in implementing the Todo list:
//
//      TdDate      - extends the Date class from the class
//                    library by providing a constructor that
//                    converts a text string into a date.
//
//      TodoEntry   - holds the data for an entry in the Todo list.
//
//      TodoList    - container for holding Todo entries
//
//      ListBox     - wrapper around the Windows listbox, providing
//                    an interface that fits with the Todo list.
//
//      BbvaWindow  - the main window for this application.  There's
//                    nothing displayed in the window except for the
//                    list box.
//
//---------------------------------------------------------------------

#if !defined( __WINDOWS_H )
#define STRICT
#include <Windows.h>
#endif  // __WINDOWS_H

#if !defined( __IOSTREAM_H )
#include <iostream.h>
#endif  // __IOSTREAM_H

#if !defined( __STRING_H )
#include <string.h>
#endif	// __STRING_H

#if !defined( __TODOWIN_H )
#include "BBVAWin.h"
#endif  // __TODOWIN_H

#include "diskId.h"
#include "syio.h"


#define TodoEntryClass  __firstUserClass

//---------------------------------------------------------------------
//
//  class BbvaWindow
//
//      the main window for this application.  There's nothing displayed
//      in the window except for the list box.
//---------------------------------------------------------------------

class BbvaWindow : public Window
{
public:

    BbvaWindow();
    ~BbvaWindow();

protected:

    virtual LONG dispatch( WPARAM, WPARAM, LPARAM );

    virtual BOOL registerClass();
    virtual BOOL createWindow();

private:
       
        
    
    DiskId	*m_disk;
    Moxa	*m_sync;
    void aboutBox();
    void Init();
    BOOL TestVSPD();
    void GateWay(HWND hWnd, char wParam );
    

        

    
    BOOL processCommand( WPARAM, LPARAM );

};

//---------------------------------------------------------------------
//
//  inline functions.
//
//---------------------------------------------------------------------


inline BbvaWindow::BbvaWindow() 
{
}

inline BbvaWindow::~BbvaWindow()
{
}

#endif  // __TODOLIST_H

