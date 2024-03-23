#include "input_manager.h"


void InputManager::SetActiveState(int state) {
  active_state_ = state;
}


int InputManager::GetActiveState() const{
  return active_state_;
}

void InputManager::HandleInput(sf::RenderWindow& window_){

  sf::Event event;
  window_.pollEvent(event);

  switch (event.type)
  {
    case sf::Event::KeyPressed:
      InputToQueue(event.key.code);
      break;

    case sf::Event::Closed:
      window_.close();
      break;

    default:break;
  }

}


void InputManager::InputToQueue(const sf::Keyboard::Key& key) {
  inputs_queue_.push(key);
}

void InputManager::ExecuteCommand() {
  if ( inputs_queue_.empty() ) {
//    std::cout << "No commands to execute" << std::endl;
    return;
  }

  // Getting next input
  sf::Keyboard::Key input = inputs_queue_.front();
  inputs_queue_.pop();

  // Execute command according to certain input
  auto it = commands_map_.find(input);
  if (it != commands_map_.end()) {
    auto commands = it->second;
    for ( const auto& [c, state] : commands ) {
         if ( active_state_ == state ) c->Execute();
    }
  }
}

void InputManager::AddCommand(const sf::Keyboard::Key& key,
                              const std::shared_ptr<Command>& command,
                              int state) {
  commands_map_[key].emplace_back(command, state);
}


void InputManager::RemoveCommand(const sf::Keyboard::Key& key, int state) {
  auto it = commands_map_.find(key);
  if (it != commands_map_.end()) {
    auto &key_commands = it->second;

    key_commands.erase( std::remove_if( key_commands.begin() , key_commands.end() ,
                                        [state](const std::pair<std::shared_ptr<Command>, int>& pair) {
                                          return pair.second == state;
    } ), key_commands.end() );
  }
}