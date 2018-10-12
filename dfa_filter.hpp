#pragma once

#include <vector>
#include <unordered_map>
#include <unordered_set>

namespace interview {

class DFAFilter {
public:

    void add(const std::vector<std::wstring>& dirtyWords);

    std::wstring filter(const std::wstring& in);

    std::unordered_map<wchar_t, std::vector<std::wstring>> getDFATree();

private:

    std::unordered_map<wchar_t, std::vector<std::wstring>> _tree;

    std::unordered_set<std::wstring> _dirtyWords;

};

}