#include "input_handler.h"


void InputHandler::HandleInput(sf::RenderWindow& window_){

  sf::Event event;
  window_.pollEvent(event);

  switch (event.type)
  {
    case sf::Event::KeyPressed:
      InputToQueue(&event.key.code);
      break;

    case sf::Event::Closed:
      window_.close();
      break;

    default:break;
  }

}


void InputHandler::InputToQueue(sf::Keyboard::Key * key) {
  if (*key == sf::Keyboard::Key::X)
    commands_queue_.push(buttonX_);
  else if (*key == sf::Keyboard::Key::Y)
    commands_queue_.push(buttonY_);
  else if (*key == sf::Keyboard::Key::A)
    commands_queue_.push(buttonA_);
  else if (*key == sf::Keyboard::Key::B)
    commands_queue_.push(buttonB_);
}

void InputHandler::ExecuteCommand() {
  if ( commands_queue_.empty() ) {
    std::cout << "No commands to execute" << std::endl;
    return;
  }

  // Getting next command
  Command * c = commands_queue_.front();
  commands_queue_.pop();
  c->Execute();
}
