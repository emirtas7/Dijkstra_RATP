#include "My_station_parser.hpp"
#include "Generic_connection_parser.hpp" // Partie 2
#include <fstream>
#include <sstream> 
#include <vector>
#include <stdexcept>
#include <unordered_map>
#include <set>


using namespace std;
using namespace travel;

//-------------------------- Partie 1 ----------------------------------------------------------------------

// Implementation de la fonction readstations
void My_station_parser::read_stations(const string& _filename) {
    ifstream file(_filename);
    if (!file.is_open()) {
        throw runtime_error("Error: Unable to open file " + _filename);
    }

    string line;
    getline(file, line); // saute la première ligne du fichier contenant les titres des colonnes
    while (getline(file, line)) {
        istringstream chaine(line);
        vector<string> contenu;
        string case_;
        while (getline(chaine, case_, ',')) {
            contenu.push_back(case_);
        }

        Station station;
        station.name = contenu[0];
        station.line_id = contenu[1];
        station.address = contenu[2];
        station.line_name = contenu[4];

        // verifie si la line_id contient bien que des chiffres
        bool is_valid = true;
        for (char c : station.line_id) {
            if (!isdigit(c)) {
                is_valid = false;
                break;
            }
        }
        if (!is_valid) {
            throw runtime_error("Error: Invalid line_id " + station.line_id);
        }

        uint64_t id = static_cast<uint64_t>(stoull(station.line_id));
        this->stations_hashmap[id] = station;
    }


    // verifie si on a bien lu le fichier
    if (file.bad()) {
        throw runtime_error("Error: Failed to read file " + _filename);
    }

    // fermeture du fichier
    file.close();

    //cout << "Le fichier 'stations' a bien été lu " << endl;
}

//-------------------------- Partie 2 ----------------------------------------------------------------------

// Implementation de la fonction readconnections
void My_station_parser::read_connections(const string& _filename) {
    ifstream file(_filename);
    if (!file.is_open()) {
        throw runtime_error("Error : Cannot open the file " + _filename);
    }

    string line;
    getline(file, line); // saute la première ligne du fichier contenant les titres des colonnes
    while (getline(file, line)) {
        istringstream chaine(line);
        vector<string> contenu;
        string case_;
        while (getline(chaine, case_, ',')) {
            contenu.push_back(case_);
        }

        uint64_t id1 = static_cast<uint64_t>(stoull(contenu[0]));
        uint64_t id2 = static_cast<uint64_t>(stoull(contenu[1]));
        uint64_t weight = static_cast<uint64_t>(stoull(contenu[2]));

        this->connections_hashmap[id1][id2] = weight;
    }

    // verifie si on a bien lu le fichier
    if (file.bad()) {
        throw runtime_error("Error: Failed to read file " + _filename);
    }

    // fermeture du fichier
    file.close();

    //cout << "Le fichier 'connections' a bien été lu " << endl;
}

//-------------------------- Partie 3 ----------------------------------------------------------------------

// Implementation de la fonction compute_travel 
vector<pair<uint64_t, uint64_t>> My_station_parser::compute_travel(uint64_t _start, uint64_t _end){
    const My_station_parser& connection_parser = *this;
    unordered_map<uint64_t, unordered_map<uint64_t, uint64_t>> connections = connection_parser.get_connections_hashmap();
    unordered_map<uint64_t, pair<uint64_t, uint64_t>> prix;

    // Initialisation des prix de tous les noeuds à l'infini sauf pour le noeud de départ qui sera initialisé à 0.
    for (auto& station : stations_hashmap) {
        prix[station.first] = make_pair(UINT64_MAX, 0);
    }

    // Initialisation de la distance du noeud de départ à 0
    prix[_start] = make_pair(0, 0);

    // On initialise chaque noeud comme étant des noeuds fermés 
    set<uint64_t> close_nodes;
    for (auto& station : stations_hashmap) {
        close_nodes.insert(station.first);
    }

    while (!close_nodes.empty()) { // Reviens à dire : tant que tous les nœuds n'ont pas été ouvert => fais !

        // On récupère le sommet avec la distance minimale dans la liste des noeuds non visités
        uint64_t current_node = *close_nodes.begin();
        uint64_t current_distance = prix[current_node].first;

        // Evaluation des couts de chaque noeud
        for (auto node : close_nodes) {
            if (prix[node].first < current_distance) {
                current_node = node;
                //cout << "current node = " << current_node << endl;
                current_distance = prix[node].first;
                //cout << "current distance = " << current_distance << endl;

            }
        }

        // Si le noeud de destination a été atteint, retourner le travel le plus court trouvé en suivant les prédecesseurs stockés dans le conteneur prix.
        if (current_node == _end) {
            vector<pair<uint64_t, uint64_t>> travel;
            uint64_t node = _end;
            while (node != _start) {
                travel.push_back(make_pair(node, prix[node].second));
                node = prix[node].second;
                //cout << "node = " << node << endl;
            }
            reverse(travel.begin(), travel.end());
            return travel;
        }

        // Pour chaque voisin du noeud actuel, mettre à jour sa distance en fonction de la distance du noeud actuel
        for (auto& neighbor : connections[current_node]) {
            uint64_t new_distance = prix[current_node].first + neighbor.second;
            //cout << "new_distance = " << new_distance << endl;

            // Si la distance mise à jour est plus petite que la distance actuelle stockée pour le voisin, mettre à jour la distance et le celui d'avant dans le conteneur prix.
            if (new_distance < prix[neighbor.first].first) {
                prix[neighbor.first] = make_pair(new_distance, current_node);
            }
        }

        // Retire le noeud actuel de la liste des noeuds non visités
        close_nodes.erase(current_node);
        //cout << "\n fin du traitement de COMPUTE TRAVEL \n" << endl;
    }

    // Si aucun travel n'a été trouvé, retourner un vecteur vide
    return vector<pair<uint64_t, uint64_t>>{};
}


