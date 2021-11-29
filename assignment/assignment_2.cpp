#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <algorithm>

const std::string margin = "=====================\n" ;

enum class FILE_STATUS
{
    READ_SUCCESSFULLY,
    NO_FILE_EXISTS
};

enum class SORT_FIELD
{
    TOTAL_GPA,
    SECONDARY_GPA,
    HIGHER_GPA
};

enum class FILE_MODE
{
    APPEND,
    WRITE
};

class student
{
public :
    int32_t id;
    std::string name;
public :
    student() = delete ;
    student(int32_t m_id , const std::string& m_name)
        : id{m_id} , name {m_name}
    {

    }
};

class bangla_medium : public student
{
public :
    float ssc_gpa,hsc_gpa,total_gpa;
public :
    bangla_medium() = delete ;
    bangla_medium(int32_t m_id , const std::string& m_name , float m_ssc , float m_hsc, float m_total)
        : student{m_id,m_name} , ssc_gpa {m_ssc} , hsc_gpa {m_hsc} , total_gpa{m_total}
    {

    }

};

class english_medium : public student
{
public :
    float o_level,a_level,total_gpa;
public :
    english_medium() = delete;
    english_medium(int32_t m_id , const std::string& m_name , float m_olevel , float m_alevel , float m_total)
        : student{m_id,m_name} , o_level{m_olevel} , a_level{m_alevel} , total_gpa{m_total}
    {

    }
};

class bangla_medium_students
{
public :
    std::vector<bangla_medium*> students;
public :
    bangla_medium_students() = default ;
    void insert(bangla_medium* b_stu)
    {
        students.emplace_back(b_stu);
    }

    static bool bangla_sort_total (const bangla_medium* left , const bangla_medium* right)
    {
        return (left->total_gpa > right->total_gpa);
    }

    static bool bangla_sort_ssc (const bangla_medium* left , const bangla_medium* right)
    {
        return (left->ssc_gpa > right->ssc_gpa);
    }

    static bool bangla_sort_hsc (const bangla_medium* left , const bangla_medium* right)
    {
        return (left->hsc_gpa > right->hsc_gpa);
    }

};
bangla_medium_students bangla;

class english_medium_students
{
public :
    std::vector<english_medium*> students;
public :
    english_medium_students() = default ;
    void insert(english_medium* e_stu)
    {
        students.emplace_back(e_stu);
    }
    static bool english_sort_total(const english_medium* left , const english_medium* right)
    {
        return (left->total_gpa > right->total_gpa);
    }

    static bool english_sort_secondary(const english_medium* left , const english_medium* right)
    {
        return (left->o_level > right->o_level);
    }

    static bool english_sort_higher(const english_medium* left , const english_medium* right)
    {
        return (left->a_level > right->a_level);
    }
};
english_medium_students english;

FILE_STATUS file_serialize(std::string file_name = "student_data.txt")
{
    FILE* m_file = fopen(file_name.c_str(),"r");
    if(m_file == nullptr)
        return FILE_STATUS::NO_FILE_EXISTS;
    int id ; char name[40];
    float total_gpa , secondary_gpa , higher_gpa ;
    char exam[10];

    while(fscanf(m_file,"%*s %d %*s %s %*s %f %s %f %*s %f",&id,name,&total_gpa,exam,&higher_gpa,&secondary_gpa) != EOF)
    {
        if(strcmp(exam,"hsc") == 0)
        {
            bangla_medium* new_student = new bangla_medium(id,name,secondary_gpa,higher_gpa,total_gpa);
            bangla.insert(new_student);
        }
        else 
        {
            english_medium* new_student = new english_medium(id,name,secondary_gpa,higher_gpa,total_gpa);
            english.insert(new_student);
        }
    }
    fclose(m_file);
    return FILE_STATUS::READ_SUCCESSFULLY;
}

void total_gpa_analysis(FILE_MODE f_mode)
{
    FILE* file = nullptr ;
    if(f_mode == FILE_MODE::APPEND)
    {
        file = fopen("student_append.txt","a");
        fprintf(file,"\n\nTOTAL GPA ANALYSIS:\n%s",margin.c_str());
    }
    if(f_mode == FILE_MODE::WRITE)
        file = fopen("total_gpa_analysis.txt","w");
    fprintf(file, "For Bangla Medium:\n%s",margin.c_str());
    std::sort(bangla.students.begin(),bangla.students.end(),bangla.bangla_sort_total);

    for(size_t i = 0 , j = 0; i < bangla.students.size() ; i+= j)
    {
        j = 0;
        fprintf(file,"\nTotal GPA: %.2f\n%s",bangla.students.at(i)->total_gpa,margin.c_str());
        do 
        {
            fprintf(file,"ID : %d;Name : %s\n",bangla.students.at(i+j)->id,bangla.students.at(i+j)->name.c_str());
            j++;
            if(i+j >= bangla.students.size())
                break;
        }
        while(bangla.students.at(i)->total_gpa == bangla.students.at(i+j)->total_gpa);
    }

    fprintf(file,"\n\n\nFor English Medium:\n%s",margin.c_str());
    std::sort(english.students.begin(),english.students.end(),english.english_sort_total);

    for(size_t i = 0 , j = 0; i < english.students.size() ; i+= j)
    {
        j = 0;
        fprintf(file,"\nTotal GPA: %.2f\n%s",english.students.at(i)->total_gpa,margin.c_str());
        do 
        {
            fprintf(file,"ID : %d;Name : %s\n",english.students.at(i+j)->id,english.students.at(i+j)->name.c_str());
            j++;
            if(i+j >= english.students.size())
                break;
        }
        while(english.students.at(i)->total_gpa == english.students.at(i+j)->total_gpa);
    }
    fclose(file);
}

