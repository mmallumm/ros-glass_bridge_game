#include "../include/game.h"
#include "kalmar_bridge/BridgeService.h"
#include "ros/ros.h"
#include "std_msgs/Char.h"

kalmar_bridge::GameServer game;
ros::Publisher publisher;

void publish_message(char input) {
  if(input == 'R' || input == 'L') {
    std_msgs::Char msg;
    msg.data = input;
    publisher.publish(msg);
  }
}

bool service_handler(kalmar_bridge::BridgeService::Request &req,
                     kalmar_bridge::BridgeService::Response &res) {
  bool result = game.Play(req.step_cell, res.response);
  publish_message(req.step_cell);

  return result;
}

int main(int argc, char **argv) {
  ros::init(argc, argv, "bridge_server");
  std::cout<<"Bridge generated: "<<game.GetSafeWay()<<std::endl;
  ros::NodeHandle handler;
  publisher = handler.advertise<std_msgs::Char>("kalmar_bridge", 1000);
  ros::ServiceServer service_server =
      handler.advertiseService("bridge_game_service", service_handler);

  while(ros::ok()){
    if(game.PlayerWon()) {
      ROS_INFO("Service shoutdown");
      ros::shutdown();
    }

    ros::spinOnce();
  }

  return 0;
}