#ifndef NUMBERTEXTCTRL_H
#define NUMBERTEXTCTRL_H

#include <wx/textctrl.h>

class ObjectTransformComponent;

class NumberTextCtrl : public wxTextCtrl
{
    public:
        NumberTextCtrl(wxWindow *parent, int id, ObjectTransformComponent *alertComponent = 0);
        virtual ~NumberTextCtrl();

        int getIntValue();

    protected:

    private:
        void valueEntered(wxKeyEvent &event);

        ObjectTransformComponent *alertComponent;
};

#endif // NUMBERTEXTCTRL_H
