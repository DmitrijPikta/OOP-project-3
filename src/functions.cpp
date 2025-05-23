#include "header.h"

double time_of_generating_file = 0;
double time_of_reading_file = 0;
double time_of_dividing = 0; // For best and worst
double time_of_sorting = 0;
double time_of_culculating = 0;
double time_of_writing_files = 0;

void Get_final_mark(vector<Stud> &grupe, bool for_average_homework_mark, bool for_both_homework_mark)
{
	//---------------------------------------------------------------------------
	auto start = std::chrono::high_resolution_clock::now(); // Time
	//---------------------------------------------------------------------------
	for (int i = 0; i < grupe.size(); i++)
	{
		if (for_average_homework_mark && for_both_homework_mark)
		{
			grupe[i].set_final_mark(0.6 * grupe[i].get_exam_mark() + 0.4 * grupe[i].Get_average_for_homework_mark());
			grupe[i].set_second_final_mark(0.6 * grupe[i].get_exam_mark() + 0.4 * grupe[i].Get_mediana_for_homework_mark());
		}
		else if (for_average_homework_mark)
		{
			grupe[i].set_final_mark(0.6 * grupe[i].get_exam_mark() + 0.4 * grupe[i].Get_average_for_homework_mark());
		}
		else
		{
			grupe[i].set_final_mark(0.6 * grupe[i].get_exam_mark() + 0.4 * grupe[i].Get_mediana_for_homework_mark());
		}
	}
	//-----------------------------------------------------------------
	auto end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> diff = end - start; // Time
	time_of_culculating += diff.count();
	//-----------------------------------------------------------------
}

double Stud::Get_average_for_homework_mark()
{
	int suma_of_marks = 0;
	int amount_of_marks = 0;
	for (int i = 0; i < Homework_marks_.size(); i++)
	{
		suma_of_marks += Homework_marks_[i];
		amount_of_marks++;
	}
	if (amount_of_marks == 0)
	{
		return 0;
	}
	return (double)suma_of_marks / amount_of_marks;
}

double Stud::Get_mediana_for_homework_mark()
{
	sort(Homework_marks_.begin(), Homework_marks_.end());

	int amount_of_marks = Homework_marks_.size();
	if (amount_of_marks == 0)
	{
		return 0;
	}
	else if (amount_of_marks % 2 == 0)
	{
		return double(Homework_marks_[(double)amount_of_marks / 2 - 0.5] + Homework_marks_[(double)amount_of_marks / 2 + 0.5]) / 2;
	}
	else
	{
		return Homework_marks_[amount_of_marks / 2];
	}
}

void Print_final_mark(vector<Stud> &grupe, bool for_average_homework_mark, bool for_both_homework_mark, bool print_results_in_terminal)
{
	//---------------------------------------------------------------------------
	auto start = std::chrono::high_resolution_clock::now(); // Time
	//---------------------------------------------------------------------------

	string path;
	if (!print_results_in_terminal)
	{
		string filename;
		if (grupe.back().get_final_mark() >= 5)
		{
			filename = "Best_grupe.txt";
		}
		else
		{
			filename = "Worst_grupe.txt";
		}
		path = GetDocumentsPath();
		path = path + "\\" + filename;
	}

	int size = Get_size_for_string_printing(grupe);
	int size_of_atribute_for_marks;
	if (for_both_homework_mark)
	{
		size_of_atribute_for_marks = 18 + 16;
	}
	else
	{
		size_of_atribute_for_marks = 18;
	}

	if (print_results_in_terminal)
	{
		cout << left << setw(size) << "Pavarde" << setw(size) << "Vardas" << "Galutinis ";
		if (for_both_homework_mark)
		{
			cout << "(vid.)" << " " << "Galutinis (med.)" << endl;
		}
		else if (for_average_homework_mark)
		{
			cout << "(vid.)" << endl;
		}
		else
		{
			cout << "(med.)" << endl;
		}
		cout << string(size + size + size_of_atribute_for_marks, '-') << endl;
	}
	else
	{
		std::ofstream fr(path);
		fr << left << setw(size) << "Pavarde" << setw(size) << "Vardas" << "Galutinis ";
		if (for_both_homework_mark)
		{
			fr << "(vid.)" << " " << "Galutinis (med.)" << endl;
		}
		else if (for_average_homework_mark)
		{
			fr << "(vid.)" << endl;
		}
		else
		{
			fr << "(med.)" << endl;
		}
		fr << string(size + size + size_of_atribute_for_marks, '-') << endl;
		fr.close();
	}

	if (print_results_in_terminal)
	{
		for (int i = 0; i < grupe.size(); i++)
		{
			cout << grupe.at(i);
		}
	}
	else
	{
		std::ofstream fr(path, std::ios::app);
		for (int i = 0; i < grupe.size(); i++)
		{
			fr << grupe.at(i);
		}
		fr.close();
	}
	//-----------------------------------------------------------------
	auto end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> diff = end - start; // Time
	time_of_writing_files += diff.count();
	//-----------------------------------------------------------------
}

