/*
* Student Information System 
*/

// MENU OPTIONS                                                                                                                                                   
const int NEW_COURSE = 1;
const int NEW_STUDENT = 2;
const int ADD_STUDENT_TO_COURSE = 3;
const int PRINT_ROSTER = 4;
const int PRINT_STUDENT_COURSES = 5;
const int QUIT = 6;
const int DELETE_COURSE = 7;
const int DELETE_STUDENT = 8;

// Maximum capacity of each course.                                                                                                                               
const int MAX_STUDENTS_PER_COURSE = 10;

// Maximum number of courses a student can take.                                                                                                                  
const int MAX_COURSES_PER_STUDENT = 5;

// Maximum total number of courses.                                                                                                                               
const int MAX_TOTAL_COURSES = 100;

// Maximum total number of students.                                                                                                                              
const int MAX_TOTAL_STUDENTS = 1000;


// Introduce the Student struct, just so we can use it below in the Course struct.                                                                                
struct Student;

// Struct to hold data for a single course.                                                                                                                       
struct Course {
  string name; // e.g., "Comp 11", "Comp 15", "English 150", etc.                                                                                                 
  Student* students[MAX_STUDENTS_PER_COURSE];
  int num_students; // keeps track of current number of students.                                                                                                 
};

// Struct to hold data for a single student.                                                                                                                      
struct Student {
  string name;
  Course* courses[MAX_COURSES_PER_STUDENT];
  int num_courses;
};

void run_command_loop(Course* all_courses[], Student* all_students[]);
int get_user_choice();
void make_new_course(Course* all_courses[], int* pnum_courses);
void make_new_student(Student* all_students[], int* pnum_students);
void add_student_to_course(Course* all_courses[], int num_courses, Student* all_students[], int num_students);
void print_roster(Course* all_courses[], int num_courses);
void print_student_courses(Student* all_students[], int num_students);
void clean_memory(Course* all_courses[], int num_courses, Student* all_students[], int num_students);
void delete_course(Course* all_courses[], int num_courses);
void delete_student(Student* all_students[], int num_students);

int main()
{
  // Initialize array containing pointers to all courses.                                                                                                         
  Course* all_courses[MAX_TOTAL_COURSES];

  // Initialize array containing pointers all students.                                                                                                           
  Student* all_students[MAX_TOTAL_STUDENTS];

  cout << "Welcome to miniSIS!" << endl;
  run_command_loop(all_courses, all_students);

  return 0;
}

/*                                                                                                                                                                
 * Runs command loop for miniSIS.                                                                                                                                 
 * Input 1: array (initially empty) of pointers to courses.                                                                                                       
 * Input 2: array (initially empty) of pointers to students.                                                                                                      
 */
void run_command_loop(Course* all_courses[MAX_TOTAL_COURSES], Student* all_students[MAX_TOTAL_STUDENTS])
{
  // Keep track of current number of courses and students.                                                                                                        
  int num_courses = 0;
  int num_students = 0;

  int user_choice;
  do {
    // Get user choice.                                                                                                                                           
    user_choice = get_user_choice();

    // Dispatch based on user choice.                                                                                                                             
    if (user_choice == NEW_COURSE){
      make_new_course(all_courses, &num_courses);
    }
    else if (user_choice == NEW_STUDENT){
      make_new_student(all_students, &num_students);
    }
    else if (user_choice == ADD_STUDENT_TO_COURSE){
      add_student_to_course(all_courses, num_courses, all_students, num_students);
    }
    else if (user_choice == PRINT_ROSTER){
      print_roster(all_courses, num_courses);
    }
    else if (user_choice == PRINT_STUDENT_COURSES){
      print_student_courses(all_students, num_students);
    }
    else if (user_choice == QUIT){
      clean_memory(all_courses, num_courses, all_students, num_students);
    }
    else if (user_choice == DELETE_COURSE) {
      delete_course(all_courses, num_courses);
    }
    else if (user_choice == DELETE_STUDENT) {
      delete_student(all_students, num_students);
    }
    else {
      cout << "Invalid choice " << user_choice << ". Please try again." << endl;
      cin.clear(); // clear cin's error flag.                                                                                                                     
      cin.ignore(100, '\n'); // ignore faulty input up to newline.                                                                                                
    }
  } while(user_choice != QUIT); // Keep going until user quits.                                                                                                   

  cout << "Have a nice day!" << endl;
}
/*                                                                                                                                                                
 * Prints menu to user, and returns the user's choice.                                                                                                            
 * Output: int representing user's choice.                                                                                                                        
 */
