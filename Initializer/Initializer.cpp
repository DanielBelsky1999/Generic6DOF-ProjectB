#include "Initializer.h"

pugi::xml_document Initializer::_document;
bool Initializer::_document_loaded = false;

pugi::xml_document& Initializer::GetDocument() {
	if (!_document_loaded) {
		_document.load_file("../../Configs/config.xml");
		_document_loaded = true;
	}
	return _document;
}

pugi::xml_node Initializer::TraversePath(const std::string& path)
{
    std::stringstream ss(path);
    std::string token;
    pugi::xml_node node = GetDocument().child("root");

    while (std::getline(ss, token, '/'))
    {
        if (token.empty()) continue; // skip extra slashes
        node = node.child(token.c_str());
    }
    return node;
}

//----------------------------------------
// Public API
//----------------------------------------
std::string Initializer::GetType(const std::string& path)
{
    pugi::xml_node node = TraversePath(path);
    pugi::xml_attribute attr = node.attribute("type");
    return attr.as_string();
}

std::string Initializer::GetValueAsString(const std::string& path)
{
    pugi::xml_node node = TraversePath(path);
    return node.text().as_string();
}

int Initializer::GetValueAsInt(const std::string& path)
{
    pugi::xml_node node = TraversePath(path);
    return node.text().as_int();
}

double Initializer::GetValueAsDouble(const std::string& path)
{
    pugi::xml_node node = TraversePath(path);
    return node.text().as_double();
}

bool Initializer::GetValueAsBool(const std::string& path)
{
    pugi::xml_node node = TraversePath(path);
    // Accepts 0/1 or true/false
    std::string val = node.text().as_string();
    return val == "1" || val == "true";
}