// Implementation de la fonction --- compute_and_display_travel ---
vector<pair<uint64_t, uint64_t>> My_station_parser::compute_and_display_travel(uint64_t _start, uint64_t _end) {
    vector<pair<uint64_t, uint64_t>> travel = compute_travel(_start, _end);

    uint64_t total_time = 0;
    for (size_t i = 0; i < travel.size() ; i++) {
        uint64_t start_node = travel[i].second;
        uint64_t end_node = travel[i].first;

        // Calcul du temps total cumulé pour chaque connexion du trajet
        total_time += connections_hashmap[start_node][end_node];
    }

    // Affiche le temps total cumulé en minutes et en secondes
    uint64_t total_minutes = total_time / 60;
    uint64_t total_seconds = total_time % 60;

    if (!travel.empty()) {
        cout << "Shortest way between " << _start << " and " << _end << " :" << endl;
        for (const auto& step : travel) {
            cout << "From station : " << step.second << " to station : " << step.first << endl;
        }
        cout << endl;
        cout << "Total accumulated time : " << total_minutes << " minutes, " << total_seconds << " seconds" << endl;
    } else {
        cout << "No connection was found between the given stations. \n";
    }

    return travel;
}




//------------------------------- PARTIE 3 - bonus -----------------------------------------------------------------------------------------------------------------------------
// Implémentation de la fonction de normalisation des noms de stations
string My_station_parser::normalize_station_name(const string& name) {
    string normalized_name = name;
    transform(normalized_name.begin(), normalized_name.end(), normalized_name.begin(), ::tolower);
    return normalized_name;
}

// Implémentation de la fonction de recherche d'une station par nom
uint64_t My_station_parser::find_station_id_by_name(const string& name) {
    string normalized_name = normalize_station_name(name);
    for (auto& station : stations_hashmap) {
        if (normalize_station_name(station.second.name) == normalized_name) {
            return station.first;
        }
    }
    // Si la station n'est pas trouvée, retourner un identifiant invalide
    return UINT64_MAX;
}

// Surcharge de la fonction compute_travel avec les noms des stations
vector<pair<uint64_t, uint64_t>> My_station_parser::compute_travel(const string& start_name, const string& end_name) {
    uint64_t start_id = find_station_id_by_name(start_name);
    uint64_t end_id = find_station_id_by_name(end_name);

    if (start_id == UINT64_MAX || end_id == UINT64_MAX) {
        cerr << "One of the given station cannot be found." << endl;
        return {};
    }

    return compute_travel(start_id, end_id);
}

// Surcharge de la fonction compute_and_display_travel avec les noms des stations
vector<pair<uint64_t, uint64_t>> My_station_parser::compute_and_display_travel(const string& start_name, const string& end_name) {
    uint64_t start_id = find_station_id_by_name(start_name);
    uint64_t end_id = find_station_id_by_name(end_name);

    if (start_id == UINT64_MAX || end_id == UINT64_MAX) {
        cerr << "One of the given station cannot be found." << endl;
        return {};
    }

    vector<pair<uint64_t, uint64_t>> direct_travel = compute_travel(start_id, end_id);

    if (!direct_travel.empty()) {
        uint64_t total_time = 0;

        for (size_t i = 0; i < direct_travel.size(); i++) {
            uint64_t start_node = direct_travel[i].second;
            uint64_t end_node = direct_travel[i].first;

            total_time += connections_hashmap[start_node][end_node];

        }

        uint64_t total_minutes = total_time / 60;
        uint64_t total_seconds = total_time % 60;

        cout << "Direct path found : " << endl;
        cout << "Departure from station -> " << start_name << " (line " << get_stations_hashmap().at(direct_travel.front().second).address << ", Direction => " << get_stations_hashmap().at(direct_travel.front().second).line_name << ") \n" << endl;
        
        for (auto it = direct_travel.begin(); it != direct_travel.end(); it++) {
            const Station& from_station = get_stations_hashmap().at(it->second);
            const Station& to_station = get_stations_hashmap().at(it->first);

            if (it + 1 != direct_travel.end()) {
                if (from_station.address != to_station.address) {
                    cout << "Stopover at -> " << from_station.name << " | From line : "<< from_station.address << " to line : " << to_station.address  << endl;
                    cout << "Take line : " << to_station.address << ", Direction => " << to_station.line_name << ") \n" << endl;
                }
            } else {
                cout << "Destination reached >> " << end_name << " (line " << get_stations_hashmap().at(direct_travel.back().first).address << ")" << endl;
            }
        }
        cout << "Total accumulated time : " << total_minutes << " minutes, " << total_seconds << " seconds" << endl;


    } else {
        cout << "No direct path founded.\n";
    }

    return direct_travel;
}

