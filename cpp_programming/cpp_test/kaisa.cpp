#include <iostream>
#include <string>

char shiftChar(char c) {
    // 处理小写字母
    if (c >= 'a' && c <= 'z') {
        return (c - 'a' + 3) % 26 + 'a';
    }
    // 处理大写字母
    else if (c >= 'A' && c <= 'Z') {
        return (c - 'A' + 3) % 26 + 'A';
    }
    // 其他字符保持不变
    else {
        return c;
    }
}

std::string shiftString(const std::string& input) {
    std::string result;
    for (char c : input) {
        result += shiftChar(c);
    }
    return result;
}

int main() {
    std::string input;
    std::cout << "请输入一个字符串: ";
    std::getline(std::cin, input);

    std::string output = shiftString(input);
    std::cout << "转换后的字符串: " << output << std::endl;

    return 0;
}