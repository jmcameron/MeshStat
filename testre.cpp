#include <wx/init.h>
#include <wx/regex.h>

int main(int argc, char **argv)
{
    wxInitializer init;
    if ( !init.IsOk() ) {
        puts("Failed to initialize wxWidgets.");
        return 1;
    }

    wxRegEx re("^[-]?[0-9]*\\.?[0-9]+$");
    return re.Matches(argv[1]);
}
