#include <ctime>
#include "ros/ros.h"
#include "../include/game.h"

kalmar_bridge::GlassBridge::GlassBridge() {
  srand(time(0));
  safe_field_.resize(BRIDGE_SIZE);
  for (auto& el : safe_field_) {
    int random_index = 1 + (rand() % 2);
    el = (random_index == 1) ? 'L' : 'R';
  }
}

char kalmar_bridge::GlassBridge::At(size_t index) const { return safe_field_.at(index); }

std::string kalmar_bridge::GlassBridge::Get() const { return safe_field_; }

bool kalmar_bridge::GameServer::PlayerWon() const {
  return (counter_ == BRIDGE_SIZE) ? true : false;
}

bool kalmar_bridge::GameServer::Play(char input, std::string& output) {
  std::string sucess = "Cell is strong. Move next!";
  std::string fail = "Oops, you're dead.";
  std::string win = "Congratulations, you won!!!";
  std::string uncorrect = "Uncorrect service request.";

  switch (input) {
    case 'R':
      if (bridge_.At(counter_) == 'R') {
        ROS_INFO(&*sucess.begin());
        output = sucess;
        ++counter_;
      } else {
        ROS_INFO(&*fail.begin());
        output = fail;
        ROS_INFO("Service shoutdown");
        ros::shutdown();
      }

      if (PlayerWon()) {
        ROS_INFO(&*win.begin());
        output = win;
      }
      break;

    case 'L':
      if (bridge_.At(counter_) == 'L') {
        ROS_INFO(&*sucess.begin());
        output = sucess;
        ++counter_;
      } else {
        ROS_INFO(&*fail.begin());
        output = fail;
        ROS_INFO("Service shoutdown");
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
  
  return true;
}

std::string kalmar_bridge::GameServer::GetSafeWay() const {
  return bridge_.Get();
}

kalmar_bridge::GameClient::GameClient() {
  srand(time(0));
  player_number_ = 1 + (rand() % 1000);
  std::cout<<"Greetings, Player "<<player_number_<<"!\n"; 
}

char kalmar_bridge::GameClient::Input() const {
  char side;
  std::cout<<"Player "<<player_number_<<", choose next cell!!!\n";
  std::cin>>side;
  return side;
}

void kalmar_bridge::GameClient::Output(char current_side) {
  current_path_ += current_side;
  std::cout<<"Path: "<<current_path_<<std::endl;
}