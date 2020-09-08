
#include <iostream>
#include <fstream>
#include <string>
#include <nlohmann/json.hpp>
#include <unordered_map>
#include <ctime>

using namespace std;

using json = nlohmann::json;
using LogData = unordered_map<string, uint32_t>;
using TotalData = unordered_map<uint32_t, LogData>;

TotalData data;

string hours_to_date(const uint32_t raw)
{
    string date;
    time_t now = raw;
    tm *ltm = localtime(&now);

    return to_string(1900 + ltm->tm_year) + "-" + to_string(1 + ltm->tm_mon) + "-" + to_string(ltm->tm_mday);
}

void process_file(const string &filename)
{
    json js;
    ifstream log("../src/" + filename);

    if (!log.is_open())
    {
        cout << "can't open file" << endl;
        return;
    }

    while(true)
    {
        string s;
        getline(log, s);
        if (s.size() > 0)
        {
            js = json::parse(move(s));

            uint32_t key_in_days = js["ts_fact"].get<uint32_t>();
            string key_name = js["fact_name"].get<string>();
            uint32_t count;

            if (data[key_in_days].count(key_name) == 1)
            {
                count = data[key_in_days].at(key_name);
            }  
            else
                count = 0;
                
            for (auto prop : js["props"])
                count += prop.get<int>();
                
            data[key_in_days][key_name] = count;
        }
        else
            break;
    }
}

int main(int argc, char *argv[])
{
    for (size_t i(0); i < argc - 1; ++i)
    {
        process_file(argv[i + 1]);
    }

    ofstream result("../src/log.txt");
    json res;
    
    for (auto it = data.begin(); it != data.end(); ++it)
    {
        json obj;
        for (auto it1 = it->second.begin(); it1 != it->second.end(); ++it1)
        {
            json facts;
            facts["1, 2, 3, 4, 5, 6, 7, 8, 9, 10"] = it1->second;
            obj[it1->first] = facts;
        }
        res[hours_to_date(it->first)] = obj;
    }

    result << setw(4) << res << endl; 
    result.close(); 

    return 0;
}