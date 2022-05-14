#include <iostream>
#include <conio.h>
#include "College.h"
#include <windows.h>
#include <fstream>
using namespace std;

void Print_Admin_Menu()
{
    print_logo("Admin Page");
    print(35, ' ') << "Choose : \n\n";
    print(40, ' ') << char(201);
    for (int i = 0; i < 21; i++)
    {
        cout << char(205);
    }
    cout << char(187) << endl;
    print(40, ' ') << char(186) << "  1- Control Teacher " << char(186) << endl;
    print(40, ' ') << char(186) << "  2- Control Student " << char(186) << endl;
    setcolor(12);
    print(40, ' ') << char(186) << "  3- Logout          " << char(186) << endl;

    print(40, ' ') << char(200);
    for (int i = 0; i < 21; i++)
    {
        cout << char(205);
    }
    cout << char(188) << endl;

    setcolor(2);
    print(25, ' ') << "Choice : ";
}

void Print_Ctrl_Tec()
{
    setcolor(2);
    print_logo("Admin Page (Teacher Control)");
    print(25, ' ') << "Choose : \n\n";
    print(40, ' ') << char(201);
    for (int i = 0; i < 23; i++)
    {
        cout << char(205);
    }
    cout << char(187) << endl;
    print(40, ' ') << char(186) << "  1- Show All Teachers " << char(186) << endl;
    print(40, ' ') << char(186) << "  2- Search Teacher    " << char(186) << endl;
    print(40, ' ') << char(186) << "  3- Add               " << char(186) << endl;
    print(40, ' ') << char(186) << "  4- Remove            " << char(186) << endl;
    print(40, ' ') << char(186) << "  5- Edit              " << char(186) << endl;

    setcolor(12);
    print(40, ' ') << char(186) << "  6- Return            " << char(186) << endl;
    print(40, ' ') << char(200);
    for (int i = 0; i < 23; i++)
    {
        cout << char(205);
    }
    cout << char(188) << endl;
    setcolor(2);
}

void ShowAllTeacher()
{
    Teacher T;
    ifstream inFile;

    inFile.open("Teachers.txt", ios ::in | ios::app);
    if (!inFile.is_open())
    {
        setcolor(12);
        Beep(500, 500);

        print(25, ' ') << "\aError here ... There is no Teacher!, Please Read the Readme.txt file and try again\n";
        return;
    }

    bool exist = false;
    inFile.read((char *)&T, sizeof(T));
    while (!inFile.eof())
    {
        if (!exist)
        {
            setcolor(2);
            print_logo("Show All Teachers", 50);
            print(25, ' ') << "ID"
                           << "\t\t\t Name"
                           << "\t\t\tpassword"
                           << "\t\t\tage"
                           << "\t\tCourse\n";
            print(25, ' ');
            print(89, '-') << "\n";
            // Last edit
            exist = true;
        }
        int szofStr = 0, szofPass = 0;
        for(int i = 0 ; i < 20 ; i++)       szofStr += (T.name[i] != '\0'); 
        for(int i = 0 ; i < 20 ; i++)       szofPass += (T.password[i] != '\0'); 
        setcolor(6);
        print(25, ' ') << T.id << "\t\t\t" << T.name << "\t\t\t" << string(szofStr - 3, ' ')  << T.password << "\t\t\t" << string(szofPass + 6, ' ') << T.age << "\t\t    " << T.course.c_Name << "\n";
        inFile.read((char *)&T, sizeof(T));
    }
    if (!exist)
    {
        cout << "\n";
        print(25, ' ') << "\aNo Teachers found"
                       << "\n";
    }
    press_any();
    cout << "\n";
    Returning();
}

