// Copyright Andra Serban
#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_
#include "Graph.h"
#include <utility>
#include <string>
#define NMAX 1000
struct driver{
    std::string name;
    int intersection_nr;
    std::string intersection_name;
    bool online;
    double rating;
    int nr_of_races;
    int distance;

    driver() {
        distance = 0;
        nr_of_races = 0;
        intersection_nr = -1;
        rating = 0;
    }
};

void remove_route(Graph<int> &map, int min_path[][NMAX], int start, int end) {
    if (map.isEdge(start, end)) {
        map.removeEdge(start, end);
        min_path[start][end] = 0;
    }
}

void add_route(Graph<int> &map, int min_path[][NMAX], int start, int end) {
    if (!map.isEdge(start, end)) {
        map.addEdge(start, end);
        min_path[start][end] = 1;
    }
}

void change_direction(Graph<int> &map, int min_path[][NMAX], int start,
    int end){
    if (map.isEdge(start, end) && !map.isEdge(end, start)) {
        map.removeEdge(start, end);
        min_path[start][end] = 0;
        map.addEdge(end, start);
        min_path[end][start] = 1;
        return;
    }
    if (map.isEdge(end, start) && !map.isEdge(start, end)) {
        map.removeEdge(end, start);
        min_path[end][start] = 0;
        map.addEdge(start, end);
        min_path[start][end] = 1;
        return;
    }
}

int find_index_for_driver(driver soferi[], std::string nume_sofer,
    int nr_of_drivers) {
    for (int i = 0 ; i < nr_of_drivers; ++i) {
        if (nume_sofer.compare(soferi[i].name) == 0) {
            return i;
        }
    }
    return -1;
}

// functie necesara la sortare dupa rating, distanta, combustibil, numar curse
template <class T>
bool sort_test(T a, T b, std::string c, std::string d) {
	return (a > b) || (a == b  && c.compare(d) > 0);
}

void calculte_min_path(int min_path[][NMAX], Graph<int> g, int  start,
    int end) {
	if (min_path[start][end] == 0)
		min_path[start][end] = g.minPath(start, end);
}

void show_info(driver sofer, std::ofstream& fout) {
    fout << sofer.name << ": " << sofer.intersection_name << " " <<
    std::fixed << std::setprecision(3) << sofer.rating << " " <<
    sofer.nr_of_races << " " << sofer.distance << " ";
    if (sofer.online == true) {
        fout << "online" << std::endl;
    } else {
        fout << "offline" << std::endl;
    }
}

void sort_by_fuel(std::pair<std::string, int> consumed_fuel[],
    int nr_intersections_to_go, std::ofstream& fout) {
    for (int i = 0; i < nr_intersections_to_go - 1; ++i) {
        for (int j = i; j < nr_intersections_to_go; ++j) {
            if (sort_test<int>(consumed_fuel[i].second, consumed_fuel[j].second,
                consumed_fuel[i].first, consumed_fuel[j].first)) {
                std::swap(consumed_fuel[i], consumed_fuel[j]);
            }
        }
    }
    for (int i = 0 ; i < nr_intersections_to_go; ++i) {
        fout << consumed_fuel[i].first << " ";
    }
}

void print_sorted_by_rating(driver soferi[], int nr_of_drivers,
	int nr_of_drivers_to_print, std::ofstream& fout) {
	if (nr_of_drivers_to_print > nr_of_drivers) {
        for (int i = 0; i < nr_of_drivers; ++i) {
        fout << soferi[i].name <<":";
        fout << std::fixed << std::setprecision(3) <<
        soferi[i].rating <<" ";
    	}
    } else {
        for (int i = 0; i < nr_of_drivers_to_print; ++i) {
            fout << soferi[i].name << ":";
            fout << std::fixed << std::setprecision(3) <<
            soferi[i].rating <<" ";
        }
    }
    fout << std::endl;
}

void sort_by_rating(int nr_of_drivers, driver help[],
	int nr_of_drivers_to_print,
	std::ofstream& fout) {
    driver soferi[NMAX];
    for (int i = 0 ; i < nr_of_drivers ; ++i) {
        soferi[i] = help[i];
    }
    for (int i = 0; i < nr_of_drivers - 1; ++i) {
        for (int j = i; j < nr_of_drivers; ++j) {
            if (sort_test<double>(soferi[j].rating, soferi[i].rating,
            	soferi[i].name, soferi[j].name)){
                std::swap(soferi[i], soferi[j]);
            }
        }
    }
    print_sorted_by_rating(soferi, nr_of_drivers, nr_of_drivers_to_print, fout);
}