int Get_size_for_string_printing(vector<Stud> &grupe)
{
	int max_length_of_string = 0;
	for (int i = 0; i < grupe.size(); i++)
	{
		if (grupe[i].get_name().length() > max_length_of_string || grupe[i].get_last_name().length() > max_length_of_string)
		{
			if (grupe[i].get_name().length() > grupe[i].get_last_name().length())
			{
				max_length_of_string = grupe[i].get_name().length();
			}
			else
			{
				max_length_of_string = grupe[i].get_last_name().length();
			}
		}
	}

	if (max_length_of_string < 11)
	{
		return 12;
	}
	else
	{
		return max_length_of_string + 2;
	}
}

void Stud::generate_marks()
{
	std::random_device rd;							   // Create a random device and seed the generator
	std::mt19937 gen(rd());							   // Mersenne Twister engine
	std::uniform_int_distribution<int> distrib(1, 10); // Define range 1 to 10
	for (int i = 0; i < distrib(gen); i++)
	{
		Homework_marks_.push_back(distrib(gen));
	}
	exam_mark_ = distrib(gen);
}

void generate_marks(vector<int> &Marks, int number_of_marks)
{
	std::random_device rd;							   // Create a random device and seed the generator
	std::mt19937 gen(rd());							   // Mersenne Twister engine
	std::uniform_int_distribution<int> distrib(1, 10); // Define range 1 to 10
	for (int i = 0; i < number_of_marks; i++)
	{
		Marks.push_back(distrib(gen));
	}
}

void Stud::generate_name()
{
	vector<string> Names = {
		"Alice", "Bob", "Charlie", "David", "Emma",
		"Frank", "Grace", "Henry", "Ivy", "Jack",
		"Karen", "Liam", "Mia", "Noah", "Olivia",
		"Paul", "Quinn", "Rachel", "Sam", "Tina"};
	vector<string> Second_names = {
		"Smith", "Johnson", "Williams", "Brown", "Jones",
		"Miller", "Davis", "Garcia", "Rodriguez", "Martinez",
		"Hernandez", "Lopez", "Gonzalez", "Wilson", "Anderson",
		"Thomas", "Taylor", "Moore", "Jackson", "Martin"};

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> distrib(0, 19);

	name_ = Names[distrib(gen)];
	last_name_ = Second_names[distrib(gen)];
}

void Sort_students(vector<Stud> &grupe, string parametr)
{
	//---------------------------------------------------------------------------
	auto start = std::chrono::high_resolution_clock::now(); // Time
	//---------------------------------------------------------------------------
	if (parametr == "final_mark")
	{
		sort(grupe.begin(), grupe.end(), [](const Stud &a, const Stud &b)
			 { return a.get_final_mark() > b.get_final_mark(); });
	}
	else if (parametr == "second_final_mark")
	{
		sort(grupe.begin(), grupe.end(), [](const Stud &a, const Stud &b)
			 { return a.get_second_final_mark() > b.get_second_final_mark(); });
	}
	else if (parametr == "name")
	{
		sort(grupe.begin(), grupe.end(), [](const Stud &a, const Stud &b)
			 { return a.get_name() < b.get_name(); });
	}
	else if (parametr == "second_name")
	{
		sort(grupe.begin(), grupe.end(), [](const Stud &a, const Stud &b)
			 { return a.get_last_name() < b.get_last_name(); });
	}
	//-----------------------------------------------------------------
	auto end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> diff = end - start; // Time
	time_of_sorting += diff.count();
	//-----------------------------------------------------------------
}

string GetDocumentsPath()
{
	char path[MAX_PATH];
	// CSIDL_PERSONAL is the "Documents" folder
	if (SUCCEEDED(SHGetFolderPathA(NULL, CSIDL_PERSONAL, NULL, 0, path)))
	{
		return string(path);
	}
	else
	{
		return "";
	}
}

