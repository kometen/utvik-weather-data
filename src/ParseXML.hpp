/*
 * ParseXML.hpp
 *
 *  Created on: 18/02/2016
 *      Author: claus
 */

#ifndef PARSEXML_HPP_
#define PARSEXML_HPP_

#include <iostream>
#include <string>

class ParseXML {
private:
    const std::string _id;              // Id of location.
    const std::string _xmldata;         // XML-data retrieved.
    std::string _date;                  // ISO-date. Is this program a plain string.
    double _relative_humidity;          // In percent.
    double _precipitation;              // In millimeters per hour (mm/h).
    double _road_surface_temperature;   // In celcius.
    double _snow_depth;                 // In meters.
    double _wind_speed;                 // In kilometers per hour (km/h).
    int _wind_direction;                // In degrees.
    double _temperature;                // Air temperature in celcius.
    double _dew_point_temperature;      // Dew point in celcius.
    int _visibility;                    // In meters.

    // Search for this location in the string.
    const std::string begin_string = "<siteMeasurements><measurementSiteReference targetClass=\"MeasurementSiteRecord\" id=\"" + _id + "\" version=\"18\"/>";
    const std::string end_string = "</siteMeasurements>";

    // Date and time for observation.
    const std::string begin_date_string = "<measurementTimeDefault>";
    const std::string end_date_string = "</measurementTimeDefault>";

    // Relative humidity in percent.
    const std::string begin_relative_humidity_string = "<relativeHumidity><percentage>";
    const std::string end_relative_humidity_string = "</percentage></relativeHumidity>";

    // Precipitation (usually rain) in mm per hour.
    const std::string begin_precipitation_string = "<precipitationIntensity><millimetresPerHourIntensity>";
    const std::string end_precipitation_string = "</millimetresPerHourIntensity></precipitationIntensity>";

    // Road surface temperature in celcius.
    const std::string begin_road_surface_temperature_string = "<roadSurfaceTemperature><temperature>";
    const std::string end_road_surface_temperature_string = "</temperature></roadSurfaceTemperature>";

    // Snow depth in meters.
    const std::string begin_snow_depth_string = "<depthOfSnow><floatingPointMetreDistance>";
    const std::string end_snow_depth_string = "</floatingPointMetreDistance></depthOfSnow>";

    // Wind speed.
    const std::string begin_windspeed_string = "<windSpeed><speed>";
    const std::string end_windspeed_string = "</speed></windSpeed>";

    // Wind direction.
    const std::string begin_winddirection_string = "<windDirectionBearing><directionBearing>";
    const std::string end_winddirection_string = "</directionBearing></windDirectionBearing>";

    // Temperature, celcius.
    const std::string begin_temperature_string = "<airTemperature><temperature>";
    const std::string end_temperature_string = "</temperature></airTemperature>";

    // Dew point temperature, celcius.
    const std::string begin_dew_point_temperature_string = "<dewPointTemperature><temperature>";
    const std::string end_dew_point_temperature_string = "</temperature></dewPointTemperature>";

    // Visibility, meters.
    const std::string begin_visibility_string = "<minimumVisibilityDistance><integerMetreDistance>";
    const std::string end_visibility_string = "</integerMetreDistance></minimumVisibilityDistance>";

public:
    ParseXML(const std::string&);
    virtual ~ParseXML();
    const std::string id();
    const std::string date();
    const double relative_humidity();
    const double precipitation();
    const double road_surface_temperature();
    const double road_surface_temperature_fahrenheit();
    const double snowdepth();
    const double windspeed();
    const double windspeedMPS();    // Meters Per Second
    const int winddirection();
    const double temperature();
    const double temperature_fahrenheit();
    const double dew_point_temperature();
    const double dew_point_temperature_fahrenheit();
    const int visibility();
};

#endif /* PARSEXML_HPP_ */
