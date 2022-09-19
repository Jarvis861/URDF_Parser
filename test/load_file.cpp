#define CATCH_CONFIG_MAIN
#include "../catch.hpp"
#include "urdf/model.h"
#include <string>
#include <iostream>
#include <exception>
#include "tinyxml/txml.h"

#define THIS_COM "/home/jarvis/Downloads/URDF_Parser/test/"

using namespace urdf;

TEST_CASE ("load a urdf file", "[UrdfFile]") {
    TiXmlDocument doc;
    const char* filename = THIS_COM "test.urdf";

    // REQUIRE_NOTHROW(doc.LoadFile(filename));     // simple method

    std::shared_ptr<UrdfModel> model;

    REQUIRE_NOTHROW(model = UrdfModel::fromUrdfFile(filename));

    // link_0 must exist
    auto link_0 = model->getLink("link_0");
    REQUIRE(link_0->name == "link_0");

}
