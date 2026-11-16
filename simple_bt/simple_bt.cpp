#include <iostream>
#include <chrono>
#include "behaviortree_cpp/action_node.h"
#include "behaviortree_cpp/bt_factory.h"

using namespace std::chrono_literals;

//Node class Method
class ApproachObject : public BT::SyncActionNode
{
public:
    explicit ApproachObject(const std::string &name) : BT::SyncActionNode(name, {})
    {

    }

    //FAILURE/SUCCESS/RUNNING
    //Since this is a synchronous node, it cannot return "RUNNING". It returns only
    //SUCESS or FAILURE
    BT::NodeStatus tick() override
    {
        std::cout << "Approach Object: " << this->name() << std::endl;
        std::this_thread::sleep_for(5s);
        return BT::NodeStatus::SUCCESS;
    }
};

// function Method
BT::NodeStatus CheckBattery()
{
    std::cout << "Battery OK" << std::endl;
    return BT::NodeStatus::SUCCESS;
}

// custom class Method
class GripperInterface
{
    bool _open;
public:
    GripperInterface() : _open(true){}

    BT::NodeStatus open()
    {
        _open = true;
        std::cout << "Gripper open" << std::endl;
        return BT::NodeStatus::SUCCESS;
    }

    BT::NodeStatus close()
    {
        _open = false;
        std::cout << "Gripper close" << std::endl;
        return BT::NodeStatus::SUCCESS;
    }
};

int main()
{
    BT::BehaviorTreeFactory factory;
    factory.registerNodeType<ApproachObject>("ApproachObject");
    
    factory.registerSimpleCondition("CheckBattery", std::bind(CheckBattery));

    GripperInterface gripper;

    factory.registerSimpleAction(
        "OpenGripper",
        std::bind(&GripperInterface::open, &gripper)
    );

    factory.registerSimpleAction(
        "CloseGripper",
        std::bind(&GripperInterface::close, &gripper)
    );

    auto tree = factory.createTreeFromFile("./../bt_tree.xml");

    tree.tickExactlyOnce();

    tree.tickExactlyOnce();

    return 0;
}
