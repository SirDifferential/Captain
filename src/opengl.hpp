#ifndef _OPENGL_HPP_
#define _OPENGL_HPP_

class Opengl
{
private:
    int id;
    int screenX;
    int screenY;
    int screenBPP;
    bool fullscreen;
    int fps;
    bool limit_fps;
public:
    Opengl();
    ~Opengl();
    
    bool start();
    float giveTicks();
    
    void swapBuffers();
    
    int getScreenX() { return screenX; }
    int getScreenY() { return screenY; }
    int getScreenBPP() { return screenBPP; }
    int getFPS() { return fps; }
    bool getFullscreen() { return fullscreen; }
    bool getLimitFPS() { return limit_fps; }
    
    void setFullscreen(bool fs);
    void setScreenX(int x);
    void setScreenY(int y);
    void setBPP(int b);
    void setFPS(int f);
    void setLimitFPS(bool b);
};

#endif
