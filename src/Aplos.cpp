#include <windows.h>
#include <cstdio>
#include <tchar.h>
#include <atlstr.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <ctime>
#include <vector>
#include <string>
#include <strsafe.h>
#include <cstdlib>
#include <filesystem>
#include "CLI11.hpp"

#define RPATH TEXT("RADAMSA_PATH")
#define BUFSIZE 256

using namespace std;
namespace fs = std::filesystem;

int TIMEOUT = 1000;
string originalFolder;

vector<string> listFilesInDirectory(const std::string& directoryPath) {
    vector<string> fileNames;
    const fs::path dest = directoryPath;
    for (const auto& entry : fs::directory_iterator(directoryPath)) {
        fileNames.push_back(entry.path().filename().string());
    }
    return fileNames;
}

string removeExtension(const string& filename) {
    size_t dotPos = filename.rfind('.');
    if (dotPos == string::npos) {
        return filename;
    }
    return filename.substr(0, dotPos);
}


BOOL mutateInputs(const string& filename, const string& mut, const string& inputFolder, const string& outputFolder, string ext)
{ 
    string nfilename = removeExtension(filename);
    string outputFileName = outputFolder + "\\" + nfilename + "_id=" + mut + "." + ext;
    STARTUPINFOA si;
    PROCESS_INFORMATION pi;
    DEBUG_EVENT debug_event;
    string args = "radamsa.exe " + inputFolder + "\\" + filename + " -m " + mut + " -o " + outputFileName;
    LPSTR cmd = (LPSTR)args.c_str();

    ZeroMemory(&si, sizeof(si));
    ZeroMemory(&pi, sizeof(pi));
    si.cb = sizeof(si);

    if (!CreateProcessA(
        nullptr,           // Target app
        cmd,                 // Command line
        nullptr,           // Process handle not inheritable
        nullptr,            // Thread handle not inheritable
        FALSE,                // Set handle inheritance to FALSE
        0,                   // No creation flag
        nullptr,               // Use parent's environment block
        nullptr,            // Use parent's starting directory
        &si,                    // Pointer to STARTUPINFO structure
        &pi)              // Pointer to PROCESS_INFORMATION structure
        )
    {
        printf("CreateProcess failed GLE=(%lu).\n", GetLastError());
        return 1;
    }

    // Wait until child process exits.
    WaitForSingleObject(pi.hProcess, INFINITE);

    // Close process and thread handles
    TerminateProcess(pi.hProcess, 0);
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

}

void reportCrash(const string& exceptionMessage, DWORD exceptionCode, const string& inputFile)
{
    string crashFolder = originalFolder + "crashes";
    if (!fs::exists(crashFolder)) 
    {
        fs::create_directory(crashFolder);
    }
    string filename = crashFolder + "\\" + "crashes_log" + ".txt";
    ofstream outfile(filename, ios::app); 
    outfile << exceptionMessage << hex << exceptionCode << "with file: " << inputFile << endl;
    outfile.close();

    fs::path source = inputFile;
    fs::path dest = crashFolder + inputFile;
    fs::copy(source, dest);

}

DWORD ProcessDebugEvent(DEBUG_EVENT* debugEvent, const string& inputFile)
{
    if (debugEvent->dwDebugEventCode == EXCEPTION_DEBUG_EVENT)
    {

        EXCEPTION_RECORD* exceptionRecord = &debugEvent->u.Exception.ExceptionRecord;
        DWORD exceptionCode = exceptionRecord->ExceptionCode;

        switch (exceptionCode)
        {
        case EXCEPTION_BREAKPOINT:
            break;
        case EXCEPTION_ACCESS_VIOLATION:
            reportCrash("Critical exception: Access Violation (0x", exceptionCode, inputFile);
            break;

        case EXCEPTION_ARRAY_BOUNDS_EXCEEDED:
            reportCrash("Critical exception: Array Bounds Exceeded (0x", exceptionCode, inputFile);
            break;

        case EXCEPTION_FLT_DENORMAL_OPERAND:
            reportCrash("Critical exception: Invalid floating-point operation (denormal operand) (0x", exceptionCode,
                        inputFile);
            break;

        case EXCEPTION_FLT_DIVIDE_BY_ZERO:
            reportCrash("Critical exception: Floating-point division by zero (0x", exceptionCode, inputFile);
            break;

        case EXCEPTION_FLT_OVERFLOW:
            reportCrash("Critical exception: Floating-point overflow (0x", exceptionCode, inputFile);
            break;

        case EXCEPTION_FLT_STACK_CHECK:
            reportCrash("Critical exception: Hardware floating-point stack overflow (0x", exceptionCode, inputFile);
            break;

        case EXCEPTION_FLT_UNDERFLOW:
            reportCrash("Critical exception: Floating-point underflow (0x", exceptionCode, inputFile);
            break;

        case EXCEPTION_ILLEGAL_INSTRUCTION:
            reportCrash("Critical exception: Illegal instruction encountered (0x", exceptionCode, inputFile);
            break;

        case EXCEPTION_IN_PAGE_ERROR:
            reportCrash("Critical exception: Page fault (0x", exceptionCode, inputFile);
            break;

        case EXCEPTION_INT_DIVIDE_BY_ZERO:
            reportCrash("Critical exception: Integer division by zero (0x", exceptionCode, inputFile);
            break;

        case EXCEPTION_INT_OVERFLOW:
            reportCrash("Critical exception: Integer overflow (0x", exceptionCode, inputFile);
            break;

        case EXCEPTION_STACK_OVERFLOW:
            reportCrash("Critical exception: Stack overflow (0x", exceptionCode, inputFile);
            break;
       
        default:
            break;
        }
        return exceptionCode;
    }
}

