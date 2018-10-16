#pragma once

#include <unordered_map>
#include <map>
#include <memory>

namespace interview {

class ACCNode;

class ACCNode {
    friend class ACCFilter;

public:

    ACCNode();
    ACCNode(const std::unordered_map<wchar_t, std::shared_ptr<ACCNode>>& childs);

    bool operator==(const ACCNode& n) const;
    bool operator!=(const ACCNode& n) const;

private:
    std::unordered_map<wchar_t, std::shared_ptr<ACCNode>> _childs;
};

class ACCFilter {

public:

    void add(const std::wstring& s);

    std::shared_ptr<ACCNode> getRoot();

private:
    std::shared_ptr<ACCNode> _root = std::make_shared<ACCNode>();
};

}