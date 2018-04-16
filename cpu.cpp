#include <fstream>
#include "split.cpp"
class Cpu{
    int *index;
    int work_jiffies_0, work_jiffies_1, total_jiffies_0, total_jiffies_1;
public:
    Cpu(int v){
        index = new int;
        work_jiffies_0 = 0;
        work_jiffies_1 = 0;
        total_jiffies_0 = 0;
        total_jiffies_1 = 0;
        *index = v;
        }
    
    int get_used(){
        int percentage, i=0;
        work_jiffies_0 = work_jiffies_1;
        total_jiffies_0 = total_jiffies_1;
        vector<string> val;
        string *line = new string;
        ifstream *input = new ifstream("/proc/stat");
        if (*index<1)
            return -1;
        getline(*input, *line);
        while(i < index && line->substr(0, 3) == "cpu"){
            getline(*line, *input);
            ++i;
            }
        val = split(line, ' ');
        val.erase(val.at(0));
        i=0;
        while(i<3){
            work_jiffies_1+=stoi(val.at(i));
            ++i;
            }
        total_jiffies_1+=work_jiffies_1;
        while(i<val.size()){
            total_jiffies_1+=stoi(val.at(i));
            }
         percentage =   (int)(
        ((float)(work_jiffies_1 - work_jiffies_0) /
        (float)(total_jiffies_1 - total_jiffies_0))
        * 100)
        return percentage;
        }
    };