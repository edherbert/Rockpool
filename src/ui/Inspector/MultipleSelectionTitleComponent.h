#ifndef MULTIPLESELECTIONTITLECOMPONENT_H
#define MULTIPLESELECTIONTITLECOMPONENT_H

#include "InspectorComponent.h"

class ObjectInspector;
class wxStaticText;

class MultipleSelectionTitleComponent : public InspectorComponent
{
    public:
        MultipleSelectionTitleComponent(ObjectInspector *inspector);
        virtual ~MultipleSelectionTitleComponent();

        void updateObjectCount(int objects);

    protected:

    private:
        wxStaticText *titleText;

        int objectCount = 0;
};

#endif // MULTIPLESELECTIONTITLECOMPONENT_H
