#include "dfa_filter.hpp"

#include <locale>
#include <codecvt>
#include <algorithm>
#include <set>
#include <sstream>

using namespace ::std;
using namespace ::interview;

bool compare(wstring s1, wstring s2) {
    return s1.size() > s2.size();
}

void DFAFilter::add(const vector<wstring>& dirtyWords) {

    for (auto& word: dirtyWords) {

        auto r = _dirtyWords.insert(word);
        if (!r.second) {
            continue;
        }


        wchar_t first = word[0];

        if (_tree.find(first) == _tree.end()) {
            _tree[first] = map<wstring, int, function<bool(wstring, wstring)>>(compare);
        }
        _tree.find(first)->second[word.substr(1, word.length()-1)] = 1;
    }
}

wstring DFAFilter::filter(const wstring& in) {

    wstringstream out;

    for(int i=0; i<in.length(); i++){
        wchar_t first = in[i];
        auto it = _tree.find(first);
        if (it != _tree.end()) {
            auto& v = it->second;
            int len = 0;
            for (auto& p: v) {
                wstring word = p.first;
                int beginIndex = i+1;
                int endIndex   = i+1+word.length();
                if((endIndex <= in.length()) && in.substr(beginIndex, endIndex-beginIndex) == word){
                    len = word.length();
                    break;
                }
            }
            if(len >= 0){
                for(int t=0; t<len+1; t++){
                    out << "*";
                }
                i += len;
                continue;
            }
        }

        out << first;
    }


    return out.str();
}

unordered_map<wchar_t, vector<wstring>> DFAFilter::getDFATree() {
    unordered_map<wchar_t, vector<wstring>> ans;

    for (auto& p1: _tree) {
        auto v = vector<wstring>();
        for (auto& p2: p1.second) {
            v.push_back(p2.first);
        }
        ans[p1.first] = v;
    }

    return ans;
}

wstring DFAFilter::search(const wstring& in) {

    wstringstream ws;

    for (auto it=_dirtyWords.begin(); it!=_dirtyWords.end(); it++) {
        auto& word = *it;

        auto start = word.find(in);
        if (it->find(in) == wstring::npos) {
            continue;
        }

        if (it!=_dirtyWords.end()) {
            ws << " ";
        }

        ws << word.substr(0, start) << "[" << in << "]" << word.substr(start+in.size());
    }

    return ws.str();
}