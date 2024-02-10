#include <iostream>
#include "lexer.cpp"

int main(int, char**)
{

    while (true)
    {
        std::cout << ">";
        std::string line;
        getline(std::cin, line);

        if (line.empty())
        {
            return -1;
        }

        Lexer l = Lexer(line);

        while (true)
        {
            SyntaxToken token = l.NextToken();
            if (token.getKind() == SyntaxKind::EOLToken)
            {
                break;
            }
            std::cout << token.getKind() << " : " << token.getText() << '\n';
        }
    }

    return 0;
}
