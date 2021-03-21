#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "Usergroup.h"
#include "Dish.h"
#include "Order.h"
#include <map>

class ProgramManager {
private:
	const std::string dishes_file = "Dishes.txt";
	const std::string groups_file = "Groups.txt";
	const std::string orders_file = "Orders.txt";
	std::vector<UserGroup> groups;
	std::vector<Dish> dishes;
	std::ofstream out_file;
	std::ifstream in_file;
public:
	void init();
private:
	template <class T>
	void load_from_file(std::vector<T>& vec, std::string file_name);
	template <class T>
	void save_to_file(std::vector<T>& vec, std::string file_name);
	template <class T>
	void append_to_file(const T& item, std::string file_name);
	template <class T>
	void print_items(const std::vector<T>& items)  const;
	void print_file(std::string file_name);
	template <class T>
	void delete_item(std::vector<T>& vec, int id, std::string file_name);
	template <typename T>
	void checkinput(T& data, T data_must_be_over, T data_must_be_under, bool silent);
	void proceed_order();
	void print_menu();
	void shutdown_program();
	void create_group();
	void create_dish();
	void edit_group();
	void edit_dish();
	int getGroups_lastID();
	int getDishes_lastID();
};