void SearchTeacher()
{
    int tea_id;
    setcolor(2);
    print_logo("Search for Teacher");
    print(25, ' ') << "Enter teacher's id to search for : ";
    setcolor(6);
    cin >> tea_id;
    cout << "\n\n";
    Teacher T;
    ifstream inFile;
    inFile.open("Teachers.txt", ios ::in);
    if (!inFile.is_open())
    {
        setcolor(12);
        Beep(500, 500);
        print(25, ' ') << "\aError here ... There is no Teacher to search for!, Please Read the Readme.txt file and try again\n";
        press_any();
        cout << "\n";
        Returning();
    }
    bool exist = false;
    inFile.read((char *)&T, sizeof(T));
    while (!inFile.eof())
    {
        if (tea_id == T.id)
        {
            if (!exist)
            {
                setcolor(2);
                print(35, ' ') << "ID\t\t"
                               << "Name\t\t"
                               << "age\t\t"
                               << "Course\n";
                exist = true;
                print(35, ' ');
                print(73, '-') << "\n";
            }
            setcolor(6);
            print(35, ' ') << T.id << "\t\t" << T.name << "\t\t" << T.age << "\t\t" << T.course.c_Name << "\n";
        }
        inFile.read((char *)&T, sizeof(T));
    }
    // Last Edit
    if (!exist)
    {
        setcolor(12);
        Beep(500, 500);
        print(25, ' ') << "\aThe ID you entered does not exist :)\n";
    }
    press_any();
    cout << "\n";
    Returning();
    // Last Edit
    inFile.close();
}

void Add_Teacher()
{
    fstream outFile;
    outFile.open("Teachers.txt", ios::out | ios::app);
    if (!outFile.is_open())
    {
        setcolor(12);
        Beep(500, 500);

        cout << "\aFile cannot be oppened :)\n";
        return;
    }
    print_logo("Add Teacher");
    Teacher T;
    setcolor(2);
    print(35, ' ') << "Enter Teacher's Name : ";
    setcolor(6);
    cin.ignore();
    cin.getline(T.name, 20);
    setcolor(2);
    print(35, ' ') << "Enter Teacher's Password: ";
    // cin.ignore(); //to Remove
    setcolor(6);
    set_Password(T.password);
    setcolor(2);
    print(35, ' ') << "Enter Teacher's Age : ";
    setcolor(6);
    cin >> T.age;
    setcolor(2);
    print(35, ' ') << "Enter Teacher's Course Name : ";
    cin.ignore();
    setcolor(6);
    cin.getline(T.course.c_Name, 20);
    T.id = teachers_ids.top();
    T.course.c_id = T.id;
    teachers_ids.pop();
    outFile.write((char *)&T, sizeof(T));
    outFile.close();
    setcolor(1);
    Beep(500, 500);

    print(25, ' ') << "\aAdding Done Succesfully ... your id is: " << T.id << "\n";
    press_any();
    cout << "\n";
    return Returning();
}

void Remove_Teacher()
{
    print_logo("Remove Teacher");
    int tea_id;
    setcolor(2);
    print(35, ' ') << "Enter Teacher's ID to Delete: ";
    setcolor(6);
    cin >> tea_id;
    Teacher T;
    ifstream inFile("Teachers.txt", ios ::in);

    if (!inFile.is_open())
    {
        setcolor(12);
        print(25, ' ') << "\aError here ... There is no Teacher to Remove!, Please Read the Readme.txt file and try again\n";
        press_any();
        cout << "\n";
        Returning();
    }
    ofstream outFile("TeacherCopy.txt", ios::out);
    bool exist = false;
    inFile.read((char *)&T, sizeof(T));
    while (!inFile.eof())
    {
        if (tea_id != T.id)
        {
            outFile.write((char *)&T, sizeof(T));
        }
        else
        {
            teachers_ids.push(T.id);
            exist = true;
        }
        inFile.read((char *)&T, sizeof(T));
    }
    inFile.close();
    outFile.close();
    remove("Teachers.txt");
    rename("TeacherCopy.txt", "Teachers.txt");
    
    if (exist)
    {
        setcolor(1);
        Beep(500, 500);
        cout << "\n";
        print(25, ' ') << "\aRemoved Successfully :) \n";

        ifstream StudentFile("Student.txt", ios::in);
        ofstream Temp("Temp.txt", ios::out);
        Student s1;
        if (!StudentFile.is_open())
        {
            Temp.close();
            remove("Temp.txt");
            return;
        }
        StudentFile.read((char *)&s1, sizeof(s1));
        while (!StudentFile.eof())
        {
            Course newCourses[10];
            int j = -1;
            for (int k = 0; k <= s1.NumOfCourses; k++)
            {
                if (tea_id != s1.courses[k].c_id)
                    newCourses[++j] = s1.courses[k];
            }

            s1.NumOfCourses = j;

            for (int k = 0; k <= s1.NumOfCourses; k++)
            {
                s1.courses[k] = newCourses[k];
            }

            Temp.write((char *)&s1, sizeof(s1));
            StudentFile.read((char *)&s1, sizeof(s1));
        }
        StudentFile.close();
        Temp.close();
        remove("Student.txt");
        rename("Temp.txt", "Student.txt");
        
    }
    else
    {
        Beep(500, 500);
        cout << "\n";
        print(25, ' ') << "\aTeacher not found, Please Try again! \n";
        press_any();
        cout << "\n";
        return Returning();
    }
}

