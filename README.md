# utvik-weather-data
Weather stats from vegvesen.no.

Statens Vegvesen in Norway collects weather information from locations in Norway,
currently approx. 400. The data is in XML-format, I use libcurl (curlpp wrapper)
to GET the data, parses and save to a postgresql-database. The weather information
is updated every ten minutes.