bool Generate_file_with_students(int number_of_students, int number_of_marks, string filename)
{
	string path = GetDocumentsPath();
	path = path + "\\" + filename;
	std::ifstream fd(path);
	if (fd)
	{
		fd.close();
		cout << "Change file name, where is file with this name" << endl;
		return false;
	}
	fd.close();

	if (filename.length() < 4 || filename.substr(filename.size() - 4) != ".txt")
	{
		cout << "Change file name, file can not have this name. Good name example: 'example.txt'" << endl;
		return false;
	}
	//---------------------------------------------------------------------------
	auto start = std::chrono::high_resolution_clock::now(); // Time
	//---------------------------------------------------------------------------
	std::ofstream fr(path);

	fr << left << setw(20) << "Vardas" << setw(20) << "Pavarde";
	for (int i = 0; i < number_of_marks; i++)
	{
		fr << "ND" << left << setw(8) << i + 1;
	}
	fr << "Egz." << endl;

	vector<int> Marks;
	for (int i = 0; i < number_of_students; i++)
	{
		fr << "Vardas" << left << setw(14) << i + 1 << "Pavarde" << setw(13) << left << i + 1;
		generate_marks(Marks, number_of_marks + 1);
		for (int j = 0; j < number_of_marks; j++)
		{
			fr << left << setw(10) << Marks[j];
		}
		fr << Marks[number_of_marks] << endl;
		Marks.clear();
	}

	fr.close();
	//-----------------------------------------------------------------
	auto end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> diff = end - start; // Time
	time_of_generating_file += diff.count();
	//-----------------------------------------------------------------
	return true;
}

void Divide_for_two_grupse(vector<Stud> &grupe, vector<Stud> &best_grupe, vector<Stud> &worst_grupe)
{
	//---------------------------------------------------------------------------
	auto start = std::chrono::high_resolution_clock::now(); // Time
	//---------------------------------------------------------------------------
	best_grupe.reserve(grupe.size() * 0.7);
	worst_grupe.reserve(grupe.size() * 0.7);
	for (int i = 0; i < grupe.size(); i++)
	{
		if (grupe.at(i).get_final_mark() >= 5)
		{
			best_grupe.push_back(grupe.at(i));
		}
		else
		{
			worst_grupe.push_back(grupe.at(i));
		}
	}
	best_grupe.shrink_to_fit();
	worst_grupe.shrink_to_fit();
	grupe.clear();
	vector<Stud>().swap(grupe);
	//-----------------------------------------------------------------
	auto end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> diff = end - start; // Time
	time_of_dividing += diff.count();
	//-----------------------------------------------------------------
}

void Divide_for_two_grupse(vector<Stud> &grupe, vector<Stud> &worst_grupe)
{
	//---------------------------------------------------------------------------
	auto start = std::chrono::high_resolution_clock::now(); // Time
	//---------------------------------------------------------------------------
	worst_grupe.reserve(grupe.size() * 0.7);

	Sort_students(grupe, "final_mark");
	while (grupe.back().get_final_mark() < 5)
	{
		worst_grupe.push_back(grupe.back());
		grupe.pop_back();
	}

	grupe.shrink_to_fit();
	worst_grupe.shrink_to_fit();
	//-----------------------------------------------------------------
	auto end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> diff = end - start; // Time
	time_of_dividing += diff.count();
	//-----------------------------------------------------------------
}

void Divide_for_two_grupse_v3(vector<Stud> &grupe, vector<Stud> &best_grupe, vector<Stud> &worst_grupe)
{
	//---------------------------------------------------------------------------
	auto start = std::chrono::high_resolution_clock::now(); // Time
	//---------------------------------------------------------------------------
	best_grupe.resize(grupe.size());
	worst_grupe.resize(grupe.size());

	auto new_end = std::copy_if(grupe.begin(), grupe.end(), best_grupe.begin(), [](const Stud s)
								{ return s.get_final_mark() >= 5; });

	best_grupe.resize(std::distance(best_grupe.begin(), new_end));

	new_end = std::copy_if(grupe.begin(), grupe.end(), worst_grupe.begin(), [](const Stud s)
						   { return s.get_final_mark() < 5; });

	worst_grupe.resize(std::distance(worst_grupe.begin(), new_end));

	grupe.clear();
	vector<Stud>().swap(grupe);
	//-----------------------------------------------------------------
	auto end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> diff = end - start; // Time
	time_of_dividing += diff.count();
	//-----------------------------------------------------------------
}

