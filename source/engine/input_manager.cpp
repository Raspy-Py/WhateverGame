#include "input_manager.h"


void InputManager::SetActiveState(size_t state) {
  active_state_ = state;
}


int InputManager::GetActiveState() const{
  return active_state_;
}

void InputManager::HandleInput(sf::RenderWindow& window_){

  sf::Event event;
  bool ok = window_.pollEvent(event);
  if ( !ok ) {
    return;
  }

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

sf::Keyboard::Key InputManager::PopNextInput() {
  if ( inputs_queue_.empty() ) {
    return {};
  }

  auto input = inputs_queue_.front();
  inputs_queue_.pop();
  return input;
}

//void InputManager::ExecuteCommand() {
//  if ( inputs_queue_.empty() ) {
//    return;
//  }
//
//  // Getting next input
//  sf::Keyboard::Key input = inputs_queue_.front();
//  inputs_queue_.pop();
//
//  // Execute command according to certain state
//  auto state_map = commands_map_[active_state_];
//  if ( !state_map.empty() ) {
//    auto commands = state_map[input];
//    for ( const auto& command : commands ) {
//      command->Execute();
//    }
//  }
//}
//
//void InputManager::AddCommand(const sf::Keyboard::Key& key,
//                              const std::shared_ptr<Command>& command,
//                              size_t state) {
//  commands_map_[state][key].emplace_back(command);
//}
//
//
////void InputManager::RemoveCommand(const sf::Keyboard::Key& key, int state) {
////  auto state_map = commands_map_[state];
////  if ( !state_map.empty() ) {
////    auto commands = state_map[key];
////
////    commands.erase( std::remove_if( commands.begin() , commands.end() ,
////                                        [state](const std::shared_ptr<Command>& c) {
////                                          return c == key;
////    } ), commands.end() );
////  }
////}