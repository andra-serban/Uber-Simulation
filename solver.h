// Copyright Andra Serban

#ifndef SOLVER_H_
#define SOLVER_H_
#include <fstream>
#include <utility>
#include <string>
#include <vector>
#include "./Hashtable.h"
#include "./HashFunctions.h"
#include "./functions.h"
#include "./Graph.h"

class solver {
	Hashtable<std::string, int> intersections;
	Graph<int> map;
	std::string vec_intersectie[NMAX];
	int min_path[NMAX][NMAX] ={{0}};
	driver soferi[NMAX];
	int nr_of_drivers = 0;
	int nr_intersections, nr_streets;
	int nr_of_querrys;

 public:
	solver(): intersections(NMAX, &char_hash), map(NMAX, true) {}
	~solver(){}

	void task1_solver(std::ifstream& fin, std::ofstream& fout) {
		fin >> nr_intersections >> nr_streets;
		for (int i = 0; i < nr_intersections; i++) {
		    std::string intersacton_name;
		    fin >> intersacton_name;
		    intersections.put(intersacton_name, i);
		    vec_intersectie[i] = intersacton_name;
		}
		for (int i = 0; i < nr_streets; i++) {
		    std::string start, end;
		    fin >> start >> end;
		    map.addEdge(intersections.get(start), intersections.get(end));
		}
		fin >> nr_of_querrys;
		for (int i = 0; i < nr_of_querrys; i++) {
		    std::string start, end;
		    fin >> start >> end;
		    fout << map.bfs(intersections.get(start), intersections.get(end))
		    << std::endl;
		}
	}

	void task2_solver(std::ifstream& fin, std::ofstream& fout) {
		fin >> nr_of_querrys;
		for (int i = 0; i < nr_of_querrys; ++i) {
		    std::string start, end;
		    fin >> start >> end;
			fout<< map.minPath(intersections.get(start), intersections.get(end))
			<< std::endl;
		}
	}

	void task3_solver(std::ifstream& fin, std::ofstream& fout) {
	  	fin >> nr_of_querrys;
	  	for (int i = 0; i < nr_of_querrys; ++i) {
	        char querry;
	        int number;
	        fin >> querry;
	        std::string first_intersection, second_intersection;
	        fin >> first_intersection >> second_intersection >> number;
	        int start, end;
	        start = intersections.get(first_intersection);
	        end = intersections.get(second_intersection);
	        switch (querry) {
	            case('c'):
	                switch (number) {
	                    case(0):
	                        map.addEdge(start, end);
	                        min_path[start][end] = 1;
	                        break;
	                    case(1):
		                    remove_route(map, min_path, start , end);
		                    remove_route(map, min_path, end , start);
	                        break;
	                    case(2):
	                    	add_route(map, min_path, start, end);
	                    	add_route(map, min_path, end, start);
	                        break;
	                    case(3):
	                    	change_direction(map, min_path, start, end);
	                }
	                break;
	            case('q'):
	                switch (number) {
	                    case(0):
	                        if (map.minPath(start, end) != -1)
	                            fout << 'y' << std::endl;
	                        else
	                            fout << 'n' << std::endl;
	                        break;
	                    case(1):
	                        fout << map.minPath(start, end) << std::endl;
	                        break;
	                    case(2):
		                    int mid_intersection;
		                    std::string third_intersection;
		                    fin >> third_intersection;
	        				mid_intersection =
	        				intersections.get(third_intersection);
	                    	if (map.minPath(start, mid_intersection) != -1 &&
	                    		map.minPath(mid_intersection, end) != -1)
	                        fout << map.minPath(start, mid_intersection) +
	                    		map.minPath(mid_intersection, end) << std::endl;
	                    	else
	                    		fout << "-1" << std::endl;
	                        break;
	                }
	                break;
	        }
	  	}
	}

