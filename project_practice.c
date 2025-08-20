
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <windows.h>
#define MAX_SEMESTERS 12
#define MAX_COURSES 12
#define FILENAME "cgpa_data.txt"

// Structure to store course information
struct Course {
    char name[50];
    int  creditHours;
    float marks;
};


// Structure to store semester data
struct Semester {
    struct Course courses[MAX_COURSES];
    int courseCount;
    float sgpa;
};

// Global variables
struct Semester semesters[MAX_SEMESTERS];
int semesterCount = 0;
float cgpa = 0.0;

// Function prototypes
void showLoadingScreen();
void displayMenu();
void handleMainMenu();
void handleSemesterMenu();
void inputCourseDetails();
void calculateSGPA();
void calculateCGPA();
void displayResults();
void saveToFile();
void loadFromFile();
void displayHelp();
void clearScreen();
float getGradePoint(float marks);
void displaySemesterReport(int semesterIndex);
void printCenteredText(const char *text);
void printBoxedText(const char *text);
void animateProgressBar(int duration);
void displayStats();
void sortCoursesByName();
void sortCoursesByMarks();
void editCourseDetails();
void deleteCourse();
void searchCourse();
void resetSystem();

int main() {
    setColor(10, 0);
    FILE *fp;
    char username[20], password[20];
    char storedUsername[20], storedPassword[20];

    // Step 1: Write username and password to file
    fp = fopen("login.txt", "w");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return 1;
    }
     clearScreen();
     printf("                                            |================================|\n");//
     printf("                                                          SIGN IN              \n");
      printf("                                            |================================|\n");//
    printf("                                                    Set your Username:");
    scanf("%s", username);
    printf("                                                    Set your Password:");
    scanf("%s", password);
     printf("                                            |================================|\n");//

    fprintf(fp, "%s %s", username, password);
    animateProgressBar(1);

    system("cls");
    fclose(fp);
animateProgressBar(2);

setColor(1, 0);
    printf("                                            |================================|\n");// Step 2: Ask for login
    printf("                                            |           Login                |\n");
    printf("                                            |================================|\n");


    printf("                                                     Enter Username:");
    scanf("%s", username);
    printf("                                                     Enter Password: ");
    scanf("%s", password);
    printf("                                            |================================|\n");
setColor(10, 0);
    // Step 3: Read from file and validate
    fp = fopen("login.txt", "r");
    if (fp == NULL) {
        printf("                                                 Error opening file!\n");
        return 1;
    }

    fscanf(fp, "%s %s", storedUsername, storedPassword);
    fclose(fp);

    if (strcmp(username, storedUsername) == 0 && strcmp(password, storedPassword) == 0) {
        printf("\nLogin Successful!\n");
    } else {
        printf("\nInvalid Username or Password.\n");
        return;
    }

    showLoadingScreen();
    clearScreen();

    // Load previous data if available
    loadFromFile();

    while(1) {
        displayMenu();
        handleMainMenu();
    }

    return 0;
}
void setColor(int textColor, int bgColor) {
    int colorCode = bgColor * 16 + textColor;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colorCode);
}

void showLoadingScreen() {


    clearScreen();
        setColor(10, 0);// Green text, black background

    printf("                        =================================================================\n");
    printf("                        |                      C G P A  C A L C U L A T O R             |\n");
    printf("                        =================================================================\n");

    printf("\n\n");
    printf("                        =================================================================\n");
    printf("                                   PLEASE WAIT OUR SYSTEM IS LOADING ");
animateProgressBar(2);

    printf("                                    Loading data modules");
animateProgressBar(2);

    printf("                                    Starting calculator engine");
    animateProgressBar(2);

    printf("\n");
    setColor(4,0);
    printf("                                     System Ready!");

    printf("\n");
    setColor(10,0);
    printf("                         =================================================================\n");
    #if defined(_WIN32)
        _sleep(1000);
    #else
        usleep(1000000);
    #endif
}