void Edit_Teacher()
{
    //ShowAllTeacher();
    print(10, '\n');
    Teacher T, Tec_Stu;
    fstream inFile;
    inFile.open("Teachers.txt", ios::in | ios::out);
    if (!inFile.is_open())
    {
        setcolor(12);
        return void(cout << "\aFile cannot be oppend :)");
    }
    print_logo("Edit Teacher");
    setcolor(2);
    int tea_id;

    print(25, ' ') << "Enter a Teacher's id to edit : ";
    setcolor(6);
    cin >> tea_id;
    bool exist = false;
    cout << "\n\n";
    ofstream outFile("TeacherCopy.txt", ios::out);

    inFile.read((char *)&T, sizeof(T));
    while (!inFile.eof())
    {
        if (T.id == tea_id)
        {
            char ch;
            
            setcolor(2);
            print(35, ' ') << "Do You Want To Change The Name (Y / N): ";
            setcolor(6);
            cin >> ch;
            cin.ignore();
            if (ch == 'Y' || ch == 'y')
            {
                setcolor(2);
                print(40, ' ') << "Enter the new Name : ";
                setcolor(6);
                //for(int i = 0 ; i < 20 ; i++)       T.name[i] = '\0';
                cin.getline(T.name, 20);
            }
            setcolor(2);

            print(35, ' ') << "Do You Want To Change The age (Y / N) : ";
            setcolor(6);
            cin >> ch;
            if (ch == 'Y' || ch == 'y')
            {
                setcolor(2);
                print(40, ' ') << "Enter the new age : ";
                setcolor(6);
                cin >> T.age;
            }
            setcolor(2);
            print(35, ' ') << "Do You Want To Change The Course's Name (Y / N): ";
            setcolor(6);
            cin >> ch;
            cin.ignore();
            if (ch == 'Y' || ch == 'y')
            {
                setcolor(2);
                print(40, ' ') << "Enter the new Course's Name : ";
                setcolor(6);
                cin.getline(T.course.c_Name, 20);
            }
        
            setcolor(2);
            cout << "\n";

        
            cout << "\n";
            setcolor(2);
            print(35, ' ') << "ID\t\t"
                            << "Name\t\t"
                            << "age\t\t"
                            << "Course\n";
            exist = true;
            print(35, ' ');
            print(73, '-') << "\n";
            print(35, ' ') << T.id << "\t\t" << T.name << "\t\t" << T.age << "\t\t" << T.course.c_Name << "\n";

            //Here
            // int curPos = inFile.tellg();
            // int stuSz = sizeof(T);
            // inFile.seekp(curPos - stuSz, ios::beg);
            // inFile.write((char *)&T, sizeof(T));
            // inFile.seekg(curPos - stuSz, ios::beg);
            // //Here
            exist = 1;
            Tec_Stu = T;
        }
        outFile.write((char*)&T, sizeof(T));
        inFile.read((char *)&T, sizeof(T));
    }
    outFile.close();
    inFile.close();
    remove("Teachers.txt");
    rename("TeacherCopy.txt", "Teachers.txt");
    if(exist)
    {
        // To edit in files
        Student S1;
        fstream to_edit("Student.txt", ios::in | ios::out);
        to_edit.read((char *)&S1, sizeof(S1));
        while (to_edit)
        {
            for (int i = 0; i <= S1.NumOfCourses; i++)
            {
                if (S1.courses[i].c_id == Tec_Stu.id)
                {
                    S1.courses[i] = Tec_Stu.course;
                    int curPos = to_edit.tellg();
                    int stuSz = sizeof(S1);
                    to_edit.seekp(curPos - stuSz, ios::beg);
                    to_edit.write((char *)&S1, sizeof(S1));
                    break;
                }
            }
            to_edit.read((char *)&S1, sizeof(S1));
        }
        to_edit.close();
    }
    else{
        setcolor(12);
        Beep(500, 500);
        print(35, ' ') << "The Id You Entered Does Not Exist :) \n";
        press_any();
        cout << "\n";
    }
    // /* debug */
    // inFile.open("Teachers.txt", ios::in | ios::out);
    // inFile.read((char *)&T, sizeof(T));
    // cout << "Debugging\n";
    // while (inFile) {
    //     print(35, ' ') << T.id << "\t\t" << T.name << "\t\t" << T.age << "\t\t" << T.course.c_Name << "\n";
    //     inFile.read((char *)&T, sizeof(T));
    // }
    // press_any();
    // /* dbug */
    return Returning();
}


