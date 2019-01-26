#ifndef BASE_CONTROLLER_H
#define BASE_CONTROLLER_H

#include <libgba-sprite-engine/gba/tonc_memmap.h>
#include "../Models/base_model.h"

class BaseController {

private:
    BaseModel* _model;

public:
    void processKeys(u16 keys);
    void setModel(BaseModel* model) {_model = model;}


};

#endif //BASE_CONTROLLER_H