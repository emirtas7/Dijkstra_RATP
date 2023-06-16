#include <iostream>
#include "My_station_parser.hpp"
//#include "Grade.hpp"

using namespace travel;
using namespace std;

int main() {

/*
  // Instanciation d'un nouvel objet de la classe My_station_parser qui vient d'être implémentée
  My_station_parser parser1;

  try {
    parser1.read_stations("data/stations.csv"); // lecture du fichier stations.csv
    parser1.read_connections("data/connections.csv"); // lecture du fichier connections.csv
  } catch (const exception& e) { // on attrape les exceptions levées dans l'implémentation de la fonction 'read_stations'
    cerr << "Error: " << e.what() << endl; // gestion d'erreur
    return 1;
  }
*/
//------------------------------- PARTIE 1 -----------------------------------------------------------------------------------------------------------------------------

  // Affichage des données 'stations' - Test de fonctionnement (OK)
  /*
  const auto& stations = parser1.get_stations_hashmap();
  for (const auto& station : stations) {
    cout << station.second << endl; // affichage direct grâce à la surcharge définie dans 'Generic_station_parser'
  }
  */

  // Question 4
  //evaluate_small.stations(parser1);   // Appel de la methode 'stations' de la classe Grade - Non fonctionnel


//------------------------------- PARTIE 2 -----------------------------------------------------------------------------------------------------------------------------

/*
  // Affichage des données 'connections' - Test de fonctionnement (OK)
  const auto& connections = parser1.get_connections_hashmap();
  for (const auto& debut : connections) {
      for (const auto& fin : debut.second) {
          cout << "From station : " << debut.first << " To station  : " << fin.first << "   -   with a period of " << fin.second << " seconds. " << endl;
      }
  }
*/

  // Question 7
  //evaluate_small.connections(parser1);   // Appel de la methode 'connections' de la classe Grade - Non fonctionnel


//------------------------------- PARTIE 3 -----------------------------------------------------------------------------------------------------------------------------
  /*
  try {
      My_station_parser parser;
      parser.read_stations("data/stations.csv");
      parser.read_connections("data/connections.csv");

      uint64_t start_station_id = 8;
      uint64_t end_station_id = 2;

      auto direct_travel = parser.compute_and_display_travel(start_station_id, end_station_id);

  } catch (const exception& e) {
      cerr << "Error : " << e.what() << "\n";
      return 1;
  }
  */

//------------------------------- PARTIE 3 - bonus -----------------------------------------------------------------------------------------------------------------------------
    // Remplacer par les noms des fichiers de données pour les stations et les connexions

My_station_parser parser;
string stations_filename = "data/s.csv";
string connections_filename = "data/c.csv";

try {
    parser.read_stations(stations_filename);
    parser.read_connections(connections_filename);

    string start_station_name = "Riquet";
    string end_station_name = "Porte de Clichy";

    cout << "\ncompute_and_display_travel :\n";
    auto direct_travel = parser.compute_and_display_travel(start_station_name, end_station_name);

} catch (const exception& e) {
    cerr << "Error : " << e.what() << endl;
    return 1;
}

    return 0;
}