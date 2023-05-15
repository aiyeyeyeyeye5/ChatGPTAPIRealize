#include "CurlWrapper.h"

CurlWrapper::CurlWrapper(const std::string& data) : postData(data) {
    curl = curl_easy_init();
    if (curl)
    {
        std::string auth = "Authorization: Bearer " + OpenAIKeys;
        headers = curl_slist_append(headers, "Content-Type: application/json");
        headers = curl_slist_append(headers, auth.c_str());
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

        NetWorkProxy proxy("51391");
        curl_easy_setopt(curl, CURLOPT_PROXY, "http://127.0.0.1:51391");
        curl_easy_setopt(curl, CURLOPT_URL, "https://api.openai.com/v1/chat/completions");

        std::cout << "initial curl success" << std::endl;

        std::cout << "please tell me what you want to talk?" << std::endl;
        while ()
        {

        }
        std::getline(std::cin, postData);
        PostData post(postData);

    }
}

CurlWrapper::~CurlWrapper() {
    std::cout << "finish curl success" << std::endl;
}

void CurlWrapper::setOpenAIKeys(const std::string OpenAIKeys) : OpenAIKeys(OpenAIKeys)
{
    std::cout << "keys load finished" << std::endl;
}


void makeRequest(const std::string& data) {
    CURL* curl = curl_easy_init();

    if (curl) {
        std::string header_auth = "Authorization: Bearer " + openai_key;

        nlohmann::json j;
        std::string a = "model";
        j[a] = "gpt-3.5-turbo-0301";
        j["messages"] = { { {"role", "user"}, {"content", data} } };
        j["max_tokens"] = 2000;
        j["temperature"] = 0.8;

        std::string payload_send_char_message = j.dump();


        curl_easy_setopt(curl, CURLOPT_PROXY, "http://127.0.0.1:51391");
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
            nlohmann::json j = nlohmann::json::parse(response);
            std::string chat_output = j["choices"][0]["message"]["content"];
            std::cout << "Response: " << chat_output << std::endl;
        }

        curl_slist_free_all(headers);
        curl_easy_cleanup(curl);
    }