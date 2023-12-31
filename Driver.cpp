#include <iostream>
#include "course.h"
#include "professor.h"
#include "algorithmsSet.h"
#include <vector>
#include <fstream>
#include <sstream>
#include <chrono>
#include <algorithm>

using namespace std;

bool isInteger(const std::string &s)
{
    return !s.empty() && all_of(s.begin(), s.end(), ::isdigit);
}

int convertToInteger(const std::string &s)
{
    if (s == "x1")
        return 0.5;
    if (s == "x2")
        return 1;
    if (s == "x3")
        return 1.5;
    return std::stoi(s);
}

void showCourses(Course UGCDCcourses[], Course UGELECTcourses[], Course HDCDCcourses[], Course HDELECTcourses[])
{
    cout << "First Degree CDC's:" << endl;
    for (int i = 0; i < Course::totalUGCDCCourses; i++)
    {
        UGCDCcourses[i].showCourse();
    }
    cout << "First Degree Electives:" << endl;
    for (int i = 0; i < Course::totalUGElectCourses; i++)
    {
        UGELECTcourses[i].showCourse();
    }
    cout << "Higher Degree CDC's:" << endl;
    for (int i = 0; i < Course::totalHDCDCCourses; i++)
    {
        HDCDCcourses[i].showCourse();
    }
    cout << "Higher Degree Electives:" << endl;
    for (int i = 0; i < Course::totalHDElectCourses; i++)
    {
        HDELECTcourses[i].showCourse();
    }
}
void printVector(const vector<int> vec)
{
    for (const auto &element : vec)
    {
        std::cout << element << " ";
    }
    std::cout << std::endl;
}

void showProfessors(vector<Professor> professors)
{
    for (int i = 0; i < professors.size(); i++)
    {
        professors[i].getDetails();
    }
}

void assigningUGCDCcourses(Course courses[], int n)
{
    for (int i = 0; i < n; i++)
    {
        Professor::UGCDCallCourse[i] = courses[i];
        Course::totalUGCDCCourses++;
    }
}
void assigningUGELECTcourses(Course courses[], int n)
{
    for (int i = 0; i < n; i++)
    {
        Professor::UGELECTallCourse[i] = courses[i];
        Course::totalUGElectCourses++;
    }
}
void assigningHDCDCcourses(Course courses[], int n)
{
    for (int i = 0; i < n; i++)
    {
        Professor::HDCDCallCourse[i] = courses[i];
        Course::totalHDCDCCourses++;
    }
}
void assigningHDELECTcourses(Course courses[], int n)
{
    for (int i = 0; i < n; i++)
    {
        Professor::HDELECTallCourse[i] = courses[i];
        Course::totalHDElectCourses++;
    }
}

void readFile(vector<Professor> &professors)
{
    std::ifstream file("prof_input.csv");

    if (!file.is_open())
    {
        std::cerr << "Error opening the file." << std::endl;
        return;
    }
    std::string line;
    while (std::getline(file, line))
    {
        string name = "";
        vector<int> UGCDC = {}, UGELECT = {}, HDCDC = {}, HDELECT = {};
        double creds = 0;
        int ctr = 0;

        stringstream ss(line);

        getline(ss, name, ',');

        string subjectToken;
        int subjectIndex = 0;
        while (getline(ss, subjectToken, ','))
        {

            if (subjectToken.empty())
                break;
            stringstream subjectStream(subjectToken);

            string grade;
            while (getline(subjectStream, grade, ' '))
            {
                if (isInteger(grade) || (grade == "x1" || grade == "x2" || grade == "x3"))
                {

                    if (grade == "x1")
                    {
                        creds = 0.5;
                    }
                    else if (grade == "x2")
                    {
                        creds = 1;
                    }
                    else if (grade == "x3")
                    {
                        creds = 1.5;
                    }
                    else
                    {
                        int gradeValue = convertToInteger(grade);

                        switch (subjectIndex)
                        {
                        case 0:
                            UGCDC.push_back(gradeValue);
                            break;
                        case 1:
                            UGELECT.push_back(gradeValue);
                            break;
                        case 2:
                            HDCDC.push_back(gradeValue);
                            break;
                        case 3:
                            HDELECT.push_back(gradeValue);
                            break;
                        default:
                            break;
                        }
                    }
                }
                else
                {
                    std::cerr << "error - " << grade << std::endl;
                }
            }
            subjectIndex++;
        }
        Professor p(name, UGCDC, UGELECT, HDCDC, HDELECT, creds);
        professors.emplace_back(p);
    }
    file.close();
}

