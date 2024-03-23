#include "input_handler.h"




void InputHandler::HandleInput(sf::RenderWindow& window_){

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


void InputHandler::InputToQueue(const sf::Keyboard::Key& key) {
  inputs_queue_.push(key);
}

void InputHandler::ExecuteCommand() {
  if ( inputs_queue_.empty() ) {
    std::cout << "No commands to execute" << std::endl;
    return;
  }

  // Getting next input
  sf::Keyboard::Key input = inputs_queue_.front();
  inputs_queue_.pop();

  // Execute command according to certain input
  auto it = commands_map_.find(input);
  if (it != commands_map_.end()) {
    std::vector<std::shared_ptr<Command>> commands = it->second;
    for ( const auto& c : commands ) {
      c->Execute();
    }
  }
}

void InputHandler::AddCommand(const sf::Keyboard::Key& key,
                              const std::shared_ptr<Command>& command) {
  commands_map_[key].emplace_back(command);
}