void displayMenu() {
    clearScreen();
    printf("                                    =================================================================\n");
    printf("                                    |                                                               |\n");
    printf("                                    |                      CGPA CALCULATOR SYSTEM                   | \n");
    printf("                                    |                                                               |\n");
    printf("                                    =================================================================\n");
    printf("                                    =================================================================\n");
    printf("                                                        Current CGPA: %.2f | Semesters: %d\n\n", cgpa, semesterCount);
    printf("                                    |                                                               |\n");
    printf("                                    |                         Main Menu:                            |\n");
    printf("                                    |                                                               |\n");
    printf("                                    |                        1. Add New Semester Data               |\n");
    printf("                                    |                                                               |\n");
    printf("                                    |                        2. View All Semester Results           |\n");
    printf("                                    |                                                               |\n");
    printf("                                    |                        3. Semester Operations                 |\n");
    printf("                                    |                                                               |\n");
    printf("                                    |                        4. System Statistics                   |\n");
    printf("                                    |                                                               |\n");
    printf("                                    |                        5. Save Data to File                   |\n");
    printf("                                    |                                                               |\n");
    printf("                                    |                        6. Load Data from File                 |\n");
    printf("                                    |                                                               |\n");
    printf("                                    |                        7. Help & Instructions                 |\n");
    printf("                                    |                                                               |\n");
    printf("                                    |                        8. Reset System                        |\n");
    printf("                                    |                                                               |\n");
    printf("                                    |                        9. Exit                                |\n\n");
    printf("                                    =================================================================\n");
    setColor(4, 0);
    printf("                                                             Enter your choice (1-9): ");
    setColor(10, 0);
}

void handleMainMenu() {
    int choice;
    scanf("%d", &choice);

    switch(choice) {
        case 1:
            inputCourseDetails();
            break;
        case 2:
            displayResults();
            break;
        case 3:
            handleSemesterMenu();
            break;
        case 4:
            displayStats();
            break;
        case 5:
            saveToFile();
            break;
        case 6:
            loadFromFile();
            break;
        case 7:
            displayHelp();
            break;
        case 8:
            resetSystem();
            break;
        case 9:
            printf("Saving data before exit...\n");
            saveToFile();
            printf("Thank you for using CGPA Calculator!\n");
            exit(0);
        default:
            printf("Invalid choice. Please enter a number between 1-9.\n");
            printf("Press Enter to continue...");
            getchar(); getchar();
    }
}

