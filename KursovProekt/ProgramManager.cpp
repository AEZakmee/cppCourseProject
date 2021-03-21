#include "ProgramManager.h"
#include "Utilities.h"

void ProgramManager::init() {
	load_from_file(groups, groups_file);
	load_from_file(dishes, dishes_file);
	print_menu();
	return;
}

template <class T>
void ProgramManager::load_from_file(std::vector<T>& vec, std::string file_name) {
	try {
		in_file.open(file_name, std::ios::in);
		if (!in_file) throw 1;
		// This code counts the lines, so the vector can alocate enough space
		std::ifstream inFile(file_name);
		int size = std::count(std::istreambuf_iterator<char>(inFile),
			std::istreambuf_iterator<char>(), '\n');
		vec.resize(size);
		// Memory is optimized by doing that
		for (int i = 0; i < size; i++) {
			in_file >> vec[i];
		}
	}
	catch (std::ifstream::failure e) {
		log("Problem occured while opening the file");
	}
	catch (int) {
		log("File couldn't open");
	} in_file.close();
}

template <class T>
void ProgramManager::save_to_file(std::vector<T>& vec, std::string file_name) {
	try {
		out_file.open(file_name, std::ios::out);
		if (!out_file) throw 1;
		if (out_file.is_open()) {
			for (T& item : vec) {
				out_file << item;
			}
		}
	}
	catch (std::ofstream::failure e) {
		log("Problem occured while opening the file");
	}
	catch (int) {
		log("File couldn't open");
	} out_file.close();
}

template <class T>
void ProgramManager::append_to_file(const T& item, std::string file_name) {
	try {
		out_file.open(file_name, std::ios::app);
		if (!out_file) throw 1;
		out_file << item;
	}
	catch (std::ofstream::failure e) {
		log("Problem occured while opening the file");
	}
	catch (int) {
		log("File couldn't open");
	} out_file.close();
}

template <class T>
void ProgramManager::print_items(const std::vector<T>& items) const {
	for (int i = 0; i < items.size(); i++) {
		std::cout << items[i];
	}
}

void ProgramManager::print_file(std::string file_name) {
	try {
		in_file.open(file_name, std::ios::in);
		if (!in_file) throw 1;
		std::string line;
		while (std::getline(in_file, line)) {
			// using printf() for consistency
			printf("%s\n", line.c_str());
		}
	}
	catch (std::ifstream::failure e) {
		log("Problem occured while opening the file");
	}
	catch (int) {
		log("File couldn't open");
	} in_file.close();
}

template <class T>
void ProgramManager::delete_item(std::vector<T>& vec, int id, std::string file_name) {
	vec.erase(vec.begin() + (id - 1));
	for (int i = id - 1; i < vec.size(); i++) {
		vec[i].SetId(vec[i].GetId() - 1);
	}
	save_to_file(vec, file_name);
}

template <typename T>
void ProgramManager::checkinput(T& data, T data_must_be_over, T data_must_be_under, bool silent) {
	if (std::cin.fail() || data <= data_must_be_over || data >= data_must_be_under) {
		std::cin.clear();
		std::cin.ignore(256, '\n');
		if (!silent) {
			std::cout << "Something went wrong, please try again..." << std::endl;
		}
		data = -1;
	}
}

