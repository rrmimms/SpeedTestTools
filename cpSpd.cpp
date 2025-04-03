#include <iostream>
#include <stdexcept>
#include <string>
#include <stdio.h>

using namespace std;

string exec(const string &cmd)
{
    char buffer[128];
    string result = "";
    FILE *pipe = popen(cmd.c_str(), "r");
    if (!pipe)
    {
        throw runtime_error("popen() failed!");
    }
    while (fgets(buffer, sizeof(buffer), pipe) != nullptr)
    {
        result += buffer;
    }
    int status = pclose(pipe);
    if (status == -1)
    {
        throw runtime_error("pclose() failed!");
    }
    return result;
}

int main()
{
    string command = "cd ~/SpeedTest; ./SpeedTest --download --output text;./SpeedTest --upload --output text;";

    FILE *file = fopen("/home/robert/CPPSpeedTest/newResTests", "a");
    if (file == nullptr)
    {
        throw runtime_error("fopen() failed!");
    }

    
    for (int i = 0; i < 5; i++)
    {
        printf("Running Test # %d\n", i + 1);
        string output = exec(command);
        size_t downloadPos = output.find("DOWNLOAD_SPEED=");
        size_t uploadPos = output.find("UPLOAD_SPEED=");
        if (downloadPos != string::npos && uploadPos != string::npos)
        {
            string downloadSpeed = output.substr(downloadPos, output.find("\n", downloadPos) - downloadPos);
            string uploadSpeed = output.substr(uploadPos, output.find("\n", uploadPos) - uploadPos);
            fprintf(file, "Download: %s Upload: %s,", downloadSpeed.c_str(), uploadSpeed.c_str());
            fprintf(file, "\n");
        }
    }
    fprintf(file, "\n\n\n");

    fclose(file);
    return 0;
}