void Print_Ctrl_Stu()
{
    setcolor(2);
    print_logo("Student Page");
    print(25, ' ') << "Choose : \n\n";
    print(40, ' ') << char(201);
    for (int i = 0; i < 23; i++)
    {
        cout << char(205);
    }
    cout << char(187) << endl;
    print(40, ' ') << char(186) << "  1- Show All Students " << char(186) << endl;
    print(40, ' ') << char(186) << "  2- Search Student    " << char(186) << endl;
    print(40, ' ') << char(186) << "  3- Add               " << char(186) << endl;
    print(40, ' ') << char(186) << "  4- Remove            " << char(186) << endl;
    print(40, ' ') << char(186) << "  5- Edit              " << char(186) << endl;
    setcolor(12);
    print(40, ' ') << char(186) << "  6- Return            " << char(186) << endl;
    print(40, ' ') << char(200);
    for (int i = 0; i < 23; i++)
    {
        cout << char(205);
    }
    cout << char(188) << endl;
    setcolor(2);
}

void ShowAllStudent()
{
    setcolor(2);
    Student s1;
    ifstream file;
    file.open("Student.txt", ios::in);
    setcolor(12);
    if (!file.is_open())
    {
        print(0, '\n');
        print(25, ' ') << "\aError here ... There is no Student!, Please Read the Readme.txt file and try again\n";
        press_any();
        cout << "\n";
        Returning();
        return;
    }

    else
    {
        setcolor(2);
        print_logo("Show All Students", 50);
        bool printed = 1;
        file.read((char *)&s1, sizeof(s1));
        while (!file.eof())
        {
            setcolor(6);
            if (printed)
            {
                print(35, ' ') << "ID\t\tPassword\tName\t\tAge\t\tLevel\t\tDepartment\n";
                print(35, ' ') << "--\t\t--------\t----\t\t---\t\t-----\t\t----------\n";
            }
            print(35, ' ') << s1.id << "\t\t" << s1.password << "\t\t" << s1.name << "\t\t" << s1.age << "\t\t" << s1.level << "\t\t" << s1.Dep << "\n", printed = 0;
            file.read((char *)&s1, sizeof(s1));
        }
        if (printed)
        {
            setcolor(12);
            print(25, ' ') << "\aError here ... There is no Student to Search for!, Please Read the Readme.txt file and try again\n";
            press_any();
            cout << "\n";
            Returning();
            setcolor(6);
            return;
        }
    }
    press_any();
    Directing();
}

