#include "Order.h"
#include "Utilities.h"

Order::Order() 
	: m_price(0.0f) {}
Order::Order(std::string starter, std::string main, std::string dessert, float price)
	: m_starter(starter), m_main(main), m_dessert(dessert), m_price(price) {}
Order::~Order() {log(" Usergroup destroyed: " << this);}

void Order::GetDishes(std::string& starter, std::string& main, std::string& dessert) const {
	starter = m_starter; main = m_main; dessert = m_dessert;
}
void Order::SetDishes(std::string starter, std::string main, std::string dessert) {
	m_starter = starter; m_main = main; m_dessert = dessert;
}
float Order::GetPrice() const { return m_price; }
void Order::SetPrice(float price) { m_price = price; }

std::ostream& operator<<(std::ostream& stream_out, const Order& order)
{
	stream_out << "Starter: " << order.m_starter << ",  MainCourse: " << order.m_main << ",  Dessert: " << order.m_dessert
		<< "    Total price: " << order.m_price << "\n";
	return stream_out;
}