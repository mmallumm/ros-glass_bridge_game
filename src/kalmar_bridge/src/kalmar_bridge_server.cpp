#include "kalmar_bridge.h"
#include "kalmar_bridge/KalmarBridge.h"
#include "ros/ros.h"

ros::KalmarBridgeGame game;

bool bridge_handler(kalmar_bridge::KalmarBridge::Request &req,
                    kalmar_bridge::KalmarBridge::Response &res) {
  if(game.PlayerWon()) {
    ros::shutdown();
  }                      
  bool result = game.Play(req.step_cell, res.response);       
  return result;             
}

int main(int argc, char **argv) {
  ros::init(argc, argv, "bridge_server");
  ROS_INFO("kalmar_bridge_server started");

  ros::NodeHandle handler;
  ros::ServiceServer service =
      handler.advertiseService("glass_bridge", bridge_handler);
  ROS_INFO("Ready to play, 456! Start from index 0\n");
  ros::spin();
}