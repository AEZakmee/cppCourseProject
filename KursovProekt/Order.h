#pragma once
#include <iostream>
#include <string>
#include <vector>

class Order
{
private:
	std::string m_starter;
	std::string m_main;
	std::string m_dessert;
	float m_price;
public:
	Order();
	Order(std::string starter, std::string main, std::string dessert, float price);
	~Order();
	void GetDishes(std::string& starter, std::string& main, std::string& dessert) const;
	void SetDishes(std::string starter, std::string main, std::string dessert);
	float GetPrice() const;
	void SetPrice(float price);
	friend std::ostream& operator<<(std::ostream& stream_out, const Order& order);
};

