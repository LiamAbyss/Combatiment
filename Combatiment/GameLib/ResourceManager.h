#ifndef INCLUDE_RESOURCE_MANAGER
#define INCLUDE_RESOURCE_MANAGER

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include "JsonHeader/json.hpp"
#include <boost/variant.hpp>
#include <iostream>
#include <Windows.h>
#include <fstream>

typedef std::shared_ptr<sf::Texture> GTexture;
typedef std::shared_ptr<sf::Music> GMusic;
typedef std::shared_ptr<sf::SoundBuffer> GSoundBuffer;
typedef std::shared_ptr<nlohmann::json> GJson;
typedef std::shared_ptr<sf::Font> GFont;
typedef boost::variant<GTexture, GJson, GSoundBuffer, GMusic, GFont> GVariant;

/** 
 * Manages all the resources.
 * \see Game::resources
 */
class ResourceManager
{
private:
	/** 
	 * \private
	 * Contains all the SFML Textures.
	 */
	std::map<std::string, GTexture> textureHolder;

	/** 
	 * \private
	 * Contains all the json files.
	 */
	std::map<std::string, GJson> jsonHolder;

	/** 
	 * \private
	 * Contains all the SFML SoundBuffers.
	 */
	std::map<std::string, GSoundBuffer> soundHolder;

	/** 
	 * \private
	 * Contains all the SFML Musics.
	 */
	std::map<std::string, GMusic> musicHolder;

	/** 
	 * \private
	 * Contains all the SFML fonts.
	 */
	std::map<std::string, GFont> fontHolder;

	/** 
	 * \private
	 * The limit in size between SFML SoundBuffers and Musics.
	 * \note SoundBuffers are loaded into the memory while Musics are streamed directly from their file.
	 */
	unsigned long long audioLimit = 1000000;

public:

	/**
	 * Loads a resource.
	 * \param key The key associated to the resource.
	 * \param file The file where the resource is located.
	 * \return true If the file could be loaded.
	 * \return false If the file doesn't exist or if the extension is not supported.
	 * \note Currently supported : Audio and image files supported by SFML, JSON files, and font files (.ttf)
	 */
	bool load(std::string key, std::string file);

	/**
	 * \private
	 * \param key The key associated to the resource.
	 * \return A boost::variant of std::shared_ptr according to the resource type.
	 * \see GTexture, GSoundBuffer, GMusic, GJson, GFont, GVariant
	 */
	GVariant get(std::string key);

	/**
	 * \private
	 * \param key The key associated to the resource.
	 * \return A boost::variant of std::shared_ptr according to the resource type.
	 * \see get()
	 */
	GVariant operator[](std::string key);

	/**
	 * \private
	 * \param key The key associated to the resource.
	 */
	void remove(std::string key);

	/**
	 * \private
	 * \param limit The limit in size between SFML SoundBuffers and Musics.
	 */
	void setAudioLimit(unsigned long long limit);

	/**
	 * \private
	 * \return The limit in size between SFML SoundBuffers and Musics.
	 */
	unsigned long long getAudioLimit() const;
};

/** 
 * \param szExtension The file extension
 * \return The MIME type of the file.
 */
std::string GetMimeType(const std::string& szExtension);

/** 
 * \param filename The name of the file.
 * \return The size of the file in bytes.
 */
long long getFileSize(const std::string& filename);

#endif // !INCLUDE_RESOURCE_MANAGER