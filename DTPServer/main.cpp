// main.cpp

#include "serverHandler.cpp"
#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/screen.hpp>

int main(void) {
    using namespace ftxui;

    //define document
    Element document =
    hbox({
      text("left")   | border,
      text("middle") | border | flex,
      text("right")  | border,
    });
 
    auto screen = Screen::Create(
    Dimension::Full(),       // Width
    Dimension::Fit(document) // Height
    );
    Render(screen, document);
    screen.Print();
 
    return EXIT_SUCCESS;

    runServer();
    return 0;
}