	void task4_solver(std::ifstream& fin, std::ofstream& fout) {
	    Hashtable<std::string, int> dictionar_soferi(191, &char_hash);
	    fin >> nr_of_querrys;
	    for (int i = 0 ; i < nr_of_querrys; i++) {
	        std::string querry;
	        fin >> querry;

	        if (querry.compare("d")== 0) {
	            driver new_driver;
	            std::string intersection;
	            fin >> new_driver.name >> intersection;
	            new_driver.online = true;
	            new_driver.intersection_name = intersection;
	            new_driver.intersection_nr = intersections.get(intersection);
	            if (!(dictionar_soferi.has_key(new_driver.name))) {
	                soferi[nr_of_drivers] = new_driver;
	                nr_of_drivers++;
	            } else {
	                for (int i = 0 ; i < nr_of_drivers; i++) {
	                    if (soferi[i].name.compare(new_driver.name) == 0) {
	                        soferi[i].online = true;
	                        soferi[i].intersection_nr =
	                        intersections.get(intersection);
	                        soferi[i].intersection_name = intersection;
	                        break;
	                    }
	                }
	            }
	            dictionar_soferi.put(new_driver.name,
	            intersections.get(intersection));
	        } else if (querry.compare("b")== 0) {
	            std::string nume_sofer;
	            fin >> nume_sofer;
	            for (int i = 0 ; i < nr_of_drivers; i++) {
	                if (nume_sofer.compare(soferi[i].name) == 0) {
	                    soferi[i].online = false;
	                    break;
	                }
	            }
	        } else if (querry.compare("r")== 0) {
	            std::string start, end;
	            double rating;
	            fin >> start >> end >> rating;
	            if (nr_of_drivers == 0) {
	                fout << "Soferi indisponibili" << std::endl;
	            } else {
	            	// calculez distanta de la start la end
	                if (min_path[intersections.get(start)]
	                	[intersections.get(end)] == 0) {
	                	min_path[intersections.get(start)]
	                [intersections.get(end)] =
	                map.minPath(intersections.get(start),
	                	intersections.get(end));
	            	}
	            	// daca nu exista drum intre start si end caut soferul care
	            	// se afla cel mai aproape
	                if (min_path[intersections.get(start)]
	                	[intersections.get(end)] == -1) {
	                    int ok = 0;
	                    int index_sofer = -1;
	                    int min_dist = -1;
	                    find_driver(intersections.get(start), nr_of_drivers,
	                    soferi, map, min_path, index_sofer, min_dist);
	                    if (index_sofer !=-1) {
	                    	// si caut o intersectie vecina cu destinatia
	                        std::vector<int> neigh =
	                        map.get_vecini(intersections.get(end));
	                        for (auto it = neigh.begin(); it != neigh.end();
	                        ++it) {
	                            calculte_min_path(min_path, map,
	                            intersections.get(start), *it);
	                            if (min_path[intersections.get(start)][*it]
	                            != -1) {
	                               	ok = 1;
	                               	modify_info_ab_driver(index_sofer, min_dist,
	                               	soferi, *it, vec_intersectie[*it],
	                               	intersections.get(start),
	                               	rating, min_path, map, fout);
	                               break;
	                            }
	                        }
	                        if (ok == 0) {
	                            fout << "Destinatie inaccesibila "<< std::endl;
	                        }
	                    } else {
	                        fout << "Soferi indisponibili" << std::endl;
	                    }
	                } else {
	                	// daca exista drum pana la destinatie ii modific
	                	// locatia soferului
	                	int index_sofer = -1;
	                    int min_dist = -1;
	                    find_driver(intersections.get(start), nr_of_drivers,
	                    soferi, map, min_path, index_sofer, min_dist);
	                    modify_info_ab_driver(index_sofer, min_dist, soferi,
	                    intersections.get(end), end, intersections.get(start),
	                    rating, min_path, map, fout);
	                }
	            }
	        } else if (querry.compare("top_rating")== 0) {
	            int nr_soferi;
	            fin >> nr_soferi;
	            sort_by_rating(nr_of_drivers, soferi, nr_soferi, fout);
	        } else if (querry.compare("top_dist")== 0) {
	            int nr_soferi;
	            fin >> nr_soferi;
	            sort_by_dist(nr_of_drivers, soferi, nr_soferi, fout);
	        } else if (querry.compare("top_rides")== 0) {
	            int nr_soferi;
	            fin >> nr_soferi;
	            sort_by_rides(nr_of_drivers, soferi, nr_soferi, fout);
	        } else if (querry.compare("info")== 0) {
	            std::string nume_sofer;
	            fin >> nume_sofer;
	             for (int i = 0 ; i < nr_of_drivers; i++) {
	                if (soferi[i].name.compare(nume_sofer) == 0){
	                    show_info(soferi[i], fout);
	                    break;
	                }
	            }
	        }
    }
}

	void task5_solver(std::ifstream& fin, std::ofstream& fout) {
		int fuel;
		std::string nume_sofer, intersection;
		fin >> fuel >> nume_sofer >> nr_of_querrys;
		int index_sofer = -1;
		// in acest vector am retinut intersectia si combustibilul consumat pana
		// la intersectie
		std::pair<std::string, int> consumed_fuel[NMAX];
        int nr_intersection_to_go = 0;
        index_sofer = find_index_for_driver(soferi, nume_sofer, nr_of_drivers);
		for (int i = 0; i < nr_of_querrys; ++i) {
			fin >> intersection;
			int j;
			for (j = 0 ; j < nr_intersection_to_go; ++j) {
				if (intersection.compare(consumed_fuel[j].first) == 0) break;
			}
			if (j == nr_intersection_to_go) {
				calculte_min_path(min_path, map, soferi[index_sofer].intersection_nr,
				intersections.get(intersection));
	       		if(fuel >= min_path[soferi[index_sofer].intersection_nr]
	       		[intersections.get(intersection)] &&
	       		min_path[soferi[index_sofer].intersection_nr]
	       		[intersections.get(intersection)] != -1) {
		       		consumed_fuel[nr_intersection_to_go].first = intersection;
		       		consumed_fuel[nr_intersection_to_go].second =
		       		min_path[soferi[index_sofer].intersection_nr]
		       		[intersections.get(intersection)];
		       		nr_intersection_to_go++;
	       		}
			}
		}
        sort_by_fuel(consumed_fuel, nr_intersection_to_go, fout);
	}
};
#endif  // SOLVER_H_
