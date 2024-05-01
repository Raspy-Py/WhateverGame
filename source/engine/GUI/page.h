#ifndef WHATEVERGAME_SOURCE_ENGINE_GUI_PAGE_H_
#define WHATEVERGAME_SOURCE_ENGINE_GUI_PAGE_H_

#include "blocks.h"

#include <memory>

namespace sgui {
class Page {
  struct BlockNode{
    std::shared_ptr<Block> item;
    std::vector<std::shared_ptr<BlockNode>> children;
  };

 public:
  Page() = default;
  explicit Page(const std::string &layout_path);

  void Update(const sf::Vector2i& mouse_position, bool is_button_pressed);
  void LoadLayout(const std::string &layout_path);
  std::shared_ptr<Block> GetBlock(const std::string &block_name);

 private:
  // Container for fast access to concrete blocks
  std::unordered_map<std::string, std::shared_ptr<BlockNode>> blocks_;

  // This tree reflects the actual hierarchy of the interface elements
  // and used for updating blocks' layouts in the correct order
  std::shared_ptr<BlockNode> dom_tree_root_;
};

} // namespace sgui

#endif //WHATEVERGAME_SOURCE_ENGINE_GUI_PAGE_H_