void secondary_gpa_analysis(FILE_MODE f_mode)
{
    FILE* file = nullptr ;
    if(f_mode == FILE_MODE::APPEND)
    {
        file = fopen("student_append.txt","a");
        fprintf(file,"\n\nSSC GPA ANALYSIS:\n%s",margin.c_str());
    }
        
    if(f_mode == FILE_MODE::WRITE)
        file = fopen("ssc_gpa_analysis.txt","w");
    // std::cout << "For Bangla Medium:\n" << margin ;
    fprintf(file, "For Bangla Medium:\n%s",margin.c_str());
    std::sort(bangla.students.begin(),bangla.students.end(),bangla.bangla_sort_ssc);

    for(size_t i = 0 , j = 0; i < bangla.students.size() ; i+= j)
    {
        j = 0;
        // std::cout << "\nSSC GPA: " << bangla.students.at(i)->ssc_gpa << '\n' << margin;
        fprintf(file,"\nSSC GPA: %.2f\n%s",bangla.students.at(i)->ssc_gpa,margin.c_str());
        do 
        {
            // std::cout << "ID : " << bangla.students.at(i+j)->id << ';' << "Name : " << bangla.students.at(i+j)->name << '\n';
            fprintf(file,"ID : %d;Name : %s\n",bangla.students.at(i+j)->id,bangla.students.at(i+j)->name.c_str());
            j++;
            if(i+j >= bangla.students.size())
                break;
        }
        while(bangla.students.at(i)->ssc_gpa == bangla.students.at(i+j)->ssc_gpa);
    }

    // std::cout << "\n\n\nFor English Medium:\n" << margin ;
    fprintf(file,"\n\n\nFor English Medium:\n%s",margin.c_str());
    std::sort(english.students.begin(),english.students.end(),english.english_sort_secondary);

    for(size_t i = 0 , j = 0; i < english.students.size() ; i+= j)
    {
        j = 0;
        // std::cout << "\nO level GPA: " << english.students.at(i)->o_level << '\n' << margin;
        fprintf(file,"\nO level GPA: %.2f\n%s",english.students.at(i)->o_level,margin.c_str());
        do 
        {
            // std::cout << "ID : " << english.students.at(i+j)->id << ';' << "Name : " << english.students.at(i+j)->name << '\n';
            fprintf(file,"ID : %d;Name : %s\n",english.students.at(i+j)->id,english.students.at(i+j)->name.c_str());
            j++;
            if(i+j >= english.students.size())
                break;
        }
        while(english.students.at(i)->o_level == english.students.at(i+j)->o_level);
    }
    fclose(file);
}

void higher_gpa_analysis(FILE_MODE f_mode)
{
    FILE* file = nullptr ;
    if(f_mode == FILE_MODE::APPEND)
    {
        file = fopen("student_append.txt","a");
        fprintf(file,"\n\nHSC GPA ANALYSIS:\n%s",margin.c_str());
    }
    if(f_mode == FILE_MODE::WRITE)
        file = fopen("hsc_gpa_analysis.txt","w");
    // std::cout << "For Bangla Medium:\n" << margin ;
    fprintf(file, "For Bangla Medium:\n%s",margin.c_str());
    std::sort(bangla.students.begin(),bangla.students.end(),bangla.bangla_sort_hsc);

    for(size_t i = 0 , j = 0; i < bangla.students.size() ; i+= j)
    {
        j = 0;
        // std::cout << "\nHSC GPA: " << bangla.students.at(i)->hsc_gpa << '\n' << margin;
        fprintf(file,"\nHSC GPA: %.2f\n%s",bangla.students.at(i)->hsc_gpa,margin.c_str());
        do 
        {
            // std::cout << "ID : " << bangla.students.at(i+j)->id << ';' << "Name : " << bangla.students.at(i+j)->name << '\n';
            fprintf(file,"ID : %d;Name : %s\n",bangla.students.at(i+j)->id,bangla.students.at(i+j)->name.c_str());
            j++;
            if(i+j >= bangla.students.size())
                break;
        }
        while(bangla.students.at(i)->hsc_gpa == bangla.students.at(i+j)->hsc_gpa);
    }

    // std::cout << "\n\n\nFor English Medium:\n" << margin ;
    fprintf(file,"\n\n\nFor English Medium:\n%s",margin.c_str());
    std::sort(english.students.begin(),english.students.end(),english.english_sort_higher);

    for(size_t i = 0 , j = 0; i < english.students.size() ; i+= j)
    {
        j = 0;
        // std::cout << "\nA level GPA: " << english.students.at(i)->a_level << '\n' << margin;
        fprintf(file,"\nA level GPA: %.2f\n%s",english.students.at(i)->a_level,margin.c_str());
        do 
        {
            // std::cout << "ID : " << english.students.at(i+j)->id << ';' << "Name : " << english.students.at(i+j)->name << '\n';
            fprintf(file,"ID : %d;Name : %s\n",english.students.at(i+j)->id,english.students.at(i+j)->name.c_str());
            j++;
            if(i+j >= english.students.size())
                break;
        }
        while(english.students.at(i)->a_level == english.students.at(i+j)->a_level);
    }
    fclose(file);
}

int main()
{
    if(file_serialize() == FILE_STATUS::NO_FILE_EXISTS)
    {
        std::cout << "File doesn't exist\n";
    }
    total_gpa_analysis(FILE_MODE::WRITE);
    secondary_gpa_analysis(FILE_MODE::WRITE);
    higher_gpa_analysis(FILE_MODE::WRITE);
    total_gpa_analysis(FILE_MODE::APPEND);
    secondary_gpa_analysis(FILE_MODE::APPEND);
    higher_gpa_analysis(FILE_MODE::APPEND);
    return 0;
}