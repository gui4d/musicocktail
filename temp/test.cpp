#include <string>

#include<gtkmm/main.h>
#include<gtkmm/window.h>
#include<gtkmm/button.h>
#include<gtkmm/stock.h>
#include<gtkmm/alignment.h>
#include<gtkmm/box.h>


int main(int argc, char* argv[]) {

    Gtk::Main app(argc, argv);
    Gtk::Window mainWindow;
    mainWindow.set_default_size(300,400);
    mainWindow.set_border_width(10);

    Gtk::Alignment quitBox(Gtk::ALIGN_END, Gtk::ALIGN_END,0,0);
    mainWindow.add(quitBox);

    Gtk::Button quitButton(Gtk::Stock::QUIT);
    quitButton.signal_clicked().connect(sigc::ptr_fun(&Gtk::Main::quit));
    quitBox.add(quitButton);

    mainWindow.show_all();    
    Gtk::Main::run(mainWindow);

    return 0;

}

