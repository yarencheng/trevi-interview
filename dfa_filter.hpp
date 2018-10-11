#pragma once

#include <vector>
#include <unordered_map>

namespace interview {

class DFAFilter {
public:

    void init(const std::vector<std::wstring>& dirtyWords);

    std::wstring filter(const std::wstring& in);

    std::unordered_map<wchar_t, std::vector<std::wstring>> getDFATree();

private:

    std::unordered_map<wchar_t, std::vector<std::wstring>> _tree;

};

}