#include <iostream>
#include "cpr/cpr.h"
#include <ncurses.h>
#include <curses.h>
#include "json.hpp"
#include <fstream>
#include <vector>
#include <cmath>
#include "fort.hpp"

using namespace std;
using json = nlohmann::json;

string roundJson(json a)
{
    double b = a.get<double>();
    double c = ceil(b * 100.0) / 100.0;
    string d = to_string(c);
    return d.substr(0, d.size()-4);
}

int main()
{
    cpr::Response r = cpr::Get(cpr::Url{"https://pro-api.coinmarketcap.com/v1/cryptocurrency/listings/latest"},
                      cpr::Header{{"X-CMC_PRO_API_KEY", "9c84b493-9cd6-47a0-8540-25b7d4abb0cd"}},
                      cpr::Parameters{{"convert", "USD"}, {"start", "1"}, {"limit", "6"}});

    json j = json::parse(r.text);
    vector<nlohmann::json> crypto {j["data"][0]["cmc_rank"], j["data"][0]["name"], j["data"][0]["quote"]["USD"]["price"], j["data"][0]["quote"]["USD"]["percent_change_1h"], j["data"][0]["quote"]["USD"]["percent_change_24h"], j["data"][0]["quote"]["USD"]["market_cap"]};
    vector<nlohmann::json> crypto2 {j["data"][1]["cmc_rank"], j["data"][1]["name"], j["data"][1]["quote"]["USD"]["price"], j["data"][1]["quote"]["USD"]["percent_change_1h"], j["data"][1]["quote"]["USD"]["percent_change_24h"], j["data"][1]["quote"]["USD"]["market_cap"]};
    vector<nlohmann::json> crypto3 {j["data"][2]["cmc_rank"], j["data"][2]["name"], j["data"][2]["quote"]["USD"]["price"], j["data"][2]["quote"]["USD"]["percent_change_1h"], j["data"][2]["quote"]["USD"]["percent_change_24h"], j["data"][2]["quote"]["USD"]["market_cap"]};
    vector<nlohmann::json> crypto4 {j["data"][3]["cmc_rank"], j["data"][3]["name"], j["data"][3]["quote"]["USD"]["price"], j["data"][3]["quote"]["USD"]["percent_change_1h"], j["data"][3]["quote"]["USD"]["percent_change_24h"], j["data"][3]["quote"]["USD"]["market_cap"]};
    vector<nlohmann::json> crypto5 {j["data"][4]["cmc_rank"], j["data"][4]["name"], j["data"][4]["quote"]["USD"]["price"], j["data"][4]["quote"]["USD"]["percent_change_1h"], j["data"][4]["quote"]["USD"]["percent_change_24h"], j["data"][4]["quote"]["USD"]["market_cap"]};

    fort::char_table table;
    table.set_border_style(FT_DOUBLE2_STYLE);

    table << fort::header
        << "Rank" << "Coin" << "Price (USD)" << "Change (1H)" << "Change (24H)" << "Market Cap (USD)" << fort::endr
        << crypto[0] <<  crypto[1]  << "$" + roundJson(crypto[2])  << roundJson(crypto[3]) + "%" << roundJson(crypto[4]) + "%" <<  "$" + roundJson(crypto[5]) << fort::endr
        << crypto2[0] <<  crypto2[1]  << "$" + roundJson(crypto2[2])  << roundJson(crypto2[3]) + "%" << roundJson(crypto2[4]) + "%" <<  "$" + roundJson(crypto2[5]) << fort::endr
        << crypto2[0] <<  crypto3[1]  << "$" + roundJson(crypto3[2])  << roundJson(crypto3[3]) + "%" << roundJson(crypto3[4]) + "%" <<  "$" + roundJson(crypto3[5]) << fort::endr
        << crypto4[0] <<  crypto4[1]  << "$" + roundJson(crypto4[2])  << roundJson(crypto4[3]) + "%" << roundJson(crypto4[4]) + "%" <<  "$" + roundJson(crypto4[5]) << fort::endr
        << crypto5[0] <<  crypto5[1]  << "$" + roundJson(crypto5[2])  << roundJson(crypto5[3]) + "%" << roundJson(crypto5[4]) + "%" <<  "$" + roundJson(crypto5[5]) << fort::endr;

    table.set_cell_text_align(fort::text_align::center);
    std::cout << table.to_string() << std::endl;

}
