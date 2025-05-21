#pragma once

#include <iostream>
#include <iomanip>
#include <string>
// #include <vector>
#include <random>
#include <fstream>
#include <sstream>
#include <chrono>
#include <algorithm>
#include "Vector.h"
#define vector Vector

using std::cin;
using std::cout;
using std::endl;
using std::exception;
using std::fixed;
using std::left;
using std::move;
using std::setprecision;
using std::setw;
using std::sort;
using std::string;
// using std::vector;

class Person
{
protected:
	string name_;
	string last_name_;

public:
	Person() {};
	Person(string name, string last_name) : name_(name), last_name_(last_name) {};
	inline string get_name() const { return name_; };
	inline string get_last_name() const { return last_name_; };
	virtual void about() const = 0;
	virtual ~Person() {};
};

class Stud : public Person
{
private:
	vector<int> Homework_marks_;
	int exam_mark_;
	double final_mark_ = 0;
	double second_final_mark_ = -1;

public:
	Stud() {};
	Stud(string name, string last_name) : Person(name, last_name), exam_mark_(0) {};
	Stud(std::stringstream &is, int number_of_homework_marks);
	Stud(const Stud &other) : Person(other.name_, other.last_name_),
							  Homework_marks_(other.Homework_marks_), exam_mark_(other.exam_mark_), final_mark_(other.final_mark_), second_final_mark_(other.second_final_mark_) {};
	Stud(Stud &&other) noexcept : Person(move(other.name_), move(other.last_name_)),
								  Homework_marks_(move(other.Homework_marks_)), exam_mark_(other.exam_mark_), final_mark_(other.final_mark_), second_final_mark_(other.second_final_mark_)
	{
		other.exam_mark_ = 0;
		other.final_mark_ = 0;
		other.second_final_mark_ = 0;
	};
	Stud &operator=(const Stud &other);
	Stud &operator=(Stud &&other) noexcept;
	friend std::ostream &operator<<(std::ostream &out, const Stud &student);
	friend std::istream &operator>>(std::istream &in, Stud &student);
	inline int get_exam_mark() const { return exam_mark_; };
	inline void set_exam_mark(int exam_mark) { exam_mark_ = exam_mark; };
	inline void set_homework_marks(int Homework_mark) { Homework_marks_.push_back(Homework_mark); };
	inline void clean_homework_marks() { Homework_marks_.clear(); };
	inline void set_final_mark(double final_mark) { final_mark_ = final_mark; };
	inline double get_final_mark() const { return final_mark_; };
	inline void set_second_final_mark(double second_final_mark) { second_final_mark_ = second_final_mark; };
	inline double get_second_final_mark() const { return second_final_mark_; };
	double Get_average_for_homework_mark();
	double Get_mediana_for_homework_mark();
	void generate_marks();
	void generate_name();
	inline void about() const override { cout << "I am a student" << endl; };
	~Stud();
};

extern double time_of_generating_file;
extern double time_of_reading_file;
extern double time_of_dividing; // For best and worst
extern double time_of_sorting;
extern double time_of_culculating;
extern double time_of_writing_files;

void Get_final_mark(vector<Stud> &grupe, bool for_average_homework_mark, bool for_both_homework_mark);
void Print_final_mark(vector<Stud> &grupe, bool for_average_homework_mark, bool for_both_homework_mark, bool print_results_in_terminal);
int Get_size_for_string_printing(vector<Stud> &grupe);
void generate_marks(vector<int> &Marks, int number_of_marks);
void Sort_students(vector<Stud> &grupe, string parametr);
bool Generate_file_with_students(int number_of_students, int number_of_marks, string filename);
void Divide_for_two_grupse(vector<Stud> &grupe, vector<Stud> &best_grupe, vector<Stud> &worst_grupe);
void Divide_for_two_grupse(vector<Stud> &grupe, vector<Stud> &worst_grupe);
void Divide_for_two_grupse_v3(vector<Stud> &grupe, vector<Stud> &best_grupe, vector<Stud> &worst_grupe);
void Enter_students_using_txt_file_bufer_P(vector<Stud> &grupe);