int main()
{
    auto start = std::chrono::high_resolution_clock::now();
    Course UGCDCcourses[] = {
        Course("CS F11 CP1", 1),       // index 0
        Course("CS F12 CP2", 1),       // index 1
        Course("CS F13 CP3", 1),       // index 2
        Course("CS F214 LCS", 1),      // index 3
        Course("CS F222 DisCo", 1),    // index 4
        Course("CS F213 OOP", 1),      // index 5
        Course("CS F215 DD", 1),       // index 6
        Course("CS F301 PoPL", 1),     // index 7
        Course("CS F342 CompArch", 1), // index 8
        Course("CS F351 ToC", 1),      // index 9
    };
    Course UGELECTcourses[] = {
        Course("BITS F311 Image Processing", 2),         // index 0
        Course("BITS F312 NEURAL NET & FUZZY LOGIC", 2), // index 1
        Course("BITS F343 FUZZY LOGIC & APPL", 2),       // index 2
        Course("BITS F364 HUMAN COMP INTERACTION", 2),   // index 3
        Course("BITS F386 QUANTUM INFO & COMPUTING", 2), // index 4
        Course("BITS F452 BLOCKCHAIN TECHNOLOGY", 2),    // index 5
        Course("BITS F463 CRYPTOGRAPHY", 2),             // index 6
    };

    Course HDCDCcourses[] = {
        Course("CS G513 Network Security", 3),                   // index 0
        Course("CSG524 Advanced Computer Architecture", 3),      // index 1
        Course("CS G525 Advanced Computer Networks", 3),         // index 2
        Course("CS G526 Advanced Algorithms and Complexity", 3), // index 3
        Course("CS C623 Advanced Operating Systems", 3)};        // index 4

    Course HDELECTcourses[] = {
        Course("SS G527 Cloud Computing", 4),               // index 0
        Course("BITS G553 Real-Time Systems", 4),           // index 1
        Course("CS G553 Reconfigurable Computing", 4),      // index 2
        Course("CS G568 Network Security Projec", 4),       // index 3
        Course("SS G513 Network Security", 4),              // index 4
        Course("CS G523 Software for Embedded Systems", 4), // index 5
        Course("SS G554 Distributed Data Systems", 4)};     // index 6

    assigningUGCDCcourses(UGCDCcourses, sizeof(UGCDCcourses) / sizeof(UGCDCcourses[0]));
    assigningUGELECTcourses(UGELECTcourses, sizeof(UGELECTcourses) / sizeof(UGELECTcourses[0]));
    assigningHDCDCcourses(HDCDCcourses, sizeof(HDCDCcourses) / sizeof(HDCDCcourses[0]));
    assigningHDELECTcourses(HDELECTcourses, sizeof(HDELECTcourses) / sizeof(HDELECTcourses[0]));

    vector<Professor> professors;
    readFile(professors);
    FILE *fp = freopen("info.txt", "w", stdout);
    for (int i = 0; i < Course::totalUGCDCCourses; i++)
    {
        if (Professor::UGCDCallCourse[i].popular == 0)
        {
            cout << "\n(Terminating Program)\nCRASH TEST: NO PROFESSOR HAS TAKEN COURSE " << Professor::UGCDCallCourse[i].name << endl;
            return -1;
        }
    }
    for (int i = 0; i < Course::totalHDCDCCourses; i++)
    {
        if (Professor::HDCDCallCourse[i].popular == 0)
        {
            cout << "\n(Terminating Program)\nCRASH TEST: NO PROFESSOR HAS TAKEN COURSE " << Professor::HDCDCallCourse[i].name << endl;
            return -1;
        }
    }

    
    cout << "Professor preferences : \n";
    showProfessors(professors);
    showCourses(Professor::UGCDCallCourse, Professor::UGELECTallCourse, Professor::HDCDCallCourse, Professor::HDELECTallCourse);
    fclose(fp);

    FILE *fp2 = freopen("assignments.txt", "w", stdout);
    AlgorithmsSet::initiateAlgorithms(vector<Professor>(professors),
                                      vector<Course>(Professor::UGCDCallCourse, Professor::UGCDCallCourse + Course::totalUGCDCCourses),
                                      vector<Course>(Professor::UGELECTallCourse, Professor::UGELECTallCourse + Course::totalUGElectCourses),
                                      vector<Course>(Professor::HDCDCallCourse, Professor::HDCDCallCourse + Course::totalHDCDCCourses),
                                      vector<Course>(Professor::HDELECTallCourse, Professor::HDELECTallCourse + Course::totalHDElectCourses));

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

    string s = "Time effiency: " + to_string(duration.count() / 1000.0) + " milliseconds\n";
    cout<<s<<endl;
    fclose(fp2);

    

    return 0;
}
