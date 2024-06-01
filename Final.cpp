#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Student {
    string name;
    int id;
    int age;
    string major;

    // Конструктор, який приймає дані про студента
public:
    Student(string name, int id, int age, string major)
        : name(name), id(id), age(age), major(major) {}


    // Геттери
    string getName() const { return name; }
    int getId() const { return id; }
    int getAge() const { return age; }
    string getMajor() const { return major; }

    // Сеттери
    void setName(const string& name) { this->name = name; }
    void setId(int id) { this->id = id; }
    void setAge(int age) { this->age = age; }
    void setMajor(const string& major) { this->major = major; }

    // Print для виводу інформації
    void print() const {
        cout << "ID: " << id << ", Name: " << name << ", Age: " << age << ", Major: " << major << endl;
    }
};

class StudentDatabase {
    Student** students; // Масив вказівників на об'єкти класу Student
    int capacity; // Максимальна кількість студентів, яку може зберігати база даних
    int count; // Максимальна кількість студентів, яку може зберігати база даних

    // Функція для зміни розміру масиву
    void resize() {
        capacity *= 2; // Подвоєння максимальної кількості студентів
        Student** newStudents = new Student * [capacity]; // Створення нового масиву з подвоєною ємністю
        for (int i = 0; i < count; ++i) {
            newStudents[i] = students[i]; // Копіювання до нового масиву
        }
        delete[] students; // Видалення попереднього класу вказівників
        students = newStudents; // Присвоєння вказівникам на студентів адрес нового масиву
    }

    // Конструктор StudentDatabase, який ініціалізує початкову ємність
public:
    StudentDatabase(int capacity) 
        : capacity(capacity), count(0) {
        students = new Student * [capacity]; // Вижілення пам'яті для масиву вказівників
    }

    // Деструктор для звільнення пам'яті
    ~StudentDatabase() {
        for (int i = 0; i < count; ++i) {
            delete students[i];
        }
        delete[] students;
    }

    // Функція додавання студента
    void addStudent(const Student& student) {
        if (count == capacity) {
            resize();
        }
        students[count++] = new Student(student);
    }

    // Функція видалення студента по id
    void removeStudent(int id) {
        for (int i = 0; i < count; ++i) {
            if (students[i]->getId() == id) {
                delete students[i];
                for (int j = i; j < count - 1; ++j) {
                    students[j] = students[j + 1];
                }
                count--;
                return;
            }
        }
        cout << "Student not found." << endl;
    }
    // Пошук студента за id
    Student* findStudent(int id) {
        for (int i = 0; i < count; ++i) {
            if (students[i]->getId() == id) { // ПОшук студента за id
                return students[i]; // Повернення студента за id
            }
        }
        return nullptr;
    }

    // Функція для виведення всіх студентів
    void listStudents() const {
        for (int i = 0; i < count; ++i) {
            students[i]->print(); // Виклик функції print 
        }
    }

    // Функція для запису у файл
    void saveToFile(const string& filename) const {
        ofstream file(filename);
        for (int i = 0; i < count; ++i) {
            file << students[i]->getId() << " " << students[i]->getName() << " "
                << students[i]->getAge() << " " << students[i]->getMajor() << endl;
        }
        file.close();
    }

    // Функція для зчитування студентів з файлу
    void loadFromFile(const string& filename) {
        ifstream file(filename); // Відкриття файлу
        string name, major;
        int id, age;
        while (file >> id >> name >> age >> major) { // Зчитування даних про студента
            addStudent(Student(name, id, age, major)); // Додавання студента
        }
        file.close();
    }

    // Функція для оновлення даних про студента за id
    void updateStudent(int id, const Student& newData) {
        Student* student = findStudent(id); // Пошук студента за id
        if (student) {
            student->setName(newData.getName());
            student->setId(newData.getId());
            student->setAge(newData.getAge());
            student->setMajor(newData.getMajor());
        }
        else {
            cout << "Student not found." << endl;
        }
    }

    // Сортування студентів за спеціальністю
    void filterByMajor(const string& major) const {
        for (int i = 0; i < count; ++i) {
            if (students[i]->getMajor() == major) { // Перевірка спеціальності
                students[i]->print();
            }
        }
    }

    // Сортування студентів за віком
    void filterByAge(int age) const {
        for (int i = 0; i < count; ++i) {
            if (students[i]->getAge() == age) {
                students[i]->print();
            }
        }
    }

    // Функція для підрахунку кількості студентів
    int getStudentCount() const {
        return count;
    }

