#include <sys/time.h>
#include <sys/resource.h>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <locale>
#include <codecvt>
#include <string>
#include <boost/program_options.hpp>
#include "dfa_filter.hpp"

using namespace ::std;
using namespace ::boost::program_options;
using namespace ::interview;

int main(int argc, char** argv);
wstring randomString(int length);
void profiling(int dataSizeMin, int dataSizeMax, int dataSizeStep, int sentenceLength, string report);
long long getCpuMs();
void interactMode();

int main(int argc, char** argv) {

    int min, max, step, len;
    string report;

    options_description options( "Filter Options");
    options.add_options()
        ("help",                                                            "Show help message")
        ("profiling",                                                       "Profile the time consumption of this filter")
        ("data-size-min",   value<int>(&min)->default_value(100000),             "Min. number of dirty words used in the profiling")
        ("data-size-max",   value<int>(&max)->default_value(2000000),            "Max. number of dirty words used in the profiling")
        ("data-size-step",  value<int>(&step)->default_value(100000),             "Number of dirty words added between each profiling")
        ("sentence-length", value<int>(&len)->default_value(1000),             "Length of the sentence to be filtered in the profiling")
        ("report-file",     value<string>(&report)->default_value("report.csv"),   "Length of the sentence to be filtered in the profiling");

    variables_map vm;
    store(parse_command_line(argc, argv, options), vm);
    notify(vm);

    if (vm.count("help")) {
        cout << options << '\n';
        return 0;
    }

    if (vm.count("profiling")) {
        profiling(min, max, step, len, report);
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

  wstringstream ss;

  for (int i = 0; i < length; ++i) {
    ss << alphanum[rand() % (sizeof(alphanum) - 1)];
  }

  return ss.str();
}

void profiling(int dataSizeMin, int dataSizeMax, int dataSizeStep, int sentenceLength, string report) {

    int size = dataSizeMin;

    ofstream fs;
    fs.open(report);
    fs << "# dirty words, add() ms, filter() ms" << endl;

    while (size <= dataSizeMax) {

        cout << "Generate [" << size << "] dirty words" << endl;

        vector<wstring> dirtyWords;
        for (int i=0; i<size; i++) {
            dirtyWords.push_back(randomString(10));
        }
        wstring sentence = randomString(sentenceLength);

        DFAFilter filter;

        cout << "Add [" << setw(10) << size << "] dirty words into filter" << endl;

        long long ms1 = getCpuMs();
        filter.add(dirtyWords);
        long long ms2 = getCpuMs();

        cout << "Add [" << setw(10) << size << "] dirty words into filter ... [" << (ms2-ms1) << "] ms" << endl;
        cout << "Filter with [" << setw(10) << size << "] dirty words" << endl;

        long long ms3 = getCpuMs();
        filter.filter(sentence);
        long long ms4 = getCpuMs();

        cout << "Filter with [" << setw(10) << size << "] dirty words     ... [" << (ms4-ms3) << "] ms" << endl;

        fs << size << "," << (ms2-ms1) << "," << (ms4-ms3) << endl;

        size += dataSizeStep;
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

    DFAFilter filter;
    wstring_convert<codecvt_utf8_utf16<wchar_t>> converter;

    while (true) {
        string line;
        getline(cin, line);

        wstring wline = converter.from_bytes(line);

        if (wline[0] == L'+') {
            filter.add({wline.substr(1)});
        } else if (wline[0] == L'?') {
            wstring result = filter.search(wline.substr(1));
            cout << "> " << converter.to_bytes(result) << endl;
        } else {
            wstring wfiltered = filter.filter(wline);
            string filtered = converter.to_bytes(wfiltered);
            cout << "> " << filtered << endl;
        }
    }

}