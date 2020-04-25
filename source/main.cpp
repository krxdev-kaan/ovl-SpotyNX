#include <tesla.hpp>
#include <string>
#include <vector>
#include <iostream>
#include <stdio.h>
#include <dirent.h>
#include <switch.h>

using namespace std;

/*vector<string> musics = vector<string>();
u64 playid = 0;

void initMusics(void) 
{
    musics.clear();

    DIR* dir = opendir("sdmc:/spoty-musics/");
    struct dirent* ent;
    if (dir != NULL) 
    {
        while ((ent = readdir(dir)))
        {
            musics.push_back(ent->d_name);
        }
        closedir(dir);
    }
}*/

class GuiMain : public tsl::Gui {
public:
    GuiMain() { }
    ~GuiMain() { }

    virtual tsl::Element* createUI() {
        auto *rootFrame = new tsl::element::Frame();

        auto *header = new tsl::element::CustomDrawer(0, 0, 100, FB_WIDTH, [](u16 x, u16 y, tsl::Screen *screen) {
            screen->drawString("Spoty-NX", false, 20, 50, 30, tsl::a(0xFFFF));
        });

        auto list = new tsl::element::List();

        auto pausePlay = new tsl::element::ListItem("Pause/Play");

        pausePlay->setClickListener([](s64 keys) {
            if (keys & KEY_A == KEY_A) 
            {
                //Implement IPC Connection
                return true;
            }

            return false;
        });

        auto skip = new tsl::element::ListItem("Skip Song");

        skip->setClickListener([](s64 keys) {
            if (keys & KEY_A == KEY_A) 
            {
                //Implement IPC Connection
                return true;
            }

            return false;
        });

        auto prev = new tsl::element::ListItem("Previous Song");

        prev->setClickListener([](s64 keys) {
            if (keys & KEY_A == KEY_A) 
            {
                //Implement IPC Connection
                return true;
            }

            return false;
        });

        list->addItem(pausePlay);
        list->addItem(skip);
        list->addItem(prev);

        rootFrame->addElement(header);
        rootFrame->addElement(list);

        return rootFrame;
    }

    virtual void update() 
    { 

    }

    // virtual void onDestroy() { }
    // virtual void preDraw(tsl::Screen *screen) { }
    // virtual void postDraw(tsl::Screen *screen) { }
};


class TemplateOverlay : public tsl::Overlay {
public:
    TemplateOverlay() { }
    ~TemplateOverlay() { }
    
    tsl::Gui* onSetup() 
    { 
        svcSleepThread(5e+8L);

        Result rc;
        rc = smInitialize();
        rc = hidInitialize();
        rc = hidsysInitialize();
        rc = timeInitialize();
        rc = fsInitialize();
        rc = fsdevMountSdmc();

        return new GuiMain(); 
    }

    //virtual void onOverlayLoad(tsl::Gui *gui) { }
    //virtual void onOverlayShow(tsl::Gui *gui) { }
    //virtual void onOverlayHide(tsl::Gui *gui) { }
    
    virtual void onDestroy() 
    { 
        fsdevUnmountAll();
        fsExit();
        timeExit();
        hidExit();
    	hidsysExit();
        smExit();
        socketExit();
    }
};

tsl::Overlay *overlayLoad() 
{
    return new TemplateOverlay();
}