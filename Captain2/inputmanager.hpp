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
    void checkMenuInput(Menu &menu);
};

extern Inputmanager inputmgr;

#endif

