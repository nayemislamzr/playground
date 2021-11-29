/**
 * standard library
 **/

#include <stdio.h>
#include <string.h>
#include <memory.h>
#include <stdbool.h> 
#include <stdlib.h>
#include <assert.h> // as no error handling implemented

/**
 * WINDOWS
 */
#ifdef _WIN32
#define CLEAR_SCREEN "cls"
#endif

/**
 * linux
 */
#ifdef linux
#define CLEAR_SCREEN "clear"
#endif

/**
 * macros
 **/

#define TOTAL_TEACHER 100
#define TOTAL_STUDENT 1000
#define SIZE 30
#define PRIME 29
const char* margin = "================================\n";
const char* s_margin="--------------------------------\n";

/**
 * global variables
 **/

char student_list[TOTAL_STUDENT][SIZE];
char teacher_list[TOTAL_TEACHER][SIZE];

enum main_option
{
    REGISTER = 1,
    LOGIN,
    EXIT
};

enum program_status
{
    EXIT_FROM_PROGRAM,
    STAY_IN_THE_PROGRAM
};

enum user
{
    STUDENT = 1,
    TEACHER
};

enum designation
{
    LECTURER = 1,
    ASSISTANT_PROFESSOR,
    PROFESSOR
};

enum reg_status
{
    ACCOUNT_EXISTS,
    ERROR_ALLOCATING_MEMORY,
    REG_SUCCESSFULL
};

enum edit
{
    NAME,
    PASSWORD
};

struct current_users
{
    int teachers, students;
}current;

/**
 * simple hash function : string -> int
 * Note : naive hashing function so may collide in high perchantage , also return negative value(fatal)
 **/ 

int hash(const char* email)
{
    int length = strlen(email);
    int ans = 0 , multi = 1;
    for(int i = 0 ; i < length ; i++)
    {
        ans = (ans+(multi%1000*(email[i]-' ')%1000)%1000)%1000;
        multi*=PRIME;
    }
    return ans;
}

/**
 * student structure
 **/ 

typedef struct
{
    int id;
    char* name;
    char* email;
    char* password;
    float cgpa;
}student;
student* studentDB = NULL ; // DataBase for students

/**
 * initializing studentDB array (contains all the info of students)
 **/

student* student_constructor(int total_student)
{
    studentDB = malloc(sizeof(student)*total_student);
    current.students = 0;
}

/**
 * registers a student to studentDB
 **/

enum reg_status student_register(char email[],char password[],char name[],float cgpa)
{
    int index = hash(email);
        if(index < 0) return ERROR_ALLOCATING_MEMORY;
    student* new_student = studentDB+index;

    if(new_student->name != NULL || new_student->email != NULL || new_student->password != NULL)
        return ACCOUNT_EXISTS;

    new_student->name = malloc(sizeof(char)*SIZE);
    new_student->email = malloc(sizeof(char)*SIZE);
    new_student->password = malloc(sizeof(char)*SIZE);

    if(new_student->name == NULL || new_student->email == NULL || new_student->password == NULL)
        return ERROR_ALLOCATING_MEMORY;

    strcpy(new_student->name,name);
    strcpy(new_student->email,email);
    strcpy(new_student->password,password);
    new_student->cgpa = cgpa;
    new_student->id = current.students+1;
    strcpy(student_list[current.students],email); // adding email(identifier) to student list

    return REG_SUCCESSFULL;
}

/**
 * takes input for registration
 **/

enum reg_status student_input(void)
{
    char email[SIZE],password[SIZE],name[SIZE];
    float cgpa;
    printf("Enter Your Name : \n"); 
    scanf("%s",name);
    printf("Enter Your Email : \n");
    scanf("%s",email);
    printf("Enter Your Password : \n");
    scanf("%s",password);
    printf("Enter CGPA : \n");
    scanf("%f",&cgpa);
    return student_register(email,password,name,cgpa);
}

/**
 * authentication with email & password
 **/

int login_student(char* email , char* password)
{
    int index = hash(email);
    if(studentDB[index].email == NULL || studentDB[index].password == NULL)
        return -1; 
    if(strcmp(studentDB[index].email,email) == 0 && strcmp(studentDB[index].password,password) == 0)
        return index;
    return -1;
}

void student_details(enum user source, int index)
{
    printf("%s",margin);
    printf("ID      : #%05d\n",studentDB[index].id);
    printf("Name    : %s\n",studentDB[index].name);
    printf("Email   : %s\n",studentDB[index].email);
    if(source == STUDENT)
        printf("Password: %s\n",studentDB[index].password);
    printf("CGPA    : %.2f\n",studentDB[index].cgpa);
    printf("%s",s_margin);
}

