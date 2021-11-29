#include <iostream>
#include <fstream>
#include <string>
#include <string_view>
#include <memory>
#include <vector>
#include <algorithm>
#include <iomanip>

namespace sga
{
    const std::string margin = "=====================\n" ;

    enum class FILE_MODE
    {
        APPEND,
        WRITE
    };

    enum class RESULT_FIELD
    {
        TOTAL_GPA,
        SECONDARY_GPA,
        HIGHER_GPA
    };

    class student
    {
    protected :
        int32_t id;
        const std::string name;
    protected :
        student(int32_t m_id,std::string_view m_name)
            : id{m_id} , name {m_name} 
        {

        }
        friend class bangla_medium;
        friend class english_medium;
    };

    class bangla_medium : protected student
    {
    protected :
        float total_gpa, ssc_gpa, hsc_gpa;
    protected :
        bangla_medium(int32_t m_id, std::string_view m_name, float m_ssc , float m_hsc , float m_total)
            : student{m_id,m_name} , ssc_gpa{m_ssc} , hsc_gpa{m_hsc}, total_gpa{m_total}
        {

        }
        friend std::ofstream& operator << (std::ofstream&,bangla_medium*);
        friend class file;
        friend class studentDB;
    };

    std::ofstream& operator << (std::ofstream& os ,bangla_medium* c_student)
    {
        os << "ID : " << c_student->id << ";Name : " << c_student->name <<'\n';
        return os;
    }

    class english_medium : protected student 
    {
    protected :
        float o_level,a_level,total_gpa;
    protected :
        english_medium() = delete;
        english_medium(int32_t m_id , std::string_view m_name , float m_olevel , float m_alevel , float m_total)
            : student{m_id,m_name} , o_level{m_olevel} , a_level{m_alevel} , total_gpa{m_total}
        {

        }
        friend std::ofstream& operator << (std::ofstream& , const english_medium*);
        friend class file;
        friend class studentDB;
    };

    std::ofstream& operator << (std::ofstream& os , const english_medium* c_student)
    {
        os << "ID : " << c_student->id << ";Name : " << c_student->name <<'\n';
        return os;
    }

    class studentDB : protected bangla_medium , protected english_medium
    {
    protected :
        static std::vector <bangla_medium*> bangla;
        static std::vector <english_medium*> english;
    protected :
        static void insert(bangla_medium* new_student)
        {
            bangla.emplace_back(new_student);
        }
        static void insert(english_medium* new_student)
        {
            english.emplace_back(new_student);
        }
    };
    std::vector <bangla_medium*> studentDB::bangla;
    std::vector <english_medium*> studentDB::english;

