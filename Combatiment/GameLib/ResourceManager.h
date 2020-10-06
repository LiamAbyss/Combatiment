#ifndef INCLUDE_RESOURCE_MANAGER
#define INCLUDE_RESOURCE_MANAGER

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <Thor/Resources.hpp>
#include <string>
#include "json.hpp"
#include <boost/variant.hpp>
#include <regex>
#include <iostream>
#include <Windows.h>
#include <fstream>

typedef std::shared_ptr<sf::Texture> GTexture;
typedef std::shared_ptr<sf::Music> GMusic;
typedef std::shared_ptr<sf::SoundBuffer> GSoundBuffer;
typedef std::shared_ptr<nlohmann::json> GJson;
typedef std::shared_ptr<sf::Font> GFont;
typedef boost::variant<GTexture, GJson, GSoundBuffer, GMusic, GFont> GVariant;


class ResourceManager
{
private:
	std::map<std::string, GTexture> textureHolder;
	std::map<std::string, GJson> jsonHolder;
	std::map<std::string, GSoundBuffer> soundHolder;
	std::map<std::string, GMusic> musicHolder;
	std::map<std::string, GFont> fontHolder;
	unsigned long long audioLimit = 1000000;

public:
	bool load(std::string key, std::string file);
	GVariant get(std::string key);
	GVariant operator[](std::string key);
	void remove(std::string key);
	void setAudioLimit(unsigned long long limit);
	unsigned long long getAudioLimit() const;
};

std::string GetMimeType(const std::string& szExtension);
long long getFileSize(const std::string& filename);

#endif // !INCLUDE_RESOURCE_MANAGER