/**
 * for updating name & password
 **/

void student_edit(int index , enum edit edit_option)
{
    printf("%s",margin);

    char new_name[SIZE],new_password[20];
    if(edit_option == NAME)
    {
        printf("Enter Your New Name : \n");
        scanf("%s",new_name);
        free(studentDB[index].name);
        studentDB[index].name = malloc(sizeof(char)*SIZE);
        strcpy(studentDB[index].name,new_name);
        printf("%sSuccessfully changed the user name :)\n%s",s_margin,margin);
    }
    else if(edit_option == PASSWORD)
    {
        printf("Enter Your New Password : \n");
        scanf("%s",new_password);
        free(studentDB[index].password);
        studentDB[index].password = malloc(sizeof(char)*SIZE);
        strcpy(studentDB[index].password,new_password);
        printf("%sSuccessfully changed the user password :)\n%s",s_margin,margin);
    }
}

/**
 * teacher structure
 **/

typedef struct
{
    int id;
    char* name;
    char* email;
    char* password;
    enum designation rank;
} teacher;
teacher* teacherDB = NULL ; // DataBase for teachers

teacher* teacher_constructor(int total_teacher) // same as student construct , here for teacher
{
    teacherDB = malloc(sizeof(teacher)*total_teacher);
    current.teachers = 0;
}

enum reg_status teacher_register(char email[],char password[],char name[],enum designation rank)
{
    int index = hash(email);
        if(index < 0) return ERROR_ALLOCATING_MEMORY;
    teacher* new_teacher = teacherDB+index;

    if(new_teacher->name != NULL || new_teacher->email != NULL || new_teacher->password != NULL)
        return ACCOUNT_EXISTS;

    new_teacher->name = malloc(sizeof(char)*SIZE);
    new_teacher->email = malloc(sizeof(char)*SIZE);
    new_teacher->password = malloc(sizeof(char)*SIZE);

    if(new_teacher->name == NULL || new_teacher->email == NULL || new_teacher->password == NULL)
        return ERROR_ALLOCATING_MEMORY;

    strcpy(new_teacher->name,name);
    strcpy(new_teacher->email,email);
    strcpy(new_teacher->password,password);
    new_teacher->id = current.teachers+1;
    new_teacher->rank = rank;
    strcpy(teacher_list[current.teachers],email);

    return REG_SUCCESSFULL;
}

enum reg_status teacher_input(void)
{
    char email[SIZE],password[SIZE],name[SIZE];
    int i_rank;
    enum designation rank;
    printf("Enter Your Name : \n");
    scanf("%s",name);
    printf("Enter Your Email : \n");
    scanf("%s",email);
    printf("Enter Your Password : \n");
    scanf("%s",password);
    printf("Select Your Designation : \n");
    printf("options :\n1. Lecturer\n2. Assistant Professor\n3. Professor\n");
    scanf("%d",&i_rank);
    
    assert(i_rank >= 1 && i_rank <= 3);

    switch (i_rank)
    {
    case LECTURER:
        rank = LECTURER;
        break;
    case ASSISTANT_PROFESSOR:
        rank = ASSISTANT_PROFESSOR;
        break;
    case PROFESSOR:
        rank = PROFESSOR;
        break;
    default:
        break;
    }

    return teacher_register(email,password,name,rank);
}

int login_teacher(char* email , char* password)
{
    int index = hash(email);
    if(teacherDB[index].email == NULL || teacherDB[index].password == NULL)
        return -1; 
    if(strcmp(teacherDB[index].email,email) == 0 && strcmp(teacherDB[index].password,password) == 0)
        return index;
    return -1;
}

void teacher_details(int index)
{
    printf("%s",margin);
    printf("ID          : #%05d\n",teacherDB[index].id);
    printf("Name        : %s\n",teacherDB[index].name);
    printf("Designation : ");
    switch(teacherDB[index].rank)
    {
        case PROFESSOR:
            printf("Professor\n");
            break;
        case ASSISTANT_PROFESSOR:
            printf("Assistant Professor\n");
            break;
        case LECTURER:
            printf("Lecturer\n");
            break;
        default:
            printf("\n");
            break;
    }
    printf("Email       : %s\n",teacherDB[index].email);
    printf("Password    : %s\n",teacherDB[index].password);
    printf("%s",margin);
}

