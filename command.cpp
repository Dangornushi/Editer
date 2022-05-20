#include "Main.hpp"

std::string Command::runCommand(void) {
    std::string line = "";
    if (inputCommand == "q") {
        system("clear");
        std::exit(0);
    }
    if (inputCommand == "w") {
        std::ofstream output_file(openFileName, std::ios::out);

        for (auto data : fileData) {
            output_file << data  << std::endl;
        }

        output_file.close();

    }
    if (inputCommand[0] == 'o') {
        lineNum = 0;
        inputCommand.erase(0, 2);
        openFileName = inputCommand;
        std::ifstream input_file(openFileName, std::ios::in);
        inputCommand = "";
        if (!input_file) {
            return "Could not open the file -> '" +openFileName + "'";
        }
        else {
            while (getline(input_file, line)) {
                fileData.push_back(line);
                lineNum++;
            }
            if (lineNum == 0) {
                lineNum++;
                fileData.push_back("\n");
            }
            lineNum--;
            cY = 0;
            cX = fileData[cY].length();
            input_file.close();
        }

    }
    return inputCommand;
}
