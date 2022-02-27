#include <iostream>
#include <bits/stdc++.h>
#include "include/printer.h"

/*! \class Encryptor
 *  \brief This is a Encryptor class.
 *
 * Use to encrypt string with virtual table
 */
class Encryptor
{
private:
    int _k1[4] = {4, 1, 3, 2};
    std::string _encryptedData;


    static bool isK2Invalid(int *k2, int k2size)
    {
        int copyK2[k2size];
        for (int i = 0; i < k2size; i++)
        {
            copyK2[i] = *(k2 + i);
        }

        std::sort(copyK2, copyK2 + k2size);

        for (int i = 0; i < k2size; i++)
        {
            if (copyK2[i] != (i + 1))
            {
                std::cout << "Incorrect second key, please try again" << std::endl;
                return true;
            }
        }
        return false;
    }

    static void setK2(int *k2, int k2size)
    {
        std::string length = std::to_string(k2size);
        std::cout << "enter k2 with " + length + " length:" << std::endl;
        for (int i = 0; i < k2size; i++)
        {
            std::cin >> k2[i];
        }
    }

    int** setTable(std::string& data, int k2size)
    {
        int k1size = (sizeof(_k1)/sizeof(_k1[0]));
        int **table = new int* [k1size];
        for (int i = 0; i < k1size; i++)
        {
            table[i] = new int [k2size];
        }

        int stringIterator = 0;
        for (int i = 0; i < k1size; i++)
        {
            int currentRow = _k1[i];
            for (int j = 0; j<k2size; j++)
            {
                table[currentRow - 1][j] = data[stringIterator];
                stringIterator++;
            }
        }

        return table;
    }

    void getEncrypted(std::string& data, int *k2, int k2size, int **table)
    {
        int k1size = (sizeof(_k1)/sizeof(_k1[0]));
        std::string result = "";
        for (int i = 0; i < k2size; i++)
        {
            int currentColumn = k2[i];
            for (int j = 0; j < k1size; j++)
            {
                result += table[j][currentColumn - 1];
            }
        }
        _encryptedData = result;
    }

    void encrypt(std::string& data, int *k2)
    {
        std::string inputData = data;
        int dataSize = inputData.size();
        int k1size = (sizeof(_k1)/sizeof(_k1[0]));

        int spaceCount = dataSize % k1size;

        for (int i = 0; i < spaceCount; i++)
        {
            data += " ";
        }

        int k2size = data.size()/k1size;

        k2 = new int[k2size];

        do
        {
            setK2(k2, k2size);
        } while (isK2Invalid(k2, k2size));

        int** table = setTable(data, k2size);

        getEncrypted(data, k2, k2size, table);
    }

public:
    explicit Encryptor(std::string& data, int *k2) {
        encrypt(data, k2);
    };

    std::string getValue()
    {
        return _encryptedData;
    }
};

/*! \class Decryptor
 *  \brief This is a Decryptor class.
 *
 * Use to decrypt string with virtual table
 */
class Decryptor
{
private:
    int _k1[4] = {4, 1, 3, 2};
    int *_k2;
    std::string _data;
    std::string _result;


    int** getTable(int k1size, int k2size)
    {
        int **table = new int* [k1size];
        for (int i = 0; i < k1size; i++)
        {
            table[i] = new int [k2size];
        }

        int stringIter = 0;
        for (int j = 0; j < k2size; j++)
        {
            int curColumn = _k2[j];
            for (int i = 0; i<k1size; i++)
            {
                table[i][curColumn-1] = _data[stringIter];
                stringIter++;
            }
        }

        return table;
    }

    bool isK2Invalid(int *k2, int k2size)
    {
        int copyk2[k2size];
        for (int i = 0; i < k2size; i++)
        {
            copyk2[i] = *(k2+i);
        }

        std::sort(copyk2, copyk2 + k2size);

        for (int i = 0; i < k2size; i++)
        {
            if (copyk2[i] != (i+1))
            {
                std::cout << "Incorrect second key, please try again" << std::endl;
                return true;
            }
        }
        return false;
    }

    void setK2(int size)
    {
        _k2 = new int[size];

        std::string length = std::to_string(size);
        std::cout << "enter k2 with " + length + " size:" << std::endl;
        for (int i = 0; i < size; i++)
        {
            std::cin >> _k2[i];
        }
    }