void registration(void)
{
    printf("%s",margin);
    unsigned int option;
    enum reg_status status;
    printf("1.Register as a student.\n2.Register as a teacher.\n%s",s_margin);
    scanf("%d",&option);
    
    assert(option == 1 || option == 2);
    printf("%s",s_margin);
    status = (option == 1) ? student_input() : teacher_input();
    printf("%s",s_margin);

    switch (status)
    {
        case REG_SUCCESSFULL:
            printf("Registration completed :)\n");
            (option == 1) ? ++current.students : ++current.teachers ;
            break;

        case ACCOUNT_EXISTS:
            printf("Account already registered :(\n");
            break;

        case ERROR_ALLOCATING_MEMORY:
            printf("Something went wrong :/\n");
            break;

        default:
            break;
    }
    printf("%s",s_margin);
}

void show_user_name(char user_name[])
{
    printf("%s",margin);
    int len = strlen(user_name);
    for(int i = 0 ; i <= len+7 ; i++)
        printf("+");
    printf("\n|   %s   |\n",user_name);
    for(int i = 0 ; i <= len+7 ; i++)
        printf("+");
    printf("\n%s",s_margin);
}

/**
 * returns the list of registered students(email) from student list
 **/

void see_all_students(void)
{
    int select;
    printf("%sTotal students : %d\n%s",margin,current.students,s_margin);
    for(int i = 0 ; i < current.students ; i++)
        printf("%d. %s\n%s",i+1,student_list[i],s_margin);
    printf("%s",margin);
    printf("Please select a student account : \n");
    scanf("%d",&select);
    
    assert(select >= 1 && select <= current.students);

    student_details(TEACHER,hash(student_list[select-1]));
}

/**
 * returns the list of registered teachers(email) from teacher list
 **/

void see_all_teachers(void)
{
    int select;
    printf("%sTotal teachers : %d\n%s",margin,current.teachers,s_margin);
    for(int i = 0 ; i < current.teachers ; i++)
        printf("%d. %s\n%s",i+1,teacher_list[i],s_margin);
    printf("%s",margin);
    printf("Please select a student account : \n");
    scanf("%d",&select);
    
    assert(select >= 1 && select <= current.teachers);

    teacher_details(hash(teacher_list[select-1]));
}

enum program_status log_in(void) // login page(UI)
{
    unsigned int option;
    int login_res;
    char email[SIZE],password[SIZE];
    printf("%s",margin);
    printf("1.Login as a Student\n");
    printf("2.Login as a Teacher\n");
    printf("%s",s_margin);
    scanf("%d",&option);

    assert(option == 1 || option == 2);
    
    printf("%s",margin);
    printf("Enter Your Email : \n");
    scanf("%s",email);
    printf("Enter Your Password : \n");
    scanf("%s",password);
    login_res = (option == 1) ? login_student(email,password) : login_teacher(email,password);
    if(login_res == -1)
    {
        printf("Login Failed :-/\n");
    }
    else 
    {
        char* user_name;
        printf("%sLogin Successful :)\n",margin);
        int category_select;
        if(option == 1)
        {
            user_name = studentDB[login_res].name ;
            show_user_name(user_name);
            printf("Options: \n 1. See Details\n 2. Edit Name \n 3. Edit Password \n 4. Logout \n 5. Exit \n%s",s_margin);
            scanf("%d",&category_select);
            assert(category_select >= 1 && category_select <=5 );
            while(1)
            {
                switch (category_select)
                {
                    case 1:
                        student_details(STUDENT,login_res);
                        break;
                    case 2:
                        student_edit(login_res,NAME);
                        break;
                    case 3:
                        student_edit(login_res,PASSWORD);
                        break;
                    case 4:
                        system(CLEAR_SCREEN);
                        return STAY_IN_THE_PROGRAM;
                    case 5:
                        printf("%sExiting....\n%s",s_margin,margin);
                        return EXIT_FROM_PROGRAM;
                    default:
                        break;
                }
                printf("Press ENTER to continue...");
                char ch;
                getchar();
                while((ch = getchar()) != '\n')
                { }   
                show_user_name(user_name);
                printf("Options: \n 1. See Details\n 2. Edit Name \n 3. Edit Password \n 4. Logout \n 5. Exit \n%s",s_margin);
                scanf("%d",&category_select);
                assert(category_select >= 1 && category_select <=5 );
            }
        }

        else 
        {
            user_name = teacherDB[login_res].name;
            show_user_name(user_name);
            printf("Options : \n1. See All Students\n2. See All Teachers\n3. Logout\n4. Exit\n");
            printf("%s",s_margin);
            scanf("%d",&category_select);
            assert(category_select >= 1 && category_select <= 4);
            while(1)
            {
                switch (category_select)
                {
                    case 1:
                        see_all_students();
                        break;
                    case 2:
                        see_all_teachers();
                        break;
                    case 3:
                        system(CLEAR_SCREEN);
                        return STAY_IN_THE_PROGRAM;
                    case 4:
                        printf("Exiting....\n");
                        return EXIT_FROM_PROGRAM;
                    default:
                        break;
                }
                printf("Press ENTER to continue...");
                char ch;
                getchar();
                while((ch = getchar()) != '\n')
                { }   
                show_user_name(user_name);
                printf("Options : \n1. See All Students\n2. See All Teachers\n3. Logout\n4. Exit\n");
                scanf("%d",&category_select);
                assert(category_select >= 1 && category_select <= 4);
            }            
        }
    }
    return STAY_IN_THE_PROGRAM;
}

