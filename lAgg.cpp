#include <stdio.h>
#include <string>
#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <fstream>

using namespace std;

int main(int argc, char* argv[]){

    if (argc < 4)
    {
        printf("Please specify the rooms file, then the data file and then output file\n");
        exit(EXIT_FAILURE);
    }    
    const char* dataFile = argv[1];
    const char* outFile = argv[2];
    ifstream data(dataFile);
    ofstream out(outFile);

    if (!data.is_open() || !out.is_open())
    {
        cerr << "Error opening files." << endl;
        exit(EXIT_FAILURE);
    }
    
    string dataLine;
    while (getline(data, dataLine))
    {
        istringstream lineStream(dataLine);
        string pair;
        double downloadSum = 0.0, uploadSum = 0.0;
        int count = 0;

        while (std::getline(lineStream, pair, ',')) {
            std::istringstream pairStream(pair);
            double download, upload;
            pairStream >> download >> upload;

            downloadSum += download;
            uploadSum += upload;
            count++;
        }       
        double avgDownload = downloadSum / count;
        double avgUpload = uploadSum / count;

        out << "Room: " << << ", "
            << "Average Download: " << avgDownload << ", "
            << "Average Upload: " << avgUpload << endl;
    }
    data.close();
    out.close();

}                       