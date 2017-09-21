#include "NumberTextCtrl.h"

NumberTextCtrl::NumberTextCtrl(wxWindow *parent, int id) : wxTextCtrl(parent, id, "0"){
    Connect(wxEVT_CHAR, wxKeyEventHandler(NumberTextCtrl::valueEntered));
}

NumberTextCtrl::~NumberTextCtrl(){

}

void NumberTextCtrl::valueEntered(wxKeyEvent &event){
    //Basically just a list of allowed keys
    //Only if the key is in this list will it be ran
    switch(event.GetKeyCode()){
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
        case WXK_NUMPAD0:
        case WXK_NUMPAD1:
        case WXK_NUMPAD2:
        case WXK_NUMPAD3:
        case WXK_NUMPAD4:
        case WXK_NUMPAD5:
        case WXK_NUMPAD6:
        case WXK_NUMPAD7:
        case WXK_NUMPAD8:
        case WXK_NUMPAD9:
        case WXK_DELETE:
        case WXK_RIGHT:
        case WXK_LEFT:
        case WXK_BACK:
        case WXK_TAB:
        case WXK_NUMPAD_END:
        case WXK_NUMPAD_BEGIN:
        case WXK_HOME:
        case WXK_END:
        case WXK_RETURN:
            event.Skip();
    }

}
