#include "acc_filter.hpp"

#include <queue>
#include <sstream>

using namespace ::std;
using namespace ::interview;

void ACCFilter::add(const wstring& s) {
    auto cur = _root;
    for (wchar_t c: s) {
        if (cur->_childs.find(c) == cur->_childs.end()) {
            cur->_childs[c] = make_shared<ACCNode>();
            cur->_childs[c]->_level = cur->_level + 1;
        }
        cur = cur->_childs[c];
    }
}

void ACCFilter::build() {
    // clear failed index nodes
    _failNodes = vector<shared_ptr<ACCNode>>();

    _root->_failIndex = 0;
    _root->_index = _failNodes.size();
    _failNodes.push_back(_root);

    // BFS queue
    queue<shared_ptr<ACCNode>> parents;
    parents.push(_root);

    // walk from top to bottom
    while (!parents.empty()) {
        auto parent = parents.front();
        parents.pop();

        for (auto p: parent->_childs) {
            wchar_t c = p.first;
            auto child = p.second;
            parents.push(child);

            child->_index = _failNodes.size();
            _failNodes.push_back(child);

            auto fail = _failNodes[parent->_failIndex];

            if (parent == _root || fail->_childs.find(c) == fail->_childs.end()) {
                child->_failIndex = parent->_failIndex;
            } else {
                child->_failIndex = fail->_childs[c]->_index;
            }
        }
    }
}

wstring ACCFilter::filter(const wstring& s) const {

    wstringstream os;

    int index = 0;
    auto cur = _root;

    while (index <= s.length()) {

        if (cur != _root && cur->_childs.empty()) {
            index += cur->_level;
            os << wstring(cur->_level, L'*');
            cur = _root;
            continue;
        }

        wchar_t c = s[index + cur->_level];

        if (cur->_childs.find(c) == cur->_childs.end()) {
            cur = _failNodes[cur->_failIndex];
            int step = cur->_level - cur->_failIndex + 1;
            os << s.substr(index, step);
            index += step;
            continue;
        }

        cur = cur->_childs[c];
    }

    return os.str();
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

ACCNode::ACCNode(int index, int failIndex)
    : _index(index), _failIndex(failIndex)
{

}

ACCNode::ACCNode(int index, int failIndex, const std::unordered_map<wchar_t, std::shared_ptr<ACCNode>>& childs)
    : _childs(childs), _index(index), _failIndex(failIndex)
{

}

bool ACCNode::operator==(const ACCNode& n) const {

    if (_index != n._index) {
        return false;
    }

    if (_failIndex != n._failIndex) {
        return false;
    }

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
