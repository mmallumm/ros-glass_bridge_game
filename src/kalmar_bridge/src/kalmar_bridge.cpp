#include "kalmar_bridge.h"

#include <ctime>

#include "ros/ros.h"

ros::GlassBridge::GlassBridge() {
  srand(time(0));
  safe_field_.resize(BRIDGE_SIZE);
  for (auto& el : safe_field_) {
    int random_index = 1 + (rand() % 2);
    el = (random_index == 1) ? 'L' : 'R';
  }
}

char ros::GlassBridge::At(size_t index) const { return safe_field_.at(index); }

std::string ros::GlassBridge::Get() { return safe_field_; }

bool ros::KalmarBridgeGame::PlayerWon() const {
  return (counter == BRIDGE_SIZE) ? true : false;
}

bool ros::KalmarBridgeGame::Play(char input, std::string& output) {
  std::string sucess = "Cell is strong. Move next!\n";
  std::string fail = "Oops, you're dead.\n";
  std::string win = "Congratulations, you won!!!\n";
  std::string uncorrect = "Uncorrect service request.\n";
  ROS_INFO("Safe subsequence is: ");
  ROS_INFO(&*bridge.Get().begin());
  ROS_INFO("Current index is: ");
  ROS_INFO("%u", counter);
  ROS_INFO("Your input is: ");
  ROS_INFO("%c", input);

  switch (input) {
    case 'R':
      if (bridge.At(counter) == 'R') {
        ROS_INFO(&*sucess.begin());
        output = sucess;
        ++counter;
      } else {
        ROS_INFO(&*fail.begin());
        output = fail;
        ros::shutdown();
      }

      if (PlayerWon()) {
        ROS_INFO(&*win.begin());
        output = win;
      }
      break;

    case 'L':
      if (bridge.At(counter) == 'L') {
        ROS_INFO(&*sucess.begin());
        output = sucess;
        ++counter;
      } else {
        ROS_INFO(&*fail.begin());
        output = fail;
        ros::shutdown();
      }

      if (PlayerWon()) {
        ROS_INFO(&*win.begin());
        output = win;
      }
      break;

    default:
      ROS_INFO(&*uncorrect.begin());
      output = uncorrect;
      return false;
  }
  ROS_INFO("Next index is: ");
  ROS_INFO("%u", counter);
  return true;
}