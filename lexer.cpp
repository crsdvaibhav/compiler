#include <iostream>

/*
Lexer makes sentences
*/

enum SyntaxKind
{
    NumberToken,
    WhitespaceToken,
    PlusToken,
    MinusToken,
    StarToken,
    SlashToken,
    OpenParanthesesToken,
    ClosedParanthesesToken,
    BadToken,
    EOLToken
};

class SyntaxToken
{

private:
    SyntaxKind Kind;
    int Position;
    std::string Text;

public:
    SyntaxToken(SyntaxKind kind, int position, std::string text)
    {
        Kind = kind;
        Position = position;
        Text = text;
    }

    int getPosition()
    {
        return Position;
    }
    SyntaxKind getKind()
    {
        return Kind;
    }
    std::string getText()
    {
        return Text;
    }
};

class Lexer
{
private:
    std::string _text;
    int _position;
    char Current;

    void Next()
    {
        _position++;
    }

    char getCurrent() // If out of bounds return \0 else the char
    {
        if (_position > _text.length())
        {
            return Current = '\0';
        }
        return Current = _text[_position];
    }

public:
    Lexer(std::string text)
    {
        _text = text;
    }

    SyntaxToken NextToken()
    {
        // <numbers>, <+,-,*,/,()> <whitespace>
        if(_position>=_text.length())
        {
            return SyntaxToken(SyntaxKind::EOLToken, _position, "\0");
        }
        if (isdigit(Current))
        {
            int start = _position;

            while (isdigit(Current))
            {
                Next();
            }
            int length = _position - start;
            std::string text = _text.substr(start, length);

            return SyntaxToken(SyntaxKind::NumberToken, start, text);
        }
        if (isspace(Current))
        {
            int start = _position;

            while (isspace(Current))
            {
                Next();
            }
            int length = _position - start;
            std::string text = _text.substr(start, length);

            return SyntaxToken(SyntaxKind::WhitespaceToken, start, text);
        }
        if (Current == '+')
        {
            return SyntaxToken(SyntaxKind::PlusToken, _position++, "+");
        }
        else if (Current == '-')
        {
            return SyntaxToken(SyntaxKind::MinusToken, _position++, "-");
        }
        else if (Current == '*')
        {
            return SyntaxToken(SyntaxKind::StarToken, _position++, "*");
        }
        else if (Current == '/')
        {
            return SyntaxToken(SyntaxKind::SlashToken, _position++, "/");
        }
        else if (Current == '(')
        {
            return SyntaxToken(SyntaxKind::OpenParanthesesToken, _position++, "(");
        }
        else if (Current == ')')
        {
            return SyntaxToken(SyntaxKind::ClosedParanthesesToken, _position++, ")");
        }

        return SyntaxToken(SyntaxKind::BadToken, _position++, _text.substr(_position-1,1));
    }
};