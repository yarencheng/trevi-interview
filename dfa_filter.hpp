#pragma once

#include <vector>
#include <unordered_map>

namespace interview {

class DFAFilter {
public:

    void init(const std::vector<std::string>& dirtyWords);

    std::string filter(const std::string& in);

    std::unordered_map<char, std::vector<std::string>> getDFATree();

private:

    std::unordered_map<char, std::vector<std::string>> _tree;

};

}