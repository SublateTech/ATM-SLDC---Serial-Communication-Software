#if !defined( __TODODLGS_H )
#define __TODODLGS_H

//---------------------------------------------------------------------
//
//  TODODLGS.H
//
//      Copyright (c) 1991, 1992 by Borland International
//      All Rights Reserved.
//
//  defines the following classes, which handle all the dialog boxes for
//  the Todo program.
//
//      AboutBox
//
//      FileBox     - provides a basic dialog for selecting a file.
//
//      EditBox     - provides a dialog box for editing an entry in the
//                    Todo list.
//
//---------------------------------------------------------------------

#if !defined( __WINDOWS_H )
#define STRICT
#include <Windows.h>
#endif  // __WINDOWS_H


#if !defined( __STRSTREAM_H )
#include <strstream.h>
#endif  // __STRSTREAM_H

#if !defined( __TODOWIN_H )
#include "BBVAWin.h"
#endif  // __TODOWIN_H

#if !defined( __TODOLIST_H )
#include "BBVA.h"
#endif  // __TODOLIST_H

//---------------------------------------------------------------------
//
//  class AboutBox
//
//      draws and manages the About dialog.
//
//---------------------------------------------------------------------

class AboutBox : public ModalDialog
{

public:

    AboutBox( HWND );

private:

    virtual LPSTR getDialogName();
    virtual BOOL dispatch( HWND, UINT, WPARAM, LPARAM );

};


class TodoEntry;                // forward reference



//---------------------------------------------------------------------
//
//  inline functions
//
//---------------------------------------------------------------------

inline AboutBox::AboutBox( HWND hOwner ) : ModalDialog( hOwner )
{
}


#endif  // __TODODLGS_H

