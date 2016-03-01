/*
 * ParseXML.cpp
 *
 *  Created on: 18/02/2016
 *      Author: claus
 */

#include "ParseXML.hpp"

ParseXML::ParseXML(const std::string& s) : _id{"123"}, _xmldata{s}, _date{""},
                                           _relative_humidity{0.0}, _precipitation{0.0},
                                           _road_surface_temperature{0.0}, _snow_depth{0.0},
                                           _wind_speed{0.0}, _wind_direction{0}, _temperature{0.0},
                                           _dew_point_temperature{0.0}, _visibility{0}
{
    size_t begin_pos = _xmldata.find(begin_string);

    if (begin_pos == -1) {
        std::cerr << "Search string not found" << std::endl;
    } else {
        size_t end_pos = _xmldata.find(end_string, begin_pos);
        std::string xmldata_sub = _xmldata.substr(begin_pos, end_pos);

        // Date.
        size_t begin_date_pos = xmldata_sub.find(begin_date_string);
        size_t end_date_pos = xmldata_sub.find(end_date_string);
        if (begin_date_pos == -1 && end_date_pos == -1) {
            std::cout << "No date registered" << std::endl;
        } else {
            size_t begin = begin_date_pos + begin_date_string.size();
            size_t end = end_date_pos - begin;
            _date = xmldata_sub.substr(begin, end);
        }

        // Relative humidity.
        size_t begin_relative_humidity_pos = xmldata_sub.find(begin_relative_humidity_string);
        size_t end_relative_humidity_pos = xmldata_sub.find(end_relative_humidity_string);
        if (begin_relative_humidity_pos == -1 && end_relative_humidity_pos == -1) {
            std::cout << "No relative humidity registered" << std::endl;
        } else {
            size_t begin = begin_relative_humidity_pos + begin_relative_humidity_string.size();
            size_t end = end_relative_humidity_pos - begin;
            _relative_humidity = stod(xmldata_sub.substr(begin, end));
        }

        // Precipitation.
        size_t begin_precipitation_pos = xmldata_sub.find(begin_precipitation_string);
        size_t end_precipitation_pos = xmldata_sub.find(end_precipitation_string);
        if (begin_precipitation_pos == -1 && end_precipitation_pos == -1) {
            std::cout << "No precipitation registered" << std::endl;
        } else {
            size_t begin = begin_precipitation_pos + begin_precipitation_string.size();
            size_t end = end_precipitation_pos - begin;
            _precipitation = stod(xmldata_sub.substr(begin, end));
        }

        // Road surface temperature.
        size_t begin_road_surface_temperature_pos = xmldata_sub.find(begin_road_surface_temperature_string);
        size_t end_road_surface_temperature_pos = xmldata_sub.find(end_road_surface_temperature_string);
        if (begin_road_surface_temperature_pos == -1 && end_road_surface_temperature_pos == -1) {
            std::cout << "No road surface temperature registered" << std::endl;
        } else {
            size_t begin = begin_road_surface_temperature_pos + begin_road_surface_temperature_string.size();
            size_t end = end_road_surface_temperature_pos - begin;
            _road_surface_temperature = stod(xmldata_sub.substr(begin, end));
        }

        // Snow depth.
        size_t begin_snow_depth_pos = xmldata_sub.find(begin_snow_depth_string);
        size_t end_snow_depth_pos = xmldata_sub.find(end_snow_depth_string);
        if (begin_snow_depth_pos == -1 && end_snow_depth_pos == -1) {
            std::cout << "No snow depth registered" << std::endl;
        } else {
            size_t begin = begin_snow_depth_pos + begin_snow_depth_string.size();
            size_t end = end_snow_depth_pos - begin;
            _snow_depth = stod(xmldata_sub.substr(begin, end));
        }

        // Wind speed.
        size_t begin_windspeed_pos = xmldata_sub.find(begin_windspeed_string);
        size_t end_windspeed_pos = xmldata_sub.find(end_windspeed_string);
        if (begin_windspeed_pos == -1 && end_windspeed_pos == -1) {
            std::cout << "No windspeed registered" << std::endl;
        } else {
            size_t begin = begin_windspeed_pos + begin_windspeed_string.size();
            size_t end = end_windspeed_pos - begin;
            _wind_speed = stod(xmldata_sub.substr(begin, end));
        }

        // Wind direction.
        size_t begin_winddirection_pos = xmldata_sub.find(begin_winddirection_string);
        size_t end_winddirection_pos = xmldata_sub.find(end_winddirection_string);
        if (begin_winddirection_pos == -1 && end_winddirection_pos == -1) {
            std::cout << "No winddirection registered" << std::endl;
        } else {
            size_t begin = begin_winddirection_pos + begin_winddirection_string.size();
            size_t end = end_winddirection_pos - begin;
            _wind_direction = stoi(xmldata_sub.substr(begin, end));
        }

        // Temperature
        size_t begin_temperature_pos = xmldata_sub.find(begin_temperature_string);
        size_t end_temperature_pos = xmldata_sub.find(end_temperature_string);
        if (begin_temperature_pos == -1 && end_temperature_pos == -1) {
            std::cout << "No air temperature registered" << std::endl;
        } else {
            size_t begin = begin_temperature_pos + begin_temperature_string.size();
            size_t end = end_temperature_pos - begin;
            _temperature = stod(xmldata_sub.substr(begin, end));
        }

        // Dew point temperature
        size_t begin_dew_point_temperature_pos = xmldata_sub.find(begin_dew_point_temperature_string);
        size_t end_dew_point_temperature_pos = xmldata_sub.find(end_dew_point_temperature_string);
        if (begin_dew_point_temperature_pos == -1 && end_dew_point_temperature_pos == -1) {
            std::cout << "No dew point temperature registered" << std::endl;
        } else {
            size_t begin = begin_dew_point_temperature_pos + begin_dew_point_temperature_string.size();
            size_t end = end_dew_point_temperature_pos - begin;
            _dew_point_temperature = stod(xmldata_sub.substr(begin, end));
        }

        // Visibility
        size_t begin_visibility_pos = xmldata_sub.find(begin_visibility_string);
        size_t end_visibility_pos = xmldata_sub.find(end_visibility_string);
        if (begin_visibility_pos == -1 && end_visibility_pos == -1) {
            std::cout << "No visibility registered" << std::endl;
        } else {
            size_t begin = begin_visibility_pos + begin_visibility_string.size();
            size_t end = end_visibility_pos - begin;
            _visibility = stoi(xmldata_sub.substr(begin, end));
        }
    }
}

ParseXML::~ParseXML() {
}

const std::string ParseXML::id() {
    return _id;
}

const std::string ParseXML::date() {
    return _date;
}

const double ParseXML::relative_humidity() {
    return _relative_humidity;
}

const double ParseXML::precipitation() {
    return _precipitation;
}

const double ParseXML::road_surface_temperature() {
    return _road_surface_temperature;
}

const double ParseXML::road_surface_temperature_fahrenheit() {
    return _road_surface_temperature * 1.8 + 32.0;
}

const double ParseXML::snowdepth() {
    return _snow_depth;
}

const double ParseXML::windspeed() {
    return _wind_speed;
}

const double ParseXML::windspeedMPS() {
    return _wind_speed / 3.6;
}

const int ParseXML::winddirection() {
    return _wind_direction;
}

const double ParseXML::temperature() {
    return _temperature;
}

const double ParseXML::temperature_fahrenheit() {
    return _temperature * 1.8 + 32.0;
}

const double ParseXML::dew_point_temperature() {
    return _dew_point_temperature;
}

const double ParseXML::dew_point_temperature_fahrenheit() {
    return _dew_point_temperature * 1.8 + 32.0;
}

const int ParseXML::visibility() {
    return _visibility;
}
