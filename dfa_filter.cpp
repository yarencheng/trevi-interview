#include "dfa_filter.hpp"

#include <algorithm>
#include <set>
#include <sstream>

using namespace ::std;
using namespace ::interview;

void DFAFilter::init(const vector<string>& dirtyWords) {

    set<string> unique;
    for (auto& s: dirtyWords) {
        unique.insert(s);
    }

    for (auto& word: unique) {
        char first = word[0];
        if (_tree.find(first) == _tree.end()) {
            _tree[first] = vector<string>();
        }
        _tree.find(first)->second.push_back(word.substr(1, word.length()-1));
    }

    for (auto& e: _tree) {
        auto& v = e.second;
        sort (v.begin(), v.end(), [](const string& s1, const string& s2){
            return s1.size() > s2.size();
        });
    }
}

string DFAFilter::filter(const string& in) {

    stringstream out;

    for(int i=0; i<in.length(); i++){
        char first = in[i];
        auto it = _tree.find(first);
        if (it != _tree.end()) {
            auto& v = it->second;
            int len = 0;
            for(int j=0; j<v.size(); j++){
                int beginIndex = i+1;
                int endIndex   = i+1+v[j].length();
                if((endIndex <= in.length()) && in.substr(beginIndex, endIndex-beginIndex) == v[j]){
                    len = v[j].length();
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

unordered_map<char, vector<string>> DFAFilter::getDFATree() {
    return _tree;
}