void SearchStudent()
{
    
    setcolor(2);
    print_logo("Search for Student");
    int stu_id;
    
    print(35, ' ') << "Enter the ID of the student to search for: ";
    setcolor(6);
    cin >> stu_id;

    Student s1;
    ifstream inFile;
    inFile.open("Student.txt", ios ::in);
    if (!inFile.is_open())
    {
        setcolor(6);
        print(25, ' ') << "\aError here ... There is no Student to Search for!, Please Read the Readme.txt file and try again\n";
        press_any();
        return Returning();
    }
    bool exist = 0;
    // Read first to ignore last deplicated objects
    inFile.read((char *)&s1, sizeof(s1));
    setcolor(2);
    while (!inFile.eof())
    { // While the file not ended
        if (s1.id == stu_id)
        {
            setcolor(6);
            print(35, ' ') << "ID\t\tPassword\tName\t\tAge\t\tLevel\t\tDepartment\n";
            print(35, ' ') << "--\t\t--------\t----\t\t---\t\t-----\t\t----------\n";
            print(35, ' ') << s1.id << "\t\t" << s1.password << "\t\t" << s1.name << "\t\t " << s1.age << "\t\t " << s1.level << ""
                           << "\t\t"
                           << "\t\t" << s1.Dep,
                exist = 1;
        }
        inFile.read((char *)&s1, sizeof(s1));
    }
    setcolor(12);
    if (!exist && print(35, ' ') << "\aStudent not found, Please try again!\n")
        ;
    inFile.close();
    cout << "\n";
    press_any();
    cout << "\n";

    if (!exist)
        Returning();
    else
        Directing();
}

void Add_Student()
{
    Student s1;
    ofstream file1;
    print_logo("Add Student");
    file1.open("Student.txt", ios::out | ios::app);
    char ch;
    do
    {
        setcolor(2);
        print(35, ' ') << "Enter student's Name: ";
        setcolor(6);
        cin.ignore();
        cin.getline(s1.name, 20);
        setcolor(2);
        print(35, ' ') << "Enter student's Password: ";
        setcolor(6);
        set_Password(s1.password);
        setcolor(2);
        print(35, ' ') << "Enter student's Age: ";
        setcolor(6);
        cin >> s1.age;
        setcolor(2);
        print(35, ' ') << "Enter student's Level: ";
        setcolor(6);
        cin >> s1.level;
        setcolor(2);
        print(35, ' ') << "Enter student's Department: ";
        setcolor(6);
        cin >> s1.Dep;
        s1.id = students_ids.top();
        students_ids.pop();
        file1.write((char *)&s1, sizeof(s1));
        setcolor(5);
        Beep(500, 500);
        print(25, ' ') << "\aAdding Done Succesfully ... your id is: ";
        setcolor(2);
        cout << s1.id << "\n";
        setcolor(2);
        print(25, ' ') << "\nDo you want to enter antother records? (Y/ N): ";
        setcolor(6);
        cin >> ch;
        cout << "\n";
    } while (ch == 'Y' || ch == 'y');
    file1.close();
    press_any();
    Returning();
}

