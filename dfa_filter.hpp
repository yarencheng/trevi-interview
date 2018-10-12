#pragma once

#include <vector>
#include <set>
#include <map>
#include <unordered_map>
#include <unordered_set>

namespace interview {

class DFAFilter {
public:

    void add(const std::vector<std::wstring>& dirtyWords);

    std::wstring filter(const std::wstring& in);

    std::map<wchar_t, std::vector<std::wstring>> getDFATree();

private:

    std::map<wchar_t, std::vector<std::wstring>> _tree;

    std::set<std::wstring> _dirtyWords;

};

}