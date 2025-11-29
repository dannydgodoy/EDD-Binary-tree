#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

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

class RoyalFamilyTree {
private:
	Person* root;

	bool insert(Person*& current, Person* newPerson) {
		if (current == nullptr) {
			current = newPerson;
			cout << "Inserted at root: " << newPerson->name << " " << newPerson->last_name << endl;
			return true;
		}

		if (current->id == newPerson->id_father) {
			if (current->left == nullptr) {
				current->left = newPerson;
				cout << "Inserted as left child of " << current->name << " " << current->last_name << ": " << newPerson->name << " " << newPerson->last_name << endl;
			} else {
				Person* child = current->left;
				while (child->right != nullptr) child = child->right;
				child->right = newPerson;
				cout << "Inserted as right child of " << current->name << " " << current->last_name << ": " << newPerson->name << " " << newPerson->last_name << endl;
			}
			return true;
		}

		bool inserted = false;
		if (current->left != nullptr) inserted = insert(current->left, newPerson);
		if (!inserted && current->right != nullptr) inserted = insert(current->right, newPerson);

		return inserted;
	}

	void deleteTree(Person* current) {
		if (!current) return;
		deleteTree(current->left);
		deleteTree(current->right);
		delete current;
	}

public:
	RoyalFamilyTree() : root(nullptr) {}

	~RoyalFamilyTree() {
		deleteTree(root);
	}

	void loadFromCSV(const string& filename) {
		ifstream file(filename);
		if (!file.is_open()) {
			string alt = string("bin/") + filename;
			file.open(alt);
			if (!file.is_open()) {
				cerr << "Error al abrir archivo: " << filename << " o " << alt << endl;
				return;
			}
		}

		string line;
		if (!getline(file, line)) return;

		int count = 0;
		while (getline(file, line)) {
			if (line.empty()) continue;
			stringstream ss(line);
			string token;

			int id = 0, age = 0, id_father = 0;
			char gender = 'U';
			bool is_dead = false, was_king = false, is_king = false;
			string name, last_name;

			if (!getline(ss, token, ',')) continue;
			id = stoi(token);
			getline(ss, name, ',');
			getline(ss, last_name, ',');
			if (getline(ss, token, ',')) if (!token.empty()) gender = token[0];
			if (getline(ss, token, ',')) age = stoi(token);
			if (getline(ss, token, ',')) id_father = stoi(token);
			if (getline(ss, token, ',')) is_dead = (stoi(token) != 0);
			if (getline(ss, token, ',')) was_king = (stoi(token) != 0);
			if (getline(ss, token, ',')) is_king = (stoi(token) != 0);

			Person* p = new Person(id, name, last_name, gender, age, id_father, is_dead, was_king, is_king);
			if (root == nullptr) {
				root = p;
			} else {
				bool ok = insert(root, p);
				if (!ok) {
					Person* it = root;
					while (it->right) it = it->right;
					it->right = p; 
				}
			}

			++count;
		}

		cout << "Cargados " << count << " miembros desde CSV." << endl;
		file.close();
	}

	void showLivingMembers() {
		cout << "Lista de familiares vivos:" << endl;
		showLivingMembers(root);
	}

	void showLivingMembers(Person* current) {
		if (current == nullptr) return;
		if (!current->is_dead) {
			cout << current->name << " " << current->last_name << " (ID: " << current->id << ")" << endl;
		}
		showLivingMembers(current->left);
		showLivingMembers(current->right);
	}

	void printAllMembers() {
		cout << "Lista de todos los miembros de la familia real:" << endl;
		printAllMembers(root);
	}

	void printAllMembers(Person* current) {
		if (current == nullptr) return;
		cout << "ID: " << current->id << ", Nombre: " << current->name << " " << current->last_name
			 << ", Género: " << current->gender << ", Edad: " << current->age
			 << ", ID Padre: " << current->id_father << ", Muerto: " << current->is_dead
			 << ", Fue Rey: " << current->was_king << ", Es Rey: " << current->is_king << endl;
		printAllMembers(current->left);
		printAllMembers(current->right);
	}
};