void Remove_Student()
{
    print_logo("Remove Student");
    int stu_id;
    setcolor(2);
    print(35, ' ') << "Enter the ID of the student to Delete: ";
    setcolor(6);
    cin >> stu_id;
    int id_s_r = stu_id;
    Student s1;
    ifstream inFile("Student.txt", ios ::in);

    if (!inFile.is_open())
    {
        setcolor(12);
        print(25, ' ') << "\aError here ... There is no Student!, Please Read the Readme.txt file and try again\n";
        press_any();
        Returning();
        return;
    }
    ofstream outFile("Temp.txt", ios::out);
    bool exist = 0;
    // Read first to ignore last deplicated objects
    inFile.read((char *)&s1, sizeof(s1));
    while (!inFile.eof())
    { // While the file not ended
        if (stu_id != s1.id)
        {
            outFile.write((char *)&s1, sizeof(s1));
        }
        else
        {
            students_ids.push(s1.id);
            exist = 1;
        }
        inFile.read((char *)&s1, sizeof(s1));
    }
    inFile.close();
    outFile.close();
    remove("Student.txt");
    rename("Temp.txt", "Student.txt");
    //
    if (exist)
    {
        fstream to_remove("Teachers.txt", ios::in);
        fstream to_replace("cpy_Teachers.txt", ios::out);
        Teacher t1;
        to_remove.read((char *)&t1, sizeof(t1));
        while (to_remove)
        {
            Student New_tec_stu[200];
            int j = -1;
            for (int i = 0; i <= t1.NumOfStudents; i++)
            {
                if (t1.Tec_Stu[i].id != stu_id)
                    New_tec_stu[++j] = t1.Tec_Stu[i];
            }
            t1.NumOfStudents = j;
            for (int i = 0; i <= t1.NumOfStudents; i++)
                t1.Tec_Stu[i] = New_tec_stu[i];

            to_replace.write((char *)&t1, sizeof(t1));
            to_remove.read((char *)&t1, sizeof(t1));
        }
        to_remove.close();
        to_replace.close();
        cout << "Teahcers.txt is removed\n";
        remove("Teachers.txt");
        // cout << "cpy_Teachers.txt renamed to Teahcers.txt\n";
        rename("cpy_Teachers.txt", "Teachers.txt");
    }
    //
    if (exist)
    {
        setcolor(2);
        print(35, ' ') << "the student whose id is ";
        setcolor(6);
        cout << stu_id;
        setcolor(2);
        Beep(500, 500);
        cout << " has been deleted\n";
    }
    Sleep(1000);
    system("CLS");
    Directing();
}

void Edit_Student()
{
    Student s1;
    fstream inFile, Temp;
    inFile.open("Student.txt", ios::in | ios::out);
    if (!inFile.is_open())
    {
        setcolor(12);
        print(25, ' ') << "\aError here ... There is no Student!, Please Read the Readme.txt file and try again\n";
        press_any();
        Returning();
        return;
    }
    int stu_id;
    setcolor(2);
    print_logo("Edit Teacher");
    print(35, ' ') << "Enter the ID of the student to Edit: ";
    setcolor(6);
    cin >> stu_id;
    bool exist = 0;
    inFile.read((char *)&s1, sizeof(s1));
    while (!inFile.eof())
    {
        if (stu_id == s1.id)
        {
            setcolor(2);
            print(35, ' ') << "Enter student's Age: ";
            setcolor(6);
            cin >> s1.age;
            setcolor(2);
            print(35, ' ') << "Enter student's Level: ";
            setcolor(6);
            cin >> s1.level;
            setcolor(2);
            print(35, ' ') << "Enter student's Department: ";
            setcolor(6);
            cin >> s1.Dep;
            int curPos = inFile.tellg();
            int stuSz = sizeof(s1);
            inFile.seekp(curPos - stuSz, ios::beg);
            inFile.write((char *)&s1, sizeof(s1));

            inFile.seekg(curPos - stuSz, ios::beg);
            setcolor(2);
            print(35, ' ') << "ID\t\tPassword\tName\t\tAge\t\tLevel\t\tDepartment\n";
            print(35, ' ') << "--\t\t--------\t----\t\t---\t\t-----\t\t----------\n";
            setcolor(6);
            print(35, ' ') << s1.id << "\t\t" << s1.password << "\t\t" << s1.name << "\t\t" << s1.age << "\t\t" << s1.level << "\t\t" << s1.Dep, exist = 1;
            exist = 1;
            break;
        }
        inFile.read((char *)&s1, sizeof(s1));
    }
    if (exist)
    {
        fstream to_edit("Teachers.txt", ios::in | ios::out);
        Temp.open("TeachersCopy.txt", ios::out);
        Teacher t1;

        to_edit.read((char *)&t1, sizeof(t1));
        while (to_edit)
        {
            for (int i = 0; i <= t1.NumOfStudents; i++)
            {
                if (t1.Tec_Stu[i].id == stu_id)
                {
                    t1.Tec_Stu[i] = s1;
                    // int curPos = to_edit.tellg();
                    // int stuSz = sizeof(t1);
                    // to_edit.seekp(curPos - stuSz, ios::beg);
                    // to_edit.write((char *)&t1, sizeof(t1));
                    // break;
                }
            }
            Temp.write((char*)& t1, sizeof(t1));
            to_edit.read((char *)&t1, sizeof(t1));
        }
        Temp.close();
        to_edit.close();
        remove("Teachers.txt");
        rename("TeachersCopy.txt", "Teachers.txt");
    }
    setcolor(12);
    if (!exist && cout << "\aNot found\n")
        inFile.close();
    system("CLS");
    Directing();
}

