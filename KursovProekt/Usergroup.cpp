#include "Usergroup.h"
#include "Utilities.h"


UserGroup::UserGroup() 
	: m_id(-1), m_groupname("Unknown"), m_discountcode(NoDiscount), m_percentage(0.0f) {}
UserGroup::UserGroup(int id, std::string groupname) 
	: m_id(id), m_groupname(groupname), m_discountcode(NoDiscount), m_percentage(0.0f) {}
UserGroup::UserGroup(int id, std::string groupname, float percentage)
	: m_id(id), m_groupname(groupname), m_discountcode(Discount), m_percentage(percentage) {}
UserGroup::UserGroup(int id, std::string groupname, int discountcode, float percentage)
	: m_id(id), m_groupname(groupname), m_discountcode(discountcode), m_percentage(percentage) {}

UserGroup::UserGroup(const UserGroup& usergroup)
	: m_id(usergroup.m_id), m_groupname(usergroup.m_groupname), m_discountcode(usergroup.m_discountcode), m_percentage(usergroup.m_percentage){
	log("Usergroup coppied: " << this->m_groupname);
}

UserGroup::~UserGroup() { log("Usergroup destroyed: " << this->m_groupname); }

int UserGroup::GetId() const { return m_id; }
void UserGroup::SetId(int id) { m_id = id; }
std::string UserGroup::GetGroupname() const { return m_groupname; }
void UserGroup::SetGroupname(std::string groupname) { m_groupname = groupname; }
int UserGroup::GetDisctype() const { return m_discountcode; }
void UserGroup::SetDisctype(Disctype discountcode) { m_discountcode = discountcode; }
float UserGroup::GetPercentage() const { return m_percentage; }
void UserGroup::SetPercentage(float percentage) { m_percentage = percentage; }

void UserGroup::PrintGroup() const {
	if (this->m_discountcode == 0) {
		std::cout << "GroupName: " << this->GetGroupname() << "\n"
		<< this->GetDisctypeprint() << std::endl;
	} else {
		std::cout << "GroupName: " << this->GetGroupname() << "\n"
		<< this->GetDisctypeprint() << this->GetPercentage() << " percent." << std::endl;
	}
}

std::string UserGroup::GetDisctypeprint() const {
	switch (m_discountcode) {
	case 0: return "has no discount.";
	case 1: return "has total discount of ";
	case 2: return "has total increase of ";
	default: return "None";
	}
}

std::ostream& operator<<(std::ostream& stream_out, const UserGroup& usergroup)
{
	stream_out << usergroup.m_id << "\t" << usergroup.m_groupname << " " 
		<< funcs::addSpaces(usergroup.m_groupname.size())
		<< usergroup.m_discountcode << "\t\t" << usergroup.m_percentage << "\n";
	return stream_out;
}
std::istream& operator>>(std::istream& stream_in, UserGroup& usergroup)
{
	stream_in >> usergroup.m_id >> usergroup.m_groupname >> usergroup.m_discountcode >> usergroup.m_percentage;
	return stream_in;
}