void handleSemesterMenu() {
    if(semesterCount == 0) {
        printf("No semester data available. Please add data first.\n");
        printf("Press Enter to continue...");
        getchar(); getchar();
        return;
    }

    while(1) {
        clearScreen();
        setColor(10, 0);
        printf("                                =================================================================\n");
        printf("                                |                                                               |\n");
        printf("                                |                      SEMESTER OPERATIONS                      |\n");
        printf("                                |                                                               |\n");
        printf("                                =================================================================\n\n");
        printf("                                |                                                               |\n");
        printf("                                |             1. View Semester Report                           |\n");
        printf("                                |             2. Edit Course Details                            |\n");
        printf("                                |             3. Delete Course                                  |\n");
        printf("                                |             4. Search Course                                  |\n");
        printf("                                |             5. Sort Courses in Semester                       |\n");
        printf("                                |             6. Back to Main Menu                              |\n\n");
        printf("                                =================================================================\n\n");
setColor(4, 0);
        printf("                                         Select semester (1-%d) or 0 to cancel: ", semesterCount);
        setColor(10, 0);
        int semChoice;
        scanf("%d", &semChoice);

        if(semChoice == 0) return;
        if(semChoice < 1 || semChoice > semesterCount) {
            printf("                                      Invalid semester selection!\n");
            printf("                                      Press Enter to continue...");
            getchar(); getchar();
            continue;
        }

        int semIndex = semChoice - 1;
        printf("                                =================================================================\n");
        printf("                                |                1. View Semester %d Report                     |\n", semChoice);
        printf("                                |                2. Edit Course Details in Semester %d          |\n", semChoice);
        printf("                                |                3. Delete Course from Semester %d              |\n", semChoice);
        printf("                                |                4. Search Course in Semester %d                |\n", semChoice);
        printf("                                |                5. Sort Courses in Semester %d                 |\n", semChoice);
        printf("                                |                6. Back to Semester Selection                 |\n\n");
        printf("                                =================================================================\n");
        setColor(4, 0);
        printf("                                                 Enter your choice (1-6): ");
        setColor(10, 0);
        int opChoice;
        scanf("%d", &opChoice);

        switch(opChoice) {
            case 1:
                displaySemesterReport(semIndex);
                break;
            case 2:
                editCourseDetails(semIndex);
                break;
            case 3:
                deleteCourse(semIndex);
                break;
            case 4:
                searchCourse(semIndex);
                break;
            case 5:
                setColor(1,0);
                printf("\n                                            Sort by:\n");
                printf("                                              1. Course Name\n");
                printf("                                              2. Marks\n");
                printf("                                              Enter choice: ");
                int sortChoice;
                scanf("%d", &sortChoice);

                if(sortChoice == 1) {
                    sortCoursesByName(semIndex);
                } else if(sortChoice == 2) {
                    sortCoursesByMarks(semIndex);
                } else {
                    setColor(4,0);
                    printf("                                         Invalid choice!\n");
                }
                setColor(10,0);
                printf("                                             Sorting completed.\n");
                printf("                                             Press Enter to continue...");
                getchar(); getchar();
                break;
            case 6:
                break;
            default:
                setColor(4,0);
                printf("                                            Invalid choice!\n");
                setColor(10,0);
                printf("                                            Press Enter to continue...");
                getchar(); getchar();
        }
    }
}

void inputCourseDetails() {
    clearScreen();
    setColor(10, 0);
    printf("                                    =================================================================\n");
    printf("                                    |                                                               |\n");
    printf("                                    |                    ADD NEW SEMESTER DATA                      | \n");
    printf("                                    |                                                               |\n");
    printf("                                    =================================================================\n\n");
 setColor(1, 0);
    if(semesterCount >= MAX_SEMESTERS) {

        printf("                                   Maximum number of semesters (%d) reached!\n", MAX_SEMESTERS);
        printf("                                   Press Enter to continue...");
        getchar(); getchar();
        return;
    }

    setColor(1, 0);

    int currentSem = semesterCount;

    printf("                                       Entering details for Semester %d\n\n", currentSem + 1);

    printf("                                       Enter number of courses (max %d): ", MAX_COURSES);
    scanf("%d", &semesters[currentSem].courseCount);

    if(semesters[currentSem].courseCount <= 0 || semesters[currentSem].courseCount > MAX_COURSES) {
         setColor(4, 0);
        printf("                                    Invalid number of courses!\n");
    setColor(10, 0);
        printf("                                    Press Enter to continue...");
        getchar(); getchar();
        return;
    }

    for(int i = 0; i < semesters[currentSem].courseCount; i++) {
        printf("                                    |=================================================================|\n");
        setColor(4, 0);

        printf("\n                                                    Course %d:\n", i+1);
        setColor(1, 0);

        printf("                                                       Name: ");

        scanf("%s", semesters[currentSem].courses[i].name);

        printf("                                                       Credit Hours: ");

        scanf("%d", &semesters[currentSem].courses[i].creditHours);
        printf("                                                       Marks (out of 100): ");

        scanf("%f", &semesters[currentSem].courses[i].marks);

    }
        printf("                                    |=================================================================|\n");
    // Calculate SGPA for this semester
    calculateSGPA(currentSem);
    // Update CGPA
    calculateCGPA();

    semesterCount++;
    setColor(1, 0);
    printf("                                      =================================================================\n");
    printf("                                     |                                                                |\n");
    printf("                                     |         Data for Semester %d added successfully!                |\n", currentSem + 1);
    printf("                                     |                                                                |\n");
    printf("                                     |         Calculated SGPA: %.2f                                  |\n", semesters[currentSem].sgpa);
    printf("                                     |                                                                |\n");
    printf("                                     |         Updated CGPA: %.2f                                     |\n", cgpa);
    printf("                                     |                                                                |\n");
    printf("                                      =================================================================\n");
setColor(10, 0);
    printf("                                                Press Enter to continue...");
    getchar(); getchar();
    setColor(10, 0);
}

