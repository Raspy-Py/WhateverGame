#ifndef WHATEVERGAME_SOURCE_ENGINE_GUI_BLOCKS_H_
#define WHATEVERGAME_SOURCE_ENGINE_GUI_BLOCKS_H_

#include "SFML/Graphics.hpp"
#include "yaml-cpp/yaml.h"

#include "gui_common.h"

#include <map>
#include <string>
#include <iostream>

namespace sgui {

class Block {
 public:
  enum State { Inactive, Hover, Active, Count };
  enum ContentAreaType { Absolute, Relative, Invalid };

  template<typename T>
  struct StaticProperty {
    T value;
  };

  template<typename T>
  struct DynamicProperty {
    union {
      struct {
        T value;
        T hover;
        T active;
      };
      T array[Count]{};
    };

    T &operator[](size_t index) {
      return array[index];
    }

    const T &operator[](size_t index) const {
      return array[index];
    }

    T *begin() { return array; }
    T *end() { return array + Count; }
    [[nodiscard]] const T *begin() const { return array; }
    [[nodiscard]] const T *end() const { return array + Count; }
  };

 public:
  explicit Block(const YAML::Node &layout_config);
  virtual ~Block() = default;

  template<class BlockType>
  BlockType *as() {
    auto block = dynamic_cast<BlockType>(this);
    if (!block) {
      std::cerr << "Error: failed to cast the block." << std::endl;
    }
    return block;
  }

  // Recalculates block positioning and sizing according to the config
  void UpdateLayout();
  // Check if Mouse is hovered over the block
  bool Contains(const sf::Vector2i &positions);
  // Update the state of the block
  bool SetState(State new_state);

 protected:
  // Widget specific update
  virtual void UpdateContent() = 0;

 protected:
  std::shared_ptr<Block> parent_;

  // Set upon initialization
  StaticProperty<sf::Vector2i> grid_size_;
  StaticProperty<sf::Vector2i> grid_position_;
  StaticProperty<sf::Vector2i> inner_grid_;
  StaticProperty<ContentAreaType> content_area_type_;
  StaticProperty<sf::Font> font_;

  DynamicProperty<sf::Vector2f> content_size_;
  DynamicProperty<sf::Color> color_;
  DynamicProperty<sf::Color> font_color_;
  DynamicProperty<float> font_size_;

  // Updated on every frame
  DynamicProperty<sf::Rect<float>> content_area_;
  State last_state_;
};

class Text final : public Block {
 public:
  explicit Text(const YAML::Node &layout_config);
  ~Text() final = default;

 protected:
  void UpdateContent() final;

 private:
  sf::Text text_;
};

};
#endif //WHATEVERGAME_SOURCE_ENGINE_GUI_BLOCKS_H_
