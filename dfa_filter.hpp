#pragma once

#include <vector>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <functional>

namespace interview {

class DFAFilter {
public:

    void add(const std::vector<std::wstring>& dirtyWords);

    std::wstring filter(const std::wstring& in);

    std::unordered_map<wchar_t, std::vector<std::wstring>> getDFATree();

    std::wstring search(const std::wstring& in);

private:

    std::unordered_map<
        wchar_t,
        std::map<
            std::wstring,
            int,
            std::function<bool(std::wstring, std::wstring)>
        >
    > _tree;

    std::unordered_set<std::wstring> _dirtyWords;

};

}