    void descrypt()
    {
        int size = _data.size();
        int k1size = sizeof(_k1)/sizeof(_k1[0]);
        int k2size = size/k1size;

        do
        {
            setK2(k2size);
        } while (isK2Invalid(_k2, k2size));


        int **table = getTable(k1size, k2size);


        _result ="";
        for (int i = 0; i<k1size; i++)
        {
            int currow = _k1[i];
            for (int j = 0; j < k2size; j++)
            {
                char curCode = (char )table[currow-1][j];
                _result += curCode;
            }
        }
    }
public:
    explicit Decryptor(std::string data, int *k2) : _data(std::move(data)), _k2(k2) {
        descrypt();
    };

    std::string getValue()
    {
        return _result;
    }
};


/*! \fn getAbsoluteFilePath(const std::string& path)
 *  \brief A function to get absolute path
 *  \param path a string.
 *  \return absolute file path
 */
std::string getAbsoluteFilePath(const std::string& path)
{
    if (path[1] == ':')
    {
        return path;
    }
    return (std::filesystem::current_path().generic_string() + "\\" + path);
}


/*! \fn getFileByPathAsString(std::string path)
 *  \brief A function to get file as string
 *  \param path a result of getAbsoluteFilePath function.
 *  \return string with content of file
 */
std::string getFileByPathAsString(std::string path)
{
    std::ifstream fileIn(getAbsoluteFilePath(path), std::ios::in);
    if (!fileIn) {
        std::cout << path + " not found" << std::endl;
        exit(1);
    } else {
        std::cout << path + " opened" << std::endl;
    }


    std::string data;
    if(fileIn) {
        std::ostringstream ss;
        ss << fileIn.rdbuf();
        data = ss.str();
    }
    fileIn.close();

    return data;
}


/*! \fn writeStringToFileAtPath(std::string path, std::string message)
 *  \brief A function to write string in file
 *  \param path a result of getAbsoluteFilePath function.
 *  \param message a string to save
 */
void writeStringToFileAtPath(std::string path, std::string message)
{
    std::ofstream fileOut(getAbsoluteFilePath(path)); //i think this must create file, but check it anyway
    if (!fileOut) {
        std::cout << path + " not found" << std::endl;
        exit(1);
    } else {
        std::cout << path + " opened" << std::endl;
    }
    fileOut << message;
    fileOut.close();
}



int main() {

    Printer printer;
    std::string beforeOpen = "Enter file path to encrypt: ";

    std::string inputPath;
    printer.print(beforeOpen, true);
    //std::cout << "Enter file path to encrypt: " << std::endl;
    getline(std::cin, inputPath);

    std::string encryptedMessage = std::move(getFileByPathAsString(std::move(inputPath)));

    int *k2;

    Encryptor encryptor = Encryptor(encryptedMessage, k2);
    std::string cryptedtext = encryptor.getValue();

    std::string beforeSave = "Enter file path to save: ";

    std::string outputpath;
    std::cin.ignore(10000,'\n');
    printer.print(beforeSave, true);
    //std::cout << "Enter file path to save: " << std::endl;
    getline(std::cin, outputpath);

    writeStringToFileAtPath(std::move(outputpath), std::move(cryptedtext));

    std::string inputPathToDecrypt;

    std::cin.ignore(10000,'\n');
    beforeOpen =  "Enter file path to descrypt: ";
    printer.print(beforeOpen, true);
    //std::cout << "Enter file path to descrypt: " << std::endl;
    getline(std::cin, inputPathToDecrypt);

    std::string decryptedMessage;
    decryptedMessage = std::move(getFileByPathAsString(std::move(inputPathToDecrypt)));


    Decryptor decryptor = Decryptor(decryptedMessage, k2);

    std::string result = decryptor.getValue();

    std::string outputpathdesc;
    std::cin.ignore(10000,'\n');
    printer.print(message, true);
    //std::cout << "Enter file path to save: " << std::endl;
    getline(std::cin, outputpathdesc);

    writeStringToFileAtPath(std::move(outputpathdesc), std::move(result));
    return 0;
}