int get_user_choice()
{
   cout << "Please select a number from the menu." << endl;
   cout << NEW_COURSE << ". Create a new course." << endl;
   cout << NEW_STUDENT << ". Create a new student." << endl;
   cout << ADD_STUDENT_TO_COURSE << ". Add student to course." << endl;
   cout << PRINT_ROSTER << ". Print course roster." << endl;
   cout << PRINT_STUDENT_COURSES << ". Print a student's course list." << endl;
   cout << QUIT << ". Quit." << endl;
   cout << DELETE_COURSE << ". Delete a course." << endl;
   cout << DELETE_STUDENT << ". Delete a student." << endl;
   cout << "Choice: ";
   int choice;
   cin >> choice;
   cin.ignore();
   return choice;
}

/*                                                                                                                                                                
 * Creates a new course and adds it to the array of all courses (if successful).                                                                                  
 * Input 1: Array all_courses of pointers to courses.                                                                                                             
 * Input 2: Int pointer pnum_courses, which points to total number of courses.                                                                                    
 */
void make_new_course(Course* all_courses[], int* pnum_courses)
{
  // First, check if we've reached the max number of courses.                                                                                                     
  if (*pnum_courses >= MAX_TOTAL_COURSES){
    cout << "Reached maximum number of courses. ";
    cout << "Cannot create a new course at this time.\n" << endl;
    return;
  }

  string course_name;
  cout << "Please enter the name of the new course: " << endl;
  // Need to use getline because course name likely has a space in it.                                                                                            
  getline(cin, course_name);

  // Search all courses to make sure this course doesn't already exist.                                                                                           
  for (int i = 0; i < *pnum_courses; i++){
    if (all_courses[i]->name == course_name) {
      cout << "Course called " << course_name << " already exists!\n" << endl;
      return;
    }
  }

  // Otherwise, we can create a new course.                                                                                                                       
  Course* c = new Course;
  // Set the name.                                                                                                                                                
  c->name = course_name;
  // Set num_students to 0;                                                                                                                                       
  c->num_students = 0;

 // Add new course to all_courses, increment num courses.                                                                                                        
  all_courses[*pnum_courses] = c;
  *pnum_courses = *pnum_courses + 1;
  cout << "Course " << course_name << " successfully created!\n" << endl;
}

/*                                                                                                                                                                
 * Creates a new student and adds it to the array of all students (if successful).                                                                                
 * Input 1: Array all_students of pointers to students.                                                                                                           
 * Input 2: Int pointer pnum_students, which points to total number of students.                                                                                  
 */
void make_new_student(Student* all_students[], int* pnum_students)
{
  string student_name;
  cout << "Please enter the name of the student: " << endl;
  getline(cin, student_name);

  // Search all students to make sure student doesn't already exist.                                                                                              
  for (int i = 0; i < *pnum_students; i++) {
    if (all_students[i]->name == student_name) {
      cout << "Student " << student_name << " already exists!\n" << endl;
      return;
    }
  }
  // Else create a new student.                                                                                                                                   
  Student* s = new Student;
  // Set student name.                                                                                                                                            
  s->name = student_name;
  //set num_courses to 0;                                                                                                                                         
  s->num_courses = 0;
 // Add new student to all students and increment num students                                                                                                   
  all_students[*pnum_students] = s;
  *pnum_students = *pnum_students + 1;
  cout << "Student " << student_name << " successfully added!\n" << endl;
}

/*                                                                                                                                                                
 * Asks for a course name and a student name.                                                                                                                     
 * Then adds that student to the course, by including the student in the Course's                                                                                 
 * list of students, and including the Course in the student's list of courses.                                                                                   
 * Input 1: Array of pointers to all courses all_courses.                                                                                                         
 * Input 2: Int number of courses num_courses.                                                                                                                    
 * Input 3: Array of pointers to all students all_students.                                                                                                       
 * Input 4: Int number of students num_students.                                                                                                                  
 */
