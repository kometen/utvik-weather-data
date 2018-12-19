//============================================================================
// Name        : utvik-weather-data.cpp
// Author      : Claus Guttesen
// Version     :
// Copyright   : Just let me know.
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <map>
#include <sstream>
#include <string>

#include <curlpp/cURLpp.hpp>
#include <curlpp/Easy.hpp>
#include <curlpp/Options.hpp>
#include <curlpp/Infos.hpp>
#include <curlpp/Exception.hpp>

#include <pugixml.hpp>
#include <pqxx/pqxx>

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
            string id, key, value, post_url = "";
            string date, relative_humidity, precipitation, road_surface_temperature, snowdepth = "0.0";
            string windspeed, winddirection, temperature, dew_point_temperature, visibility, version = "0.0";
            pugi::xml_document url_doc;
            map<string, string> readings_map;

            std::string username = argv[1];
            std::string password = argv[2];
            std::string credentials = username + ":" + password;

            curlpp::Cleanup cleaner;
            curlpp::Easy request;

            request.setOpt(new curlpp::options::Url(url));
            request.setOpt(new curlpp::options::UserPwd(credentials));

            ostringstream out;
            out << request;

//cout << out.str() << endl;

            pugi::xml_parse_result result = url_doc.load(out.str().c_str());

            if (result) {
                //cout << "XML-weather-data parsed without errors" << endl;
            } else {
                cerr << "XML-weather-data parsed with errors" << endl;
            }

            pugi::xml_node payloadPublication = url_doc.
                    child("d2LogicalModel").
                    child("payloadPublication");

            string child_name = "";
            for (pugi::xml_node siteMeasurement = payloadPublication.child("siteMeasurements"); siteMeasurement; siteMeasurement = siteMeasurement.next_sibling("siteMeasurements")) {
                id = siteMeasurement.child("measurementSiteReference").attribute("id").value();
                if (id == "123") {
                    readings_map["id"] = id;
                    //cout << siteMeasurement.child("measurementSiteReference").attribute("id").name() << ": " << id << endl;

                    key = siteMeasurement.child("measurementSiteReference").attribute("version").name();
                    value = siteMeasurement.child("measurementSiteReference").attribute("version").value();
                    //cout << key << ": " << value << endl;
                    readings_map[key] = value;

                    key = siteMeasurement.child("measurementTimeDefault").name();
                    value =siteMeasurement.child("measurementTimeDefault").child_value();
                    //cout << key << ": " << value << endl;
                    readings_map[key] = value;

                    for (pugi::xml_node measuredValue: siteMeasurement.children("measuredValue")) {
                        child_name = measuredValue.child("measuredValue").first_child().first_child().first_child().name();
                        // A level deeper
                        if (child_name == "roadSurfaceConditionMeasurementsExtension") {
                            key = measuredValue.child("measuredValue").first_child().first_child().first_child().first_child().first_child().name();
                            value = measuredValue.child("measuredValue").first_child().first_child().first_child().first_child().first_child().first_child().child_value();
                            ////cout << key << ": " << value << endl;
                            readings_map[key] = value;
                        } else {
                            key = measuredValue.child("measuredValue").first_child().first_child().first_child().name();
                            value = measuredValue.child("measuredValue").first_child().first_child().first_child().first_child().child_value();
                            //cout << key << ": " << value << endl;
                            readings_map[key] = value;
                        }
                    }
                }
            }

            for (auto reading : readings_map) {
//                cout << reading.first << ": " << reading.second << endl;
                if (reading.first == "id") { id = reading.second; }
                if (reading.first == "measurementTimeDefault") { date = reading.second; }
                if (reading.first == "relativeHumidity") { relative_humidity = reading.second; }
                if (reading.first == "precipitationIntensity") { precipitation = reading.second; }
                if (reading.first == "roadSurfaceTemperature") { road_surface_temperature = reading.second; }
                if (reading.first == "windSpeed") { windspeed = reading.second; }
                if (reading.first == "windDirectionBearing") { winddirection = reading.second; }
                if (reading.first == "airTemperature") { temperature = reading.second; }
                if (reading.first == "dewPointTemperature") { dew_point_temperature = reading.second; }
                if (reading.first == "minimumVisibilityDistance") { visibility = reading.second; }
                if (reading.first == "version") { version = reading.second; }
            }

            string sql = "insert into readings (_id, date, relative_humidity, precipitation, road_surface_temperature";
            sql += ", wind_speed, wind_direction, temperature, dew_point_temperature, visibility)";
            sql += " values (" + id + ", '" + date + "'";
            sql += ", " + relative_humidity + ", " + precipitation;
            sql += ", " + road_surface_temperature;
            sql += ", " + windspeed + ", " + winddirection;
            sql += ", " + temperature + ", " + dew_point_temperature;
            sql += ", " + visibility + ")";

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
