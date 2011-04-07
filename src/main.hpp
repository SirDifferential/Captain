#ifndef __MAIN_HPP_
#define __MAIN_HPP_

class Captain
{
private:
	friend int main(int argc, char** argv);
	bool running;
	float time;
	float delta;
	int nextFPS;
	int screenX;
	int screenY;
	int screenBPP;
public:
	Captain();
	~Captain();
	void start();
	float getTime() { return time; }
	float getDelta() { return delta; }
	void handleEvents();
	void render();
	void update();
	int getScreenX() { return screenX; }
	int getScreenY() { return screenY; }
};

extern Captain captain;

#endif
