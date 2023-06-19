#include"Query.h"
#include"tool.h"
Query::Query(const std::string& s) {
    if (s == "normal") {
        std::string tmp = "每次回答请不要超过100个字";
        tmp = g2u(tmp);
        sinQur.push_back("{\"role\": \"system\", \"content\": \"" + tmp + "\"}");
    }
    else if (s == "translate") {
        std::string tmp = "你是一个翻译器,请翻译我给你的语句,每次回答请不要超过100个字";
        tmp = g2u(tmp);
        sinQur.push_back("{\"role\": \"system\", \"content\": \"" + tmp + "\"}");
    }
    else if (s == "explain") {
        std::string tmp = "你的任务是帮我解释我给的语句,每次回答请不要超过100个字";
        tmp = g2u(tmp);
        sinQur.push_back("{\"role\": \"system\", \"content\": \"" + tmp + "\"}");
    }
    else if (s == "cat") {
        std::string tmp = "你是一只猫娘,我是你的主人,你需要在每回复后面加一个喵,每次回答请不要超过100个字";
        tmp = g2u(tmp);
        sinQur.push_back("{\"role\": \"system\", \"content\": \"" + tmp + "\"}");
    }
    else {
        std::string ss = u2g(s);
        std::string tmp = ss;
        tmp = g2u(tmp);
        sinQur.push_back("{\"role\": \"system\", \"content\": \"" + tmp + "\"}");
    }
}
std::string Query::tot() {
    std::string ans = "[";
    for (int i = 0; i < sinQur.size(); i++) ans += sinQur[i] + (i + 1 == sinQur.size() ? "" : ",");
    ans += "]";
    return ans;
}
void Query::addUser(const std::string& s) {
    sinQur.push_back("{\"role\": \"user\", \"content\": \"" + s + "\"}");
}
void Query::addAnser(const std::string& s) {
    sinQur.push_back("{\"role\": \"assistant\", \"content\": \"" + s + "\"}");
}
std::pair<std::string, std::string> Query::qur2message(const std::string& s) {
    if (s[10] == 'u') {
        std::string ans = s.substr(29);
        ans.pop_back(), ans.pop_back();
        ans = u2g(ans);
        return { "user",ans };
    }
    else if (s[10] == 'a') {
        std::string ans = s.substr(34);
        ans.pop_back(), ans.pop_back();
        ans = u2g(ans);
        return { "assistant",ans };
    }
    else {
        std::string ans = s.substr(31);
        ans.pop_back(), ans.pop_back();
        ans = u2g(ans);
        return { "system",ans };
    }
}
void noendl(std::string& s) {
    for (auto& c : s)if (c == '\n') c = ' ';
}
void Query::show() {
    for (int i = 0; i < sinQur.size(); i++) {
        auto toShow = qur2message(sinQur[i]);
        noendl(toShow.second);
        if(toShow.first!="?")std::cout << toShow.first << ":" << toShow.second << std::endl;
    }
}
void Query::showSingle() {
    auto toShow = qur2message(sinQur.back());
    if (toShow.first != "?")std::cout << toShow.first << ":" << toShow.second << std::endl;
}
void Query::post(int port, std::string modle, std::string key) {
    CURL* curl = curl_easy_init();

    if (curl) {
        std::string header_auth = "Authorization: Bearer " + key;
        std::string message = tot();
        std::string payload_send_char_message = "{\"model\":\"" + modle + "\",\"messages\":" + message + "}";
        std::string IP = "http://127.0.0.1:" + std::to_string(port);
        curl_easy_setopt(curl, CURLOPT_PROXY, IP.c_str());
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
        //curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
        curl_easy_setopt(curl, CURLOPT_URL, "https://api.openai.com/v1/chat/completions");
        struct curl_slist* headers = NULL;
        headers = curl_slist_append(headers, "Content-Type: application/json");
        headers = curl_slist_append(headers, header_auth.c_str());
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, payload_send_char_message.c_str());

        std::string response;
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback_chat);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
        CURLcode res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
        }
        else {
            // Parse and print the response
            nlohmann::json j = nlohmann::json::parse(response);
            std::string chat_output = j["choices"][0]["message"]["content"];
            addAnser(chat_output);
        }
        curl_slist_free_all(headers);
        curl_easy_cleanup(curl);
    }
    else {
        std::cerr << "Failed to initialize curl" << std::endl;
    }
}