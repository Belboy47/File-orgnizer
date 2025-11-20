#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <vector>
#include <map>
using namespace std;

int main()
{
    int number = 1;
    char dot = '.';
    map<string, vector<string>> filesByExtension{};

    cout << "Type your file Directory: ";
    string userPath{};
    getline(cin, userPath);

    for (auto fileEntry : filesystem::directory_iterator(userPath))
    {
        if (fileEntry.path().extension() != "")
        {
            filesByExtension[fileEntry.path().extension().string()].push_back(fileEntry.path().stem().string());
        }
    }

    for (auto &extensionEntry : filesByExtension)
    {
        number = 1;
        string ext = extensionEntry.first;
        string extensionDirName = extensionEntry.first;

        extensionDirName = extensionDirName.erase(extensionDirName.find(dot), 1);

        if (filesystem::create_directory(extensionDirName))
        {
            cout << "Directory Created Successfully.";
        }
        else
        {
            cout << "Directory existed.";
        }

        for (string fileStem : extensionEntry.second)
        {
            filesystem::path sourcePath = userPath, destinationPath = userPath;
            sourcePath /= fileStem;
            sourcePath += ext;
            destinationPath /= extensionDirName;
            destinationPath /= fileStem;

            if (filesystem::exists(destinationPath.string() + ext))
            {
                while (filesystem::exists(destinationPath.string() + " (" + to_string(number) + ")" + ext))
                {
                    number++;
                }
                filesystem::copy_file(sourcePath, destinationPath.string() + " (" + to_string(number) + ")" + ext);
                cout << "Files copied with a change.";
            }
            else
            {
                filesystem::copy_file(sourcePath, destinationPath.string() + ext);
            }
        }
        cout << '\n';
    }
}