#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    string s = argv[1];
    string cpp = s + ".cpp";
    string exe = s + ".exe";
    string out = s + ".out";

    string cp = "g++ -std=c++20 -O2 " + cpp + " -o " + exe;
    if (system(cp.c_str()) != 0) {
        cerr << "Compile Failed!" << endl;
        return 1;
    }

    string run = exe;
    if (argc > 2) {
        run += " < " + string(argv[2]);
    }
    run += " > " + out;

    system(run.c_str());

    cout << "\n--- Output ---\n";
    system(("type " + out).c_str());
    cout << "\n--------------\n";

    return 0;
}
/*
首先编译运行脚本，这只需要执行一次: g++ r.cpp -o r.exe
以文件内容作为输入: r a a.in (文件名可以随意指定)
手动输入: r a
*/