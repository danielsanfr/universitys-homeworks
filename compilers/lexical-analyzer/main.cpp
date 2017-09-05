#include <iostream>

#include "LexicalAnalyzer.hpp"
#include "FileCodeReader.hpp"

using namespace std;

int main()
{
    LexicalAnalyzer la = LexicalAnalyzer(new FileCodeReader("../LexicalAnalyzer/samples/fibonacci.san"));
    while (la.hasNextToken()) {
        cout << la.nextToken().toString() << endl;
    }
    return 0;
}
