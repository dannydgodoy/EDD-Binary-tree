#include <iostream>
#include <string>

using namespace std;

struct Person {
		int id;
		string name;
		string last_name;
		char gender;
		int age;
		int id_father;
		bool is_dead;
		bool was_king;
		bool is_king;
		Person* left;
		Person* right;

		Person(int _id,
					 const string& _name,
					 const string& _last_name,
					 char _gender,
					 int _age,
					 int _id_father,
					 bool _is_dead,
					 bool _was_king,
					 bool _is_king)
				: id(_id),
					name(_name),
					last_name(_last_name),
					gender(_gender),
					age(_age),
					id_father(_id_father),
					is_dead(_is_dead),
					was_king(_was_king),
					is_king(_is_king),
					left(nullptr),
					right(nullptr) {}
};