void calculateSGPA(int semesterIndex) {
    float totalPoints = 0;
    int totalCredits = 0;

    for(int i = 0; i < semesters[semesterIndex].courseCount; i++) {
        float gradePoint = getGradePoint(semesters[semesterIndex].courses[i].marks);
        totalPoints += gradePoint * semesters[semesterIndex].courses[i].creditHours;
        totalCredits += semesters[semesterIndex].courses[i].creditHours;
    }

    semesters[semesterIndex].sgpa = (totalCredits > 0) ? (totalPoints / totalCredits) : 0.0;
}

void calculateCGPA() {
    float totalPoints = 0;
    int totalCredits = 0;

    for(int i = 0; i < semesterCount; i++) {
        for(int j = 0; j < semesters[i].courseCount; j++) {
            float gradePoint = getGradePoint(semesters[i].courses[j].marks);
            totalPoints += gradePoint * semesters[i].courses[j].creditHours;
            totalCredits += semesters[i].courses[j].creditHours;
        }
    }

    cgpa = (totalCredits > 0) ? (totalPoints / totalCredits) : 0.0;
}

float getGradePoint(float marks) {
    if(marks >= 80) return 4.00;
    if(marks >= 75) return 3.75;
    if(marks >= 70) return 3.50;
    if(marks >= 65) return 3.25;
    if(marks >= 60) return 3.00;
    if(marks >= 55) return 2.75;
    if(marks >= 50) return 2.50;
    if(marks >= 45) return 2.25;
    if(marks >= 40) return 2.00;
    if(marks <= 39) return 0.00;
    return 0.0;
}

void displayResults() {
    clearScreen();
    setColor(10, 0);
    printf("                        =================================================================\n");
    printf("                        |                                                               |\n");
    printf("                        |                   SEMESTER RESULTS SUMMARY                    |\n");
    printf("                        |                                                               |\n");
    printf("                        =================================================================\n\n");

    if(semesterCount == 0) {
            setColor(4,0);
        printf("                                     No semester data available.\n");
    setColor(10, 0);
    } else {
        printf("Current CGPA: %.2f\n\n", cgpa);

        for(int i = 0; i < semesterCount; i++) {
            printf("Semester %d - SGPA: %.2f\n", i+1, semesters[i].sgpa);
            printf("--------------------------------------------------------------\n");
            printf("%-5s %-30s %-8s %-6s %6s\n", "No.", "Course Name", "Credits", "Marks", "Grade");

            for(int j = 0; j < semesters[i].courseCount; j++) {
                float gradePoint = getGradePoint(semesters[i].courses[j].marks);
                printf("%-5d %-30s %-8d %-6.1f %6.1f\n",
                      j+1,
                      semesters[i].courses[j].name,
                      semesters[i].courses[j].creditHours,
                      semesters[i].courses[j].marks,
                      gradePoint);
            }
            printf("\n");
        }
    }

    printf("\nPress Enter to continue...");
    getchar(); getchar();
}

