#ifndef BRIDGE_H
#define BRIDGE_H

#include <string>

#define BRIDGE_SIZE 18

namespace kalmar_bridge {
class GlassBridge {
 public:
  GlassBridge();
  char At(size_t index) const;
  std::string Get() const;

 private:
  std::string safe_field_;
};

class GameServer {
 public:
  bool Play(char input, std::string& output);
  bool PlayerWon() const;
  std::string GetSafeWay() const;

 private:
  GlassBridge bridge_;
  size_t counter_;
};

class GameClient {
 public:
  GameClient();
  char Input() const;
  void Output(char current_side);

 private:
  size_t player_number_;
  std::string current_path_;
};
}  // namespace ros

#endif