#ifndef NUMBERTEXTCTRL_H
#define NUMBERTEXTCTRL_H

#include <wx/textctrl.h>

class NumberTextCtrl : public wxTextCtrl
{
    public:
        NumberTextCtrl(wxWindow *parent, int id);
        virtual ~NumberTextCtrl();

    protected:

    private:
        void valueEntered(wxKeyEvent &event);
};

#endif // NUMBERTEXTCTRL_H
