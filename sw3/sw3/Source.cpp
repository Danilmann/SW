#include <iostream>;
#include <fstream>;
#include <iomanip>;
#include <sstream>;
using namespace std;

long GetFileSize(string filename);

int main() {
    int countLine = 0;
    string line;
    string path = "sw3.txt";
    ifstream file;
    file.open(path);
    if (!file.is_open()) {
        cout << "Error" << endl;
    }
    struct TrpoStudent {
        string studentName;
        int trpoMark;
        double averagemarkLabs;
        int rating;
    };
    while (getline(file, line)) {
        ++countLine;
    }
    file.clear();
    file.seekg(0, ios_base::beg);
    TrpoStudent* student = new TrpoStudent[countLine];

    int i = 0;
    while (!file.eof()) {
        file >> student[i].studentName
            >> student[i].trpoMark
            >> student[i].averagemarkLabs
            >> student[i].rating;
        i++;
    }
    file.close();

    ofstream out;
    out.open(path, ofstream::app);
    if (!out.is_open()) {
        cout << "Error" << endl;
    }
    for (i = 0; i < countLine; i++) {
        out << endl
            << student[i].studentName
            << " "
            << student[i].trpoMark
            << " "
            << student[i].averagemarkLabs
            << " "
            << student[i].rating;
    }
    long fileSize;
    fileSize = GetFileSize(path);
    cout << "file size in bites: " << fileSize << endl;
    /*sort by rating*/
    for (int i = 0; i < countLine; i++) {
        for (int j = 0; j < countLine; j++) {
            if (student[j].rating > student[i].rating) {
                swap(student[i].rating, student[j].rating);
                swap(student[i].studentName, student[j].studentName);
                swap(student[i].trpoMark, student[j].trpoMark);
                swap(student[i].averagemarkLabs, student[j].averagemarkLabs);
            }
        }
    }
    for (i = 0; i < countLine; i++) {
        out << endl << student[i].studentName << " " << student[i].trpoMark << " " << student[i].averagemarkLabs << " " << student[i].rating;
    }
    out.close();
    delete[] student;
    system("pause");
    return 0;
}

long GetFileSize(string filename) {
    struct stat stat_buf;
    int rc = stat(filename.c_str(), &stat_buf);
    return rc == 0 ? stat_buf.st_size : -1;
}