    // Сортування студентів за іменем
    void sortByName() {
        for (int i = 0; i < count - 1; ++i) {
            for (int j = 0; j < count - i - 1; ++j) {
                if (students[j]->getName() > students[j + 1]->getName()) {
                    swap(students[j], students[j + 1]);
                }
            }
        }
    }

    // Сортування студентів за id
    void sortById() {
        for (int i = 0; i < count - 1; ++i) {
            for (int j = 0; j < count - i - 1; ++j) {
                if (students[j]->getId() > students[j + 1]->getId()) {
                    swap(students[j], students[j + 1]);
                }
            }
        }
    }

    // Сортування студентів за віком
    void sortByAge() {
        for (int i = 0; i < count - 1; ++i) {
            for (int j = 0; j < count - i - 1; ++j) {
                if (students[j]->getAge() > students[j + 1]->getAge()) {
                    swap(students[j], students[j + 1]);
                }
            }
        }
    }
};

// Функція відображення меню
void displayMenu() {
    cout << "1. Add Student" << endl;
    cout << "2. Remove Student" << endl;
    cout << "3. Find Student" << endl;
    cout << "4. List All Students" << endl;
    cout << "5. Save Students to File" << endl;
    cout << "6. Load Students from File" << endl;
    cout << "7. Update Student" << endl;
    cout << "8. Filter Students by Major" << endl;
    cout << "9. Filter Students by Age" << endl;
    cout << "10. Count Students" << endl;
    cout << "11. Sort Students by Name" << endl;
    cout << "12. Sort Students by ID" << endl;
    cout << "13. Sort Students by Age" << endl;
    cout << "0. Exit" << endl;
}

void processChoice(StudentDatabase& db, int choice) {
    switch (choice) {
    case 0: // Вихід з програми
        exit(0);
    case 1: { // Додавання студента
        string name, major;
        int id, age;
        cout << "Enter ID: ";
        cin >> id;
        cout << "Enter Name: ";
        cin >> name;
        cout << "Enter Age: ";
        cin >> age;
        cout << "Enter Major: ";
        cin >> major;
        db.addStudent(Student(name, id, age, major));
        break;
    }
    case 2: { // Видалення студента
        int id;
        cout << "Enter ID to remove: ";
        cin >> id;
        db.removeStudent(id);
        break;
    }
    case 3: { // Пошук студента
        int id;
        cout << "Enter ID to find: ";
        cin >> id;
        Student* student = db.findStudent(id);
        if (student) {
            student->print();
        }
        else {
            cout << "Student not found." << endl;
        }
        break;
    }
    case 4: // Виведення списку всіх студентів
        db.listStudents();
        break;
    case 5: { // Збереження студентів у файл
        string filename;
        cout << "Enter filename: ";
        cin >> filename;
        db.saveToFile(filename);
        break;
    }
    case 6: { // Завантаження студентів з файлу
        string filename;
        cout << "Enter filename: ";
        cin >> filename;
        db.loadFromFile(filename);
        break;
    }
    case 7: { // Оновлення даних про студента
        int id;
        cout << "Enter ID to update: ";
        cin >> id;
        string name, major;
        int age;
        cout << "Enter new Name: ";
        cin >> name;
        cout << "Enter new Age: ";
        cin >> age;
        cout << "Enter new Major: ";
        cin >> major;
        db.updateStudent(id, Student(name, id, age, major));
        break;
    }
    case 8: { // Сортування студентів за спеціальністю
        string major;
        cout << "Enter Major: ";
        cin >> major;
        db.filterByMajor(major);
        break;
    }
    case 9: { // Сортування студентів за віком
        int age;
        cout << "Enter Age: ";
        cin >> age;
        db.filterByAge(age);
        break;
    }
    case 10: // Підрахунок кількості студентів
        cout << "Total Students: " << db.getStudentCount() << endl;
        break;
    case 11: // Сортування студентів за іменем
        db.sortByName();
        break;
    case 12: // Сортування студентів за id
        db.sortById();
        break;
    case 13: // Сортування студентів за віком
        db.sortByAge();
        break;
    default: // Невірний вибір
        cout << "Invalid choice." << endl;
        break;
    }
}

int main() {
    StudentDatabase db(10); // Створення об'єкту бази даних студентів

    while (true) {
        displayMenu(); // Виведення меню
        int choice;
        cout << "Enter your choice: ";
        cin >> choice;
        processChoice(db, choice);
    }

    return 0;
}