void displaySemesterReport(int semesterIndex) {
    clearScreen();
    setColor(10, 0);
    printf("                          =================================================================\n");
    printf("                          |                                                               |\n");
    printf("                          |                    SEMESTER %d DETAILED REPORT                |\n", semesterIndex+1);
    printf("                          |                                                               |\n");
    printf("                          =================================================================\n\n");

    printf("SGPA: %.2f\n\n", semesters[semesterIndex].sgpa);

    printf("%-5s %-30s %-8s %-6s %6s %10s\n",
          "No.", "Course Name", "Credits", "Marks", "Grade", "Points");

    float totalPoints = 0;
    int totalCredits = 0;

    for(int i = 0; i < semesters[semesterIndex].courseCount; i++) {
        float gradePoint = getGradePoint(semesters[semesterIndex].courses[i].marks);
        float coursePoints = gradePoint * semesters[semesterIndex].courses[i].creditHours;

        printf("%-5d %-30s %-8d %-6.1f %6.1f %10.2f\n",
              i+1,
              semesters[semesterIndex].courses[i].name,
              semesters[semesterIndex].courses[i].creditHours,
              semesters[semesterIndex].courses[i].marks,
              gradePoint,
              coursePoints);

        totalPoints += coursePoints;
        totalCredits += semesters[semesterIndex].courses[i].creditHours;
    }

    printf("\nSummary:\n");
    printf("Total Credits: %d\n", totalCredits);
    printf("Total Points: %.2f\n", totalPoints);
    printf("SGPA: %.2f\n", semesters[semesterIndex].sgpa);

    printf("\nPress Enter to continue...");
    getchar(); getchar();
}

void saveToFile() {
    FILE *file = fopen(FILENAME, "wb");
    if(file == NULL) {
        printf("Error opening file for writing!\n");
        printf("Press Enter to continue...");
        getchar(); getchar();
        return;
    }

    // Write semester count
    fwrite(&semesterCount, sizeof(int), 1, file);

    // Write each semester
    for(int i = 0; i < semesterCount; i++) {
        fwrite(&semesters[i].courseCount, sizeof(int), 1, file);
        fwrite(&semesters[i].sgpa, sizeof(float), 1, file);

        // Write each course in the semester
        for(int j = 0; j < semesters[i].courseCount; j++) {
            fwrite(&semesters[i].courses[j], sizeof(struct Course), 1, file);
        }
    }

    fclose(file);

    printf("                                                            Data saved to %s successfully!\n", FILENAME);
    printf("                                                            Press Enter to continue...");
    getchar(); getchar();
}

void loadFromFile() {
    FILE *file = fopen(FILENAME, "rb");
    if(file == NULL) {
            setColor(4,0);
        printf("No existing data file found. Starting with empty system.\n");
    setColor(10,0);
        printf("Press Enter to continue...");
        getchar(); getchar();
        return;
    }

    // Read semester count
    fread(&semesterCount, sizeof(int), 1, file);

    // Read each semester
    for(int i = 0; i < semesterCount; i++) {
        fread(&semesters[i].courseCount, sizeof(int), 1, file);
        fread(&semesters[i].sgpa, sizeof(float), 1, file);

        // Read each course in the semester
        for(int j = 0; j < semesters[i].courseCount; j++) {
            fread(&semesters[i].courses[j], sizeof(struct Course), 1, file);
        }
    }

    fclose(file);

    // Recalculate CGPA
    calculateCGPA();

    printf("                                    Data loaded from %s successfully!\n", FILENAME);
    printf("                                    Press Enter to continue...");
    getchar(); getchar();
}

void displayHelp() {
    clearScreen();
    setColor(10, 0);
    printf("                             =================================================================\n");
    printf("                             |                                                               |\n");
    printf("                             |                      HELP & INSTRUCTIONS                      | \n");
    printf("                             |                                                               |\n");
    printf("                             =================================================================\n\n");


    printf("                             =================================================================\n");
    printf("                             |                   GRADE POINT SCALE:                          |\n");
    printf("                             |                   Marks Range   | Grade Point                 |\n");
    printf("                             |                 ----------------------------                  |\n");
    printf("                             |                   80-100        | 4.00                        |\n");
    printf("                             |                   75-79         | 3.75                        |\n");
    printf("                             |                   70-74         | 3.50                        |\n");
    printf("                             |                   65-69         | 3.25                        |\n");
    printf("                             |                   60-64         | 3.00                        |\n");
    printf("                             |                   55-59         | 2.75                        |\n");
    printf("                             |                   50-54         | 2.50                        |\n");
    printf("                             |                   45-49         | 2.25                        |\n");
    printf("                             |                   40-44         | 2.00                        |\n");
    printf("                             |                   00-39         | 0.0                         |\n");
    printf("                             =================================================================\n");
    setColor(1,0);
    printf("CALCULATION FORMULAS:\n");
    printf("SGPA = (Sum of (Grade Point × Credit Hours) for all courses) / Total Credit Hours\n");
    printf("CGPA = (Sum of (Grade Point × Credit Hours) for all semesters) / Total Credit Hours\n\n");
setColor(4,0);
    printf("TIPS:\n");
    printf("- Regularly save your data to file\n");
    printf("- You can edit course details if you made any mistakes\n");
    printf("- The system automatically calculates SGPA and CGPA\n");
    printf("- For best results, enter accurate marks and credit hours\n");
setColor(10,0);
    printf("\nPress Enter to continue...");
    getchar(); getchar();
}

