#include "blocks.h"
#include <ranges>
#include "engine/utils.h"
#include "engine/resource_manager.h"

namespace sgui {

void Block::UpdateLayout() {
  if (parent_) {
    sf::Vector2i &parent_grid = parent_->grid_size_.value;
    sf::Rect<float> &parent_content_area = parent_->content_area_.value;
    sf::Vector2f parent_content_position = parent_content_area.getPosition();

    sf::Vector2f grid_cell_size = {
        parent_content_area.getSize().x / static_cast<float>(parent_grid.y),
        parent_content_area.getSize().y / static_cast<float>(parent_grid.x)
    };

    // Size of content, when margin == None
    sf::Vector2f full_size = {
        grid_cell_size.x * static_cast<float>(grid_size_.value.y),
        grid_cell_size.y * static_cast<float>(grid_size_.value.x),
    };

    // Grid offset
    DynamicProperty<sf::Vector2f> offset;
    for (auto offs : offset) {
      offs.x = parent_content_position.x + grid_cell_size.x * static_cast<float>(grid_position_.value.y); // cols -> y
      offs.y = parent_content_position.y + grid_cell_size.y * static_cast<float>(grid_position_.value.x); // rows -> x;
    }

    // Content area size
    if (content_area_type_.value == Relative) {
      // TODO: incorporate the min\max dimensions properties for blocks, to avoid hardcoding
      for (size_t i = 0; i < State::Count; ++i){
        content_area_[i].width = full_size.x * std::max(0.1f, (1.0f - content_size_[i].x));
        content_area_[i].height = full_size.y * std::max(0.1f, (1.0f - content_size_[i].y));
      }
    } else { // Absolute
      for (size_t i = 0; i < State::Count; ++i) {
        content_area_[i].width = std::min(full_size.x, content_size_[i].x);
        content_area_[i].height = std::min(full_size.y, content_size_[i].y);
      }
    }

    // Margin offset
    for (size_t i = 0; i < State::Count; ++i) {
      content_area_[i].left = offset[i].x + (full_size.x - content_area_[i].width) / 2.0f;
      content_area_[i].top = offset[i].y + (full_size.y - content_area_[i].height) / 2.0f;
    }

    UpdateContent();
  }
}

Block::Block(const YAML::Node &layout_config) {
  last_state_ = State::Inactive;

  grid_size_.value = ParseAs<sf::Vector2i>(layout_config["grid-size"]);
  grid_position_.value = ParseAs<sf::Vector2i>(layout_config["grid-position"]);
  inner_grid_.value = ParseAs<sf::Vector2i>(layout_config["inner-grid"]);

  content_area_type_.value = ParseAs<ContentAreaType>(layout_config["content"]["type"]);

  auto& resource_manager = ResourceManager::GetInstance();
  font_.value = resource_manager.GetFont(layout_config["font"].as<std::string>());

  content_size_.value = ParseAs<sf::Vector2f>(layout_config["content"]["size"]);
  content_size_.active = content_size_.hover = content_size_.value;


  UpdateLayout();
}

bool Block::Contains(const sf::Vector2i &positions) {
  return content_area_[last_state_].contains({
      static_cast<float>(positions.x),
      static_cast<float>(positions.y)
  });
}

bool Block::SetState(Block::State new_state) {
  return last_state_ = new_state;
}

Text::Text(const YAML::Node &layout_config)
  : Block(layout_config),
    text_(font_.value){}

void Text::UpdateContent() {

}

} // namespace sgui
