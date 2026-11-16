#include <iostream>
#include <chrono>
#include "behaviortree_cpp/action_node.h"
#include "behaviortree_cpp/bt_factory.h"

using namespace std::chrono_literals;

//Node class Method
class ApproachObject : public BT::SyncActionNode
{
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

int main()
{
    
}