void clearScreen() {
    #if defined(_WIN32)
        system("cls");
    #else
        system("clear");
    #endif
}

void printCenteredText(const char *text) {
    int width = 50; // Assuming terminal width of 50 characters
    int len = strlen(text);
    int pad = (width - len) / 2;
    printf("%*s%s\n", pad, "", text);
}

void printBoxedText(const char *text) {
    int len = strlen(text);
    printf("+");
    for(int i = 0; i < len + 2; i++) printf("-");
    printf("+\n");

    printf("| %s |\n", text);

    printf("+");
    for(int i = 0; i < len + 2; i++) printf("-");
    printf("+\n");
}

void animateProgressBar(int duration) {
    int steps = 20;
    printf("[");
    for(int i = 0; i < steps; i++) {
        printf(">");
        fflush(stdout);

        int sleepTime = duration * 1000000 / steps;
        #if defined(_WIN32)
            _sleep(sleepTime / 1000);
        #else
            usleep(sleepTime);
        #endif
    }
    printf("] Done!\n");
}

void displayStats() {
    clearScreen();
    setColor(10, 0);
    printf("                        =================================================================\n");
    printf("                        |                                                               |\n");
    printf("                        |                      SYSTEM STATISTICS                        |\n");
    printf("                        |                                                               |\n");
    printf("                        =================================================================\n\n");

    int totalCourses = 0;
    int totalCredits = 0;
    float minSGPA = 4.0;
    float maxSGPA = 0.0;
    float totalSGPAs = 0.0;

    for(int i = 0; i < semesterCount; i++) {
        totalCourses += semesters[i].courseCount;
        totalSGPAs += semesters[i].sgpa;

        if(semesters[i].sgpa < minSGPA) minSGPA = semesters[i].sgpa;
        if(semesters[i].sgpa > maxSGPA) maxSGPA = semesters[i].sgpa;

        for(int j = 0; j < semesters[i].courseCount; j++) {
            totalCredits += semesters[i].courses[j].creditHours;
        }
    }

    printf("                                        Number of Semesters: %d\n", semesterCount);
    printf("                                        Total Courses: %d\n", totalCourses);
    printf("                                        Total Credit Hours: %d\n", totalCredits);

    if(semesterCount > 0) {
        printf("\n                                  SGPA Stats:\n");
        printf("                                    Highest SGPA: %.2f\n", maxSGPA);
        printf("                                    Lowest SGPA: %.2f\n", minSGPA);
        printf("                                    Average SGPA: %.2f\n", totalSGPAs / semesterCount);
    }
setColor(4,0);
    printf("\n                                        Current CGPA: %.2f\n", cgpa);
setColor(10,0);
    printf("\n                                        Press Enter to continue...");
    getchar(); getchar();
}

void sortCoursesByName(int semesterIndex) {
    for(int i = 0; i < semesters[semesterIndex].courseCount - 1; i++) {
        for(int j = 0; j < semesters[semesterIndex].courseCount - i - 1; j++) {
            if(strcmp(semesters[semesterIndex].courses[j].name,
                     semesters[semesterIndex].courses[j+1].name) > 0) {
                // Swap courses
                struct Course temp = semesters[semesterIndex].courses[j];
                semesters[semesterIndex].courses[j] = semesters[semesterIndex].courses[j+1];
                semesters[semesterIndex].courses[j+1] = temp;
            }
        }
    }
}

