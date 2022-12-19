// WE POINTED OUT SOURCES WE USED WITH COMMENT LINES.
#include "hashT.h"

int main() {
    hashT stopW(1201);
    std::ifstream stopData;
    stopData.open("stopwordMacOsVersion.txt"); //line separators is differents ,Linux MacOx and windows. It for only macos
    std::string stopWord;
    if (!stopData.is_open())
        std::cerr << "File could not open.\n";
    else
    {
        while (!stopData.eof()) {
            int stopIndex = 0;
            getline(stopData, stopWord);
            char* tmpStopWord = (char*)calloc(30, sizeof(char));
            while (stopIndex < stopWord.length()) {
                tmpStopWord[stopIndex] = stopWord[stopIndex];
                stopIndex++;
            }
            tmpStopWord[stopIndex] = '\0';
            element tempElemStop;
            tempElemStop.word = tmpStopWord;
            tempElemStop.count = 0;
            ft_to_lower(tempElemStop.word);
            stopW.insert(stopW.hashFunction(tempElemStop.word), tempElemStop);
            free(tmpStopWord);
        }
    }
    stopData.close();

    hashT words(180001);
    std::ifstream dataTxt;
    std::string str;
    char* not_alpha = (char*)calloc(43, sizeof(char));
    int ascii = 32; // FIRST 31 ARE WHITESPACES
    int i = 0;
    while (ascii < 127)
    {
        if (!std::isalpha(ascii) && ascii != 39)
        {
            not_alpha[i] = (char)ascii;
            i++;
        }
        ascii++;
    }
    not_alpha[i] = '\0';

    dataTxt.open("PublicationsDataSet.txt");
    int publicationIndex;
    int publicationCount = 0;
    if (!dataTxt.is_open())
        std::cerr << "File could not open.\n";
    else
    {
        while (!dataTxt.eof()) {
            getline(dataTxt, str);
            if (str.empty()) break;
            publicationCount++;
            publicationIndex = 300;
            while (publicationIndex < str.length()) {
                if (str[publicationIndex] == ':') {
                    if (str[publicationIndex + 1] == '{') {
                        publicationIndex = publicationIndex + 2;
                        while (str[publicationIndex] != '}') {
                            publicationIndex++;
                            int tmpIndex = 0;
                            char* tmp_word = (char*)calloc(700, sizeof(char));
                            if (!tmp_word) break;
                            while (str[publicationIndex] != '"') {
                                tmp_word[tmpIndex] = str[publicationIndex];
                                publicationIndex++;
                                tmpIndex++;
                                if (str[publicationIndex] == '"' && str[publicationIndex + 1] != ':')
                                    publicationIndex++;
                            }
                            tmp_word[tmpIndex] = '\0';
                            tmp_word = ft_strtrim(tmp_word, not_alpha);
                            publicationIndex = publicationIndex + 2;
                            char* countIndex = (char*)calloc(5, sizeof(char));
                            if (!countIndex)
                                break;
                            tmpIndex = 0;
                            while (str[publicationIndex] >= '0' && str[publicationIndex] <= '9')
                            {
                                countIndex[tmpIndex] = str[publicationIndex];
                                publicationIndex++;
                                tmpIndex++;
                            }
                            countIndex[tmpIndex] = '\0';
                            if (ft_is_word_valid(tmp_word))
                            {
                                bool isFound = false;
                                element tempElem;
                                tempElem.word = tmp_word;
                                tempElem.count = ft_atoi(countIndex);
                                ft_to_lower(tempElem.word);
                                stopW.search(stopW.hashFunction(tempElem.word), tempElem, isFound);
                                if (!isFound)
                                    words.insert(words.hashFunction(tempElem.word), tempElem);
                            }
                            free(tmp_word);
                            free(countIndex);
                            publicationIndex++;
                        }
                    }
                    else
                        publicationIndex++;
                }
                else
                    publicationIndex++;
            }
        }
    }
    free(not_alpha);
    words.selection();

    std::cout << "Total Elapsed Time: " << (double)clock() / CLOCKS_PER_SEC << " seconds" << std::endl;

    return 0;
}
