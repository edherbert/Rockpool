#include "ObjectTransformNumberCtrl.h"

#include "../../map/Object/Object.h"

ObjectTransformNumberCtrl::ObjectTransformNumberCtrl(wxWindow *parent, int id, ObjectAxis axis) : NumberTextCtrl(parent, id),
    axis(axis){

}

ObjectTransformNumberCtrl::~ObjectTransformNumberCtrl(){

}

ObjectAxis ObjectTransformNumberCtrl::getAxis(){
    return axis;
}
