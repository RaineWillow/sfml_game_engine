#include "resource_manager.hpp"

ResourceManager::ResourceManager(std::string path)
{
	_path = path;

	std::ifstream input_stream;
	input_stream.open(_path + "res_data.dat");

	if (input_stream.fail()) {
		std::cout << "failed to read\n";
		return;
	}
	std::string fLine;
	std::vector<std::string> lines;
	while (getline(input_stream, fLine)) {
		lines.push_back(fLine);
	}
	input_stream.close();

	if (lines[0] == "imgs:") {

		for (size_t i = 1; i < lines.size(); i++) {
			if (lines[i] == "-") {
				break;
			}
			Split myData(lines[i], " ");
			if (myData[0] == "//") {
				std::cout << "Comment: " << myData[1] << "\n";
			} else {
				std::cout << "Loading: " << myData[1] << "\n";
				loadTexture(std::stoi(myData[0]), myData[1]);
			}
		}
	}

}

ResourceManager::~ResourceManager()
{
	for (auto const& x : _imgLists) {
		delete x.second;
	}
}

void ResourceManager::loadTexture(int id, std::string path)
{
	std::string myPath = _path + path;
	RImg * myImg = new RImg;

	if (!myImg->tex.loadFromFile(myPath))
	{
		std::cout << "Error loading:" << myPath << "\n";
		return;
	}

	myImg->spr.setTexture(myImg->tex);

	_imgLists.insert({id, myImg});
	return;
}

sf::Sprite ResourceManager::getSprite(int id)
{
	return _imgLists[id]->spr;
}