void ProgramManager::proceed_order() {
	std::cout << "New order... Choose Starter, MainCourse and Dessert" << std::endl;
	std::map<int, int> pairs;
	std::string order_dishes[3];
	float total_price = 0;
	auto print_dishtype = [&](std::string type) // This function prints all dishes of given type
	{
		auto vector_searcher = [&](int type) { // Looping and printing the given type, also takes input
			pairs.clear();
			for (int i = 0, j = 1; i < dishes.size(); i++) {
				if (dishes[i].GetDishcode() == type) {
					std::cout << j << "\t" << dishes[i].GetDishname() << " "
						<< funcs::addSpaces(dishes[i].GetDishname().size())
						<< dishes[i].GetGrams() << "\t" << dishes[i].GetPrice() << "\n";
					pairs[j] = dishes[i].GetId();
					j++;
				}
			}
			std::cout << "Type any other character to skip!";
			std::cout << "\n" << "Please enter id of the element: ";
			int choice = 0;
			std::cin >> choice;
			checkinput(choice, 0, (int)dishes.size() + 1, true);
			if (choice != -1) {
				order_dishes[type] = dishes[pairs[choice] - 1].GetDishname();
				total_price += dishes[pairs[choice] - 1].GetPrice();
			}
			else {
				order_dishes[type] = "None";
			}
		};
		if (type == "starter") {
			vector_searcher(0);
			return true;
		}
		else if (type == "main") {
			vector_searcher(1);
			return true;
		}
		else if (type == "dessert") {
			vector_searcher(2);
			return true;
		}
		else {
			return false;
		}
	};
	while (!print_dishtype("starter"));
	while (!print_dishtype("main"));
	while (!print_dishtype("dessert"));
	std::cout << "Alright, from which groups is the client?" << std::endl;
	for (int i = 0; i < groups.size(); i++) {
		std::cout << groups[i];
	}
	int id = -1;
	std::cout << "Please choose id: ";
	while (id == -1) {
		std::cin >> id;
		checkinput(id, 0, (int)groups.size() + 1, false);
	}
	id--;
	std::cout << "You have chosen group: " << groups[id].GetGroupname() << std::endl;
	float new_price = total_price;
	if (groups[id].GetDisctype() == 1) {
		std::cout << "This group has " << groups[id].GetPercentage() << " percent discount" << std::endl;
		new_price = (total_price - total_price * groups[id].GetPercentage() / 100);
		std::cout << "Total price is " << total_price << ", discount is " << total_price - new_price
			<< ", price after discount is " << new_price << std::endl;
	}
	if (groups[id].GetDisctype() == 2) {
		std::cout << "This group has " << groups[id].GetPercentage() << " percent increase" << std::endl;
		new_price = (total_price * groups[id].GetPercentage() / 100 + total_price);
		std::cout << "Total price is " << total_price << ", increase is " << new_price - total_price
			<< ", price after increase is " << new_price << std::endl;
	}
	Order new_order(order_dishes[0], order_dishes[1], order_dishes[2], new_price);
	std::cout << "\nOrder successful, with total price of " << new_price << std::endl;
	append_to_file(new_order, orders_file);
}

void ProgramManager::print_menu() {
	std::cout << "------------Main Menu-------------\n"
		"1) Show all user groups			  \n"
		"2) Show all dishes					  \n"
		"3) Proceed an order				  \n"
		"4) Show previous orders			  \n"
		"5) Add new group					  \n"
		"6) Add new dish					  \n"
		"7) Edit/Delete group				  \n"
		"8) Edit/Delete dish				  \n"
		"9) Shutdown program				  \n"
		"Please type the number to proceed:" << std::endl;
	int ans = -1;
	while (ans == -1) {
		std::cin >> ans;
		checkinput(ans, 0, 10, false);
	}
	auto clear = [&](bool recall) // This function clears the terminal
	{
		std::cin.get();
		system("CLS");
		if (recall == 1) {
			print_menu();
		}

	};
	switch (ans) {
	case 1:
		clear(0);
		std::cout << "Id      Group name           type      percent" << std::endl;
		print_items(groups);
		clear(1);
	case 2:
		clear(0);
		std::cout << "Id      Dish name            type      grams    price" << std::endl;
		print_items(dishes);
		clear(1);
	case 3:
		clear(0);
		proceed_order();
		std::cin.get();
		clear(1);
	case 4:
		clear(0);
		print_file(orders_file);
		clear(1);
	case 5:
		clear(0);
		create_group();
		std::cin.get();
		clear(1);
	case 6:
		clear(0);
		create_dish();
		std::cin.get();
		clear(1);
	case 7:
		clear(0);
		edit_group();
		std::cin.get();
		clear(1);
	case 8:
		clear(0);
		edit_dish();
		std::cin.get();
		clear(1);
	case 9:
		std::cout << "Shuting down..." << std::endl;
		shutdown_program();
	}
}

void ProgramManager::shutdown_program() {
	groups.clear();
	dishes.clear();
	exit(1);
}

void ProgramManager::create_group() {
	int id = 0;
	if (groups.size() > 0) id = getGroups_lastID() + 1;
	else id = 1;
	std::string groupname(20, '\0');
	std::string answer;
	int discountcode = -1;
	float percentage = -1;
	std::cout << "Enter group name: (Maximum 20 characters)";
	std::cin >> groupname;
	while (discountcode == -1) {
		std::cout << "Enter discount type (NoDiscount/Discount/Increase): ";
		std::cin >> answer;
		if (answer == "NoDiscount") discountcode = UserGroup::Disctype::NoDiscount;
		else if (answer == "Discount") discountcode = UserGroup::Disctype::Discount;
		else if (answer == "Increase") discountcode = UserGroup::Disctype::Increase;
		else std::cout << "Something went wrong, please try again..." << std::endl;
	}
	if (discountcode != 0) {
		while (percentage == -1) {
			std::cout << "Enter percentage: ";
			std::cin >> percentage;
			checkinput(percentage, 0.0f, 100.0f, false);
		}
	}
	UserGroup group(id, groupname, discountcode, percentage);
	std::cout << "Group created -> ";
	group.PrintGroup();
	groups.push_back(group);
	append_to_file(group, groups_file);
	log("File updated");
}

