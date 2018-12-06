//============================================================================
// Name        : utvik-weather-data.cpp
// Author      : Claus Guttesen
// Version     :
// Copyright   : Just let me know.
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <sstream>
#include <string>

#include <curlpp/cURLpp.hpp>
#include <curlpp/Easy.hpp>
#include <curlpp/Options.hpp>
#include <curlpp/Infos.hpp>
#include <curlpp/Exception.hpp>

#include <pqxx/pqxx>

#include "ParseXML.hpp"

using namespace std;

int main(int argc, char* argv[]) {
    if (argc != 3) {
        cerr << "Usage: " << argv[0] << " <username> <password>" << endl;
        return EXIT_FAILURE;
    }
    try {
        try {
            pqxx::connection C("dbname=weather user=claus hostaddr=127.0.0.1 port=5432");
            if (!C.is_open()) {
                cerr << "Unable to connect to database" << C.dbname() << endl;
                return EXIT_FAILURE;
            }

            const string url = "https://www.vegvesen.no/ws/no/vegvesen/veg/trafikkpublikasjon/vaer/2/GetMeasuredWeatherData/";

            std::string username = argv[1];
            std::string password = argv[2];
            std::string credentials = username + ":" + password;

            curlpp::Cleanup cleaner;
            curlpp::Easy request;

            request.setOpt(new curlpp::options::Url(url));
            request.setOpt(new curlpp::options::UserPwd(credentials));

//string effUrl = curlpp::infos::EffectiveUrl::get(request);
//cout << "effective URL: " << effUrl << endl;

            ostringstream out;
            out << request;

//cout << out.str() << endl;

            ParseXML parse{out.str()};

            string sql = "insert into readings (_id, date, relative_humidity, precipitation, road_surface_temperature";
            sql += ", snow_depth, wind_speed, wind_direction, temperature, dew_point_temperature, visibility)";
            sql += " values (" + parse.id() + ", '" + parse.date() + "'";
            sql += ", " + to_string(parse.relative_humidity()) + ", " + to_string(parse.precipitation());
            sql += ", " + to_string(parse.road_surface_temperature()) + ", " + to_string(parse.snowdepth());
            sql += ", " + to_string(parse.windspeed()) + ", " + to_string(parse.winddirection());
            sql += ", " + to_string(parse.temperature()) + ", " + to_string(parse.dew_point_temperature());
            sql += ", " + to_string(parse.visibility()) + ")";

            pqxx::work W(C);
            W.exec(sql);
            W.commit();
            C.disconnect();
            return EXIT_SUCCESS;
        } catch (const exception& e) {
            cerr << e.what() << endl;
            return EXIT_FAILURE;
        }

    } catch (curlpp::LogicError& e) {
        cout << e.what() << endl;
    } catch (curlpp::RuntimeError& e) {
        cout << e.what() << endl;
    }

    return EXIT_FAILURE;
}
