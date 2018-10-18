#include <sys/time.h>
#include <sys/resource.h>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <locale>
#include <codecvt>
#include <string>
#include <numeric>
#include <chrono>
#include <boost/program_options.hpp>
#include "dfa_filter.hpp"
#include "acc_filter.hpp"

using namespace ::std;
using namespace ::std::chrono;
using namespace ::boost::program_options;
using namespace ::interview;

int main(int argc, char** argv);
wstring randomString(int length);
void profiling(int dirtyLen, int searchLen, int filterLen, int searchRound, int filterRound, int dirtyMax, string report);
long long getCpuMs();
void interactMode();

int main(int argc, char** argv) {

    int dirtyLen, searchLen, filterLen, searchRound, filterRound, dirtyMax;
    string report;

    options_description options( "Filter Options");
    options.add_options()
        ("help",                                                               "Show help message")
        ("profiling",                                                          "Profile the time consumption of this filter")
        ("dirty-length",  value<int>(&dirtyLen)->default_value (           5), "Length of a dirty word in the profiling mode")
        ("search-length", value<int>(&searchLen)->default_value(           2), "Length of the pattern string to search dirty words in the profiling mode")
        ("filter-length", value<int>(&filterLen)->default_value(         100), "Length of the string to be filtered by dirty words in the profiling mode")
        ("search-round",  value<int>(&searchRound)->default_value(         5), "Number of rounds to re-profile time consumption of searching after a dirty word is added in the profiling mode")
        ("filter-round",  value<int>(&filterRound)->default_value(         5), "Number of rounds to re-profile time consumption of filtering after a dirty word is added in the profiling mode")
        ("dirty-max",     value<int>(&dirtyMax)->default_value(       200000), "Max. number of dirty words used in the profiling mode")
        ("report-file",   value<string>(&report)->default_value("report.csv"), "Length of the sentence to be filtered in the profiling");

    variables_map vm;
    store(parse_command_line(argc, argv, options), vm);
    notify(vm);

    if (vm.count("help")) {
        cout << options << '\n';
        return 0;
    }

    if (vm.count("profiling")) {
        profiling(dirtyLen, searchLen, filterLen, searchRound, filterRound, dirtyMax, report);
        return 0;
    }

    interactMode();

    return 0;
}

wstring randomString(int length) {
    static const wchar_t alphanum[] =
        L"0123456789"
        L"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        L"abcdefghijklmnopqrstuvwxyz";
    static int size = sizeof(alphanum)/sizeof(alphanum[0]);

    wstringstream ss;

    for (int i = 0; i < length; ++i) {
        ss << alphanum[rand() % (size - 1)];
    }

    return ss.str();
}

void profiling(int dirtyLen, int searchLen, int filterLen, int searchRound, int filterRound, int dirtyMax, string report) {

    ofstream fs;
    fs.open(report);
    fs << "# dirty words, add() ms, build() ms, search() avg ms, filter() avg ms" << endl;

    ACCFilter filter;
    filter.build();

    int lastPercent = -1;
    auto c0 = high_resolution_clock::now();

    for (int dirtyCount=1; dirtyCount<=dirtyMax; dirtyCount++) {
        if (dirtyCount*100/dirtyMax > lastPercent) {
            lastPercent = dirtyCount*100/dirtyMax;
            auto cdiff = high_resolution_clock::now() - c0;
            cout << "[" << setw(5) << duration_cast<seconds>(cdiff).count() << "] dirtyCount = " << dirtyCount << "/" << dirtyMax << " (" << lastPercent << "%)" << endl;
        }

        wstring dirtyWord = randomString(dirtyLen);

        auto t0 = getCpuMs();
        filter.add(dirtyWord);
        auto addMs = getCpuMs() - t0;

        if (dirtyCount % (dirtyMax/1000) != 0) {
            continue;
        }

        t0 = getCpuMs();
        filter.build();
        auto buildMs = getCpuMs() - t0;

        vector<long long> searchMss;
        for (int i=0; i<searchLen; i++) {
            wstring searchPattern = randomString(searchLen);

            t0 = getCpuMs();
            filter.search(searchPattern);
            auto searchMs = getCpuMs() - t0;

            searchMss.push_back(searchMs);
        }
        auto searchMsAvg = accumulate(searchMss.begin(), searchMss.end(), 0.0)/searchMss.size();

        vector<long long> filterMss;
        for (int i=0; i<filterRound; i++) {
            wstring filterSentence = randomString(filterLen);

            t0 = getCpuMs();
            filter.filter(filterSentence);
            auto filterMs = getCpuMs() - t0;

            filterMss.push_back(filterMs);
        }
        auto filterMsAvg = accumulate(filterMss.begin(), filterMss.end(), 0.0)/filterMss.size();

        fs  << dirtyCount << ","
            << addMs << ","
            << buildMs << ","
            << searchMsAvg << ","
            << filterMsAvg
            << endl;
    }

    fs.close();
}

long long getCpuMs(){
    struct rusage usage;
    if (0 != getrusage(RUSAGE_SELF, &usage)) {
        throw runtime_error("Failed to read CPU time");
    }

    long long ms = usage.ru_utime.tv_sec;
    ms *= 1000 * 1000;
    ms += usage.ru_utime.tv_usec;

    return ms;
}

void interactMode() {

    ACCFilter filter;
    filter.build();
    wstring_convert<codecvt_utf8_utf16<wchar_t>> converter;

    while (true) {
        string line;
        getline(cin, line);

        wstring wline = converter.from_bytes(line);

        if (wline.length() == 0) {
            cout << endl<< "EXIT" << endl << endl;
            return;
        } if (wline[0] == L'+') {
            filter.add(wline.substr(1));
            filter.build();
        } else if (wline[0] == L'?') {
            auto words = filter.search(wline.substr(1));

            cout << "[";

            if (words.empty()) {
                cout << " NOT FOUND ";
            }

            for (auto it=words.begin(); it!=words.end(); it++) {
                if (it != words.begin()) {
                    cout << ", ";
                }
                cout << converter.to_bytes(*it);
            }

            cout << "]" << endl;
        } else {
            wstring wfiltered = filter.filter(wline);
            string filtered = converter.to_bytes(wfiltered);
            cout << "> " << filtered << endl;
        }
    }

}