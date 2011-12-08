#ifndef _INPUTMANAGER_HPP_
#define _INPUTMANAGER_HPP_

class Menu;

class Inputmanager
{
private:
    int id;
public:
    Inputmanager();
    ~Inputmanager();
    
    void checkInput();
};

extern Inputmanager inputmgr;

#endif