void sortCoursesByMarks(int semesterIndex) {
    for(int i = 0; i < semesters[semesterIndex].courseCount - 1; i++) {
        for(int j = 0; j < semesters[semesterIndex].courseCount - i - 1; j++) {
            if(semesters[semesterIndex].courses[j].marks <
               semesters[semesterIndex].courses[j+1].marks) {
                // Swap courses
                struct Course temp = semesters[semesterIndex].courses[j];
                semesters[semesterIndex].courses[j] = semesters[semesterIndex].courses[j+1];
                semesters[semesterIndex].courses[j+1] = temp;
            }
        }
    }
}

void editCourseDetails(int semesterIndex) {
    if(semesters[semesterIndex].courseCount == 0) {
            setColor(4,0);
        printf("                                    No courses in this semester!\n");
    setColor(10,0);
        printf("                                    Press Enter to continue...");
        getchar(); getchar();
        return;
    }

    while(1) {
        clearScreen();
        printf("Courses in Semester %d:\n", semesterIndex+1);
        for(int i = 0; i < semesters[semesterIndex].courseCount; i++) {
            printf("%d. %s (%.1f)\n", i+1, semesters[semesterIndex].courses[i].name,
                  semesters[semesterIndex].courses[i].marks);
        }

        printf("\nEnter course number to edit (1-%d) or 0 to cancel: ",
              semesters[semesterIndex].courseCount);
        int courseNum;
        scanf("%d", &courseNum);

        if(courseNum == 0) return;
        if(courseNum < 1 || courseNum > semesters[semesterIndex].courseCount) {
            printf("Invalid course number!\n");
            printf("Press Enter to continue...");
            getchar(); getchar();
            continue;
        }

        int courseIndex = courseNum - 1;

        printf("\nCurrent Details:\n");
        printf("Name: %s\n", semesters[semesterIndex].courses[courseIndex].name);
        printf("Credit Hours: %d\n", semesters[semesterIndex].courses[courseIndex].creditHours);
        printf("Marks: %.1f\n\n", semesters[semesterIndex].courses[courseIndex].marks);

        printf("Enter new details (leave blank to keep current):\n");

        printf("Name [%s]: ", semesters[semesterIndex].courses[courseIndex].name);
        char newName[50];
        getchar(); // Clear input buffer
        fgets(newName, 50, stdin);
        newName[strcspn(newName, "\n")] = 0;
        if(strlen(newName) > 0) {
            strcpy(semesters[semesterIndex].courses[courseIndex].name, newName);
        }

        printf("Credit Hours [%d]: ", semesters[semesterIndex].courses[courseIndex].creditHours);
        char creditInput[10];
        fgets(creditInput, 10, stdin);
        if(strlen(creditInput) > 1) { // More than just newline
            semesters[semesterIndex].courses[courseIndex].creditHours = atoi(creditInput);
        }

        printf("Marks [%.1f]: ", semesters[semesterIndex].courses[courseIndex].marks);
        char marksInput[10];
        fgets(marksInput, 10, stdin);
        if(strlen(marksInput) > 1) { // More than just newline
            semesters[semesterIndex].courses[courseIndex].marks = atof(marksInput);
        }

        // Recalculate SGPA and CGPA
        calculateSGPA(semesterIndex);
        calculateCGPA();

        printf("\nCourse details updated successfully!\n");
        printf("Press Enter to continue...");
        getchar(); getchar();
    }
}

