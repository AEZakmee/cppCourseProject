#pragma once
#include <iostream>
#include <string>

class Dish {
public:
	enum Dishtype {
		Starter,
		MainCourse,
		Dessert
	};
private:
	unsigned int m_id;
	std::string m_dishname;
	int m_dishcode;
	int m_grams;
	float m_price;
public:
	Dish();
	Dish(int, std::string, int, int, float);
	Dish(const Dish&);
	~Dish();
	int GetId() const;
	void SetId(int id);
	std::string GetDishname() const;
	void SetDishname(std::string dishname);
	int GetDishcode() const;
	void SetDishcode(Dishtype dishcode);
	int GetGrams() const;
	void SetGrams(int grams);
	float GetPrice() const;
	void SetPrice(float price);
	void PrintDish() const;
	friend std::ostream& operator<<(std::ostream& stream_out, const Dish& usergroup);
	friend std::istream& operator>>(std::istream& stream_in, Dish& usergroup);
};
