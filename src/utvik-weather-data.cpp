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
#include <curlpp/Exception.hpp>

#include "ParseXML.hpp"

using namespace std;

int main(int argc, char* argv[]) {
    if (argc != 3) {
        cerr << "Usage: " << argv[0] << " <username> <password>" << endl;
        return EXIT_FAILURE;
    }
    try {
        const string url = "https://www.vegvesen.no/ws/no/vegvesen/veg/trafikkpublikasjon/vaer/1/GetMeasuredWeatherData/";
        std::string username = argv[1];
        std::string password = argv[2];
        std::string credentials = username + ":" + password;

        curlpp::Cleanup cleaner;
        curlpp::Easy request;

        request.setOpt(new curlpp::options::Url(url));
        request.setOpt(new curlpp::options::UserPwd(credentials));

        ostringstream out;
        out << request;

        ParseXML parse{out.str()};

        cout << "Id: " << parse.id() << endl;
        cout << "Date: " << parse.date() << endl;
        cout << "Relative humidity: " << parse.relative_humidity() << " %" << endl;
        cout << "Precipitation: " << parse.precipitation() << " mm" << endl;
        cout << "Road surface temperature: " << parse.road_surface_temperature() << " ºC, " << parse.road_surface_temperature_fahrenheit() << " ºF" << endl;
        cout << "Snow depth: " << parse.snowdepth() << " meters" << endl;
        cout << "Windspeed: " << parse.windspeed() << " km/h, " << parse.windspeedMPS() << " m/s" << endl;
        cout << "Winddirection: " << parse.winddirection() << endl;
        cout << "Temperature: " << parse.temperature() << " ºC, " << parse.temperature_fahrenheit() << " ºF" << endl;
        cout << "Dew point temperature: " << parse.dew_point_temperature() << " ºC, " << parse.dew_point_temperature_fahrenheit() << " ºF" << endl;
        cout << "Visibility: " << parse.visibility() << " meters" << endl;

        return EXIT_SUCCESS;
    } catch (curlpp::LogicError& e) {
        cout << e.what() << endl;
    } catch (curlpp::RuntimeError& e) {
        cout << e.what() << endl;
    }

    return EXIT_FAILURE;
}
