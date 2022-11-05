#include <iostream>
#include "ros/ros.h"
#include "std_msgs/Char.h"
#include "../include/game.h"
#include "kalmar_bridge/BridgeService.h"

kalmar_bridge::GameClient game;
void receive(const std_msgs::Char& side) {
    game.Output(side.data);
}

int main(int argc, char **argv) {
    ros::init(argc, argv, "bridge_client");
    ros::NodeHandle handler;
    ros::Subscriber subscriber = handler.subscribe("kalmar_bridge", 1000, receive);
    while(ros::ok()) {
        ros::spinOnce();
    }

    return 0;
}