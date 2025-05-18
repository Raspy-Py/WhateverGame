#include "page.h"

#include "yaml-cpp/yaml.h"
#include <string>

namespace sgui{

void Page::LoadLayout(const std::string &layout_path) {
  YAML::Node layout = YAML::LoadFile(layout_path);

  if (layout.Type() != YAML::NodeType::Map){
    std::cerr << "Error: invalid layout format." << std::endl;
    return;
  }

  for (auto block : layout){
    auto block_name = block.first.as<std::string>();
    if (block_name == "defaults"){
      continue;
    }

    auto block_config = block.second;
    std::shared_ptr<Block> new_block;
    /*
    if (block_config["type"].as<std::string>() == "container")
      new_block = std::make_shared<Container>(block_config);
    else if(block_config["type"].as<std::string>() == "input")
      new_block = std::make_shared<Input>(block_config);
    else if(block_config["type"].as<std::string>() == "button")
      new_block = std::make_shared<Button>(block_config);
    else if(block_config["type"].as<std::string>() == "text")
      new_block = std::make_shared<Text>(block_config);
    */
  }

}

Page::Page(const std::string &layout_path) {
  LoadLayout(layout_path);
}

std::shared_ptr<Block> Page::GetBlock(const std::string &block_name) {
  auto block_ptr = blocks_.find(block_name);

  if (block_ptr == blocks_.end()){
    std::cerr << "GUI block: " << block_name << "is not present on this page." << std::endl;
    return {};
  }

  return block_ptr->second->item;
}

}; // namespace sgui