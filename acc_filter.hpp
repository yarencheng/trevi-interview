#pragma once

#include <unordered_map>
#include <memory>

namespace interview {

class ACCNode;

class ACCNode {

public:

private:
    std::unordered_map<wchar_t, std::shared_ptr<ACCNode>> _childs;
};

class ACCFilter {

public:
    void add(const std::wstring& s);

private:
    std::shared_ptr<ACCNode> _root = std::make_shared<ACCNode>();
};

}