void Enter_students_using_txt_file_bufer_P(vector<Stud> &grupe)
{
	string file_name;
	int mark;

	string element;
	bool last_homework_mark = false;
	int number_of_homework_marks = -1;

	while (true)
	{
		cout << "Please enter file name" << endl;
		cin >> file_name;
		string path = GetDocumentsPath();
		path = path + "\\" + file_name;
		std::ifstream fd(path);

		try
		{
			if (!fd)
			{
				throw std::runtime_error("");
			}
			//---------------------------------------------------------------------------
			auto start = std::chrono::high_resolution_clock::now(); // Time
			//---------------------------------------------------------------------------
			std::stringstream my_buffer;
			my_buffer << fd.rdbuf();
			fd.close();
			cout << "Nuskaityta i buferi" << endl;

			my_buffer >> element >> element;
			while (!last_homework_mark)
			{
				number_of_homework_marks++;
				my_buffer >> element;
				if (element == "Egz.")
				{
					last_homework_mark = true;
				}
			}

			string line;
			getline(my_buffer, line);
			while (getline(my_buffer, line))
			{
				std::stringstream ss(line);
				Stud student(ss, number_of_homework_marks);
				grupe.push_back(student);
			}

			grupe.shrink_to_fit();

			//-----------------------------------------------------------------
			auto end = std::chrono::high_resolution_clock::now();
			std::chrono::duration<double> diff = end - start; // Time
			time_of_reading_file += diff.count();
			//-----------------------------------------------------------------
		}
		catch (exception)
		{
			cout << "unable to open file" << endl;
			continue;
		}
		break;
	}
}

Stud::Stud(std::stringstream &is, int number_of_homework_marks)
{
	int mark;
	is >> name_ >> last_name_;
	for (int i = 0; i < number_of_homework_marks; i++)
	{
		is >> mark;
		set_homework_marks(mark);
	}
	is >> mark;
	set_exam_mark(mark);
}

Stud::~Stud()
{
	name_ = "";
	last_name_ = "";
	exam_mark_ = 0;
	final_mark_ = 0;
	second_final_mark_ = 0;
	Homework_marks_.clear();
}

Stud &Stud::operator=(const Stud &other)
{
	if (this != &other)
	{
		name_ = other.name_;
		last_name_ = other.last_name_;
		Homework_marks_ = other.Homework_marks_;
		exam_mark_ = other.exam_mark_;
		final_mark_ = other.final_mark_;
		second_final_mark_ = other.second_final_mark_;
	}
	return *this;
}

Stud &Stud::operator=(Stud &&other) noexcept
{
	if (&other != this)
	{
		name_ = move(other.name_);
		last_name_ = move(other.last_name_);
		Homework_marks_ = move(other.Homework_marks_);
		exam_mark_ = other.exam_mark_;
		final_mark_ = other.final_mark_;
		second_final_mark_ = other.second_final_mark_;
		other.exam_mark_ = 0;
		other.final_mark_ = 0;
		other.second_final_mark_ = 0;
	}
	return *this;
}

std::ostream &operator<<(std::ostream &out, const Stud &student)
{
	if (student.second_final_mark_ == -1)
	{
		out << left << setw(15) << student.last_name_ << setw(15) << student.name_ << fixed << setprecision(2) << student.final_mark_ << endl;
	}
	else
	{
		out << left << setw(15) << student.last_name_ << setw(15) << student.name_ << fixed << setprecision(2) << setw(17) << student.final_mark_ << student.second_final_mark_ << endl;
	}
	return out;
}

std::istream &operator>>(std::istream &in, Stud &student)
{
	cout << "Please enter name" << endl;
	in >> student.name_;
	cout << "Please enter last name" << endl;
	in >> student.last_name_;
	cout << "Please input student's one homework mark, when to save it, press enter. To finish entering marks enter double slash '//'" << endl;
	string entered_mark;
	in >> entered_mark;
	while (entered_mark != "//")
	{
		try
		{
			int checked_mark = stoi(entered_mark);
			if (checked_mark < 0 || checked_mark > 10)
			{
				cout << "Entered simbol can not be a mark" << endl;
				in >> entered_mark;
				continue;
			}
			student.set_homework_marks(checked_mark);
		}
		catch (exception)
		{
			cout << "Entered simbol can not be a mark" << endl;
		}
		in >> entered_mark;
	}

	cout << "Please input student's exam mark" << endl;
	in >> entered_mark;
	bool exam_mark_have_saved = false;
	while (!exam_mark_have_saved)
	{
		try
		{
			int checked_mark = stoi(entered_mark);
			if (checked_mark < 0 || checked_mark > 10)
			{
				cout << "Entered simbol can not be a mark" << endl;
				in >> entered_mark;
				continue;
			}
			student.set_exam_mark(checked_mark);
			exam_mark_have_saved = true;
		}
		catch (exception)
		{
			cout << "Entered simbol can not be a mark" << endl;
			in >> entered_mark;
		}
	}

	return in;
}