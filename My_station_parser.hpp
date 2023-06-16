#pragma once

#ifndef MY_STATION_PARSER_HPP
#define MY_STATION_PARSER_HPP

#include "Generic_station_parser.hpp" // Partie 1
#include "Generic_connection_parser.hpp" // Partie 2
#include "Generic_mapper.hpp" // Partie 3


using namespace std;

namespace travel {

    class My_station_parser : public Generic_mapper {
    
    public:
      void read_stations(const string& _filename) override;
      void read_connections(const std::string& _filename) override;
      vector<pair<uint64_t,uint64_t>> compute_travel(uint64_t _start, uint64_t _end) override;
      vector<pair<uint64_t,uint64_t>> compute_and_display_travel(uint64_t _start, uint64_t _end) override;
      
      string normalize_station_name(const string& name);
      uint64_t find_station_id_by_name(const string& name);
      vector<pair<uint64_t, uint64_t>> compute_travel(const string& start_name, const string& end_name)override;
      vector<pair<uint64_t, uint64_t>> compute_and_display_travel(const string& start_name, const string& end_name)override;
    };
}

#endif