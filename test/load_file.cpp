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
    const char* filename = THIS_COM "arm_v2.urdf";

    // REQUIRE_NOTHROW(doc.LoadFile(filename));     // simple method

    std::shared_ptr<UrdfModel> model;

    REQUIRE_NOTHROW(model = UrdfModel::fromUrdfFile(filename));


    // =============== link =============== 
    CHECK(model->link_map.size() == 9);
    auto link = model->getLink("shoulder_link");
    CHECK(link != nullptr);

    //check inertial info of link
    CHECK(link->inertial != nullopt);
    auto inertial = &link->inertial.value();
    CHECK(inertial != nullptr);
    CHECK(inertial->mass == 0.61357);
    CHECK(inertial->iyy == 0.00031);

    printf("%f %f %f %f\n", inertial->origin.rotation.x,
        inertial->origin.rotation.y,
        inertial->origin.rotation.z,
        inertial->origin.rotation.w );

    CHECK(inertial->origin.position.z == 0.04101);



    // =============== joint =============== 
    CHECK(model->joint_map.size() == 8);
    auto joint = model->getJoint("joint_3");
    CHECK(joint != nullptr);

    CHECK(joint->parent_link_name == "arm_link");
    CHECK(joint->child_link_name == "elbow_link");
    CHECK(joint->type == JointType::REVOLUTE);

    CHECK(joint->axis.x == 0.);
    CHECK(joint->axis.y == 0.);
    CHECK(joint->axis.z == 1.);

    printf("%f %f %f %f\n", joint->parent_to_joint_transform.rotation.x,
        joint->parent_to_joint_transform.rotation.y,
        joint->parent_to_joint_transform.rotation.z,
        joint->parent_to_joint_transform.rotation.w );

    CHECK(joint->parent_to_joint_transform.position.x == 0.);
    CHECK(joint->parent_to_joint_transform.position.y == 0.3);
    CHECK(joint->parent_to_joint_transform.position.z == 0.);

    // world
    REQUIRE( model->getRoot() != nullptr );
    CHECK(model->getRoot()->name == "world");



    // =============== links and joints =============== 
    #if 1
    vector<std::shared_ptr<Joint>> _joints;
    model->getJoints(_joints);    // wrong sequence !!!
    #else
    std::shared_ptr<Joint> _joints[8];
    _joints[0] = model->getJoint("joint_world");
    _joints[1] = model->getJoint("joint_1");
    _joints[2] = model->getJoint("joint_2");
    _joints[3] = model->getJoint("joint_3");
    _joints[4] = model->getJoint("joint_4");
    _joints[5] = model->getJoint("joint_5");
    _joints[6] = model->getJoint("joint_6");
    _joints[7] = model->getJoint("hand_tool_joint");
    #endif
    CHECK(_joints[7] == model->getJoint("joint_world"));
    CHECK(_joints[1] == model->getJoint("joint_1"));
    CHECK(_joints[2] == model->getJoint("joint_2"));
    CHECK(_joints[3] == model->getJoint("joint_3"));
    CHECK(_joints[4] == model->getJoint("joint_4"));
    CHECK(_joints[5] == model->getJoint("joint_5"));
    CHECK(_joints[6] == model->getJoint("joint_6"));
    CHECK(_joints[0] == model->getJoint("hand_tool_joint"));


    vector<std::shared_ptr<Link>> _links;
    #if 1
    model->getLinks(_links);    // wrong sequence !!!
    #else
    auto link_0 = model->getLink("world");          _links.push_back(link_0);
    auto link_1 = model->getLink("base_link");      _links.push_back(link_1);
    auto link_2 = model->getLink("shoulder_link");  _links.push_back(link_2);
    auto link_3 = model->getLink("arm_link");       _links.push_back(link_3);
    auto link_4 = model->getLink("elbow_link");     _links.push_back(link_4);
    auto link_5 = model->getLink("forearm_link");   _links.push_back(link_5);
    auto link_6 = model->getLink("wrist_link");     _links.push_back(link_6);
    auto link_7 = model->getLink("hand_link");      _links.push_back(link_7);
    auto link_8 = model->getLink("tool_link");      _links.push_back(link_8);
    #endif

    CHECK(_links[0] == model->getLink("arm_link"));
    CHECK(_links[0]->inertial->mass == 0.81);

    CHECK(_links[1] == model->getLink("base_link"));
    CHECK(_links[1]->inertial->mass == 0.87143);

    CHECK(_links[2] == model->getLink("elbow_link"));
    CHECK(_links[2]->inertial->mass == 0.47756);

    CHECK(_links[3] == model->getLink("forearm_link"));
    CHECK(_links[3]->inertial->mass == 0.53754);

    CHECK(_links[4] == model->getLink("hand_link"));
    CHECK(_links[4]->inertial->mass == 0.00923);

    CHECK(_links[5] == model->getLink("shoulder_link"));
    CHECK(_links[5]->inertial->mass == 0.61357);

    CHECK(_links[6] == model->getLink("tool_link"));
    CHECK(_links[6]->inertial->mass == 0.);

    CHECK(_links[7] == model->getLink("world"));
    CHECK(_links[7]->inertial->mass == 0.);

    CHECK(_links[8] == model->getLink("wrist_link"));
    CHECK(_links[8]->inertial->mass == 0.40192);

}
