#include <iostream>
#include <chrono>
#include <curl/curl.h>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

void fetchAggTrades() {
    CURL* curl;
    CURLcode res;
    std::string readBuffer;

    curl = curl_easy_init();
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, "https://fapi.binance.com/fapi/v1/aggTrades?symbol=BTCUSDT&limit=5");
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);

        if(res != CURLE_OK) {
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
            return;
        }

        auto start = std::chrono::high_resolution_clock::now();
        json trades = json::parse(readBuffer);
        auto end = std::chrono::high_resolution_clock::now();

        json formattedTrades = json::array();
        for (const auto& trade : trades) {
            json formattedTrade = {
                {"a", trade["a"]}, // Aggregate tradeId
                {"p", trade["p"]}, // Price
                {"q", trade["q"]}, // Quantity
                {"f", trade["f"]}, // First tradeId
                {"l", trade["l"]}, // Last tradeId
                {"T", trade["T"]}, // Timestamp
                {"m", trade["m"]}  // Was the buyer the maker?
            };
            formattedTrades.push_back(formattedTrade);
        }

        std::cout << formattedTrades.dump(4) << std::endl;

        std::chrono::duration<double> duration = end - start;
        std::cout << "Time taken to parse trades: " << duration.count() << " seconds" << std::endl;
    }
}