    class file : protected studentDB
    {
    public :
    /*
        Note : parse function is really dumb . No errors is checked & only works with 
        expected file format.
        Any kind of unexpected file format may lead your pc to vacation :p
    */
        static void parse(std::string input_file = "student_data.txt")
        {
            std::ifstream input;
            int32_t id;
            std::string name , skip , exam;
            float secondary,higher,total;
            input.open(input_file , std::ios::in);
            while(!input.eof())
            {
                input >> skip >> id >> skip >> name >> skip >> total >> exam >> higher >> skip >> secondary;
                if(exam == "hsc")
                {
                    studentDB::insert(new bangla_medium(id,name,secondary,higher,total));
                }
                else 
                {
                    studentDB::insert(new english_medium(id,name,secondary,higher,total));
                }
            }
            input.close();
        }
        static void gpa_analysis(RESULT_FIELD r_field, FILE_MODE f_mode, std::string output_file = "student_list.txt")
        {
            std::ofstream output;
            if(f_mode == FILE_MODE::WRITE)
                output.open(output_file , std::ios::out);
            else
            {
                output.open(output_file, std::ios::app);
                output << "\n\n";
            } 

            switch(r_field)
            {
                case RESULT_FIELD::TOTAL_GPA :
                    output << "TOTAL GPA ANALYSIS:\n" << margin << "\n\n" ;
                    std::sort(studentDB::bangla.begin() , studentDB::bangla.end(), [](bangla_medium* a ,bangla_medium* b){ return(a->total_gpa > b->total_gpa);});
                    std::sort(studentDB::english.begin() , studentDB::english.end(), [](english_medium* a, english_medium* b){return (a->total_gpa > b->total_gpa);});
                    break;
                case RESULT_FIELD::SECONDARY_GPA :
                    output << "SSC GPA ANALYSIS:\n" << margin << "\n\n" ;
                    std::sort(studentDB::bangla.begin() , studentDB::bangla.end(), [](bangla_medium* a ,bangla_medium* b){ return(a->ssc_gpa > b->ssc_gpa);});
                    std::sort(studentDB::english.begin() , studentDB::english.end(), [](english_medium* a, english_medium* b){return (a->o_level > b->o_level);});
                    break;
                case RESULT_FIELD::HIGHER_GPA :
                    output << "HSC GPA ANALYSIS:\n" << margin << "\n\n" ;
                    std::sort(studentDB::bangla.begin() , studentDB::bangla.end(), [](bangla_medium* a ,bangla_medium* b){ return(a->hsc_gpa > b->hsc_gpa);});
                    std::sort(studentDB::english.begin() , studentDB::english.end(), [](english_medium* a, english_medium* b){return (a->a_level > b->a_level);});
                    break;
                default :
                    output << "TOTAL GPA ANALYSIS:\n" << margin << "\n\n" ;
                    std::sort(studentDB::bangla.begin() , studentDB::bangla.end(), [](bangla_medium* a ,bangla_medium* b){ return(a->total_gpa > b->total_gpa);});
                    std::sort(studentDB::english.begin() , studentDB::english.end(), [](english_medium* a, english_medium* b){return (a->total_gpa > b->total_gpa);});
            }

            output << "For Bangla Medium:\n" << margin;
            output << std::fixed << std::setprecision(2) ;

            for(size_t i = 0 , j = 0; i < studentDB::bangla.size() ; i+= j)
            {
                j = 0;
                if(r_field == RESULT_FIELD::TOTAL_GPA)
                    output << "\nTotal GPA: " << studentDB::bangla.at(i)->total_gpa << '\n' << margin;
                else if(r_field == RESULT_FIELD::SECONDARY_GPA)
                    output << "\nSSC GPA: " << studentDB::bangla.at(i)->ssc_gpa << '\n' << margin;
                else 
                    output << "\nHSC GPA: " << studentDB::bangla.at(i)->hsc_gpa << '\n' << margin;
                do 
                {
                    output << studentDB::bangla.at(i+j);
                    j++;
                    if(i+j >= studentDB::bangla.size())
                        break;
                }
                while((r_field == RESULT_FIELD::TOTAL_GPA && studentDB::bangla.at(i)->total_gpa == studentDB::bangla.at(i+j)->total_gpa) ||
                      (r_field == RESULT_FIELD::SECONDARY_GPA && studentDB::bangla.at(i)->ssc_gpa == studentDB::bangla.at(i+j)->ssc_gpa) ||
                      (r_field == RESULT_FIELD::HIGHER_GPA && studentDB::bangla.at(i)->hsc_gpa == studentDB::bangla.at(i+j)->hsc_gpa));
            }

            output << "\n\nFor English Medium:\n" << margin ;

            for(size_t i = 0 , j = 0; i < studentDB::english.size() ; i+= j)
            {
                j = 0;
                if(r_field == RESULT_FIELD::TOTAL_GPA)
                    output << "\nTotal GPA: " << studentDB::english.at(i)->total_gpa << '\n' << margin;
                else if(r_field == RESULT_FIELD::SECONDARY_GPA)
                    output << "\nO level GPA: " << studentDB::english.at(i)->o_level << '\n' << margin;
                else 
                    output << "\nA level GPA: " << studentDB::english.at(i)->a_level << '\n' << margin;
                do 
                {
                    output << studentDB::english.at(i+j);
                    j++;
                    if(i+j >= studentDB::english.size())
                        break;
                }
                while((r_field == RESULT_FIELD::TOTAL_GPA && studentDB::english.at(i)->total_gpa == studentDB::english.at(i+j)->total_gpa) ||
                      (r_field == RESULT_FIELD::SECONDARY_GPA && studentDB::english.at(i)->o_level == studentDB::english.at(i+j)->o_level) ||
                      (r_field == RESULT_FIELD::HIGHER_GPA && studentDB::english.at(i)->a_level == studentDB::english.at(i+j)->a_level));
            }
            output.close();
        }
    };
}

int main(int argc , char** argv)
{
    sga::file::parse();
    sga::file::gpa_analysis(sga::RESULT_FIELD::TOTAL_GPA, sga::FILE_MODE::WRITE , "total_gpa_analysis.txt");
    sga::file::gpa_analysis(sga::RESULT_FIELD::SECONDARY_GPA, sga::FILE_MODE::WRITE , "ssc_gpa_analysis.txt");
    sga::file::gpa_analysis(sga::RESULT_FIELD::HIGHER_GPA, sga::FILE_MODE::WRITE , "hsc_gpa_analysis.txt");
    sga::file::gpa_analysis(sga::RESULT_FIELD::TOTAL_GPA, sga::FILE_MODE::APPEND, "student_append.txt");
    sga::file::gpa_analysis(sga::RESULT_FIELD::SECONDARY_GPA, sga::FILE_MODE::APPEND, "student_append.txt");
    sga::file::gpa_analysis(sga::RESULT_FIELD::HIGHER_GPA, sga::FILE_MODE::APPEND, "student_append.txt");
    return 0;
}