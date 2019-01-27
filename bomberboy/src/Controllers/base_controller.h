#ifndef BASE_CONTROLLER_H
#define BASE_CONTROLLER_H

#include <libgba-sprite-engine/gba/tonc_memmap.h>
#include "../Models/base_model.h"

class BaseController {

private:
    BaseModel* _model;

public:
    virtual void processKeys(u16 keys) = 0;
    void setModel(BaseModel* model) {_model = model;}
    BaseModel* getModel() {return _model;}


};

#endif //BASE_CONTROLLER_H