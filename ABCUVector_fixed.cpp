// Ahmed Ahmed
// CS-300 Project 2, Vector Data Structure
// Implemented: 03.01.2026

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>
#include <limits>

using namespace std;

// Course object holds ID, title, and list of prerequisite IDs
struct Course {
    string courseId;
    string courseTitle;
    vector<string> preRequisite;
};

// Trim whitespace from both ends
static inline string trim(const string& s) {
    size_t a = 0, b = s.size();
    while (a < b && isspace((unsigned char)s[a])) ++a;
    while (b > a && isspace((unsigned char)s[b-1])) --b;
    return s.substr(a, b - a);
}

// Split a CSV line on commas (no quoted fields required for this dataset)
vector<string> splitCsvLine(const string& line) {
    vector<string> out;
    istringstream ss(line);
    string token;
    while (getline(ss, token, ',')) out.push_back(trim(token));
    return out;
}

// Load courses from CSV into the vector<Course>
void loadVector(const string& textFile, vector<Course>& courses) {
    ifstream file(textFile);
    if (!file) {
        cout << "Error: File not found: " << textFile << '\n';
        return;
    }

    courses.clear(); // replace existing data
    string line;
    while (getline(file, line)) {
        if (line.empty()) continue;
        auto cols = splitCsvLine(line);
        if (cols.size() < 2) continue; // require at least id and title
        Course c;
        c.courseId = cols[0];
        c.courseTitle = cols[1];
        for (size_t i = 2; i < cols.size(); ++i) if (!cols[i].empty()) c.preRequisite.push_back(cols[i]);
        courses.push_back(move(c));
    }
    cout << "Courses imported from '" << textFile << "' (" << courses.size() << " entries)." << endl;
}

// Print sorted alphanumeric list of CSCI and MATH courses
void printCourseList(const vector<Course>& courses) {
    if (courses.empty()) {
        cout << "No courses loaded. Use option 1 to load data first." << '\n';
        return;
    }

    vector<Course> sorted = courses; // copy to sort without mutating original
    sort(sorted.begin(), sorted.end(), [](const Course& a, const Course& b){
        return a.courseId < b.courseId; // alphanumeric by courseId
    });

    for (const auto& c : sorted) {
        if (c.courseId.size() >= 4 && (c.courseId.substr(0,4) == "CSCI" || c.courseId.substr(0,4) == "MATH")) {
            cout << c.courseId << ", " << c.courseTitle << '\n';
        }
    }
}

// Helper: find course pointer by id (returns nullptr if not found)
const Course* findCourseById(const vector<Course>& courses, const string& id) {
    for (const auto& c : courses) if (c.courseId == id) return &c;
    return nullptr;
}

// Print course title and prerequisites (with prerequisite titles if available)
void printCourseInformation(const vector<Course>& courses, const string& courseNumber) {
    const Course* c = findCourseById(courses, courseNumber);
    if (!c) {
        cout << "Course not found: " << courseNumber << '\n';
        return;
    }
    cout << c->courseId << ": " << c->courseTitle << '\n';
    if (c->preRequisite.empty()) {
        cout << "Prerequisites: None listed." << '\n';
        return;
    }
    cout << "Prerequisites:" << '\n';
    for (const auto& pid : c->preRequisite) {
        const Course* p = findCourseById(courses, pid);
        if (p) cout << " - " << pid << ": " << p->courseTitle << '\n';
        else cout << " - " << pid << ": (title not found)" << '\n';
    }
}

int main() {
    vector<Course> courses;
    string filename;

    // Main menu loop
    while (true) {
        cout << "\nMenu:\n";
        cout << "1. Load the file data into the data structure\n";
        cout << "2. Print an alphanumeric list of all CSCI and MATH courses\n";
        cout << "3. Print the course title and prerequisites for a course\n";
        cout << "9. Exit\n";
        cout << "Select an option: ";

        int choice = 0;
        if (!(cin >> choice)) {
            cout << "Invalid input. Exiting." << endl;
            break;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (choice == 1) {
            cout << "Enter course data filename: ";
            getline(cin, filename);
            filename = trim(filename);
            if (filename.empty()) {
                cout << "Error: filename cannot be empty." << endl;
            } else {
                loadVector(filename, courses);
            }
        } else if (choice == 2) {
            printCourseList(courses);
        } else if (choice == 3) {
            if (courses.empty()) {
                cout << "No courses loaded. Use option 1 to load data first." << '\n';
            } else {
                cout << "Enter course ID to look up (e.g. CSCI300): ";
                string id;
                getline(cin, id);
                id = trim(id);
                if (id.empty()) cout << "Error: course ID cannot be empty." << '\n';
                else printCourseInformation(courses, id);
            }
        } else if (choice == 9) {
            cout << "Thank you for using the course planner!" << endl;
            break;
        } else {
            cout << "Error: " << choice << " is not a valid option." << endl;
        }
    }

    return 0;
}