BOOL runTargetProcess(const string& targetApp, const string& inputFile) 
{ 
    STARTUPINFOA si;
    PROCESS_INFORMATION pi;
    DEBUG_EVENT debug_event;
    const string& arg1 = targetApp;
    string arg2 = " ";
    const string& arg3 = inputFile;
    string args = arg1 + arg2 + arg3;
    auto cmd = (LPSTR)args.c_str();

    ZeroMemory(&si, sizeof(si));
    ZeroMemory(&pi, sizeof(pi));
    si.cb = sizeof(si);

    if (!CreateProcessA(
        nullptr,   // NULL
        cmd,        // Command line
        nullptr,           // Process handle not inheritable
        nullptr,           // Thread handle not inheritable
        TRUE,          // Set handle inheritance to FALSE
        DEBUG_ONLY_THIS_PROCESS, // Debug only this process flag
        nullptr,           // Use parent's environment block
        nullptr,           // Use parent's starting directory
        &si,            // Pointer to STARTUPINFO structure
        &pi)           // Pointer to PROCESS_INFORMATION structure
        )
    {
        printf("CreateProcess failed GLE=(%lu).\n", GetLastError());
        return 1;
    }

    while (WaitForDebugEvent(&debug_event, TIMEOUT))
    {
        // Processing the debug events
        DWORD exceptionCode = ProcessDebugEvent(&debug_event, inputFile);  
        ContinueDebugEvent(debug_event.dwProcessId, debug_event.dwThreadId, DBG_CONTINUE);
    }

    // Close process and thread handles
    TerminateProcess(pi.hProcess, 0);
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

}

int _tmain(int argc, char *argv[])
{
    // Declaring mutation arguments list
    vector<string> mutationArguments = {"ab", "bd", "bf", "bi", "br", "bp", "bei", "bed", "ber", "sr", "sd", "ld", "lds", "lr2",
                                        "li", "lr", "ls", "lp", "lis", "lrs", "td", "tr2", "ts1", "ts2", "tr", "uw", "ui", "num", "xp", "ft", "fn",
                                        "fo"};
    
    // Command line interface logic
    CLI::App aplos{"Aplos is a simple fuzzer."};
    argv = aplos.ensure_utf8(argv);

    string targetApp, inputs, ext;
    aplos.add_option("-t, --target", targetApp, "The target application you want to fuzz.")
        ->required()
        ->check(CLI::ExistingFile);

    aplos.add_option("-i, --input", inputs, "The input folder containing initial testcases.")
        -> required()
        -> check(CLI::ExistingDirectory);

    aplos.add_option("-e, --extension", ext, "The extension used to generate testcases.")
        ->required();

    aplos.add_option("-D, --delay", TIMEOUT, "The timeout delay in ms before closing target app.");
    CLI11_PARSE(aplos, argc, argv);
    
    // Create timestamp for the initial output folder
    time_t now = time(nullptr);
    struct tm formattedTime{};
    localtime_s(&formattedTime, &now);
    stringstream timestampStream;
    timestampStream << setw(2) << setfill('0') << formattedTime.tm_mday << "_"
        << setw(2) << setfill('0') << formattedTime.tm_hour << "_"
        << setw(2) << setfill('0') << formattedTime.tm_min;
    string timestamp = timestampStream.str();
    string outputFolderName = "output_" + timestamp;
    fs::create_directory(outputFolderName);

    // Create and initialize file list
    vector<string> files, mutatedFiles;
    string outputFolder, inputFolder;
    originalFolder = inputs;

// Main fuzzing logic loop
for (int generation = 1;; ++generation)
{
    // Check for input folder logic
    cout << "Mutating corpus to create testcases generation: " << generation << endl;
    if (generation == 1)
    {
        inputFolder = inputs;
    }
    else
    {
        inputFolder = outputFolder;
        
        // Delete input files from previous generations if applicable
        if (generation > 3)
        {
            string prevGenerationFolder = outputFolderName + "\\" + "generation_" + to_string(generation - 3);
            fs::remove_all(prevGenerationFolder);
            cout << "Deleted input files from generation " << generation - 3 << endl;
        }
    }

    // Listing previous generation before mutation
    files = listFilesInDirectory(inputFolder);

    // Core logic
    outputFolder = outputFolderName + "\\" + "generation_" + to_string(generation);
    fs::create_directory(outputFolder);

    // Mutating each file with every mutation
    for (const string& file : files)
    {
        for (const string& mut : mutationArguments)
        {
            cout << "Mutating file: " << file << " with mutation " << mut << endl;
            mutateInputs(file, mut, inputFolder, outputFolder, ext);
        }
    }

    // Listing mutated file then running against target app
    mutatedFiles = listFilesInDirectory(outputFolder);
    for (const string& file : mutatedFiles)
    {
        cout << "Running target app with file: " << file << endl;
        string input = outputFolder + "\\" + file;
        runTargetProcess(targetApp, input);
    }
}

    return 0;
}
