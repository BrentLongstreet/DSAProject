/*
Programmer: Brent Longstreet
Date: 08/12/2023
Course: CS-300
*/

#include <iostream>
#include<fstream>
#include<vector>
#include <string>
#include<algorithm>
using namespace std;


struct Course {
    string courseNumber;
    string courseName;
    vector<string> prerequisites;
};
//Splits strings into list given the delimiter
vector<string> structuredCourses(string s, string del = " "){
      vector<string> stringArray;
      int start = 0;
      int end = s.find(del);
      while (end != -1) {
        stringArray.push_back(s.substr(start, end - start));
        start = end + del.size();
        end = s.find(del, start);
      }
      stringArray.push_back(s.substr(start, end - start));
      return stringArray;
    }
// Loads file and stores course information
vector<Course> LoadDataStructure(string fname) {
        // Creating an object of iftsream class to open file 
        ifstream fin(fname,ios::in);
        vector<Course> courses;
        string line;
        while (true) {
            getline(fin, line);
            //loop until end of file
            if (line == "end") {
                break;
            }
            //create course object
            Course course;
            vector<string> structuredCoursesInformation = structuredCourses(line, ",");
            course.courseNumber = structuredCoursesInformation[0];
            course.courseName = structuredCoursesInformation[1];
            for (int i = 2; i < structuredCoursesInformation.size(); i++) {
                course.prerequisites.push_back(structuredCoursesInformation[i]);
            }
            //append new course to courses
            courses.push_back(course);
        }
        //close file
        fin.close();
        return courses;
    }


void printCourse(Course course) {
    //output course information
    cout << course.courseNumber << ", " << course.courseName << "\n";

}

void printCourseList(vector<Course>courses) {
    int n = courses.size();
    //bubble sort
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (courses[j].courseNumber > courses[j + 1].courseNumber) {
                swap(courses[j + 1], courses[j]);
            }
        }
    }
    //call print course on each item
    for (int i = 0; i < n; i++) {
        printCourse(courses[i]);
    }
    cout << "\n";
}

void searchCourse(vector<Course> courses) {
    int n = courses.size();
    string courseNumber;
    //flag to see if course was found
    bool found = false;
    cout << "What course do you want to know about? ";
    cin >> courseNumber;
    //convert to uppcase to validate case-insensitive-input
    transform(courseNumber.begin(), courseNumber.end(), courseNumber.begin(), ::toupper);
    for (int i = 0; i < n; i++) {
        if (courses[i].courseNumber == courseNumber) {
            //update found to true
            found = true;
            printCourse(courses[i]);
            //output all prereqs
            cout << "Prerequisites: ";
            for (int j = 0; j < courses[i].prerequisites.size(); j++) {
                cout << courses[i].prerequisites[j] << ", ";
            }
            cout << "\n\n";
            break;
        }
    }
    //if course wasn't found
    if (found == false) {
        cout << "Course with given course number not found\n\n";
    }
}
int main()
{
    //menu
    vector<Course> courses;
    int choice;
    string filename;
    cout << "Welcome to the course planner. \n";
    //retrieve file name
    cout << "Enter file name (MUST CONTAIN \"end\" AT THE END OF .TXT FILE): ";
    cin >> filename;
    cout << "\n\n";
    do {
        //output menu options
        cout << "1. Load Data Structure\n";
        cout << "2. Print Course List\n";
        cout << "3. Print Course\n";
        cout << "9. Exit\n";
        cout << "\nWhat would you like to do? ";
        cin >> choice;
        switch (choice) {
            //input options
        case 1: courses = LoadDataStructure(filename); break;
        case 2: cout << "Here is a sample schedule: \n\n"; printCourseList(courses); break;
        case 3: searchCourse(courses); break;
        case 9: cout<<"Thanks for using the course planner!"; break;
        default: cout << choice << " is not a valid option.\n\n";
        }
    } while (choice != 9);
    return 0;
}



// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
