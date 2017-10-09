#ifndef NUMBERTEXTCTRL_H
#define NUMBERTEXTCTRL_H

#include <wx/textctrl.h>

class ObjectTransformComponent;

class NumberTextCtrl : public wxTextCtrl
{
    public:
        NumberTextCtrl(wxWindow *parent, int id);
        virtual ~NumberTextCtrl();

        int getIntValue();

    protected:

    private:
        void valueEntered(wxKeyEvent &event);
};

#endif // NUMBERTEXTCTRL_H
