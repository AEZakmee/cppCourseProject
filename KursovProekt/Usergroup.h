#pragma once
#include <iostream>
#include <string>

class UserGroup {
public:
	enum Disctype {
		NoDiscount = 0,
		Discount, 
		Increase
	};
private:
	unsigned int m_id;
	std::string m_groupname;
	int m_discountcode;
	float m_percentage;
public:
	UserGroup();
	UserGroup(int, std::string);
	UserGroup(int, std::string, float);
	UserGroup(int, std::string, int, float);
	UserGroup(const UserGroup&);
	~UserGroup();
	int GetId() const;
	void SetId(int id);
	std::string GetGroupname() const;
	void SetGroupname(std::string groupname);
	int GetDisctype() const;
	void SetDisctype(Disctype discountcode);
	float GetPercentage() const;
	void SetPercentage(float percentage);
	void PrintGroup() const;
	friend std::ostream& operator<<(std::ostream& stream_out, const UserGroup& usergroup);
	friend std::istream& operator>>(std::istream& stream_in, UserGroup& usergroup);
private:
	std::string GetDisctypeprint() const;
};