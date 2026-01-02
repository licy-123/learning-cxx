#include "../exercise.h"
#include <cstring>
#include <memory>
#include <string>
#include <vector>

// READ: `std::unique_ptr` <https://zh.cppreference.com/w/cpp/memory/unique_ptr>

std::vector<std::string> RECORDS;

class Resource {
    std::string _records;

public:
    void record(char record) {
        _records.push_back(record);
    }

    ~Resource() {
        RECORDS.push_back(_records);
    }
};

using Unique = std::unique_ptr<Resource>;
Unique reset(Unique ptr) {
    if (ptr) ptr->record('r');
    return std::make_unique<Resource>();
}
Unique drop(Unique ptr) {
    if (ptr) ptr->record('d');
    return nullptr;
}
Unique forward(Unique ptr) {
    if (ptr) ptr->record('f');
    return ptr;
}

/*
int main(int argc, char **argv) {
    std::vector<std::string> problems[3];

    drop(forward(reset(nullptr)));
    problems[0] = std::move(RECORDS);

    forward(drop(reset(forward(forward(reset(nullptr))))));
    problems[1] = std::move(RECORDS);

    drop(drop(reset(drop(reset(reset(nullptr))))));
    problems[2] = std::move(RECORDS);

    // ---- 不要修改以上代码 ----

    std::vector<const char *> answers[]{
        {"fd"},
        // TODO: 分析 problems[1] 中资源的生命周期，将记录填入 `std::vector`
        // NOTICE: 此题结果依赖对象析构逻辑，平台相关，提交时以 CI 实际运行平台为准
        {"d", "ffr"},
        {"r", "d", "d"},
    };

    // ---- 不要修改以下代码 ----

    for (auto i = 0; i < 3; ++i) {
        ASSERT(problems[i].size() == answers[i].size(), "wrong size");
        for (auto j = 0; j < problems[i].size(); ++j) {
            ASSERT(std::strcmp(problems[i][j].c_str(), answers[i][j]) == 0, "wrong location");
        }
    }

    return 0;
}
*/
// -------------- 调试版 main --------------
int main(int argc, char **argv) {
    std::vector<std::string> problems[3];

    auto print = [&](int idx) {
        std::cout << "chain " << idx << " : ";
        for (auto &s : RECORDS) std::cout << '"' << s << "\" ";
        std::cout << '\n';
        problems[idx] = std::move(RECORDS);
    };

    drop(forward(reset(nullptr)));
    print(0);

    forward(drop(reset(forward(forward(reset(nullptr))))));
    print(1);

    drop(drop(reset(drop(reset(reset(nullptr))))));
    print(2);

    // 把下面终端里显示的字符串按顺序填进 answers 即可
    std::vector<const char *> answers[] = {
        {nullptr},   // 先空着，跑完按输出填
        {nullptr},
        {nullptr}
    };

    // 下面这段仅用于让你看到结果，不会进正式提交
    for (int i = 0; i < 3; ++i) {
        std::cout << "answers[" << i << "] = {";
        for (auto &s : problems[i]) std::cout << "\"" << s << "\",";
        std::cout << "}\n";
    }
    return 0;
}
