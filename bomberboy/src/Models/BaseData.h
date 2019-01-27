//
// Created by Ruben on 27/01/2019.
//

#ifndef GBA_SPRITE_ENGINE_PROJECT_BASEDATA_H
#define GBA_SPRITE_ENGINE_PROJECT_BASEDATA_H


#include <string>

class BaseData {
private:
    int _n;
    std::string _string;
public:
    virtual void setInt(int n) {
        _n = n;
    }
    virtual int getInt() {
        return _n;
    }
    virtual void setString(std::string string) {
        _string = string;
    }
    virtual std::string getStrign() {
        return _string;
    }


};


#endif //GBA_SPRITE_ENGINE_PROJECT_BASEDATA_H
