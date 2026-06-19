#pragma once
#include "pugiXML\pugixml.hpp"
#include <string>
#include <sstream>

class Initializer
{
public:
    // Get the value of a node as a specific type
    static bool GetValueAsBool(const std::string& path);
    static int GetValueAsInt(const std::string& path);
    static double GetValueAsDouble(const std::string& path);
    static std::string GetValueAsString(const std::string& path);

    // Get the value of the 'type' attribute
    static std::string GetType(const std::string& path);

private:
    // Singleton document access
    static pugi::xml_document& GetDocument();

    // Traverse XML tree by path ("A/B/C")
    static pugi::xml_node TraversePath(const std::string& path);

    static bool _document_loaded;
    static pugi::xml_document _document;
};