void add_student_to_course(Course* all_courses[], int num_courses, Student* all_students[], int num_students)
{
  string course_name;
  string student_name;

  // Ask for course to be added to                                                                                                                                
  cout << "What is the name of the course you'd like to add to?" << endl;
  getline(cin, course_name);

  Course* pcourse = NULL;

  // Search all courses to make sure this course exists.                                                                                                          
  for (int i = 0; i < num_courses; i++){
    if (all_courses[i]->name == course_name) {
      pcourse = all_courses[i];
    }
  }
 if (pcourse == NULL) {
    cout << "Course not found." << endl;
    return;
  }
  if (num_students >= MAX_STUDENTS_PER_COURSE) {
    cout << "Class is full." << endl;
    return;
  }

  // Else ask for student to add to course                                                                                                                        
  cout << "What is the name of the student you'd like to add to this course?" << endl;
  getline(cin, student_name);

  Student* pstudent = NULL;

 // Search all students to make sure student exists.                                                                                                              
 for (int j = 0; j < num_students; j++){
  if (all_students[j]->name == student_name) {
    pstudent = all_students[j];
  }
  if (pstudent == NULL) {
    cout << "Student not found." << endl;
    return;
  }
  if (num_courses >= MAX_COURSES_PER_STUDENT) {
    cout << "Student is already enrolled in the maximum number of classes!" << endl;
    return;
  }

 //Update the students field of Course to include pointer to newly added student                                                                                  
 pcourse->students[pcourse->num_students] = pstudent;
 // Increment num students ++                                                                                                                                     
 pcourse->num_students = pcourse->num_students + 1;

 //Update the courses field of Student to include pointer to newly joined course                                                                                  
 pstudent->courses[pstudent->num_courses] = pcourse;
 // Incremement num courses ++                                                                                                                                    
 pstudent->num_courses = pstudent->num_courses + 1;

 cout << "Student " << all_students[j]->name << " successfully enrolled in " << course_name << ".\n";
 }
 cout << endl;
}

/*                                                                                                                                                                
 * Asks for a course name, then prints all students in that course.                                                                                               
 * Input 1: array of pointers to all courses all_courses.                                                                                                         
 * Input 2: Int number of courses num_courses.                                                                                                                    
 */
void print_roster(Course* all_courses[], int num_courses)
{
  string course_name;
  cout << "Which course roster would you like to see?" << endl;
  getline(cin, course_name);

  cout << course_name << " roster: " << endl;

  for (int i = 0; i < num_courses; i++) {
    if (!(course_name == all_courses[i]->name)) {
      cout << "No course called " << course_name << " was found.\n" << endl;
      return;
    }
    if (course_name == all_courses[i]->name) {
      cout << all_courses[i]->students[i]->name << "\n" << endl;
      return;
    }
  }
}
/*                                                                                                                                                                
 * Asks for a student name, then prints all courses that student is taking.                                                                                       
 * Input 1: array of pointers to all students all_students.                                                                                                       
 * Input 2: Int number of students num_students.                                                                                                                  
 */
void print_student_courses(Student* all_students[], int num_students)
{
  string student_name;
  cout << "Which student's course list would you like to see?" << endl;
  getline(cin, student_name);

  cout << student_name << " course list: " << endl;

  for (int i = 0; i < num_students; i++) {
    if (!(student_name == all_students[i]->name)) {
      cout << "No student named " << student_name << " was found.\n" << endl;
      return;
   }
    if (student_name == all_students[i]->name) {
     cout << all_students[i]->courses[i]->name << "\n" << endl;
     return;
   }
  }
}
/*                                                                                                                                                                
 * deletes all heap allocated memory.                                                                                                                             
 * Input 1: Array of pointers to all courses all_courses.                                                                                                         
 * Input 2: Int number of courses num_courses.                                                                                                                    
 * Input 3: Array of pointers to all students all_students.                                                                                                       
 * Input 4: Int number of students num_students.                                                                                                                  
 */
void clean_memory(Course* all_courses[], int num_courses, Student* all_students[], int num_students)
{
  for (int i = 0; i < num_courses; i++) {
    delete all_courses[i];
    all_courses[i] = NULL;
  }
  for (int j = 0; j < num_students; j++) {
    delete all_students[j];
    all_students[j] = NULL;
  }
}

/*                                                                                                                                                                
 *delete course specified by user.                                                                                                                                
 *Input 1: Array of pointers to all courses                                                                                                                       
 *Input 2: Int num of courses                                                                                                                                     
 */
void delete_course(Course* all_courses[], int num_courses)
{
  string course_name;
  cout << "Which course would you like to delete?" << endl;
  getline(cin, course_name);

  for (int i = 0; i < num_courses; i++) {
    if (course_name == all_courses[i]->name) {
      delete all_courses[i];
      delete all_courses[i]->students[i];
      cout << "Course " << course_name << " has been successfully deleted!\n" << endl;
    }
  }
}

/*                                                                                                                                                                
 *delete student specified by user.                                                                                                                               
 *Input 1: Array of pointers to all students                                                                                                                      
 *Input 2: Int num of students                                                                                                                                    
*/
void delete_student(Student* all_students[], int num_students)
{
  string student_name;
  cout << "Which student would you like to delete?" << endl;
  getline(cin, student_name);

  for (int i = 0; i < num_students; i++) {
    if (student_name == all_students[i]->name) {
      delete all_students[i];
      delete all_students[i]->courses[i];
      cout << "Student " << student_name << " has been successfully deleted!\n" << endl;
    }
  }
}
