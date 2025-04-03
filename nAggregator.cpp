#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>

using namespace std;

int main(int argc, char* argv[]) {
    if (argc < 3) {
        cerr << "Please specify the data file and the output file." << endl;
        exit(EXIT_FAILURE);
    }

    const char* dataFile = argv[1];
    const char* outFile = argv[2];

    ifstream data(dataFile);
    ofstream out(outFile);

    if (!data.is_open() || !out.is_open()) {
        cerr << "Error opening files." << endl;
        exit(EXIT_FAILURE);
    }

    string dataLine;
    while (getline(data, dataLine)) {
        istringstream lineStream(dataLine);
        int roomNumber;
        lineStream >> roomNumber; // Extract the room number

        string pair;
        double downloadSum = 0.0, uploadSum = 0.0;
        int count = 0;

        while (getline(lineStream, pair, ',')) {
            istringstream pairStream(pair);
            double download, upload;
            pairStream >> download >> upload;

            downloadSum += download;
            uploadSum += upload;
            count++;
        }

        if (count > 0) {
            double avgDownload = downloadSum / count;
            double avgUpload = uploadSum / count;
            out << "Room: " << roomNumber
                << ", Average Download: " << avgDownload
                << ", Average Upload: " << avgUpload << endl;
        }
    }

    data.close();
    out.close();

    return 0;
}       