#include"Query.h"
#include"tool.h"
const std::string gpt3 = "gpt-3.5-turbo", gpt4 = "gpt-4";
using namespace std;
int main() {
    #pragma warning(disable:4996)
    //填入你的私钥
    std::string openai_key = "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";
    //填入你的端口号
    int port = 51391;
    freopen("default.txt", "r", stdin);
    std::vector<std::string> input;
    for (int i = 0;; i++) {
        input.push_back("");
        if (!getline(std::cin, input[i])) { input.pop_back(); break; }
    }
   // for (int i = 0; i <= input.size() - 1; i++) cout << input[i];
    //cout << endl;
    for (auto& s : input) {
        zhuanyi(s);
    }
    Query q("");
    for (int i = 0;; i++) if (input[0][i] == ':') { q = Query{ input[0].substr(i + 1) }; break; }
    for (int i = 1; i < input.size(); i++) {
        std::string& s = input[i];
        int t = s[0];
        s= u2g(s);
        s = g2u(s);
        for (int i = 0;; i++) { 
            if (s[i] == ':') {
                s = s.substr(i + 1);
                if (t == 'a') {
                    q.addAnser(s);
                }
                else if (t == 'u') {
                    q.addUser(s);
                }
                break;
            }
        }
    }
    q.post(port, gpt4, openai_key);
    freopen("default.txt", "w", stdout);
    q.show();
    return 0;
}