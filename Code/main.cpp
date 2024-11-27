#include <iostream>
#include <vector>
#include <map>
#include <string>

using namespace std;

// Classe repr�sentant un �l�ve
class Student {
public:
    string firstName;
    string lastName;
    string id; // Identifiant en tant que cha�ne de caract�res
    map<string, vector<float>> subjects;

    // Constructeur de la classe Student
    Student(string firstName, string lastName, string id)
        : firstName(firstName), lastName(lastName), id(id) {}

    // Ajouter une mati�re pour l'�tudiant
    void addSubject(string subject) {
        subjects[subject] = vector<float>();
    }

    // Ajouter une note pour une mati�re sp�cifique
    void addGrade(string subject, float grade) {
        subjects[subject].push_back(grade);
    }

    // Modifier une note sp�cifique
    void modifyGrade(string subject, int index, float newGrade) {
        if (index >= 0 && index < subjects[subject].size()) {
            subjects[subject][index] = newGrade;
        } else {
            cout << "Indice de note invalide.\n";
        }
    }

    // Supprimer une note sp�cifique
    void removeGrade(string subject, int index) {
        if (index >= 0 && index < subjects[subject].size()) {
            subjects[subject].erase(subjects[subject].begin() + index);
        } else {
            cout << "Indice de note invalide.\n";
        }
    }

    // Calculer la moyenne pour une mati�re sp�cifique
    float calculateSubjectAverage(string subject) {
        if (subjects[subject].empty()) return 0;
        float sum = 0;
        for (float grade : subjects[subject]) {
            sum += grade;
        }
        return sum / subjects[subject].size();
    }

    // Calculer la moyenne g�n�rale pour toutes les mati�res
    float calculateOverallAverage() {
        float sum = 0;
        int count = 0;
        for (auto& subject : subjects) {
            for (float grade : subject.second) {
                sum += grade;
                count++;
            }
        }
        return count == 0 ? 0 : sum / count;
    }

    // G�n�rer le bulletin de notes de l'�tudiant
    void generateReportCard() {
        cout << "Bulletin de notes pour " << firstName << " " << lastName << " (ID: " << id << ")\n";
        for (auto& subject : subjects) {
            cout << subject.first << " : ";
            for (float grade : subject.second) {
                cout << grade << " ";
            }
            cout << "(Moyenne : " << calculateSubjectAverage(subject.first) << ")\n";
        }
        cout << "Moyenne G�n�rale : " << calculateOverallAverage() << "\n";
    }
};

// Classe repr�sentant l'�cole
class School {
public:
    vector<Student> students;

    // Ajouter un �tudiant � l'�cole
    void addStudent(string firstName, string lastName, string id) {
        students.push_back(Student(firstName, lastName, id));
    }

    // Trouver un �tudiant par son identifiant
    Student* findStudentById(string id) {
        for (auto& student : students) {
            if (student.id == id) {
                return &student;
            }
        }
        return nullptr;
    }

    // Trouver un �tudiant par son nom et pr�nom
    Student* findStudentByName(string firstName, string lastName) {
        for (auto& student : students) {
            if (student.firstName == firstName && student.lastName == lastName) {
                return &student;
            }
        }
        return nullptr;
    }
};