void Ch_Admin()
{

    int Reg_sign;
    print(0, '\n');
    setcolor(2);
    print(25, ' ') << "Choose : \n\n";
    print(40, ' ') << char(201);
    for (int i = 0; i < 18; i++)
    {
        cout << char(205);
    }
    cout << char(187) << endl;

    print(40, ' ') << char(186) << "  1- Sign in      " << char(186) << endl;
    setcolor(12);
    print(40, ' ') << char(186) << "  2- Return Back  " << char(186) << endl;
    print(40, ' ') << char(200);
    for (int i = 0; i < 18; i++)
    {
        cout << char(205);
    }
    cout << char(188) << endl;

    setcolor(2);
    cout << "\n\n";
    print(20, ' ') << "Choice : ";
    setcolor(6);
    cin >> Reg_sign;
    cout << "\n"
         << string(35, ' ');
    (Reg_sign == 2 ? Returning() : Directing());

    if (Reg_sign == 1)
    {
        bool found = 0;
        int id;
        char pass[10];
        setcolor(2);
        print_logo("Admin Login Page", 40);
        print(25, ' ') << "Enter: \n\n";
        print(35, ' ') << "ID: ";
        setcolor(6);
        cin >> id;
        setcolor(2);
        print(35, ' ') << "Password: ";
        setcolor(6);
        set_Password(pass);
        
        Directing();
        // 1 TODO: Checking Valid ID and Password for admin
        found = 1;
        if (found)
        {
            do
            {
                setcolor(2);
                int Admin_choice;
                Print_Admin_Menu();
                setcolor(6);
                cin >> Admin_choice;
                if (Admin_choice == 1)
                {
                    Directing();
                    // Control Teacher
                    int Ad_Teac_choice;
                    do
                    {    
                        
                        Print_Ctrl_Tec();
                        print(15, ' ') << "Choice : ";
                        setcolor(6);
                        cin >> Ad_Teac_choice;
                        
                        if (Ad_Teac_choice == 1)
                        {
                            Directing();
                            ShowAllTeacher();
                        }
                        else if (Ad_Teac_choice == 2)
                        {
                            Directing();
                            SearchTeacher();
                        }
                        else if (Ad_Teac_choice == 3)
                        {
                            Directing();
                            Add_Teacher();
                        }
                        else if (Ad_Teac_choice == 4)
                        {
                            Directing();
                            Remove_Teacher();
                        }
                        else if (Ad_Teac_choice == 5)
                        {
                            Directing();
                            Edit_Teacher();
                        }
                        else if (Ad_Teac_choice >= 6)
                        {
                            Returning();
                            break;
                        }
                    } while (1);
                }
                else if (Admin_choice == 2)
                {
                    Directing();
                    // Control Student
                    int Ad_Stud_choice;
                    do
                    {

                        Print_Ctrl_Stu();
                        print(25, ' ') << "Choice : ";
                        setcolor(6);
                        cin >> Ad_Stud_choice;
                        
                        if (Ad_Stud_choice == 1)
                        {
                            Directing();
                            ShowAllStudent();
                        }
                        else if (Ad_Stud_choice == 2)
                        {
                            Directing();
                            SearchStudent();
                        }
                        else if (Ad_Stud_choice == 3)
                        {
                            Directing();
                            Add_Student();
                        }
                        else if (Ad_Stud_choice == 4)
                        {
                            Directing();
                            Remove_Student();
                        }
                        else if (Ad_Stud_choice == 5)
                        {
                            Directing();
                            Edit_Student();
                        }
                        else if (Ad_Stud_choice >= 6)
                        {
                            Returning();
                            break;
                        }

                    } while (1);
                }
                else if (Admin_choice >= 3){
                    Returning();
                    break;
                }
            } while (1);
        }
    }
    else
        return;
}
