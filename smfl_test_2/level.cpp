#include "level.h"

using namespace sf;


TileMap::~TileMap()
{
	if (texture)
		delete texture;
	//std::cout << "TileMap deconstructor works!\n";
}

bool TileMap::load(const std::string& tmx_file_path)
{
	tinyxml2::XMLDocument document;

	if (document.LoadFile(tmx_file_path.c_str()) != tinyxml2::XML_SUCCESS)
	{
		std::cout << "Loading file " << tmx_file_path << " failed..." << std::endl;
		return false;
	}
	// get all tileset data
	tinyxml2::XMLElement* root_element = document.FirstChildElement("map");
	const size_t tile_width = std::stoul(root_element->Attribute("tilewidth"));
	const size_t tile_height = std::stoul(root_element->Attribute("tileheight"));

	auto tileset = root_element->FirstChildElement("tileset");
	const size_t tile_count = std::stoul(tileset->Attribute("tilecount"));
	const size_t columns = std::stoul(tileset->Attribute("columns"));
	// get path
	auto image = tileset->FirstChildElement("image");
	std::string path = image->Attribute("source");

	while (!isalpha(path.front())) // if the editor wrote the path, for example, like this: "../textures/Tiles.png"
		path.erase(0, 1);          // remove all unnecessary characters at the beginning of the line (../) to avoid a load failure

	texture = new sf::Texture();

	if (!texture->loadFromFile(path))
		return false;
	// create a mesh, where the index of each tile depends on its coordinates in the texture
	// For example, if the tile width is 32 pixels, the coordinates in the texture:
	// first tile (0, 0), second (32, 0), third (64, 0) and so on
	std::vector<sf::Vector2f> texture_grid;
	texture_grid.reserve(tile_count);

	size_t rows = tile_count / columns;

	for (size_t y = 0u; y < rows; ++y)
		for (size_t x = 0u; x < columns; ++x)
			texture_grid.emplace_back(sf::Vector2f((float)x * tile_width, (float)y * tile_height));
	// process csv arrays
	for (auto layer = root_element->FirstChildElement("layer");
		layer != nullptr;
		layer = layer->NextSiblingElement("layer"))
	{
		/*if (!layer)
		{
			std::cerr << "Bad map. No layer information found." << std::endl;
			return false;
		}*/
		// Width and height of the layer in tiles
		const size_t width = std::stoul(layer->Attribute("width"));
		const size_t height = std::stoul(layer->Attribute("height"));
		// We convert the layer into a vector of integers, where each number is the number of a tile in the tileset
		tinyxml2::XMLElement* data = layer->FirstChildElement("data");
		std::string dirty_string = data->GetText(), buffer;

		std::vector<size_t> csv_array;
		csv_array.reserve(dirty_string.size());

		for (auto& character : dirty_string)
		{
			if (isdigit(character))
				buffer += character;
			else
				if (!buffer.empty())
				{
					csv_array.push_back(std::stoi(buffer));
					buffer.clear();
				}
		}
		csv_array.shrink_to_fit();
		// create an array of vertices
		sf::VertexArray vertices;
		vertices.setPrimitiveType(sf::Quads);

		for (size_t y = 0u, index = 0u; y < height; ++y)
		{
			for (size_t x = 0u; x < width; ++x, ++index)
			{
				size_t tile_num = csv_array[index];
				// if the tile number is greater than zero the place is not empty - write the tile to the vertex array
				if (tile_num)
				{   // walk clockwise
					sf::Vertex leftTop;
					sf::Vertex rightTop;
					sf::Vertex rightBottom;
					sf::Vertex leftBottom;
					// Place the tile in a position on the map
					leftTop.position = sf::Vector2f((float)x * tile_width, (float)y * tile_height);
					rightTop.position = sf::Vector2f(((float)x + 1) * tile_width, (float)y * tile_height);
					rightBottom.position = sf::Vector2f(((float)x + 1) * tile_width, (float)(y + 1) * tile_height);
					leftBottom.position = sf::Vector2f((float)x * tile_width, (float)(y + 1) * tile_height);
					// its texture coords
					leftTop.texCoords = sf::Vector2f(texture_grid[tile_num - 1].x, texture_grid[tile_num - 1].y);
					rightTop.texCoords = sf::Vector2f(texture_grid[tile_num - 1].x + tile_width, texture_grid[tile_num - 1].y);
					rightBottom.texCoords = sf::Vector2f(texture_grid[tile_num - 1].x + tile_width, texture_grid[tile_num - 1].y + tile_height);
					leftBottom.texCoords = sf::Vector2f(texture_grid[tile_num - 1].x, texture_grid[tile_num - 1].y + tile_height);

					vertices.append(leftTop);
					vertices.append(rightTop);
					vertices.append(rightBottom);
					vertices.append(leftBottom);
				}
			}
		}
		tile_layers.push_back(std::move(vertices));
	}
	// Load objects, if any
	for (auto object_group = root_element->FirstChildElement("objectgroup");
		object_group != nullptr;
		object_group = object_group->NextSiblingElement("objectgroup"))
	{// we get all the data - type, name, position, etc
		for (auto object = object_group->FirstChildElement("object");
			object != nullptr;
			object = object->NextSiblingElement("object"))
		{
			std::string object_name;
			if (object->Attribute("name"))
				object_name = object->Attribute("name");

			std::string object_type;
			if (object->Attribute("type"))
				object_type = object->Attribute("type");

			float x = std::stof(object->Attribute("x"));
			float y = std::stof(object->Attribute("y"));

			float width{}, height{};

			if (object->Attribute("width") && object->Attribute("height"))
			{
				width = std::stof(object->Attribute("width"));
				height = std::stof(object->Attribute("height"));
			}

			Object new_object(x, y, width, height);
			new_object.name = object_name;
			new_object.type = object_type;

			auto properties = object->FirstChildElement("properties");

			if (properties)
			{
				for (auto property = properties->FirstChildElement("property");
					property != nullptr;
					property = property->NextSiblingElement("property"))
				{
					std::string name, value;

					if (property->Attribute("name"))
						name = property->Attribute("name");

					if (property->Attribute("value"))
						value = property->Attribute("value");

					new_object.properties[name] = value;
				}
			}
			objects.emplace_back(std::move(new_object));
		}
	}
	return true;
}
// Only the first object with the given name
Object TileMap::getObject(const std::string& name)
{
	auto found = std::find_if(objects.begin(), objects.end(), [&](const Object& obj)
		{
			return obj.name == name;
		});

	return *found;
}
// All objects with the given name
std::vector<Object> TileMap::getObjectsByName(const std::string& name)
{
	std::vector<Object> objects_by_name;

	std::copy_if(objects.begin(), objects.end(), std::back_inserter(objects_by_name), [&](const Object& obj)
		{
			return obj.name == name;
		});

	return objects_by_name;
}
// All objects with the given type
std::vector<Object> TileMap::getObjectsByType(const std::string& type)
{
	std::vector<Object> objects_by_type;

	std::copy_if(objects.begin(), objects.end(), std::back_inserter(objects_by_type), [&](const Object& obj)
		{
			return obj.type == type;
		});

	return objects_by_type;
}

std::vector<Object>& TileMap::getAllObjects()
{
	return objects;
}

void TileMap::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (auto& layer : tile_layers)
		target.draw(layer, texture);
}

int Object::GetPropertyInt(const std::string& name)
{
	return std::stoi(properties[name]);
}

float Object::GetPropertyFloat(const std::string& name)
{
	return std::stof(properties[name]);
}

std::string Object::GetPropertyString(const std::string& name)
{
	return properties[name];
}
