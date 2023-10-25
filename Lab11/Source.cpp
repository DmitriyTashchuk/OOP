#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <vector>
using namespace std;
struct Grade { //��������� � ��������
	int math;
	int chemistry;
	int physics;
	int history;
	int oop;
	int prog;
	int web;
};
struct Student { // ��������� ��������
	char name[10];
	int course;
	char group[10];
	Grade grade;

};
int count_grade(Student student) { //����������� ������� �������� �� ������
	int count = 0;
	if (student.grade.chemistry == 5) {
		count++;
	}
	if (student.grade.math == 5) {
		count++;
	}
	if (student.grade.history == 5) {
		count++;
	}
	if (student.grade.physics == 5) {
		count++;
	}
	return count;
} 
void RW(string student) { //������� ������ � ��������� ����
	ofstream file_write("file.txt", ios::app);
	file_write << student << endl;
	file_write.close();
}
void RW(Student student) { // ������� ������ � ���������� ����
	ofstream file_write("file.dat", ios::app|ios::binary);
	file_write.write((char*)&student, sizeof(Student));
	file_write.close();
}
void RD_for_olimpiad(string filename, string filename2) { // ������� ������ �������� �� �������
	vector<Student> students;
	//���������� ����� � �����
	ifstream file_read(filename);
	//�������� ����������� ��� ������ ������� ����������
	ofstream file_write(filename2, ios::trunc | ios::binary);
	cout << "C�������, ������ ��� �������:" << endl;
	while (file_read) {
		Student student;
		file_read >> student.name >> student.course >> student.group >> student.grade.math >> student.grade.chemistry >> student.grade.physics >> student.grade.history >> student.grade.oop >> student.grade.prog >> student.grade.web;
		if (!file_read.eof() && student.grade.oop == 5 && student.grade.prog == 5 && student.grade.web == 5) {
			file_write.write((char*)&student, sizeof(Student));
			cout << "��'�: " << student.name << " ����: " << student.course << endl;
			cout << "������: ���: " << student.grade.oop << " �������������: " << student.grade.prog << " ���-�������㳿: " << student.grade.web << endl;
		}
	}
	file_write.close();
	file_read.close();
}
void RD(string filename) { // ������� ���������� � ����������
	vector<Student> students;
	ifstream file_read(filename);
	while (file_read){ 
		// ���� � ���������� �����
		Student student;
		file_read >> student.name >> student.course >> student.group >> student.grade.math >> student.grade.chemistry >> student.grade.physics >> student.grade.history >> student.grade.oop >> student.grade.prog >> student.grade.web;
		/*file_read >> student.name >> student.course >> student.group >> student.grade.math >> student.grade.chemistry >> student.grade.physics >> student.grade.history;*/
		if (!file_read.eof()) {
			students.push_back(student);
		}
	}
	file_read.close();
	// ���������� �� ������ ��������� �� ������
	int length = students.size();
	vector<string> used_group;
	for (int i = 0; i < length; i++) {
		string current_group = students[i].group;
		bool found = find(used_group.begin(), used_group.end(), current_group) != used_group.end();
		if (found == false) {
			used_group.push_back(current_group);
			vector<Student> temp;
			for (int A_count = 4; A_count > -1; A_count--) {
				for (int j = 0; j < length; j++) {
					if (students[j].group == current_group) {
						int count = count_grade(students[j]);
						if (count == A_count) {
							temp.push_back(students[j]);
						}
					}
				}
			}
			//���� ������������ ����������
			cout << "�����: " << current_group << endl;
			for (int j = 0; j < temp.size(); j++) {
				cout << "��'�: " << temp[j].name << " ����: " << temp[j].course << endl;
				cout << "������: ����������: " << temp[j].grade.math << " ճ��: " << temp[j].grade.chemistry << " Գ����: " <<
					temp[j].grade.physics << " ������: " << temp[j].grade.history << endl;
			}
		}
	}
}
void RD(string filename, int trash) { //������� ���������� � ����������� �����
	ifstream file_read(filename, ios::binary);
	float hist = 0, math = 0, phys = 0, chem = 0, count = 0;
	while (file_read) {
		Student student;
		file_read.read((char*)&student, sizeof(Student));
		if (!file_read.eof()) { //����������� ���� ������ � �������� �� ��� ���������
			hist += student.grade.history;
			math += student.grade.math;
			phys += student.grade.physics;
			chem += student.grade.chemistry;
			count++;
		}
	}
	//���� ������� ������� �� ���������
	cout << "������ ���� �� ��������� : " << endl;
	cout << "����������: " << setprecision(2) << math / count << " ճ��: " << chem / count << endl;
	cout << "Գ����: " << phys / count << " ������: " << hist / count << endl;
	file_read.close();
}
int main() { // ������� �������
	setlocale(LC_ALL, "ukrainian");
	//��� ����� �������� � ����� � �����
	/*int number;
	cout << "������ ������� ��������" << endl;
	cin >> number;
	for (int i = 0; i < number; i++) {
		Student student;
		cout << "������ ��'�" << endl; cin >> student.name;
		cout << "������ ����" << endl; cin >> student.course;
		cout << "������ �����" << endl; cin >> student.group;
		cout << "������ ������ � �������� � �������: ���������� - ���� - ������ - ������" << endl;
		cin >> student.grade.math >> student.grade.chemistry >> student.grade.physics >> student.grade.history;
		string student_string = string(student.name) + ' ' + to_string(student.course) + ' ' + string(student.group) + ' ' + to_string(student.grade.math) + ' ' + to_string(student.grade.chemistry) + ' ' +
			to_string(student.grade.physics) + ' ' + to_string(student.grade.history);
		RW(student);
		RW(student_string);
	}*/
	//������� ����������
	RD("file.txt");
	RD("file.dat", 1);
	RD_for_olimpiad("file.txt", "file2.dat");
	cin.get();
}