// Fonction de menu principal
void menu(School& school) {
    int choice;
    while (true) {
        cout << "\nMenu Principal\n";
        cout << "1. Ajouter un �tudiant\n";
        cout << "2. Ajouter des mati�res � un �tudiant\n";
        cout << "3. Ajouter des notes � une mati�re\n";
        cout << "4. Modifier ou supprimer une note\n";
        cout << "5. Calculer la moyenne d'un �tudiant\n";
        cout << "6. G�n�rer un bulletin de notes\n";
        cout << "7. Rechercher un �tudiant\n";
        cout << "8. Quitter\n";
        cout << "Choix: ";
        cin >> choice;

        // V�rifier si l'entr�e est un chiffre valide
        if(cin.fail() || choice < 1 || choice > 8) {
            cin.clear(); // Clear any errors
            cin.ignore(10000, '\n'); // Discard any invalid input
            cout << "Choix invalide. Veuillez entrer un chiffre entre 1 et 8.\n";
            continue; // Restart the loop
        }

        if (choice == 1) {
            string firstName, lastName, id;
            cout << "Pr�nom: ";
            cin >> firstName;
            cout << "Nom: ";
            cin >> lastName;
            cout << "Identifiant: ";
            cin >> id;
            school.addStudent(firstName, lastName, id);
        } else if (choice == 2) {
            string id;
            cout << "Identifiant de l'�tudiant: ";
            cin >> id;
            Student* student = school.findStudentById(id);
            if (student) {
                int numSubjects;
                cout << "Nombre de mati�res � ajouter: ";
                cin >> numSubjects;
                for (int i = 0; i < numSubjects; ++i) {
                    string subject;
                    cout << "Nom de la mati�re: ";
                    cin >> subject;
                    student->addSubject(subject);
                }
            } else {
                cout << "�tudiant non trouv�.\n";
            }
        } else if (choice == 3) {
            string id;
            cout << "Identifiant de l'�tudiant: ";
            cin >> id;
            Student* student = school.findStudentById(id);
            if (student) {
                string subject;
                cout << "Nom de la mati�re: ";
                cin >> subject;
                int numGrades;
                cout << "Nombre de notes � ajouter: ";
                cin >> numGrades;
                for (int i = 0; i < numGrades; ++i) {
                    float grade;
                    cout << "Note: ";
                    cin >> grade;
                    student->addGrade(subject, grade);
                }
            } else {
                cout << "�tudiant non trouv�.\n";
            }
        } else if (choice == 4) {
            string id;
            int index;
            cout << "Identifiant de l'�tudiant: ";
            cin >> id;
            Student* student = school.findStudentById(id);
            if (student) {
                string subject;
                cout << "Nom de la mati�re: ";
                cin >> subject;
                cout << "Indice de la note � modifier/supprimer: ";
                cin >> index;
                int subChoice;
                cout << "1. Modifier la note\n";
                cout << "2. Supprimer la note\n";
                cout << "Choix: ";
                cin >> subChoice;
                if (subChoice == 1) {
                    float newGrade;
                    cout << "Nouvelle note: ";
                    cin >> newGrade;
                    student->modifyGrade(subject, index, newGrade);
                } else if (subChoice == 2) {
                    student->removeGrade(subject, index);
                } else {
                    cout << "Choix invalide.\n";
                }
            } else {
                cout << "�tudiant non trouv�.\n";
            }
        } else if (choice == 5) {
            string id;
            cout << "Identifiant de l'�tudiant: ";
            cin >> id;
            Student* student = school.findStudentById(id);
            if (student) {
                cout << "Moyenne G�n�rale : " << student->calculateOverallAverage() << "\n";
            } else {
                cout << "�tudiant non trouv�.\n";
            }
        } else if (choice == 6) {
            string id;
            cout << "Identifiant de l'�tudiant: ";
            cin >> id;
            Student* student = school.findStudentById(id);
            if (student) {
                student->generateReportCard();
            } else {
                cout << "�tudiant non trouv�.\n";
            }
        } else if (choice == 7) {
            string firstName, lastName;
            cout << "NOM: ";
            cin >> firstName;
            cout << "PENOM: ";
            cin >> lastName;
            Student* student = school.findStudentByName(firstName, lastName);
            if (student) {
                cout << "�tudiant trouv� : " << student->firstName << " " << student->lastName << " (ID: " << student->id << ")\n";
            } else {
                cout << "�tudiant non trouv�.\n";
            }
        } else if (choice == 8) {
            break; // Quitter le menu
        } else {
            cout << "Choix invalide.\n";
        }
    }
}

// Fonction principale
int main() {
    School school;
    menu(school); // Appel � la fonction de menu principal
    return 0; // Fin du programme
}
