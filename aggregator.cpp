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
        const char* roomsFile = argv[1];
        const char* dataFile = argv[2];
        const char* outFile = argv[3];
        ifstream rooms(roomsFile);
        ifstream data(dataFile);
        ofstream out(outFile);

        if (!rooms.is_open() || !data.is_open() || !out.is_open())
        {
            cerr << "Error opening files." << endl;
            exit(EXIT_FAILURE);
        }
        
        string roomsLine, dataLine;
        while (getline(rooms, roomsLine) && getline(data, dataLine))
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

            out << "Room: " << roomsLine << ", "
                << "Average Download: " << avgDownload << ", "
                << "Average Upload: " << avgUpload << endl;
        }
        rooms.close();
        data.close();
        out.close();

    }