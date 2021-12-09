#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cstdio>

using namespace std;

bool resolveSwitch(char* swh, bool* requestedDummyName){
    bool found = false;
    bool ifContinue = true;

    /*
        Current arguments list:
        help h - Help text
        output o - File output
    */
	if(strcmp(swh, "-h") == 0 || strcmp(swh, "--help") == 0){
		cout << "QuickDummy CLI - Creates empty dummy files of a specified size" << endl
		<< "Usage: [command] [ARGUMENTS or BYTES]" << endl
		<< "Example: \"[command] 1024\" will create a 1KB dummy file in the current directory" << endl
		<< "Switches:" << endl
		<< "\t-o, --output: Desired output filename" << endl
		<< "\t\tExample: \"[command] 1024 -o yeah\" will create a 1KB dummy file called \"yeah\"" << endl;
		//TODO update help text for future features
		ifContinue = false;
		found = true;
	}else
    if(strcmp(swh, "-o") == 0 || strcmp(swh, "--output") == 0){
        *requestedDummyName = true;
        found = true;
	}

	if(!found){
		cout << swh << " is not a valid switch. Use --help or -h for instructions." << endl;
		ifContinue = false;
	}

	return ifContinue;
}


void createDummy(unsigned long long bytes, const char* filename){
	FILE* dummyFile;
	dummyFile = fopen(filename, "w");
	char fill = '\0';
	for(unsigned long long i = 0; i < bytes; i++){
		fwrite(&fill, 1, 1, dummyFile);
	}
	fclose(dummyFile);
}
void createDummy(unsigned long long bytes){
    createDummy(bytes, "./dummy.bin");
}


int main(int argc, char** args){
    bool ifContinue = true;
    bool requestedDummyName = false;
    char* sizeString = NULL;
    char* fileName = NULL;

	if(argc >= 2){
        //arguments handling
        for(int i = 1; i < argc && ifContinue == true; i++){
            if(args[i][0] == '-'){
                ifContinue = resolveSwitch(args[i], &requestedDummyName);

                //If -o is specified
                if(requestedDummyName){
                    i++;
                    if(i < argc && fileName == NULL){
                        fileName = args[i];
                        requestedDummyName = false;
                    }else{
                        ifContinue = false;
                        if(i >= argc)
                            cerr << "No file name has been specified." << endl;
                        else
                            cerr << "Filename can't be specified more than once." << endl;
                    }
                }

            //Consider argument as dummy file size if not a switch or an argument for a switch
            }else{
                if(sizeString == NULL){
                    sizeString = args[i];
                }else{
                    ifContinue = false;
                    cerr << "Bytes can't be specified more than once." << endl;
                }
            }
        }
        if(ifContinue){ //Enters only if arguments have been given correctly
            if(sizeString != NULL){
                char* pNumberEnd;
                unsigned long long bytes = strtoll(sizeString, &pNumberEnd, 10);
                cout << "Creating dummy file of " << bytes << "B long" << endl;
                if(fileName == NULL)
                    createDummy(bytes);
                else
                    createDummy(bytes, fileName);
                cout << "Done executing" << endl;
            }else{
                cerr << "Bytes have not been specified." << endl;
            }

        }

	}else if (argc == 1) cout << "Too few arguments. Use --help or -h for instructions." << endl;
	else cout << "Too many arguments. Use --help or -h for instructions" << endl;

	return 0;
}
