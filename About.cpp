
#define STRICT

#if !defined( __WINDOWS_H )
#include <Windows.h>
#endif  // __WINDOWS_H

#if !defined( __STRING_H )
#include <String.h>
#endif  // __STRING_H

#if !defined( __TODODLGS_H )
#include "About.h"
#endif  // __TODODLGS_H

#include "resource.h"


//---------------------------------------------------------------------
//
//  member functions for class AboutBox.
//
//  not much needed here...
//
//---------------------------------------------------------------------

LPSTR AboutBox::getDialogName()
{
    return "IDD_ABOUT";
}

BOOL AboutBox::dispatch( HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam )
{
    switch( msg )
        {

        case WM_INITDIALOG:

            return TRUE;        // no initialization.

        case WM_COMMAND:

            if( wParam == IDOK || wParam == IDCANCEL )
		{
                EndDialog( hDlg, TRUE );  // selecting OK or Cancel
                return TRUE;              // terminates the dialog
                }

        default:                // if we don't handle it, pass it
                                // to our parent.

            return ModalDialog::dispatch( hDlg, msg, wParam, lParam );

        }
}




