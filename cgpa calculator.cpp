#include <iostream>
#include <iomanip>
#include <string>
using namespace std;


struct Course {
    string courseName;
    float grade;         
    int creditHours;
};


void inputCourses(Course courses[], int numCourses) {
    for (int i = 0; i < numCourses; i++) {
        cout << "\nCourse " << i + 1 << ":\n";
        cout << "Enter course name: ";
        cin.ignore(); 
        getline(cin, courses[i].courseName);

        
        do {
            cout << "Enter grade (0.0 - 4.0): ";
            cin >> courses[i].grade;
            if (courses[i].grade < 0.0 || courses[i].grade > 4.0) {
                cout << "Invalid grade! Please enter between 0.0 and 4.0.\n";
            }
        } while (courses[i].grade < 0.0 || courses[i].grade > 4.0);
        
        
        do {
            cout << "Enter credit hours (1 - 5): ";
            cin >> courses[i].creditHours;
            if (courses[i].creditHours < 1 || courses[i].creditHours > 5) {
                cout << "Invalid credit hours! Please enter between 1 and 5.\n";
            }
        } while (courses[i].creditHours < 1 || courses[i].creditHours > 5);
    }
}


float calculateCGPA(Course courses[], int numCourses, int &totalCredits) {
    
	float totalGradePoints = 0;
    totalCredits = 0;

    for (int i = 0; i < numCourses; i++) {
        totalGradePoints += courses[i].grade * courses[i].creditHours;
        totalCredits += courses[i].creditHours;
    }

    if (totalCredits == 0) return 0;
    return totalGradePoints / totalCredits;
}

// Function to display course results
void displayResults(Course courses[], int numCourses, float cgpa, int totalCredits) {
    cout << "\n-------------------------------------\n";
    cout << left << setw(20) << "Course Name"
         << setw(10) << "Grade"
         << setw(15) << "Credit Hours" << endl;
    cout << "-------------------------------------\n";

    for (int i = 0; i < numCourses; i++) {
        cout << left << setw(20) << courses[i].courseName
             << setw(10) << fixed << setprecision(2) << courses[i].grade
             << setw(15) << courses[i].creditHours << endl;
    }

    cout << "-------------------------------------\n";
    cout << "Total Credit Hours: " << totalCredits << endl;
    cout << "Your CGPA is: " << fixed << setprecision(2) << cgpa << endl;
    cout << "-------------------------------------\n";
}


int main() {
    int numCourses;

    cout << "===== CGPA Calculator =====\n";
    cout << "Enter number of courses: ";
    cin >> numCourses;

    if (numCourses <= 0) {
        cout << "Invalid number of courses!\n";
        return 1;
    }

    Course courses[50]; 
    inputCourses(courses, numCourses);

    int totalCredits = 0;
    float cgpa = calculateCGPA(courses, numCourses, totalCredits);

    displayResults(courses, numCourses, cgpa, totalCredits);

    return 0;
}

