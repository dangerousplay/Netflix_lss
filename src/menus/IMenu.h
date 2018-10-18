//
// Created by aluno on 17/10/18.
//

#ifndef IMENU_HEADER
#define IMENU_HEADER


#include <iostream>

class IMenu {
public:
    IMenu() = default;

    virtual void render(){
        std::cout << "Not Implemented" << std::endl;
    }
};

#endif
