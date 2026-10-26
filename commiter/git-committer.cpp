#include <cctype>
#include <cstdlib>
#include <filesystem>
#include <iostream>
#include <string>

namespace fs = std::filesystem;

std::string check_git(fs::path path);

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cout << "add git project path\n";
        return EXIT_FAILURE;
    }

    std::string check = check_git(argv[1]);

    if (!check.empty()) {
        std::cout << check;
        return EXIT_FAILURE;
    }

    while (true) {
        std::string option;
        int choice;
        std::string commit;

        std::cout << "Type of commit?\n"
                  << "1 - feat\n"
                  << "2 - fix\n"
                  << "3 - docs\n"
                  << "4 - style\n"
                  << "5 - refactor\n"
                  << "6 - perf\n"
                  << "7 - test\n"
                  << "8 - build\n"
                  << "9 - ci\n"
                  << "10 - chore\n"
                  << "11 - revert\n"
                  << "Enter type (1-11): ";

        std::getline(std::cin, option);

        if (option.empty()) {
            std::cout << "Option cannot be empty\n";
            continue;
        }

        try {
            choice = std::stoi(option);
        } catch (...) {
            std::cout << option << " is not a valid option\n";
            continue;
        }

        if (choice < 1 || choice > 11) {
            std::cout << option << " is not a valid option\n";
            continue;
        }

        switch (choice) {
            case 1:
                commit = "feat";
                break;
            case 2:
                commit = "fix";
                break;
            case 3:
                commit = "docs";
                break;
            case 4:
                commit = "style";
                break;
            case 5:
                commit = "refactor";
                break;
            case 6:
                commit = "perf";
                break;
            case 7:
                commit = "test";
                break;
            case 8:
                commit = "build";
                break;
            case 9:
                commit = "ci";
                break;
            case 10:
                commit = "chore";
                break;
            case 11:
                commit = "revert";
                break;
        }

        std::cout
            << "\nScope of this commit? (press enter to skip)\n Enter scope: ";
        std::getline(std::cin, option);

        if (!option.empty()) {
            for (char& c : option) {
                c = std::tolower(c);
            }
            commit += '(' + option + ')';
        }
        commit += ": ";

        std::cout << "\nCommit description?\n Enter commit description: ";
        std::getline(std::cin, option);

        if (!option.empty()) {
            option[0] = std::tolower(option[0]);
            if (option.back() == '.') {
                option.pop_back();
            }
        }
        commit += option;

        std::cout << "\nFinal commit message: " << commit << "\n";

        std::cout << "Start over? y/N: ";
        std::getline(std::cin, option);

        for (char& c : option) {
            c = std::tolower(c);
        }

        if (option == "y") {
            continue;
        }

        std::string command = "git commit -m \" + commit + \"";
        std::system(command.c_str());

        std::cout
            << "\nPush to what branch? (press enter to skip)\n Enter branch: ";
        std::string branch;
        std::getline(std::cin, branch);

        if (branch.empty()) {
            return EXIT_SUCCESS;
        }

        std::string push_command = "git push origin " + branch;
        std::system(push_command.c_str());
        return EXIT_SUCCESS;
    }
}

std::string check_git(fs::path path) {
    if (!fs::is_directory(path)) {
        return path.string() + " is not a directory\n";
    }

    fs::path git_folder = path / ".git";
    if (!fs::exists(git_folder)) {
        return "no .git folder\n";
    }

    return "";
}
