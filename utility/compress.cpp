#include "defs.h"

namespace NHuffmanUtil {

    void Compress(char *InFile, char *OutFile) {
        std::ifstream fin = NFileUtils::OpenInputFile(InFile);
        std::ofstream fout = NFileUtils::OpenOutputFile(OutFile);

        uchar RBUF[READ_BUFFER_SIZE];
        TFrequencyCounter fc;

        while (fin) {
            fin.read((char *) RBUF, sizeof(RBUF));
            fc.Update(RBUF, fin.gcount());
        }
        // put fin to start of file
        fin.clear();
        fin.seekg(0, std::ios::beg);
    }

}