void ProgramManager::create_dish() {
	int id = 0;
	if (dishes.size() > 0) id = getDishes_lastID() + 1;
	else id = 1;
	std::string dishname(20, '\0');;
	std::string answer;
	int dishcode = -1;
	int grams = -1;
	float price = -1;
	std::cout << "Enter dish name: ";
	std::cin >> dishname;
	while (dishcode == -1) {
		std::cout << "Enter dish type (Starter/MainCourse/Dessert): ";
		std::cin >> answer;
		if (answer == "Starter") dishcode = Dish::Dishtype::Starter;
		else if (answer == "MainCourse") dishcode = Dish::Dishtype::MainCourse;
		else if (answer == "Dessert") dishcode = Dish::Dishtype::Dessert;
		else std::cout << "Something went wrong, please try again..." << std::endl;
	}
	while (grams == -1) {
		std::cout << "Enter grams: ";
		std::cin >> grams;
		checkinput(grams, 1, INT_MAX, false);
	}
	while (price == -1) {
		std::cout << "Enter price: ";
		std::cin >> price;
		checkinput(price, 0.0f, 10000.0f, false);
	}
	Dish dish(id, dishname, dishcode, grams, price);
	std::cout << "Dish created -> ";
	dish.PrintDish();
	dishes.push_back(dish);
	append_to_file(dish, dishes_file);
	log("File updated");
}

void ProgramManager::edit_group() {
	std::cout << "Id" << std::endl;
	print_items(groups);
	int id = -1;
	while (id == -1) {
		std::cout << "Enter id of group to edit: ";
		std::cin >> id;
		checkinput(id, 0, getGroups_lastID()+1, false);
	}
	std::cout << "\nYou have chosen:\n" << groups[id - 1] << std::endl;
	std::cout << "What would you like to do? (Delete/Edit)\n";
	int ans = -1;
	while (ans == -1) {
		std::cout << "\nEnter 1) to Delete or 2) to Edit:";
		std::cin >> ans;
		checkinput(ans, 0, 3, false);
	}
	if (ans == 1) {
		delete_item(groups, id, groups_file);
	}
	else if (ans == 2) {
		std::cout << "\nWhat would you like to edit! Type:\n"
			"1) To edit name!\n"
			"2) To edit percentage!\n";
		int editnum = -1;
		while (editnum == -1) {
			std::cin >> editnum;
			checkinput(editnum, 0, 3, false);
		}
		if (editnum == 1) {
			std::cout << "\nEnter new name:";
			std::string name;
			std::cin >> name;
			groups[id - 1].SetGroupname(name);
			save_to_file(groups, groups_file);
		}
		else if (editnum == 2) {
			float perc = -1;
			while (perc == -1) {
				std::cout << "\nEnter new percentage: ";
				std::cin >> perc;
				checkinput(perc, 0.0f, 100.0f, false);
			}
			groups[id - 1].SetPercentage(perc);
			save_to_file(groups, groups_file);
		}
	}
	else {
		log("Something went wrong");
	}
}

void ProgramManager::edit_dish() {
	std::cout << "Id" << std::endl;
	print_items(dishes);
	int id = -1;
	while (id == -1) {
		std::cout << "Enter id of dish to edit: ";
		std::cin >> id;
		checkinput(id, 0, getDishes_lastID() + 1, false);
	}
	std::cout << "\nYou have chosen:\n" << dishes[id - 1] << std::endl;
	std::cout << "What would you like to do? (Delete/Edit)\n";
	int ans = -1;
	while (ans == -1) {
		std::cout << "\nEnter 1) to Delete or 2) to Edit:";
		std::cin >> ans;
		checkinput(ans, 0, 3, false);
	}
	if (ans == 1) {
		delete_item(dishes, id, dishes_file);
	}
	else if (ans == 2) {
		std::cout << "\nWhat would you like to edit! Type:\n"
			"1) To edit name!\n"
			"2) To edit price!\n";
		int editnum = -1;
		while (editnum == -1) {
			std::cin >> editnum;
			checkinput(editnum, 0, 3, false);
		}
		if (editnum == 1) {
			std::cout << "\nEnter new name:";
			std::string name;
			std::cin >> name;
			dishes[id - 1].SetDishname(name);
			save_to_file(dishes, dishes_file);
		}
		else if (editnum == 2) {
			float price = -1;
			while (price == -1) {
				std::cout << "\nEnter new price: ";
				std::cin >> price;
				checkinput(price, 0.0f, 10000.0f, false);
			}
			dishes[id - 1].SetPrice(price);
			save_to_file(dishes, dishes_file);
		}
	}
	else {
		log("Something went wrong");
	}
}

int ProgramManager::getGroups_lastID() {
	return groups[groups.size() - 1].GetId();
}

int ProgramManager::getDishes_lastID() {
	return dishes[dishes.size() - 1].GetId();
}