void deleteCourse(int semesterIndex) {
    if(semesters[semesterIndex].courseCount == 0) {
        printf("No courses in this semester!\n");
        printf("Press Enter to continue...");
        getchar(); getchar();
        return;
    }

    while(1) {
        clearScreen();
        printf("Courses in Semester %d:\n", semesterIndex+1);
        for(int i = 0; i < semesters[semesterIndex].courseCount; i++) {
            printf("%d. %s\n", i+1, semesters[semesterIndex].courses[i].name);
        }

        printf("\nEnter course number to delete (1-%d) or 0 to cancel: ",
              semesters[semesterIndex].courseCount);
        int courseNum;
        scanf("%d", &courseNum);

        if(courseNum == 0) return;
        if(courseNum < 1 || courseNum > semesters[semesterIndex].courseCount) {
            printf("Invalid course number!\n");
            printf("Press Enter to continue...");
            getchar(); getchar();
            continue;
        }

        int courseIndex = courseNum - 1;

        printf("\nYou are about to delete:\n");
        printf("Course: %s\n", semesters[semesterIndex].courses[courseIndex].name);
        printf("Credit Hours: %d\n", semesters[semesterIndex].courses[courseIndex].creditHours);
        printf("Marks: %.1f\n\n", semesters[semesterIndex].courses[courseIndex].marks);

        printf("Are you sure? (y/n): ");
        char confirm;
        scanf(" %c", &confirm);

        if(confirm == 'y' || confirm == 'Y') {
            // Shift all elements after the deleted course
            for(int i = courseIndex; i < semesters[semesterIndex].courseCount - 1; i++) {
                semesters[semesterIndex].courses[i] = semesters[semesterIndex].courses[i+1];
            }

            semesters[semesterIndex].courseCount--;

            // Recalculate SGPA and CGPA
            if(semesters[semesterIndex].courseCount > 0) {
                calculateSGPA(semesterIndex);
            } else {
                semesters[semesterIndex].sgpa = 0.0;
            }
            calculateCGPA();

            printf("\nCourse deleted successfully!\n");
        } else {
            printf("\nOperation cancelled.\n");
        }

        printf("Press Enter to continue...");
        getchar(); getchar();

        if(semesters[semesterIndex].courseCount == 0) {
            printf("No more courses in this semester. Returning to menu...\n");
            printf("Press Enter to continue...");
            getchar(); getchar();
            return;
        }
    }
}

void searchCourse(int semesterIndex) {
    if(semesters[semesterIndex].courseCount == 0) {
            setColor(4,0);
        printf("No courses in this semester!\n");
    setColor(10,0);
        printf("Press Enter to continue...");
        getchar(); getchar();
        return;
    }

    clearScreen();
    printf("Enter search term (course name or part of name): ");
    char searchTerm[50];
    scanf("%s", searchTerm);

    printf("\nSearch Results in Semester %d:\n", semesterIndex+1);
    printf("-------------------------------------------------\n");

    int found = 0;
    for(int i = 0; i < semesters[semesterIndex].courseCount; i++) {
        if(strstr(semesters[semesterIndex].courses[i].name, searchTerm) != NULL) {
            printf("Course %d: %s\n", i+1, semesters[semesterIndex].courses[i].name);
            printf("Credit Hours: %d\n", semesters[semesterIndex].courses[i].creditHours);
            printf("Marks: %.1f\n", semesters[semesterIndex].courses[i].marks);
            printf("Grade Point: %.1f\n\n", getGradePoint(semesters[semesterIndex].courses[i].marks));
            found = 1;
        }
    }

    if(!found) {
            setColor(4,0);
        printf("No courses found matching '%s'\n", searchTerm);
    }
setColor(10,0);
    printf("\nPress Enter to continue...");
    getchar(); getchar();
}

void resetSystem() {
    setColor(4,0);
    printf("\nWARNING: This will delete ALL data in the system!\n");
    printf("Are you sure you want to reset? (y/n): ");
    setColor(10,0);
    char confirm;
    scanf(" %c", &confirm);

    if(confirm == 'y' || confirm == 'Y') {
        semesterCount = 0;
        cgpa = 0.0;
        printf("\n                                  System reset successfully!\n");
    } else {
        setColor(4,0);
        printf("\n                                  Reset cancelled.\n");
    }
setColor(10,0);
    printf("                                        Press Enter to continue...");
    getchar(); getchar();
}
