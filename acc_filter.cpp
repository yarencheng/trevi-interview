#include "acc_filter.hpp"

using namespace ::std;
using namespace ::interview;

void ACCFilter::add(const wstring& s) {
    auto cur = _root;
    for (wchar_t c: s) {
        if (cur->_childs.find(c) == cur->_childs.end()) {
            cur->_childs[c] = make_shared<ACCNode>();
        }
        cur = cur->_childs[c];
    }
}

std::shared_ptr<ACCNode> ACCFilter::getRoot() {
    return this->_root;
}

ACCNode::ACCNode() {

}

ACCNode::ACCNode(const std::unordered_map<wchar_t, std::shared_ptr<ACCNode>>& childs)
    : _childs(childs)
{

}

ACCNode::ACCNode(const std::map<wchar_t, std::shared_ptr<ACCNode>>& childs)
    : _childs(childs.begin(), childs.end())
{

}

bool ACCNode::operator==(const ACCNode& n) const {
    if (_childs.size() != n._childs.size()) {
        return false;
    }

    for (auto p: _childs) {
        auto it = n._childs.find(p.first);

        if (it == n._childs.end()) {
            return false;
        }

        if (*p.second == *it->second) {
            continue;
        } else {
            return false;
        }
    }

    return true;
}
