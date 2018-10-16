#pragma once

#include <unordered_map>
#include <vector>
#include <memory>
#include <ostream>

namespace interview {

class ACCNode;

class ACCNode {
    friend class ACCFilter;

public:

    ACCNode();
    ACCNode(const std::unordered_map<wchar_t, std::shared_ptr<ACCNode>>& childs);
    ACCNode(int index, int failIndex);
    ACCNode(int index, int failIndex, const std::unordered_map<wchar_t, std::shared_ptr<ACCNode>>& childs);

    bool operator==(const ACCNode& n) const;
    bool operator!=(const ACCNode& n) const;

    friend std::ostream& operator<<(std::ostream& os, const ACCNode& node) {

        os << "[" << node._index << "," << node._failIndex;

        for (const auto& p: node._childs) {
            os << "," << (wchar_t)p.first << ":" << *p.second;
        }

        os << "]";

        return os;
    }

private:
    std::unordered_map<wchar_t, std::shared_ptr<ACCNode>> _childs;
    int _index = -1;
    int _failIndex = -1;
    int _level = 0;
};

class ACCFilter {

public:

    void add(const std::wstring& s);

    void build();

    std::wstring filter(const std::wstring& s) const ;

    std::shared_ptr<ACCNode> getRoot();

private:
    std::shared_ptr<ACCNode> _root = std::make_shared<ACCNode>();
    std::vector<std::shared_ptr<ACCNode>> _failNodes;
};

}