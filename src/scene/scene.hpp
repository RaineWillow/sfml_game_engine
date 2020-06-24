#ifndef Scene_hpp
#define Scene_hpp
#include <vector>
#include <string>

struct SceneData {
	int id;
	std::vector<std::string> args;
};

class Scene {
public:
	virtual void update()=0;
	virtual void render()=0;

	SceneData run() {
		while (_isActive) {
			this->update();
			this->render();
		}
	return _myDat;
	}
	
	bool _isActive = true;
	SceneData _myDat;
};

#endif
