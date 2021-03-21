#include "Dish.h"
#include "Utilities.h"

Dish::Dish() 
	: m_id(-1), m_dishname("Unknown"), m_dishcode(-1), m_grams(0), m_price(0.0f) {}
Dish::Dish(int id, std::string dishname, int dishcode, int grams, float price)
	: m_id(id), m_dishname(dishname), m_dishcode(dishcode), m_grams(grams), m_price(price) {}

Dish::Dish(const Dish& dish)
	: m_id(dish.m_id), m_dishname(dish.m_dishname), m_dishcode(dish.m_dishcode), m_grams(dish.m_grams), m_price(dish.m_price) {
	log("Dish coppied: " << this->m_dishname);
}

Dish::~Dish() { log("Dish destroyed: " << this->m_dishname); }

int Dish::GetId() const { return m_id; }
void Dish::SetId(int id) { m_id = id; }
std::string Dish::GetDishname() const { return m_dishname; }
void Dish::SetDishname(std::string dishname) { m_dishname = dishname; }
int Dish::GetDishcode() const { return m_dishcode; }
void Dish::SetDishcode(Dishtype dishcode) { m_dishcode = dishcode; }
int Dish::GetGrams() const { return m_grams; }
void Dish::SetGrams(int grams) { m_grams = grams; }
float Dish::GetPrice() const { return m_price; }
void Dish::SetPrice(float price) { m_price = price; }

void Dish::PrintDish() const {
	std::cout << "Dishname: " << this->GetDishname() << ", Dishcode: " << this->GetDishcode()
		<< ", grams: " << this->GetGrams() << ", price: " << this->GetPrice() << std::endl;
}

std::ostream& operator<<(std::ostream& stream_out, const Dish& dish)
{
	stream_out << dish.m_id << "\t" << dish.m_dishname << " "
		<< funcs::addSpaces(dish.m_dishname.size()) 
		<< dish.m_dishcode << "\t\t" << dish.m_grams << "\t" << dish.m_price << "\n";
	return stream_out;
}
std::istream& operator>>(std::istream& stream_in, Dish& dish)
{
	stream_in >> dish.m_id >> dish.m_dishname >> dish.m_dishcode >> dish.m_grams >> dish.m_price;
	return stream_in;
}