/**
 * main menu of the program
 **/

void    main_menu(void)
{
    int main_option = -1;
    enum program_status pg_status = STAY_IN_THE_PROGRAM;
    printf("%s",margin);
    printf("Total registered students   : %d\n",current.students);
    printf("Total registered teacher    : %d\n",current.teachers);
    printf("%s",s_margin);
    printf("Select an option : \n");
    printf("1. Register\n2. Login\n3. Exit");
    printf("\n%s",s_margin);
    scanf("%d",&main_option);

    assert(main_option >= 1 && main_option <= 3);

    while(main_option != EXIT)
    {
        switch (main_option)
        {
            case REGISTER:
                registration();
                break;
            case LOGIN:
                pg_status = log_in();
                break;
            case EXIT:
                return;

            default:
                break;
        }
        if(pg_status == EXIT_FROM_PROGRAM)
            return;
        printf("%s",margin);
        printf("Total registered students   : %d\n",current.students);
        printf("Total registered teacher    : %d\n",current.teachers);
        printf("%s",s_margin);
        printf("Select an option : \n");
        printf("1. Register\n2. Login\n3. Exit\n");
        printf("%s",s_margin);
        scanf("%d",&main_option);
        printf("%s",s_margin);
    }
}

/**
 * reads user info from file
 **/

bool input_from_file(const char* file_name)
{
    FILE* fptr = fopen(file_name,"r");
    if(fptr == NULL)
        return false;
    char email[SIZE],name[SIZE],password[SIZE],buffer[1000];
    float cgpa;
    int total_line = 0,total_success = 0,user_info,rank;

    while(fgets(buffer, 1000, fptr)) 
	{
        sscanf(buffer,"%d",&user_info);

        if(user_info == STUDENT)
        {
            sscanf(buffer,"%d %s %s %s %f",&user_info,email,name,password,&cgpa);
            if(student_register(email,password,name,cgpa) == REG_SUCCESSFULL)
            {
                current.students++;
                ++total_success;
            }
        }

        else if(user_info == TEACHER)
        {
            sscanf(buffer,"%d %s %s %s %d",&user_info,email,name,password,&rank);
            if(teacher_register(email,password,name,rank) == REG_SUCCESSFULL)
            {
                current.teachers++;
                ++total_success;
            }
        }
        
        total_line++;
    }
    printf("%sSuccessfully registered %d user(s) out of %d from \"%s\".\n%s",s_margin,total_success,total_line,file_name,s_margin);
    return true;
}

void show_intro()
{
    printf("==============================================\n");
    printf("|    A simple STUDENT, TEACHER Database      |\n");
    printf("==============================================\n");
    printf("|   Name          | Sopnil                   |\n");
    printf("++++++++++++++++++++++++++++++++++++++++++++++\n");
    printf("|   Registration  | 201900000                |\n");
    printf("++++++++++++++++++++++++++++++++++++++++++++++\n");
    printf("|   Course code   | CSE 103D                 |\n");
    printf("==============================================\n");
    char ch;
    printf("\nPress ENTER to continue...");
    while((ch = getchar()) != '\n')
    {

    }
    system(CLEAR_SCREEN);
}

int main(int argc, char** argv)
{
    system(CLEAR_SCREEN); // clearing screen
    show_intro();
    student_constructor(TOTAL_STUDENT);
    teacher_constructor(TOTAL_TEACHER);
    if(argc > 1)
    {
        for(int i = 1 ; i < argc ; i++)
        {
            if(!input_from_file(argv[i]))
                printf("Error opening \"%s\"\n",argv[i]);
        }
    }
    main_menu();
}


