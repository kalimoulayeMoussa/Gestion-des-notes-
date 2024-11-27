#include <iostream>
#include <vector>
#include <map>
#include <string>

using namespace std;

// Classe représentant un éléve
class Student {
public:
    string firstName;
    string lastName;
    string id; // Identifiant en tant que chaîne de caractères
    map<string, vector<float>> subjects;

    // Constructeur de la classe Student
    Student(string firstName, string lastName, string id)
        : firstName(firstName), lastName(lastName), id(id) {}

    // Ajouter une matière pour l'étudiant
    void addSubject(string subject) {
        subjects[subject] = vector<float>();
    }

    // Ajouter une note pour une matière spécifique
    void addGrade(string subject, float grade) {
        subjects[subject].push_back(grade);
    }

    // Modifier une note spécifique
    void modifyGrade(string subject, int index, float newGrade) {
        if (index >= 0 && index < subjects[subject].size()) {
            subjects[subject][index] = newGrade;
        } else {
            cout << "Indice de note invalide.\n";
        }
    }

    // Supprimer une note spécifique
    void removeGrade(string subject, int index) {
        if (index >= 0 && index < subjects[subject].size()) {
            subjects[subject].erase(subjects[subject].begin() + index);
        } else {
            cout << "Indice de note invalide.\n";
        }
    }

    // Calculer la moyenne pour une matière spécifique
    float calculateSubjectAverage(string subject) {
        if (subjects[subject].empty()) return 0;
        float sum = 0;
        for (float grade : subjects[subject]) {
            sum += grade;
        }
        return sum / subjects[subject].size();
    }

    // Calculer la moyenne générale pour toutes les matières
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

    // Générer le bulletin de notes de l'étudiant
    void generateReportCard() {
        cout << "Bulletin de notes pour " << firstName << " " << lastName << " (ID: " << id << ")\n";
        for (auto& subject : subjects) {
            cout << subject.first << " : ";
            for (float grade : subject.second) {
                cout << grade << " ";
            }
            cout << "(Moyenne : " << calculateSubjectAverage(subject.first) << ")\n";
        }
        cout << "Moyenne Générale : " << calculateOverallAverage() << "\n";
    }
};

// Classe représentant l'école
class School {
public:
    vector<Student> students;

    // Ajouter un étudiant à l'école
    void addStudent(string firstName, string lastName, string id) {
        students.push_back(Student(firstName, lastName, id));
    }

    // Trouver un étudiant par son identifiant
    Student* findStudentById(string id) {
        for (auto& student : students) {
            if (student.id == id) {
                return &student;
            }
        }
        return nullptr;
    }

    // Trouver un étudiant par son nom et prénom
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
        cout << "1. Ajouter un étudiant\n";
        cout << "2. Ajouter des matières à un étudiant\n";
        cout << "3. Ajouter des notes à une matière\n";
        cout << "4. Modifier ou supprimer une note\n";
        cout << "5. Calculer la moyenne d'un étudiant\n";
        cout << "6. Générer un bulletin de notes\n";
        cout << "7. Rechercher un étudiant\n";
        cout << "8. Quitter\n";
        cout << "Choix: ";
        cin >> choice;

        // Vérifier si l'entrée est un chiffre valide
        if(cin.fail() || choice < 1 || choice > 8) {
            cin.clear(); // Clear any errors
            cin.ignore(10000, '\n'); // Discard any invalid input
            cout << "Choix invalide. Veuillez entrer un chiffre entre 1 et 8.\n";
            continue; // Restart the loop
        }

        if (choice == 1) {
            string firstName, lastName, id;
            cout << "Prénom: ";
            cin >> firstName;
            cout << "Nom: ";
            cin >> lastName;
            cout << "Identifiant: ";
            cin >> id;
            school.addStudent(firstName, lastName, id);
        } else if (choice == 2) {
            string id;
            cout << "Identifiant de l'étudiant: ";
            cin >> id;
            Student* student = school.findStudentById(id);
            if (student) {
                int numSubjects;
                cout << "Nombre de matières à ajouter: ";
                cin >> numSubjects;
                for (int i = 0; i < numSubjects; ++i) {
                    string subject;
                    cout << "Nom de la matière: ";
                    cin >> subject;
                    student->addSubject(subject);
                }
            } else {
                cout << "Étudiant non trouvé.\n";
            }
        } else if (choice == 3) {
            string id;
            cout << "Identifiant de l'étudiant: ";
            cin >> id;
            Student* student = school.findStudentById(id);
            if (student) {
                string subject;
                cout << "Nom de la matière: ";
                cin >> subject;
                int numGrades;
                cout << "Nombre de notes à ajouter: ";
                cin >> numGrades;
                for (int i = 0; i < numGrades; ++i) {
                    float grade;
                    cout << "Note: ";
                    cin >> grade;
                    student->addGrade(subject, grade);
                }
            } else {
                cout << "Étudiant non trouvé.\n";
            }
        } else if (choice == 4) {
            string id;
            int index;
            cout << "Identifiant de l'étudiant: ";
            cin >> id;
            Student* student = school.findStudentById(id);
            if (student) {
                string subject;
                cout << "Nom de la matière: ";
                cin >> subject;
                cout << "Indice de la note à modifier/supprimer: ";
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
                cout << "Étudiant non trouvé.\n";
            }
        } else if (choice == 5) {
            string id;
            cout << "Identifiant de l'étudiant: ";
            cin >> id;
            Student* student = school.findStudentById(id);
            if (student) {
                cout << "Moyenne Générale : " << student->calculateOverallAverage() << "\n";
            } else {
                cout << "Étudiant non trouvé.\n";
            }
        } else if (choice == 6) {
            string id;
            cout << "Identifiant de l'étudiant: ";
            cin >> id;
            Student* student = school.findStudentById(id);
            if (student) {
                student->generateReportCard();
            } else {
                cout << "Étudiant non trouvé.\n";
            }
        } else if (choice == 7) {
            string firstName, lastName;
            cout << "NOM: ";
            cin >> firstName;
            cout << "PENOM: ";
            cin >> lastName;
            Student* student = school.findStudentByName(firstName, lastName);
            if (student) {
                cout << "Étudiant trouvé : " << student->firstName << " " << student->lastName << " (ID: " << student->id << ")\n";
            } else {
                cout << "Étudiant non trouvé.\n";
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
    menu(school); // Appel à la fonction de menu principal
    return 0; // Fin du programme
}