void print_sort_by_dist(driver soferi[], int nr_of_drivers,
	int nr_of_drivers_to_print, std::ofstream& fout) {
	if (nr_of_drivers_to_print > nr_of_drivers) {
        for (int i = 0; i < nr_of_drivers; ++i) {
        fout << soferi[i].name << ":" << soferi[i].distance <<" ";
    	}
    } else {
        for (int i = 0; i < nr_of_drivers_to_print; ++i) {
            fout << soferi[i].name << ":" << soferi[i].distance <<" ";
        }
    }
    fout << std::endl;
}

void sort_by_dist(int nr_of_drivers, driver help[], int nr_of_drivers_to_print,
	std::ofstream& fout) {
    driver soferi[NMAX];
    for (int i = 0 ; i < nr_of_drivers ; ++i) {
        soferi[i] = help[i];
    }
    for (int i = 0; i < nr_of_drivers - 1; ++i) {
        for (int j = i; j < nr_of_drivers; ++j) {
            if (sort_test<int>(soferi[j].distance, soferi[i].distance,
            	soferi[i].name, soferi[j].name)) {
                std::swap(soferi[i], soferi[j]);
            }
        }
    }
    print_sort_by_dist(soferi, nr_of_drivers, nr_of_drivers_to_print, fout);
}

void print_sort_by_rides(driver soferi[], int nr_of_drivers,
	int nr_of_drivers_to_print, std::ofstream& fout) {
	if (nr_of_drivers_to_print > nr_of_drivers) {
        for (int i = 0; i < nr_of_drivers; ++i) {
        fout << soferi[i].name << ":" << soferi[i].nr_of_races << " ";
    	}
    } else {
        for (int i = 0; i < nr_of_drivers_to_print; ++i) {
            fout << soferi[i].name << ":" << soferi[i].nr_of_races << " ";
        }
    }
    fout << std::endl;
}

void sort_by_rides(int nr_of_drivers, driver help[], int nr_of_drivers_to_print,
	std::ofstream& fout) {
    driver soferi[NMAX];
    for (int i = 0 ; i < nr_of_drivers ; ++i) {
        soferi[i] = help[i];
    }
    for (int i = 0; i < nr_of_drivers - 1; ++i) {
        for (int j = i; j < nr_of_drivers; ++j) {
            if (sort_test<int>(soferi[j].nr_of_races, soferi[i].nr_of_races,
            	soferi[i].name, soferi[j].name)) {
                std::swap(soferi[i], soferi[j]);
            }
        }
    }
    print_sort_by_rides(soferi, nr_of_drivers, nr_of_drivers_to_print, fout);
}

void modify_info_ab_driver(int indice, int min_dist, driver soferi[], int end,
    std::string end_name, int start, int rating, int min_path[][NMAX],
    Graph<int> g, std::ofstream& fout) {
    if (indice != -1) {
        soferi[indice].intersection_nr = end;
        soferi[indice].intersection_name = end_name;
        soferi[indice].nr_of_races++;
        soferi[indice].rating = (soferi[indice].rating *
        (soferi[indice].nr_of_races - 1) + rating) /
        soferi[indice].nr_of_races;
        if (min_path[start][end] == 0) min_path[start][end] =
            g.minPath(start, end);
        soferi[indice].distance += min_dist + min_path[start][end];
    } else {
        fout << "Soferi indisponibili" << std::endl;
    }
}

void equality_case(int min_path[][NMAX], driver soferi[], int start,
    int& min_dist, driver& soferul, int& indice, int i) {
    if (min_path[soferi[i].intersection_nr][start] == min_dist) {
        if (soferi[i].rating > soferi[indice].rating) {
            min_dist =
            min_path[soferi[i].intersection_nr][start];
            soferul = soferi[i];
            indice = i;
        } else if (soferi[i].rating == soferi[indice].rating) {
            if (soferi[indice].name.compare(soferi[i].name)
            > 0){
                min_dist =
                min_path[soferi[i].intersection_nr][start];
                soferul = soferi[i];
                indice = i;
            }
        }
    }
}

void find_driver(int start, int nr_of_drivers,
    driver soferi[], Graph<int> g, int min_path[][NMAX], int& indice,
    int&min_dist) {
    driver soferul;
    soferul.name = "";
    for (int i = 0; i < nr_of_drivers; i++) {
        if (min_path[soferi[i].intersection_nr][start] == 0)
            min_path[soferi[i].intersection_nr][start] =
            g.minPath(soferi[i].intersection_nr, start);
        if (soferi[i].online == true &&
            min_path[soferi[i].intersection_nr][start] != -1) {
            if (min_dist == -1) {
                min_dist = min_path[soferi[i].intersection_nr][start];
                soferul = soferi[i];
                indice = i;
            } else if (min_path[soferi[i].intersection_nr][start] < min_dist) {
                min_dist = min_path[soferi[i].intersection_nr][start];
                soferul = soferi[i];
                indice = i;
            } else {
                equality_case(min_path, soferi, start, min_dist, soferul,
                    indice, i);
            }
        }
    }
}
#endif  // FUNCTIONS_H_
