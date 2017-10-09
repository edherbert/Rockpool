#ifndef OBJECTTRANSFORMNUMBERCTRL_H
#define OBJECTTRANSFORMNUMBERCTRL_H

#include "NumberTextCtrl.h"

enum ObjectAxis : unsigned int;

class ObjectTransformNumberCtrl : public NumberTextCtrl
{
    public:
        ObjectTransformNumberCtrl(wxWindow *parent, int id, ObjectAxis axis);
        virtual ~ObjectTransformNumberCtrl();

        ObjectAxis getAxis();

    protected:

    private:
        ObjectAxis axis;
};

#endif // OBJECTTRANSFORMNUMBERCTRL_H
